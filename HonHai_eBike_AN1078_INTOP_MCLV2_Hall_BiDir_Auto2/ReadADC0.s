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
; ReadSignedADC0
;  
;Description:        
;  Read Channel 0 of ADC, scale it using qK and put results in qADValue.
;  Do not call this routine until conversion is completed.
;
;  ReadSignedADC0 range is qK*(-1.0 ->0.9999).
;
;  Scaling constant, qK, must be set elsewhere such that
;         iResult = qK * ADCBUF0
;
;Functional prototype:
; 
; void ReadSignedADC0( tReadADCParm* pParm ) : Calculates signed value qK -> qK
;
;On Entry:   ReadADCParm structure must contain qK. ADC channel 0
;            must contain signed fractional value.
;
;On Exit:    ReadADCParm will contain qADValue
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0
;     If there is any chance that Accumulator will overflow must set
;         CORCON.SATDW = 1  
;
; Support routines required: None
;
; Local Stack usage: None
;
; Registers modified: w0,w4,w5
;
; Timing: 13 cycles
;
;*******************************************************************
;
          .include "general.inc"

; External references
          .include "ReadADC.inc"

; Register usage
          .equ ParmBaseW,w0  ; Base of parm structure
          .equ Work0W,   w4
          .equ Work1W,   w5



;=================== CODE =====================

          .section  .text  

          .global   _ReadSignedADC0
          .global   ReadSignedADC0

_ReadSignedADC0:
ReadSignedADC0:

     ;; iResult = qK * ADCBUF0
      
	mov.w     [ParmBaseW+ADC_qK],Work0W
	mov.w	    _ADC1BUF0, Work1W

	mpy       Work0W*Work1W,A
	sac       A,#0,Work0W
	mov.w     Work0W,[ParmBaseW+ADC_qADValue]

	return

          .global   _ReadADC0_VDC
          .global   ReadADC0_VDC
_ReadADC0_VDC:
ReadADC0_VDC:

		; Read DC Bus, remove sign
		mov.w	_ADC1BUF0, Work0W
		asr.w 	Work0W, Work1W
  		mov.w	#0x4000, Work0W
		add.w	Work1W, Work0W, Work0W
		mov.w	Work0W, _DCbus

		return

          .end
