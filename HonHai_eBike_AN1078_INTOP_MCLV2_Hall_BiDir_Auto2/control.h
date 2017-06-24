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
#ifndef Control_H
#define Control_H
//------------------  C API for Control routine ---------------------

typedef struct {
    short   qVelRef;    // Reference velocity
    short   qVdRef;     // Vd flux reference value
    short   qVqRef;     // Vq torque reference value
    } tCtrlParm;

typedef union   {
        struct
            {
            unsigned OpenLoop:1;	// Indicates if motor is running in open or closed loop
            unsigned RunMotor:1;	// If motor is running, or stopped.
            unsigned EnTorqueMod:1;	// This bit enables Torque mode when running closed loop
            unsigned EnVoltRipCo:1;	// Bit that enables Voltage Ripple Compensation
            unsigned Btn1Pressed:1;	// Button 1 has been pressed.
            unsigned Btn2Pressed:1;	// Button 2 has been pressed.
            unsigned ChangeMode:1;	// This flag indicates that a transition from open to closed
                                        // loop, or closed to open loop has happened. This
                                        // causes DoControl subroutine to initialize some variables
                                        // before executing open or closed loop for the first time
            unsigned ChangeSpeed:1;	// This flag indicates a step command in speed reference.
                                        // This is mainly used to analyze step response
            unsigned ADCH0_PotOrVdc:1;  //This bit Indicates ADC Channel O Sample A or Sample B is converted
            unsigned ChangeDir:1;
            unsigned DirectionAuto:1;   // motor spin direction
            unsigned Direction:1;
            unsigned FindHallStart:1;   // 1: Start to find the Hall position          
            unsigned    :3;
            }bit;
        //WORD Word;
        unsigned short Word;
        } tuGF;



#endif



