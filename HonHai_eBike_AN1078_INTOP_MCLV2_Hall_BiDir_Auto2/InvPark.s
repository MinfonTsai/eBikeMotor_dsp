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
; InvPark
;  
;Description:        
;  Calculate the inverse Park transform. Assumes the Cos and Sin values 
;  are in the ParkParm structure.
;
;         Valpha =  Vd*cos(Angle) - Vq*sin(Angle)
;         Vbeta  =  Vd*sin(Angle) + Vq*cos(Angle)
;
;  This routine works the same for both integer scaling and 1.15 scaling.
;
;Functional prototype:
; 
; void InvPark( void )
;
;On Entry:   The ParkParm structure must contain qCos, qSin, qVd and qVq.
;
;On Exit:    ParkParm will contain qValpha, qVbeta.
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
; Registers modified: w3 -> w7, A
;
; Timing:
;  About 14 instruction cycles
;
;*******************************************************************
;
          .include "general.inc"

; External references
          .include "park.inc"

; Register usage
          .equ ParmW,  w3    ; Ptr to ParkParm structure

          .equ SinW,   w4
          .equ CosW,   w5
          .equ VdW,    w6    ; copy of qVd
          .equ VqW,    w7    ; copy of qVq



;=================== CODE =====================

          .section  .text
          .global   _InvPark
          .global   InvPark

_InvPark:
InvPark:
     ;; Get qVd, qVq from ParkParm structure
          mov.w     _ParkParm+Park_qVd,VdW
          mov.w     _ParkParm+Park_qVq,VqW

     ;; Get qSin, qCos from ParkParm structure
          mov.w     _ParkParm+Park_qSin,SinW
          mov.w     _ParkParm+Park_qCos,CosW

     ;; Valpha =  Vd*cos(Angle) - Vq*sin(Angle)

          mpy       CosW*VdW,A        ; Vd*qCos -> A
          msc       SinW*VqW,A        ; sub Vq*qSin from A

          mov.w     #_ParkParm+Park_qValpha,ParmW
          sac       A,[ParmW++]        ; store to qValpha, inc ptr to qVbeta

     ;; Vbeta  =  Vd*sin(Angle) + Vq*cos(Angle)
          mpy       SinW*VdW,A        ; Vd*qSin -> A
          mac       CosW*VqW,A        ; add Vq*qCos to A
          sac       A,[ParmW]          ; store to Vbeta

           return
          .end
