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
#ifndef UserParms_H
#define UserParms_H
#define BiDir                      // Reverse the motor

#include "park.h"
#include "control.h"

#define PWM_DT_ERRATA

//************** Start-Up Parameters **************

#define LOCKTIMEINSEC  1		// Initial rotor lock time in seconds
								// Make sure LOCKTIMEINSEC*(1.0/LOOPTIMEINSEC)
								// is less than 65535.
#define OPENLOOPTIMEINSEC 3	// Open loop time in seconds. This is the time that
								// will take from stand still to closed loop.
								// Optimized to overcome the brake inertia.
								// (Magtrol AHB-3 brake inertia = 6.89 kg x cm2).
#define INITIALTORQUE	2		// Initial Torque demand in Amps.
								// Enter initial torque demand in Amps using REFINAMPS() 
								// macro. Maximum Value for reference is defined by 
								// shunt resistor value and differential amplifier gain.
								// Use this equation to calculate maximum torque in 
								// Amperes:
								// 
								// Max REFINAMPS = (VDD/2)/(RSHUNT*DIFFAMPGAIN)
								//
								// For example:
								//
								// RSHUNT = 0.005
								// VDD = 3.3
								// DIFFAMPGAIN = 75
								//
								// Maximum torque reference in Amps is:
								//
								// (3.3/2)/(.005*75) = 4.4 Amperes, or REFINAMPS(4.4)
#define ENDSPEEDOPENLOOP MINSPEEDINRPM

// Values used to test Hurst Motor "NT Dynamo DMB0224C10002" at 24VDC input. Motor datasheet at www.hurstmfg.com
#define POLEPAIRS      	5       // Number of pole pairs
#define PHASERES		((float)0.03)//((float)2.03)	// Phase resistance in Ohms.
#define PHASEIND		((float)0.00005)//((float)0.0023)// Phase inductance in Henrys.
#define NOMINALSPEEDINRPM 3500//2800	// Make sure NOMINALSPEEDINRPM generates a MAXOMEGA < 1.0
								// Use this formula:
								// MAXOMEGA = NOMINALSPEEDINRPM*SPEEDLOOPTIME*POLEPAIRS*2/60
								// If MAXOMEGA > 1.0, reduce NOMINALSPEEDINRPM or execute
								// speed loop faster by reducing SpeedLoopTime.
								// Maximum position of POT will set a reference of 
								// NOMINALSPEEDINRPM.
#define MINSPEEDINRPM	500	// Minimum speed in RPM. Closed loop will operate at this
								// speed. Open loop will transition to closed loop at
								// this minimum speed. Minimum POT position (CCW) will set
								// a speed reference of MINSPEEDINRPM
#define FIELDWEAKSPEEDRPM 3500//2800 	// Make sure FIELDWEAKSPEEDRPM generates a MAXOMEGA < 1.0
								// Use this formula:
								// MAXOMEGA = FIELDWEAKSPEEDRPM*SPEEDLOOPTIME*POLEPAIRS*2/60
								// If MAXOMEGA > 1.0, reduce FIELDWEAKSPEEDRPM or execute
								// speed loop faster by reducing SpeedLoopTime.
								// Maximum position of POT will set a reference of 
								// FIELDWEAKSPEEDRPM.

//************** Oscillator Parameters **************

#define PLLIN		8000000		// External Crystal or Clock Frequency (Hz)
#define DESIREDMIPS	70000000	// Enter desired MIPS. If RTDM is used, copy
								// this value to RTDM_FCY in RTDMUSER.h file

//************** PWM and Control Timing Parameters **********

#define PWMFREQUENCY	20000		// PWM Frequency in Hertz
#define DEADTIMESEC     0.000001        // Dead time in seconds - 700ns
#define	BUTPOLLOOPTIME	0.0200		// Button polling loop period in sec
#define SPEEDLOOPFREQ	1000		// Speed loop Frequency in Hertz. This value must
									// be an integer to avoid pre-compiler error

//************** Slide Mode Controller Parameters **********

#define SMCGAIN		0.99		// Slide Mode Controller Gain (0.0 to 0.9999)
#define MAXLINEARSMC    0.15		// If measured current - estimated current
								// is less than MAXLINEARSMC, the slide mode
								// Controller will have a linear behavior
								// instead of ON/OFF. Value from (0.0 to 0.9999)
