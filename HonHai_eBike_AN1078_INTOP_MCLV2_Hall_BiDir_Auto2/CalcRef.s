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
; CalcRefVec
;  
;Description:        
;  Calculate the scaled reference vector, (Vr1,Vr2,Vr3), from qValpha,qVbeta.
;  The method is an modified inverse Clarke transform where Valpha & Vbeta 
;  are swapped compared to the normal Inverse Clarke.
;
;       Vr1 = Vbeta
;       Vr2 = (-Vbeta/2 + sqrt(3)/2 * Valpha)
;       Vr3 = (-Vbeta/2 - sqrt(3/2) * Valpha)
;
;Functional prototype:
; 
; void CalcRefVec( void )
;
;On Entry:   The ParkParm structure must contain qCos, qSin, qValpha and qVbeta.
;
;On Exit:    SVGenParm will contain qVr1, qVr2, qVr3
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0

; Support routines required: None
;
; Local Stack usage: none
;
; Registers modified: w0, w4,w5,w6 
;
; Timing:
;  About 20 instruction cycles
;
;*******************************************************************
;
; External references
          .include "park.inc"
          .include "SVGen.inc"

; Register usage
          .equ WorkW,   w0    ; working

          .equ ValphaW, w4    ; qValpha (scaled)
          .equ VbetaW,  w5    ; qVbeta (scaled)
          .equ ScaleW,  w6    ; scaling

; Constants

          .equ Sq3OV2,0x6ED9 ; sqrt(3)/2 in 1.15 format

;=================== CODE =====================

          .section  .text
          .global   _CalcRefVec
          .global   CalcRefVec

_CalcRefVec:
CalcRefVec:
     ;; Get qValpha, qVbeta from ParkParm structure
          mov.w     _ParkParm+Park_qValpha,ValphaW
          mov.w     _ParkParm+Park_qVbeta,VbetaW

     ;; Put Vr1 = Vbeta
          mov.w     VbetaW,_SVGenParm+SVGen_qVr1

     ;; Load Sq(3)/2
          mov.w     #Sq3OV2,ScaleW

     ;; AccA = -Vbeta/2
          neg.w     VbetaW,VbetaW
          lac       VbetaW,#1,A

     ;; Vr2 = -Vbeta/2 + sqrt(3)2 * Valpha)
          mac       ValphaW*ScaleW,A ; add Valpha*sqrt(3)/2 to A
          sac       A,WorkW
          mov.w     WorkW,_SVGenParm+SVGen_qVr2

     ;; AccA = -Vbeta/2
          lac       VbetaW,#1,A

     ;; Vr3 = (-Vbeta/2 - sqrt(3)2 * Valpha)
          msc       ValphaW*ScaleW,A ; sub Valpha*sqrt(3)2 to A
          sac       A,WorkW
          mov.w     WorkW,_SVGenParm+SVGen_qVr3
          return
          .end
