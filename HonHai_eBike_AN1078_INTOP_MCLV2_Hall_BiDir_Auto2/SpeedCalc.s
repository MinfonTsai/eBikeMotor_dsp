; WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
; LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
; PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
; BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
; DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
; PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
; BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
; ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
;
; REVISION HISTORY:
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Author            Date      Comments on this revision
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; First Last Name   mm/dd/yy  Place your comments here
; Jorge Zambada     08/17/05  Assembly functions for WIB
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

;;.include "p30f3010.inc"

	.global _SpeedCalculation
	.global _SpeedControl

;********************************************************************
; This subroutine Calculates the speed of the BLDC motor in fractional
; format using Fractional Division as follows:
;
;                                        Minimum Period
;   Actual Speed = (Fractinal Division) -----------------
;                                        Actual Period
;
;********************************************************************

_SpeedCalculation:
	MOV _MinPeriod, W8
	MOV _Period, W9
	REPEAT #17
	DIVF W8, W9
	MOV W0, _Speed
	RETURN

.end
