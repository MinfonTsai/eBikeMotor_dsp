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
; PI
;  
;Description:  Calculate PI correction.
;
;void CalcPI( tPIParm *pParm)
;{
;    Err  = InRef - InMeas
;    U  = Sum + Kp * Err
;    if( U > Outmax )
;        Out = Outmax
;    else if( U < Outmin )
;        Out = Outmin
;    else        
;        Out = U 
;    Exc = U - Out
;    Sum = Sum + Ki * Err - Kc * Exc
;}
;
;
;void InitPI( tPIParm *pParm)
;{
;    Sum = 0
;    Out = 0
;}
;
;----------------------------
; Representation of PI constants:
; The constant Kp is scaled so it can be represented in 1.15 format by 
; adjusting the constant by a power of 2 which is removed when the
; calculation is completed.
;
; Kp is scaled Kp = qKp * 2^NKo 
;
; Ki & Kc are scaled Ki = qKi, Kc = qKc
;
;
;Functional prototype:
; 
; void InitPI( tPIParm *pParm)
; void CalcPI( tPIParm *pParm)
;
;On Entry:   PIParm structure must contain qKp,qKi,qKc,qOutMax,qOutMin,
;                                           InRef,InMeas
;On Exit:    PIParm will contain qOut
;
;Parameters: 
; Input arguments: tPIParm *pParm
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0
;         CORCON.IF    = 0
;
; Support routines required: None
;
; Local Stack usage: 0
;
; Registers modified: w0-w6,AccA
;
; Timing:
;  31 instruction cycles max, 28 cycles min
;
;*******************************************************************
;
          .include "general.inc"

; External references
          .include "PI.inc"

; Register usage

          .equ BaseW0,   w0  ; Base of parm structure

          .equ OutW1,    w1  ; Output
          .equ SumLW2,   w2  ; Integral sum
          .equ SumHW3,   w3  ; Integral sum

          .equ ErrW4,    w4  ; Error term: InRef-InMeas
          .equ WorkW5,   w5  ; Working register
          .equ UnlimitW6,w6  ; U: unlimited output 
          .equ WorkW7,   w7  ; Working register


;=================== CODE =====================

          .section  .text

          .global   _InitPI
          .global   InitPI
_InitPI:
InitPI:
          mov.w     w1,[BaseW0+PI_qOut]
          return


          .global   _CalcPI
          .global   CalcPI

_CalcPI:
CalcPI:
     ;; Err  = InRef - InMeas

          mov.w     [BaseW0+PI_qInRef],WorkW7
          mov.w     [BaseW0+PI_qInMeas],WorkW5
          sub.w     WorkW7,WorkW5,ErrW4
          
     ;; U  = Sum + Kp * Err * 2^NKo
          lac       [++BaseW0],B               ; AccB = Sum          
          mov.w     [--BaseW0],WorkW5
          mov.w     WorkW5,ACCBLL

          mov.w     [BaseW0+PI_qKp],WorkW5
          mpy       ErrW4*WorkW5,A
          sftac     A,#-NKo                  ; AccA = Kp*Err*2^NKo     
          add       A                        ; Sum = Sum + Kp*Err*2^NKo
          sac       A,UnlimitW6              ; store U before tests

     ;; if( U > Outmax )
     ;;     Out = Outmax
     ;; else if( U < Outmin )
     ;;     Out = Outmin
     ;; else        
     ;;     Out = U 

          mov.w     [BaseW0+PI_qOutMax],OutW1
          cp        UnlimitW6,OutW1
          bra       GT,jPI5            ; U > Outmax; OutW1 = Outmax

          mov.w     [BaseW0+PI_qOutMin],OutW1
          cp        UnlimitW6,OutW1
          bra       LE,jPI5            ; U < Outmin; OutW1 = Outmin

          mov.w     UnlimitW6,OutW1         ; OutW1 = U
jPI5:
          mov.w     OutW1,[BaseW0+PI_qOut]

     ;; Ki * Err
          mov.w     [BaseW0+PI_qKi],WorkW5
          mpy       ErrW4*WorkW5,A

     ;; Exc = U - Out
          sub.w     UnlimitW6,OutW1,UnlimitW6

     ;; Ki * Err - Kc * Exc 
          mov.w     [BaseW0+PI_qKc],WorkW5
          msc       WorkW5*UnlimitW6,A

     ;; Sum = Sum + Ki * Err - Kc * Exc 
          add       A
          
          sac       A,[++BaseW0]             ; store Sum 
          mov.w     ACCALL,WorkW5
          mov.w     WorkW5,[--BaseW0]
          return

          .end
