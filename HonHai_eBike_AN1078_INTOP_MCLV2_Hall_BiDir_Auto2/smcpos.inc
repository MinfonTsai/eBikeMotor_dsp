; ******************************************************************************
; © 2012 Microchip Technology Inc.
; 
; SOFTWARE LICENSE AGREEMENT:
; Microchip Technology Incorporated ("Microchip") retains all ownership and 
; intellectual property rights in the code accompanying this message and in all 
; derivatives hereto.  You may use this code, and any derivatives created by 
; any person or entity by or on your behalf, exclusively with Microchip's
; proprietary products.  Your acceptance and/or use of this code constitutes 
; agreement to the terms and conditions of this notice.
;
; CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
; WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
; TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
; PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
; PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
;
; YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
; IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
; STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
; PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
; ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
; ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
; ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
; THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
; HAVE THIS CODE DEVELOPED.
;
; You agree that you are solely responsible for testing the code and 
; determining its suitability.  Microchip has no obligation to modify, test, 
; certify, or support the code.
;
; ******************************************************************************
;;------------------  ASM30 API for smcpos.s routines -------------------
; SMC stucture:
;typedef struct	{  
;	SFRAC16  Valpha;   		// Input: Stationary alfa-axis stator voltage 
;	SFRAC16  Ealpha;   		// Variable: Stationary alfa-axis back EMF 
;	SFRAC16  EalphaFinal;	// Variable: Filtered EMF for Angle calculation
;	SFRAC16  Zalpha;      	// Output: Stationary alfa-axis sliding control 
;	SFRAC16  Gsmopos;    	// Parameter: Motor dependent control gain 
;	SFRAC16  EstIalpha;   	// Variable: Estimated stationary alfa-axis stator current 
;	SFRAC16  Fsmopos;    	// Parameter: Motor dependent plant matrix 
;	SFRAC16  Vbeta;   		// Input: Stationary beta-axis stator voltage 
;	SFRAC16  Ebeta;  		// Variable: Stationary beta-axis back EMF 
;	SFRAC16  EbetaFinal;	// Variable: Filtered EMF for Angle calculation
;	SFRAC16  Zbeta;      	// Output: Stationary beta-axis sliding control 
;	SFRAC16  EstIbeta;    	// Variable: Estimated stationary beta-axis stator current 
;	SFRAC16  Ialpha;  		// Input: Stationary alfa-axis stator current 
;	SFRAC16  IalphaError; 	// Variable: Stationary alfa-axis current error                 
;	SFRAC16  Kslide;     	// Parameter: Sliding control gain 
;	SFRAC16  MaxSMCError;  	// Parameter: Maximum current error for linear SMC 
;	SFRAC16  Ibeta;  		// Input: Stationary beta-axis stator current 
;	SFRAC16  IbetaError;  	// Variable: Stationary beta-axis current error                 
;	SFRAC16  Kslf;       	// Parameter: Sliding control filter gain 
;	SFRAC16  KslfFinal;    	// Parameter: BEMF Filter for angle calculation
;	SFRAC16  FiltOmCoef;   	// Parameter: Filter Coef for Omega filtered calc
;	SFRAC16  ThetaOffset;	// Output: Offset used to compensate rotor angle
;	SFRAC16  Theta;			// Output: Compensated rotor angle 
;	SFRAC16  Omega;     	// Output: Rotor speed
;	SFRAC16  OmegaFltred;  	// Output: Filtered Rotor speed for speed PI
;} SMC;

				.equ SMC_Valpha,0
				.equ SMC_Ealpha,2
				.equ SMC_EalphaFinal,4
				.equ SMC_Zalpha,6
				.equ SMC_Gsmopos,8
				.equ SMC_EstIalpha,10
				.equ SMC_Fsmopos,12
				.equ SMC_Vbeta,14
				.equ SMC_Ebeta,16
				.equ SMC_EbetaFinal,18
				.equ SMC_Zbeta,20
				.equ SMC_EstIbeta,22
				.equ SMC_Ialpha,24
				.equ SMC_IalphaError,26
				.equ SMC_Kslide,28
				.equ SMC_MaxSMCError,30
				.equ SMC_Ibeta,32
				.equ SMC_IbetaError,34
				.equ SMC_Kslf,36
				.equ SMC_KslfFinal,38
				.equ SMC_FiltOmCoef,40
				.equ SMC_ThetaOffset,42
				.equ SMC_Theta,44
				.equ SMC_Omega,46
				.equ SMC_OmegaFltred,48

				.extern _scm1

