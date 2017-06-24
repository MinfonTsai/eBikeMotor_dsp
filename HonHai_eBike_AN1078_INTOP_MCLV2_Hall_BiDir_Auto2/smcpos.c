/**********************************************************************
* © 2012 Microchip Technology Inc.
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
******************************************************************************/
 /**********************************************************************
 *      Code Description                                               *
 *                                                                     *
 *  This file implements a slide mode observer. This observer is used  *
 *  to estimate rotor position and speed. Rotor position, Theta, is    *
 *  then compensated from phase delays introduced by the filters       *
 *                                                                     *
 **********************************************************************/

#include "general.h"
#include "smcpos.h"
#include "UserParms.h"
#include "Control.h"

extern tuGF uGF;
void SMC_Position_Estimation (SMC *s)
{
	PUSHCORCON();
	CORCONbits.SATA = 1;
	CORCONbits.SATB = 1;
	CORCONbits.ACCSAT = 1;

	CalcEstI();

	CalcIError();

	// Sliding control calculator

	if (_Q15abs(s->IalphaError) < s->MaxSMCError)
	{
		// s->Zalpha = (s->Kslide * s->IalphaError) / s->MaxSMCError
		// If we are in the linear range of the slide mode controller,
		// then correction factor Zalpha will be proportional to the
		// error (Ialpha - EstIalpha) and slide mode gain, Kslide.
		CalcZalpha();
	}
	else if (s->IalphaError > 0)
		s->Zalpha = s->Kslide;
	else
		s->Zalpha = -s->Kslide;

	if (_Q15abs(s->IbetaError) < s->MaxSMCError)
	{
		// s->Zbeta = (s->Kslide * s->IbetaError) / s->MaxSMCError
		// If we are in the linear range of the slide mode controller,
		// then correction factor Zbeta will be proportional to the
		// error (Ibeta - EstIbeta) and slide mode gain, Kslide.
		CalcZbeta();
	}
	else if (s->IbetaError > 0)
		s->Zbeta = s->Kslide;
	else
		s->Zbeta = -s->Kslide;

	// Sliding control filter -> back EMF calculator
	// s->Ealpha = s->Ealpha + s->Kslf * s->Zalpha -
	//						   s->Kslf * s->Ealpha
	// s->Ebeta = s->Ebeta + s->Kslf * s->Zbeta -
	//						 s->Kslf * s->Ebeta
	// s->EalphaFinal = s->EalphaFinal + s->KslfFinal * s->Ealpha
	//								   - s->KslfFinal * s->EalphaFinal
	// s->EbetaFinal = s->EbetaFinal + s->KslfFinal * s->Ebeta
	//								 - s->KslfFinal * s->EbetaFinal
	CalcBEMF();

	// Rotor angle calculator -> Theta = atan(-EalphaFinal,EbetaFinal)

	s->Theta = atan2CORDIC(-s->EalphaFinal,s->EbetaFinal);

	AccumTheta += s->Theta - PrevTheta;
	PrevTheta = s->Theta;
	
	AccumThetaCnt++;
	if (AccumThetaCnt == IRP_PERCALC)
	{
		s->Omega = AccumTheta;
		AccumThetaCnt = 0;
		AccumTheta = 0;
	}
    //                    Q15(Omega) * 60
    // Speed RPMs = -----------------------------
    //               SpeedLoopTime * Motor Poles
    // For example:
    //    Omega = 0.5
    //    SpeedLoopTime = 0.001
    //    Motor Poles (pole pairs * 2) = 10
    // Then:
    //    Speed in RPMs is 3,000 RPMs

	// s->OmegaFltred = s->OmegaFltred + FilterCoeff * s->Omega
	//								   - FilterCoeff * s->OmegaFltred

	CalcOmegaFltred();

	// Adaptive filter coefficients calculation
	// Cutoff frequency is defined as 2*_PI*electrical RPS
	//
	// 		Wc = 2*_PI*Fc.
	// 		Kslf = Tpwm*2*_PI*Fc
	//
	// Fc is the cutoff frequency of our filter. We want the cutoff frequency
	// be the frequency of the drive currents and voltages of the motor, which
	// is the electrical revolutions per second, or eRPS.
	//
	// 		Fc = eRPS = RPM * Pole Pairs / 60
	//
	// Kslf is then calculated based on user parameters as follows:
	// First of all, we have the following equation for RPMS:
	//
	// 		RPM = (Q15(Omega) * 60) / (SpeedLoopTime * Motor Poles)
	//		Let us use: Motor Poles = Pole Pairs * 2
	//		eRPS = RPM * Pole Pairs / 60), or
	//		eRPS = (Q15(Omega) * 60 * Pole Pairs) / (SpeedLoopTime * Pole Pairs * 2 * 60)
	//	Simplifying eRPS
	//		eRPS = Q15(Omega) / (SpeedLoopTime * 2)
	//	Using this equation to calculate Kslf
	//		Kslf = Tpwm*2*_PI*Q15(Omega) / (SpeedLoopTime * 2)
	//	Using diIrpPerCalc = SpeedLoopTime / Tpwm
	//		Kslf = Tpwm*2*Q15(Omega)*_PI / (diIrpPerCalc * Tpwm * 2)
	//	Simplifying:
	//		Kslf = Q15(Omega)*_PI/diIrpPerCalc
	//
	// We use a second filter to get a cleaner signal, with the same coefficient
	//
	// 		Kslf = KslfFinal = Q15(Omega)*_PI/diIrpPerCalc
	//
	// What this allows us at the end is a fixed phase delay for theta compensation
	// in all speed range, since cutoff frequency is changing as the motor speeds up.
	// 
	// Phase delay: Since cutoff frequency is the same as the input frequency, we can
	// define phase delay as being constant of -45 DEG per filter. This is because
	// the equation to calculate phase shift of this low pass filter is 
	// arctan(Fin/Fc), and Fin/Fc = 1 since they are equal, hence arctan(1) = 45 DEG.
	// A total of -90 DEG after the two filters implemented (Kslf and KslfFinal).
	
	s->Kslf = s->KslfFinal = FracMpy(s->OmegaFltred,Q15(_PI / IRP_PERCALC));
        // For Bi-direction operation
        if(s->Kslf < 0)     
        {
          s->Kslf = - s->Kslf;
          s->KslfFinal = -s->KslfFinal;
        }

	// Since filter coefficients are dynamic, we need to make sure we have a minimum
	// so we define the lowest operation speed as the lowest filter coefficient

	if (s->Kslf < Q15(OMEGA0 * _PI / IRP_PERCALC))
	{
		s->Kslf = Q15(OMEGA0 * _PI / IRP_PERCALC);
		s->KslfFinal = Q15(OMEGA0 * _PI / IRP_PERCALC);
	}
	s->ThetaOffset = CONSTANT_PHASE_SHIFT;
        if(uGF.bit.ChangeDir)
            s->Theta = s->Theta - s->ThetaOffset;
        else
            s->Theta = s->Theta + s->ThetaOffset;

	POPCORCON();

	return;
}

