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
#include "FdWeak.h"
#include "general.h"
#include "smcpos.h"
tFdWeakParm	FdWeakParm;

SFRAC16 FieldWeakening(SFRAC16 qMotorSpeed)
{
    /* if the speed is less than one for activating the FW */
	if (qMotorSpeed <= FdWeakParm.qFwOnSpeed)
	{
		/* set Idref as first value in magnetizing curve */
		FdWeakParm.qIdRef = FdWeakParm.qFwCurve[0];
	} 
	else
	{
		// Index in FW-Table. The result is left shifted 11 times because
		// we have a field weakening table of 16 (4 bits) values, and the result
		// of the division is 15 bits (16 bits, with no sign). So
		// Result (15 bits) >> 11 -> Index (4 bits).
		FdWeakParm.qFWPercentage = FracDiv((qMotorSpeed-FdWeakParm.qFwOnSpeed), \
							   Q15(OMEGAFIELDWK-OMEGANOMINAL+1));
		FdWeakParm.qIndex = FdWeakParm.qFWPercentage >> 11;

		// Interpolation betwen two results from the Table. First mask 11 bits,
		// then left shift 4 times to get 15 bits again.
		FdWeakParm.qInterpolPortion = (FdWeakParm.qFWPercentage & 0x07FF) << 4;

		FdWeakParm.qIdRef = FdWeakParm.qFwCurve[FdWeakParm.qIndex] \
							- FracMpy(FdWeakParm.qFwCurve[FdWeakParm.qIndex] \
									- FdWeakParm.qFwCurve[FdWeakParm.qIndex+1] \
									 ,FdWeakParm.qInterpolPortion);

	}
	return FdWeakParm.qIdRef;
}

void FWInit(void)
{
	/* initialize magnetizing curve values */
	FdWeakParm.qFwOnSpeed = Q15(OMEGANOMINAL);
	FdWeakParm.qFwCurve[0]	= dqKFw0;
	FdWeakParm.qFwCurve[1]	= dqKFw1;
	FdWeakParm.qFwCurve[2]	= dqKFw2;
	FdWeakParm.qFwCurve[3]	= dqKFw3;
	FdWeakParm.qFwCurve[4]	= dqKFw4;
	FdWeakParm.qFwCurve[5]	= dqKFw5;
	FdWeakParm.qFwCurve[6]	= dqKFw6;
	FdWeakParm.qFwCurve[7]	= dqKFw7;
	FdWeakParm.qFwCurve[8]	= dqKFw8;
	FdWeakParm.qFwCurve[9]	= dqKFw9;
	FdWeakParm.qFwCurve[10]	= dqKFw10;
	FdWeakParm.qFwCurve[11]	= dqKFw11;
	FdWeakParm.qFwCurve[12]	= dqKFw12;
	FdWeakParm.qFwCurve[13]	= dqKFw13;
	FdWeakParm.qFwCurve[14]	= dqKFw14;
	FdWeakParm.qFwCurve[15]	= dqKFw15;	
	return;
}
