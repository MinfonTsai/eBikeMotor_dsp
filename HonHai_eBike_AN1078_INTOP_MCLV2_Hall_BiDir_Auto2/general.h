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
#ifndef general_H
#define general_H

//--------------------- Common stuff for C routines ---------------------

#include <p33Exxxx.h>
#include "UserParms.h"
typedef unsigned short WORD;
typedef signed int SFRAC16;
typedef unsigned char  BYTE;
typedef unsigned char  bool;
#define False  0
#define True   1
#define _0_05DEG 9	// The value for 0.05 degrees is converted
					// to Q15 as follows:
					// .05 * 32768 / 180 = 9.1, approx 9.

#define Q15(Float_Value)	\
        ((Float_Value < 0.0) ? (SFRAC16)(32768 * (Float_Value) - 0.5) \
        : (SFRAC16)(32767 * (Float_Value) + 0.5))

#define REFINAMPS(Amperes_Value)	\
		(Q15((Amperes_Value)*(DQKA/32768.0)*RSHUNT*DIFFAMPGAIN/(VDD/2)))

#define pinButton1	!PORTGbits.RG7 //S2 - BTN_1
#define pinButton2	!PORTGbits.RG6 //S3 - BTN_2

// Main functions prototypes
void SetupPorts( void );
bool SetupParm(void);
inline void DoControl( void );
inline void CalculateParkAngle(void);
void SetupControlParameters(void);
void DebounceDelay(void);
SFRAC16 VoltRippleComp(SFRAC16 Vdq1);
void __attribute__ ((__interrupt__, no_auto_psv)) _IC1Interrupt(void);
void __attribute__ ((__interrupt__, no_auto_psv)) _IC2Interrupt(void);
void __attribute__ ((__interrupt__, no_auto_psv)) _IC3Interrupt(void);
inline void GetHallAngle_Inline (void);
inline void GetInitHallAngle_Inline(void);
inline void HallAngle_Inline (void);
extern void SpeedCalculation(void);
inline void CalculateParkAngleHall(void);
#ifdef INITIALIZE
    // allocate storage
    #define EXTERN
#else
    #define EXTERN extern
#endif

#endif      // end of general_H
