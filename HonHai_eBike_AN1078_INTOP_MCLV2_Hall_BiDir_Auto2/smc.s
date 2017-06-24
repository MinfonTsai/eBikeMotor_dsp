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
          .include "general.inc"

; External references
          .include "smcpos.inc"

;=================== CODE =====================

          .section  .text  

          .global   _CalcEstI
          .global   CalcEstI

_CalcEstI:
CalcEstI:

;	// Sliding mode current observer
;
;	//
;	//	s->EstIalpha = s->Gsmopos * s->Valpha
;	//				 - s->Gsmopos * s->Ealpha
;	//				 - s->Gsmopos * s->Zalpha
;	//				 + s->Fsmopos * s->EstIalpha
;	//

	mov _smc1+SMC_Gsmopos,W4
	mov _smc1+SMC_Valpha,W5
	mpy W4*W5,A

	mov _smc1+SMC_Ealpha,W5
	mpy W4*W5,B
	neg B
	add A

	mov _smc1+SMC_Zalpha,W5
	mpy W4*W5,B
	neg B
	add A

	mov _smc1+SMC_Fsmopos,W4
	mov _smc1+SMC_EstIalpha,W5
	mpy W4*W5,B
	add A

	sac.r A,#0,W0
	mov W0,_smc1+SMC_EstIalpha

;	//
;	//	s->EstIbeta = s->Gsmopos * s->Vbeta
;	//				- s->Gsmopos * s->Ebeta
;	//				- s->Gsmopos * s->Zbeta
;	//				+ s->Fsmopos * s->EstIbeta
;	//

	mov _smc1+SMC_Gsmopos,W4
	mov _smc1+SMC_Vbeta,W5
	mpy W4*W5,A

	mov _smc1+SMC_Ebeta,W5
	mpy W4*W5,B
	neg B
	add A

	mov _smc1+SMC_Zbeta,W5
	mpy W4*W5,B
	neg B
	add A

	mov _smc1+SMC_Fsmopos,W4
	mov _smc1+SMC_EstIbeta,W5
	mpy W4*W5,B
	add A

	sac.r A,#0,W0
	mov W0,_smc1+SMC_EstIbeta

	return;

          .global   _CalcIError
          .global   CalcIError

_CalcIError:
CalcIError:

;	// s->IalphaError = s->EstIalpha - s->Ialpha;

	mov _smc1+SMC_EstIalpha,W0
	mov _smc1+SMC_Ialpha,W1
	lac W0, A
	lac W1, B
	sub A
	sac.r A, #0, W0
	mov W0, _smc1+SMC_IalphaError

;	// s->IbetaError = s->EstIbeta - s->Ibeta;

	mov _smc1+SMC_EstIbeta,W0
	mov _smc1+SMC_Ibeta,W1
	lac W0, A
	lac W1, B
	sub A
	sac.r A, #0, W0
	mov W0, _smc1+SMC_IbetaError

	return

          .global   _CalcZalpha
          .global   CalcZalpha

_CalcZalpha:
CalcZalpha:

		; s->Zalpha = (s->Kslide * s->IalphaError) / s->MaxSMCError

		mov _smc1+SMC_Kslide, W4
		mov _smc1+SMC_IalphaError, W5
		mov _smc1+SMC_MaxSMCError, W7
		mpy W4*W5, A
		sac.r A, #0, W0
		repeat #17
		divf W0, W7
		mov W0,_smc1+SMC_Zalpha

	return

          .global   _CalcZbeta
          .global   CalcZbeta

_CalcZbeta:
CalcZbeta:

		; s->Zbeta = (s->Kslide * s->IbetaError) / s->MaxSMCError

		mov _smc1+SMC_Kslide, W4
		mov _smc1+SMC_IbetaError, W5
		mov _smc1+SMC_MaxSMCError, W7
		mpy W4*W5, A
		sac.r A, #0, W0
		repeat #17
		divf W0, W7
		mov W0,_smc1+SMC_Zbeta

	return

          .global   _CalcBEMF
          .global   CalcBEMF

