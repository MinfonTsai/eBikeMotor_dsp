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
;;------------------  ASM30 API for Park Clarke routines ---------------------
; ParkParm stucture:

; typedef struct {
;    short   qAngle;
;    short   qCos;
;    short   qSin;
;    short   qIa;
;    short   qIb;
;    short   qIalpha;
;    short   qIbeta;
;    short   qId;
;    short   qIq;
;    short   qVd;
;    short   qVq;
;    short   qValpha;
;    short   qVbeta;
;    short   qV1;
;    short   qV2;
;    short   qV3;
;    } tParkParm;

; Note that pairs qCos,qSin, qIa,qIb, etc must remain consecutive

          .equ Park_qAngle,0       ; qAngle
          .equ Park_qSin,2         ; qSin
          .equ Park_qCos,4         ; qCos
          .equ Park_qIa,6          ; qIa
          .equ Park_qIb,8          ; qIb
          .equ Park_qIalpha,10     ; qIalpha
          .equ Park_qIbeta,12      ; qIbeta
          .equ Park_qId,14         ; qId
          .equ Park_qIq,16         ; qIq
          .equ Park_qVd,18         ; qVd
          .equ Park_qVq,20         ; qVq
          .equ Park_qValpha,22     ; qValpha
          .equ Park_qVbeta,24      ; qVbeta
          .equ Park_qV1,26         ; qV1
          .equ Park_qV2,28         ; qV2
          .equ Park_qV3,30         ; qV3

          .extern _ParkParm