//************** Hardware Parameters ****************

#define RSHUNT		0.025    //	0.025	// Value in Ohms of shunt resistors used.
#define DIFFAMPGAIN	15      //	15		// Gain of differential amplifier.
#define VDD		3.3         // VDD voltage, only used to convert torque
								// reference from Amps to internal variables

#define UMAX 24         // Maximum DC link voltage on inverter
#define IPEAK 8.8//22    //8.8           // maximum current (peak to peak) that can be read by adc with the shunt/opamp settings above

//************** Real Time Data Monitor, RTDM *******************

//#define RTDM		// This definition enabled Real Time Data Monitor, UART interrupts
					// to handle RTDM protocol, and array declarations for buffering
					// information in real time

#undef DMCI_DEMO	// Define this if a demo with DMCI is done. Start/stop of motor
					// and speed variation is done with DMCI instead of push button
					// and POT. Undefine "DMCI_DEMO" is user requires operating
					// this application with no DMCI

#ifdef RTDM
#define DATA_BUFFER_SIZE 410  //Size in 16-bit Words
#define SNAPDELAY	10 // In number of PWM Interrupts
#define	SNAP1		ParkParm.qIq    //AngleStepByPWM
#define	SNAP2		ParkParm.qAngle
#define SNAP3	    ParkParm.qId    //Period
#define SNAP4	    CtrlParm.qVqRef //HallState
#endif


#define SPEEDDELAY 1 // Delay for the speed ramp.
					  // Necessary for the PI control to work properly at high speeds.

//*************** Optional Modes **************
#define TORQUEMODE
//#define ENVOLTRIPPLE

//************** PI Coefficients **************

//******** D Control Loop Coefficients *******
#define     DKP        Q15(0.05)
#define     DKI        Q15(0.002)
#define     DKC        Q15(0.99999)
#define     DOUTMAX    Q15(0.99999)

//******** Q Control Loop Coefficients *******
#define     QKP        Q15(0.05)
#define     QKI        Q15(0.002)
#define     QKC        Q15(0.99999)
#define     QOUTMAX    Q15(0.99999)

//*** Velocity Control Loop Coefficients *****
#define     WKP        Q15(0.05)
#define     WKI        Q15(0.002)
#define     WKC        Q15(0.99999)
#define     WOUTMAX    Q15(0.49999)

//************** ADC Scaling **************
// Scaling constants: Determined by calibration or hardware design. 
#define     DQK        Q15(0.49)    //Q15((OMEGA10 - OMEGA0)/2.0)	// POT Scaling
#define     DQKA       Q15(0.999999)	// Current feedback software gain
#define     DQKB       Q15(0.999999)	// Current feedback software gain

//************** Field Weakening **************
// Enter flux demand Amperes using REFINAMPS() macro. Maximum Value for
// reference is defined by shunt resistor value and differential amplifier gain.
// Use this equation to calculate maximum torque in Amperes:
// 
// Max REFINAMPS = (VDD/2)/(RSHUNT*DIFFAMPGAIN)
//
// For example:
//
// RSHUNT = 0.005
// VDD = 3.3
// DIFFAMPGAIN = 75
//
// Maximum torque reference in Amps is:
//
// (3.3/2)/(.005*75) = 4.4 Amperes, or REFINAMPS(4.4)
//
// in order to have field weakening, this reference value should be negative,
// so maximum value in this example is -4.4, or REFINAMPS(-4.4)
#define     dqKFw0  REFINAMPS(0) //3000
#define     dqKFw1  REFINAMPS(-0.650)*5 //3166
#define     dqKFw2  REFINAMPS(-0.915)*5 //3333
#define     dqKFw3  REFINAMPS(-1.075)*5 //3500
#define     dqKFw4  REFINAMPS(-1.453)*5 //3666
#define     dqKFw5  REFINAMPS(-1.732)*5 //3833
#define     dqKFw6  REFINAMPS(-1.970)*5 //4000
#define     dqKFw7  REFINAMPS(-2.038)*5 //4166
#define     dqKFw8  REFINAMPS(-2.152)*5 //4333
#define     dqKFw9  REFINAMPS(-2.242)*5 //4500
#define     dqKFw10  REFINAMPS(-2.364)*5 //4666
#define     dqKFw11  REFINAMPS(-2.40)*5 //4833
#define     dqKFw12  REFINAMPS(-2.425)*5 //5000
#define     dqKFw13  REFINAMPS(-2.45)*5 //5166
#define     dqKFw14  REFINAMPS(-2.475)*5 //5333
#define     dqKFw15  REFINAMPS(-2.5)*5 //5500