_CalcBEMF:
CalcBEMF:

	;// Sliding control filter -> back EMF calculator
	;// s->Ealpha = s->Ealpha + s->Kslf * s->Zalpha
	;//                       - s->Kslf * s->Ealpha

	mov _smc1+SMC_Ealpha, W0
	lac W0, A

	mov _smc1+SMC_Zalpha, W4
	mov _smc1+SMC_Kslf, W5
	mpy W4*W5, B
	add A

	mov _smc1+SMC_Ealpha, W4
	mpy W4*W5, B
	neg B
	add A

	sac.r A, #0, W0
	mov W0,_smc1+SMC_Ealpha

	;// s->Ebeta = s->Ebeta + s->Kslf * s->Zbeta
	;//                     - s->Kslf * s->Ebeta

	mov _smc1+SMC_Ebeta, W0
	lac W0, A

	mov _smc1+SMC_Zbeta, W4
	mov _smc1+SMC_Kslf, W5
	mpy W4*W5, B
	add A

	mov _smc1+SMC_Ebeta, W4
	mpy W4*W5, B
	neg B
	add A

	sac.r A, #0, W0
	mov W0,_smc1+SMC_Ebeta

	;// New filter used to calculate Position	
	;// s->EalphaFinal = s->EalphaFinal + s->KslfFinal * s->Ealpha
	;//                                 - s->KslfFinal * s->EalphaFinal

	mov _smc1+SMC_EalphaFinal, W0
	lac W0, A

	mov _smc1+SMC_Ealpha, W4
	mov _smc1+SMC_KslfFinal, W5
	mpy W4*W5, B
	add A

	mov _smc1+SMC_EalphaFinal, W4
	mpy W4*W5, B
	neg B
	add A

	sac.r A, #0, W0
	mov W0,_smc1+SMC_EalphaFinal

	;// s->EbetaFinal = s->EbetaFinal + s->KslfFinal * s->Ebeta
	;//                               - s->KslfFinal * s->EbetaFinal

	mov _smc1+SMC_EbetaFinal, W0
	lac W0, A

	mov _smc1+SMC_Ebeta, W4
	mov _smc1+SMC_KslfFinal, W5
	mpy W4*W5, B
	add A

	mov _smc1+SMC_EbetaFinal, W4
	mpy W4*W5, B
	neg B
	add A

	sac.r A, #0, W0
	mov W0,_smc1+SMC_EbetaFinal

	return;

          .global   _CalcOmegaFltred
          .global   CalcOmegaFltred

_CalcOmegaFltred:
CalcOmegaFltred:

	;// s->OmegaFltred = s->OmegaFltred + s->FiltOmCoef * s->Omega
	;//                                 - s->FiltOmCoef * s->OmegaFltred

	mov _smc1+SMC_OmegaFltred, W0
	mov _smc1+SMC_Omega, W4
	mov _smc1+SMC_FiltOmCoef, W5

	lac W0, A
	mpy W4*W5, B
	add A

	mov _smc1+SMC_OmegaFltred, W4
	mpy W4*W5, B
	neg B
	add A

	sac.r A, #0, W0
	mov W0, _smc1+SMC_OmegaFltred

	return

          .global   _FracMpy
          .global   FracMpy

_FracMpy:
FracMpy:

	push W4
	push W5
	mov	W0, W4
	mov	W1, W5
	mpy W4*W5, A
	sac.r A, W0
	pop W5
	pop W4
	return

          .global   _FracDiv
          .global   FracDiv

_FracDiv:
FracDiv:

	push W2
	mov	W1, W2
	repeat #17
	divf W0, W2
	pop W2
	return


          .global   _Q15SQRT
          .global   Q15SQRT

_Q15SQRT:
Q15SQRT:
             mov.w w0,w7             
             clr.w w0                
             cpsgt.w w0,w7           
             nop
             nop
             nop
             mov.d w8,[w15++]        
             ff1l w7,w3            
             sub.w w3,#2,w1          
             sl w7,w1,w2             
             mov.w #0x8000,w0        
             sub.w w2,w0,w5          
             mov.w w5,w4             
             sl w5,#1,w5             
             mov.w #0x4000,w6        
             mul.ss w4,w6,w6         
             mul.ss w4,w5,w8         
             mov.w #0xf000,w0        
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0x800,w0         
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0xfb00,w0        
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0x380,w0         
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0xfd60,w0        
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0x210,w0         
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             mul.ss w9,w5,w8         
             mov.w #0xfe53,w0        
             mul.ss w0,w9,w2         
             add.w w2,w6,w6          
             addc.w w3,w7,w7         
             lsr w6,#15,w6           
             sl w7,#1,w0             
             ior.w w6,w0,w6          
             asr w7,#15,w7           
             mov.w #0x8000,w0        
             add.w w0,w6,w6          
             addc.w w7,#0,w7         
             lsr w1,#1,w2            
             subr.w w2,#16,w0        
             lsr w6,w2,w6            
             sl w7,w0,w0             
             ior.w w6,w0,w6          
             asr w7,w2,w7            
             btst.c w1,#0            
             bra nc, Sqrt_else       
             mov.w #0x5a82,w4        
             mul.ss w6,w4,w0         
             lsr w0,#15,w0           
             sl w1,#1,w1             
             ior.w w0,w1,w6          
Sqrt_else:   mov.w w6,w0             
             mov.d [--w15],w8        
             return 
             
             
          .end

