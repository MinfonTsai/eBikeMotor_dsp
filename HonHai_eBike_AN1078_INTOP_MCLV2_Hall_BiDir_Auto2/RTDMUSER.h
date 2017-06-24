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
//	File:		RTDMUSER.h
//
// This program along with MPLAB DMCI ( MPLAB 8.10 or higher) create an alternative link 
//between Host PC and target device for debugging applications in real-time. 
//It is required to include the RTDM.C file and RTDM.h into the application project 
//in order to send/receive data through the UART to/from the host PC running under 
//MPLAB (release 8.10 or higher) DMCI environment. 
// NOTE:DMCI included in MPLAB 8.10 or higher is ready and enabled to support data exchange 
//between the host PC and target device. Previous versions of DMCI do not support this feature. 
// NOTE: RTDM is currently supported by PIC24H, dsPIC30F, dsPIC33F and dsPIC33E processors
//
//
//	Written By:		M.Ellis, D. Torres,
//				Microchip Technology Inc
//						
// 
// The following files should be included in the MPLAB project:
//
//		RTDM.c			-- RTDM source code file
//		RTDM.h			-- RTDM header file
//		RTDMUSER.h		-- RTDM user definitions file
//		libpXXXX-coff.a		-- Your dsPIC/PIC24 Peripheral Library		
//		pXXXXXXX.gld		-- your dsPIC/PIC24 Linker script file
//				
//
/*****************************************************************************/
//
// Revision History
//
// 4/7/08  -- First Version Release
/****************************************************************************/
//
// Revision History
//
// 4/12/10  -- Added support for dsPIC33E and PIC24E
/****************************************************************************/

#ifndef RTDMUSER_H
#define RTDMUSER_H

#define YES  1
#define NO 	 0
/************************************** RTDM DEFINITIONS  ***************************************/
#define RTDM_FCY	 	70000000	//This define has to be the system operating freq, this 
									//value is used to calculate the value of the BRG register
#define RTDM_BAUDRATE	57600		//This is the desired baudrate for the UART module to be 
									//used by RTDM
#define RTDM_UART			2		// This is the UART module to be used by RTDM. It has only
									// two possible values: 1 or 2
									// For dsPIC33E and PIC24E, values 3 and 4 are also supported
#define RTDM_UART_PRIORITY	1		//This the UART RX interrupt priority assigned to receive
									// the RTDM messages
#define RTDM_RXBUFFERSIZE	32		// This is the buffer size used by RTDM to handle messaages 
#define RTDM_MAX_XMIT_LEN   0x1000	//This the size in bytes of the max num of bytes allowed in 
									//the RTDM protocol Frame
#define RTDM_POLLING		YES		// This defines the mode that RTDM will be operating in 
									//user's application. If it is YES then the user should place the 
									//RTDM_ProcessMsgs()	function in the main loop. 
									//In order to make sure that the messages are being preoccessed
									// it is recommended that the main loop always polls this 
									//function as fast as possible						
#define RTDM_MIN_CODE_SIZE	YES		//When defined causes the RTDM library to build  without 
									//including a pre-calculated polynomial  table for the CRC algorythim. 
									//This saves 768  bytes of code space. 
/*************************************************************************************************/		

#endif
