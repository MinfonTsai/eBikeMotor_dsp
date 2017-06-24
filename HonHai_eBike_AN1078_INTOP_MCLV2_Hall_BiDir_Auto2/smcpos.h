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
#ifndef smcpos_H
#define smcpos_H

#include "UserParms.h"

typedef struct	{  
				SFRAC16  Valpha;   		// Input: Stationary alfa-axis stator voltage 
                SFRAC16  Ealpha;   		// Variable: Stationary alfa-axis back EMF 
				SFRAC16  EalphaFinal;	// Variable: Filtered EMF for Angle calculation
                SFRAC16  Zalpha;      	// Output: Stationary alfa-axis sliding control 
                SFRAC16  Gsmopos;    	// Parameter: Motor dependent control gain 
                SFRAC16  EstIalpha;   	// Variable: Estimated stationary alfa-axis stator current 
                SFRAC16  Fsmopos;    	// Parameter: Motor dependent plant matrix 
                SFRAC16  Vbeta;   		// Input: Stationary beta-axis stator voltage 
                SFRAC16  Ebeta;  		// Variable: Stationary beta-axis back EMF 
				SFRAC16  EbetaFinal;	// Variable: Filtered EMF for Angle calculation
                SFRAC16  Zbeta;      	// Output: Stationary beta-axis sliding control 
                SFRAC16  EstIbeta;    	// Variable: Estimated stationary beta-axis stator current 
                SFRAC16  Ialpha;  		// Input: Stationary alfa-axis stator current 
                SFRAC16  IalphaError; 	// Variable: Stationary alfa-axis current error                 
                SFRAC16  Kslide;     	// Parameter: Sliding control gain 
                SFRAC16  MaxSMCError;  	// Parameter: Maximum current error for linear SMC 
                SFRAC16  Ibeta;  		// Input: Stationary beta-axis stator current 
                SFRAC16  IbetaError;  	// Variable: Stationary beta-axis current error                 
                SFRAC16  Kslf;       	// Parameter: Sliding control filter gain 
                SFRAC16  KslfFinal;    	// Parameter: BEMF Filter for angle calculation
                SFRAC16  FiltOmCoef;   	// Parameter: Filter Coef for Omega filtered calc
				SFRAC16  ThetaOffset;	// Output: Offset used to compensate rotor angle
                SFRAC16  Theta;			// Output: Compensated rotor angle 
				SFRAC16  Omega;     	// Output: Rotor speed
				SFRAC16  OmegaFltred;  	// Output: Filtered Rotor speed for speed PI
				} SMC;	            

typedef SMC *SMC_handle;

#define SMC_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

// Define this in RPMs

#define SPEED0 MINSPEEDINRPM
#define SPEED1 (SPEED0 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED2 (SPEED1 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED3 (SPEED2 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED4 (SPEED3 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED5 (SPEED4 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED6 (SPEED5 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED7 (SPEED6 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED8 (SPEED7 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED9 (SPEED8 + (int)((FIELDWEAKSPEEDRPM - MINSPEEDINRPM) / 10.0))
#define SPEED10 (FIELDWEAKSPEEDRPM)

// Define this in Degrees, from 0 to 360

#define THETA_AT_ALL_SPEED 90

#define OMEGA0 (float)(SPEED0 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA1 (float)(SPEED1 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA2 (float)(SPEED2 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA3 (float)(SPEED3 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA4 (float)(SPEED4 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA5 (float)(SPEED5 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA6 (float)(SPEED6 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA7 (float)(SPEED7 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA8 (float)(SPEED8 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA9 (float)(SPEED9 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGA10 (float)(SPEED10 * LOOPTIMEINSEC * \
                IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)


#define OMEGANOMINAL	(float)(NOMINALSPEEDINRPM * LOOPTIMEINSEC * \
                		IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGAFIELDWK	(float)(FIELDWEAKSPEEDRPM * LOOPTIMEINSEC * \
                		IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)

#define THETA_ALL (unsigned int)(THETA_AT_ALL_SPEED / 180.0 * 32768.0)
#define CONSTANT_PHASE_SHIFT THETA_ALL

#define PUSHCORCON()  {__asm__ volatile ("push CORCON");}
#define POPCORCON()   {__asm__ volatile ("pop CORCON");}
#define _PI 3.1416

void SMC_Position_Estimation(SMC_handle);
void SMCInit(SMC_handle);
void CalcEstI(void);
void CalcIError(void);
void CalcZalpha(void);
void CalcZbeta(void);
void CalcBEMF(void);
void CalcOmegaFltred(void);
SFRAC16 FracMpy(SFRAC16 mul_1, SFRAC16 mul_2);
SFRAC16 FracDiv(SFRAC16 num_1, SFRAC16 den_1);

extern SFRAC16 PrevTheta;
extern SFRAC16 AccumTheta;
extern WORD AccumThetaCnt;

#endif
