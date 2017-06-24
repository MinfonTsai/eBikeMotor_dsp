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
; ClarkePark
;  
;Description:        
;  Calculate Clarke & Park transforms. 
;  Assumes the Cos and Sin values are in qSin & qCos.
;
;         Ialpha = Ia
;         Ibeta  = Ia*dOneBySq3 + 2*Ib*dOneBySq3;
;             where Ia+Ib+Ic = 0
;
;         Id =  Ialpha*cos(Angle) + Ibeta*sin(Angle)
;         Iq = -Ialpha*sin(Angle) + Ibeta*cos(Angle)
;
;  This routine works the same for both integer scaling and 1.15 scaling.
;
;Functional prototype:
; 
; void ClarkePark( void )
;
;On Entry:   ParkParm structure must contain qSin, qCos, qIa and qIb.
;
;On Exit:    ParkParm will contain qId, qIq  
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0
;     If there is any chance that (Ia+2*Ib)/sqrt(3) will overflow must set
;         CORCON.SATDW = 1  
;
; Support routines required: None
;
; Local Stack usage: None
;
; Registers modified: w3 -> w7
;
; Timing: 20 cycles
;
;*******************************************************************
;
          .include "general.inc"

; External references
          .include "park.inc"

; Register usage
          .equ ParmW,  w3    ; Ptr to ParkParm structure

          .equ Sq3W,   w4    ; OneBySq3
          .equ SinW,   w4    ; replaces Work0W

          .equ CosW,   w5


          .equ IaW,    w6    ; copy of qIa
          .equ IalphaW,w6    ; replaces Ia

          .equ IbW,    w7    ; copy of qIb
          .equ IbetaW, w7    ; Ibeta  replaces Ib

; Constants
          .equ OneBySq3,0x49E7   ; 1/sqrt(3) in 1.15 format


;=================== CODE =====================

          .section  .text
          .global   _ClarkePark
          .global   ClarkePark

_ClarkePark:
ClarkePark:
     ;; Ibeta = Ia*OneBySq3 + 2*Ib*OneBySq3;

          mov.w     #OneBySq3,Sq3W     ; 1/sqrt(3) in 1.15 format

          mov.w     _ParkParm+Park_qIa,IaW
          mpy       Sq3W*IaW,A

          mov.w     _ParkParm+Park_qIb,IbW
          mac       Sq3W*IbW,A
          mac       Sq3W*IbW,A

          mov.w     _ParkParm+Park_qIa,IalphaW
          mov.w     IalphaW,_ParkParm+Park_qIalpha
          sac       A,IbetaW
          mov.w     IbetaW,_ParkParm+Park_qIbeta

     ;; Ialpha and Ibeta have been calculated. Now do rotation.

     ;; Get qSin, qCos from ParkParm structure
          mov.w     _ParkParm+Park_qSin,SinW
          mov.w     _ParkParm+Park_qCos,CosW

     ;; Id =  Ialpha*cos(Angle) + Ibeta*sin(Angle)

          mpy       SinW*IbetaW,A     ; Ibeta*qSin -> A
          mac       CosW*IalphaW,A    ; add Ialpha*qCos to A
          mov.w     #_ParkParm+Park_qId,ParmW
          sac       A,[ParmW++]        ; store to qId, inc ptr to qIq

     ;; Iq = -Ialpha*sin(Angle) + Ibeta*cos(Angle)
          mpy       CosW*IbetaW,A     ; Ibeta*qCos -> A
          msc       SinW*IalphaW,A    ; sub Ialpha*qSin from A
          sac       A,[ParmW]          ; store to qIq
          return
          .end