void SMCInit(SMC *s)
{
    //                R * Ts
    // Fsmopos = 1 - --------
    //                  L
    //            Ts
    // Gsmopos = ----
    //            L
    // Ts = Sampling Period. If sampling at PWM, Ts = 50 us
    // R = Phase Resistance. If not provided by motor datasheet,
    //     measure phase to phase resistance with multimeter, and
    //     divide over two to get phase resistance. If 4 Ohms are
    //     measured from phase to phase, then R = 2 Ohms
    // L = Phase inductance. If not provided by motor datasheet,
    //     measure phase to phase inductance with multimeter, and
    //     divide over two to get phase inductance. If 2 mH are
    //     measured from phase to phase, then L = 1 mH

	if (Q15(PHASERES * LOOPTIMEINSEC) > Q15(PHASEIND))
		s->Fsmopos = Q15(0.0);
	else
		s->Fsmopos = Q15(1 - PHASERES * LOOPTIMEINSEC / PHASEIND);

	if (Q15(LOOPTIMEINSEC) > Q15(PHASEIND))
		s->Gsmopos = Q15(0.99999);
	else
		s->Gsmopos = Q15(LOOPTIMEINSEC / PHASEIND * UMAX / IPEAK);

	s->Kslide = Q15(SMCGAIN);
	s->MaxSMCError = Q15(MAXLINEARSMC);
	s->FiltOmCoef = Q15(OMEGA0 * _PI / IRP_PERCALC); // Cutoff frequency for omega filter
													 // is minimum omega, or OMEGA0

	return;
}

