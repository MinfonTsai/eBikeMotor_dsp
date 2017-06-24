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
/***********************************************************************
 *      Code Description                                               *
 *                                                                     *
 *  Initialization for dsPIC's ports                                   *
 *                                                                     *
 **********************************************************************/

#include "general.h"

void SetupPorts( void )
{

	// ============= Port A ==============
	LATA  = 0;
	TRISA = 0x1F93;			// Reset value (all inputs)
    ANSELA = 0;
    ANSELAbits.ANSA1 = 1;	// RA1 (AN1) Opamp input C2IN1+ used for Ia
	ANSELAbits.ANSA0 = 1;	// RA0 (AN0) Opamp output OA2OUT used for Ia
	
	// ============= Port B ==============
    LATB  = 0x0000;
    TRISB = 0x03FF;			// RB10~15 outputs for PWM, rest are inputs
    ANSELB = 0;
    ANSELBbits.ANSB0 = 1;	// RB0 (AN2) Opamp input C2IN1- used for Ia
    ANSELBbits.ANSB1 = 1;	// RB1 (AN3) Opamp output OA1OUT used for Isum
    ANSELBbits.ANSB2 = 1;	// RB2 (AN4) Opamp input C1IN1+ used for Isum
    ANSELBbits.ANSB3 = 1;	// RB3 (AN5) Opamp input C1IN1- used for Isum
    
	// ============= Port C ==============
	LATC  = 0x0000;
	TRISC = 0xBFFF;			// Reset value (all inputs)
    ANSELC = 0;
    ANSELCbits.ANSC2 = 1;	// RC2 (AN8) Opamp input C3IN1+ used for Ib
    ANSELCbits.ANSC1 = 1;	// RC1 (AN7) Opamp input C3IN1- used for Ib
    ANSELCbits.ANSC0 = 1;	// RC0 (AN6) Opamp output C3OUT used for Ib
    _TRISC10 = 0;           // RC10 (Home) Test output
    
	// ============= Port D ==============
    LATD  = 0x0000;
    TRISD = 0x0160;			// Reset value (all inputs)
    TRISDbits.TRISD6 = 0;	// DBG_LED1 output
    TRISDbits.TRISD5 = 0;	// DBG_LED2 output
   
   	// ============= Port E ==============
    LATE  = 0x0000;
    TRISE = 0xF000;			// Reset value (all inputs)
    ANSELE = 0;
    ANSELEbits.ANSE13 = 1;	// Pot (AN13)
	
	// ============= Port F ==============
    LATF  = 0x0000;
    TRISF = 0x0173;			// Reset value (all inputs)
    TRISFbits.TRISF1 = 0;	// Output - UART TX

	// ============= Port G ==============
    LATG  = 0x0000;
    TRISG = 0x03C0;			// Reset value (all inputs)
		
	/****************************************************************/
	
	/************** Code section for the low pin count devices ******/
	/*Assigning the TX and RX pins to ports RP97 & RP53 to the dsPIC*/
	__builtin_write_OSCCONL(OSCCON & (~(1<<6))); // clear bit 6 

    RPINR19bits.U2RXR = 53;		// Make Pin RP53 U2RX
    RPOR7bits.RP97R = 3;	    // Make Pin RP97 U2TX
    //------------------------------------------------------------------------
    RPINR7bits.IC1R = 24;  // IC1-->RPI24/RA8 (Hall A)
    RPINR7bits.IC2R = 54;  // IC2-->RP54/RC6 (Hall B)
    RPINR8bits.IC3R = 96;  // IC3-->RPI96/RF0 (Hall C)
    //-------------------------------------------------------------------------	
	__builtin_write_OSCCONL(OSCCON | (1<<6)); 	 // Set bit 6 	
	/****************************************************************/


	return;
}