//************** Derived Parameters ****************

#define DFCY        70000000	// Instruction cycle frequency (Hz)
#define DTCY        (float)(1.0/DFCY)		// Instruction cycle period (sec)
#define DDEADTIME   (unsigned int)(DEADTIMESEC*DFCY)	// Dead time in dTcys
#define LOOPTIMEINSEC (1.0/PWMFREQUENCY) // PWM Period = 1.0 / PWMFREQUENCY
#define SPEEDLOOPTIME (1.0/SPEEDLOOPFREQ) // Speed Control Period
#define IRP_PERCALC (unsigned int)(SPEEDLOOPTIME/LOOPTIMEINSEC)	// PWM loops per velocity calculation
// PWM loops necessary for transitioning from open loop to closed loop
#define TRANSITION_STEPS   IRP_PERCALC/4

#define LOOPINTCY	(unsigned int)(DFCY/PWMFREQUENCY)   // Basic loop period in units of Tcy
#define LOCKTIME	(unsigned int)(LOCKTIMEINSEC*(1.0/LOOPTIMEINSEC))
// Time it takes to ramp from zero to MINSPEEDINRPM. Time represented in seconds
#define DELTA_STARTUP_RAMP	(unsigned int)(MINSPEEDINRPM*POLEPAIRS*LOOPTIMEINSEC* \
							LOOPTIMEINSEC*65536*65536/(60*OPENLOOPTIMEINSEC))
// Number of control loops that must execute before the button routine is executed.
#define	BUTPOLLOOPCNT	(unsigned int)(BUTPOLLOOPTIME/LOOPTIMEINSEC)

//------------------------------------------------------------------------------
// MINCOUNTS = DFCY/T2 scale/(Max RPM/60)/6/PolePairs
#define MINCOUNTS   91     // Based on 6000RPM for 10-pole motor, Hallx3
// AngleStep = 60 degrees * 70MHz / PWM freq./T2 scale
// 10922.67*70000000/20000/256 = 149333.378
#define ANGLESTEP   (float)10922.67*70000000/20000/256
#define OFFSETANGLE 0//45*32768/180
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Hall sensor inputs IO define
#define HALL_A  _RA8
#define HALL_B  _RC6
#define HALL_C  _RF0
#define HALL_A_CNIE   CNENAbits.CNIEA8
#define HALL_B_CNIE   CNENCbits.CNIEC6
#define HALL_C_CNIE   CNENFbits.CNIEF0
//------------------------------------------------------------------------------
// This pre-processor condition will generate an error if maximum speed is out of
// range on Q15 when calculating Omega.
#if (FIELDWEAKSPEEDRPM < NOMINALSPEEDINRPM)
	#error FIELDWEAKSPEEDRPM must be greater than NOMINALSPEEDINRPM for field weakening.
	#error if application does not require Field Weakening, set FIELDWEAKSPEEDRPM value
	#error equal to NOMINALSPEEDINRPM
#else
	#if ((FIELDWEAKSPEEDRPM*POLEPAIRS*2/(60*SPEEDLOOPFREQ)) >= 1)
		#error FIELDWEAKSPEEDRPM will generate an Omega value greater than 1 which is the
		#error maximum in Q15 format. Reduce FIELDWEAKSPEEDRPM value, or increase speed
		#error control loop frequency, SPEEDLOOPFREQ
	#endif
#endif

#ifdef PWM_DT_ERRATA
    #define MIN_DUTY  (unsigned int)(DDEADTIME/2 + 1)        // Should be >= DDEADTIME/2 for PWM Errata workaround
#else
    #define MIN_DUTY  0x00
#endif

#endif
