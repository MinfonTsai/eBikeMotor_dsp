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
* //-----------------------------------------------------------------------------
* // Motor type: Hurst BLDC motor
* // MCLV-2 demo board
* // HA: Brown HB: White HC: Green
* // M1: White M2:Black  M3:Red
//-----------------------------------------------------------------------------
******************************************************************************/
/************** GLOBAL DEFINITIONS ***********/
#define INITIALIZE
#include "general.h"
#include "Parms.h"
#include "SVGen.h"
#include "ReadADC.h"
#include "MeasCurr.h"
#include "Control.h"
#include "PI.h"
#include "Park.h"
#include "UserParms.h"
#include "smcpos.h"
#include "FdWeak.h"
#include "RTDM.h"
#include "HallScan.h"
#include <stdlib.h>



/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/
_FPOR(ALTI2C1_OFF & ALTI2C2_OFF);
_FWDT(PLLKEN_ON & FWDTEN_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF & PWMLOCK_OFF);
_FGS(GWRP_OFF & GCP_OFF);

_FICD(ICS_PGD2 & JTAGEN_OFF);	// PGD3 for 28pin 	PGD2 for 44pin
_FOSC(FCKSM_CSECMD & POSCMD_XT);		//XT W/PLL
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE); // FRC W/PLL	

/************** END OF GLOBAL DEFINITIONS ***********/


/********************* Variables to display data using DMCI *********************************/

#ifdef RTDM

int RecorderBuffer1[DATA_BUFFER_SIZE]; //Buffer to store the data samples for the DMCI data viewer Graph1
int RecorderBuffer2[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph2
int RecorderBuffer3[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph3
int RecorderBuffer4[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph4

int * PtrRecBuffer1 = &RecorderBuffer1[0];	//Tail pointer for the DMCI Graph1
int * PtrRecBuffer2 = &RecorderBuffer2[0];	//Tail pointer for the DMCI Graph2
int * PtrRecBuffer3 = &RecorderBuffer3[0];	//Tail pointer for the DMCI Graph3
int * PtrRecBuffer4 = &RecorderBuffer4[0];	//Tail pointer for the DMCI Graph4
int * RecBuffUpperLimit = RecorderBuffer4 + DATA_BUFFER_SIZE -1;	//Buffer Recorder Upper Limit
typedef struct DMCIFlags{
		    unsigned Recorder : 1;	// Flag needs to be set to start buffering data
			unsigned StartStop : 1;
			unsigned unused : 14;  
} DMCIFLAGS;
DMCIFLAGS DMCIFlags;
int	SnapCount = 0;

int SnapShotDelayCnt = 0;
int SnapShotDelay = SNAPDELAY;
int SpeedReference = 0;

#endif // End of #ifdef RTDM

int count = 0; // delay for ramping the reference velocity 
int VelReq = 0; 

SMC smc1 = SMC_DEFAULTS;

unsigned long Startup_Ramp = 0;	/* Start up ramp in open loop. This variable
								is incremented in CalculateParkAngle()
								subroutine, and it is assigned to 
								ParkParm.qAngle as follows:
								ParkParm.qAngle += (int)(Startup_Ramp >> 16);*/

unsigned int Startup_Lock = 0;	/* This is a counter that is incremented in
								CalculateParkAngle() every time it is called. 
								Once this counter has a value of LOCK_TIME, 
								then theta will start increasing moving the 
								motor in open loop. */
unsigned int  trans_counter = 0;


tuGF        uGF;
tPIParm     PIParmD;	// Structure definition for Flux component of current, or Id
tPIParm     PIParmQ;	// Structure definition for Torque component of current, or Iq
tPIParm     PIParmW;	// Structure definition for Speed, or Omega
tCtrlParm   CtrlParm;
tParkParm   ParkParm; 

tReadADCParm ReadADCParm;	// Struct used to read ADC values.

// Speed Calculation Variables

WORD iADCisrCnt = 0;	// This Counter is used as a timeout for polling the push buttons
						// in main() subroutine. It will be reset to zero when it matches
						// dButPolLoopCnt defined in UserParms.h
SFRAC16 PrevTheta = 0;	// Previous theta which is then substracted from Theta to get
						// delta theta. This delta will be accumulated in AccumTheta, and
						// after a number of accumulations Omega is calculated.
SFRAC16 AccumTheta = 0;	// Accumulates delta theta over a number of times
WORD AccumThetaCnt = 0;	// Counter used to calculate motor speed. Is incremented
						// in SMC_Position_Estimation() subroutine, and accumulates
						// delta Theta. After N number of accumulations, Omega is 
						// calculated. This N is diIrpPerCalc which is defined in
						// UserParms.h.

// Vd and Vq vector limitation variables

SFRAC16 qVdSquared = 0;	// This variable is used to know what is left from the VqVd vector
						// in order to have maximum output PWM without saturation. This is
						// done before executing Iq control loop at the end of DoControl()

SFRAC16 DCbus = 0;		// DC Bus measured continuously and stored in this variable
						// while motor is running. Will be compared with TargetDCbus
						// and Vd and Vq will be compensated depending on difference
						// between DCbus and TargetDCbus

SFRAC16 TargetDCbus = 0;// DC Bus is measured before running motor and stored in this
						// variable. Any variation on DC bus will be compared to this value
						// and compensated linearly.	

SFRAC16 Theta_error = 0;// This value is used to transition from open loop to closed looop. 
						// At the end of open loop ramp, there is a difference between 
						// forced angle and estimated angle. This difference is stored in 
						// Theta_error, and added to estimated theta (smc1.Theta) so the 
						// effective angle used for commutating the motor is the same at 
						// the end of open loop, and at the begining of closed loop. 
						// This Theta_error is then substracted from estimated theta 
						// gradually in increments of 0.05 degrees until the error is less
						// than 0.05 degrees.
volatile unsigned int HallState;
volatile unsigned int OldHallState;
volatile unsigned char T2INTCnt;
volatile unsigned int CapNew;
volatile signed int PulseCnts; 
volatile unsigned int Speed;
volatile signed int HallAngle;
volatile signed int MinPeriod = MINCOUNTS;
volatile unsigned long Period = 30000;
volatile unsigned int Temp16;
volatile unsigned int SpeedLoopCnt = 0;
extern volatile unsigned int FindHallAngleCnt;
union{
    struct{
        unsigned A:1;
        unsigned B:1;
        unsigned C:1;
        unsigned :13;
    }bits; 
    unsigned int word;
}ReadHall;
extern tFindHallAngle FindHallAngle;
extern unsigned int MotorAlignLockTime;
/************* START OF MAIN FUNCTION ***************/
int main ( void )
{
  //The settings below set up the oscillator and PLL for x MIPS as
    //follows:
    //                  Fin  * M
    // Fosc       =     ---------
    //                   N2 * N1   
    //
    // Fin   	  = 7.37 MHz (Internal Oscillator) or 8MHZ ( Crystal Oscillator)
    // Fosc       = x MHz
    // Fcy        = Fosc/2 = 

	/****************** Clock definitions *********************************/
/*
    // 70 MIPS (70.015 Mhz) (i.e 7.37 * (76/4))  Configuration for Internal Oscillator 

    PLLFBD =  74; 			    // M = 76    74
    CLKDIVbits.PLLPOST = 0; 	// N2 = (2 x (PLLPOST + 1)) = 2   0
    CLKDIVbits.PLLPRE = 0;		// N1 = (PLLPRE + 2) = 2        0
*/
    // 70 MIPS (70.00 Mhz) (i.e 8 * (70/4)) Clock Configuration using External Oscillator
	PLLFBD = 68; 			    // M = 70
	CLKDIVbits.PLLPOST = 0;		// N1=2
	CLKDIVbits.PLLPRE = 0;		// N2=2

    
// Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)

    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);
   
    while(OSCCONbits.COSC != 0x03);
    
    while(OSCCONbits.LOCK != 1);	
    
    // Initiate Clock Switch to FRC with PLL (NOSC=0b001)

/*    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);

    while(OSCCONbits.COSC != 0b001);
    
    while(OSCCONbits.LOCK != 1);
 */

    
	#ifdef RTDM
    RTDM_Start();  // Configure the UART module used by RTDM
				   // it also initializes the RTDM variables
	#endif
	//SMCInit(&smc1);
    SetupPorts();
   	SetupControlParameters(); 
	FWInit();
    uGF.Word = 0;                   // clear flags

	#ifdef TORQUEMODE
    uGF.bit.EnTorqueMod = 1;
	#endif

	#ifdef ENVOLTRIPPLE
    uGF.bit.EnVoltRipCo = 1;
    uGF.bit.ADCH0_PotOrVdc = 0;        // Selects POT as CHO Input
	#endif


	#ifdef RTDM
	DMCIFlags.StartStop = 0;
	DMCIFlags.Recorder = 0;
	#endif
   // _LATC10 = 1;        // reset test output
   // DebounceDelay();
   // _LATC10 = 0; 
    if(pinButton1 && pinButton2)
    {
      DebounceDelay();
      if(pinButton1 && pinButton2)
      {
        uGF.bit.FindHallStart = 1;
        while(pinButton1 && pinButton2);  
        DebounceDelay();
      }

    }
    
    while(1)
    {
        uGF.bit.ChangeSpeed = 0;
        // init Mode
        uGF.bit.OpenLoop = 1;           // start in openloop
        trans_counter = 0;                 //initialize transition counter		
        IEC0bits.AD1IE = 0;				// Make sure ADC does not generate
										// interrupts while parameters
										// are being initialized
        
        // init user specified parms and stop on error
        if( SetupParm() )
        {
            // Error
            uGF.bit.RunMotor=0;
            return;
        }
        
        // zero out i sums 
        PIParmD.qdSum = 0;
        PIParmQ.qdSum = 0;
        PIParmW.qdSum = 0;
		OldHallState = HALL_A + ((unsigned int)HALL_B * 2) + ((unsigned int)HALL_C * 4);
        //GetInitHallAngle_Inline();		
        GetInitHallAngleAuto_Inline();
        
        // Enable ADC interrupt and begin main loop timing
        IFS0bits.AD1IF = 0; 
        IEC0bits.AD1IE = 1;

        if(!uGF.bit.RunMotor)
        {	            
            #ifdef DMCI_DEMO
            // Initialize current offset compensation
            while(!DMCIFlags.StartStop)	// wait here until user starts motor
            {							// with DMCI
                #ifdef RTDM
                RTDM_ProcessMsgs();
                #endif
            }
            #else
            // Initialize current offset compensation
            while(!pinButton1)                  //wait here until button 1 is pressed 
            {
                #ifdef RTDM
                RTDM_ProcessMsgs();
                #endif
                if(pinButton2)
                {
                    DebounceDelay();
                    if(pinButton2)
                    {
                        if( !uGF.bit.Btn2Pressed )
                            uGF.bit.Btn2Pressed  = 1;
                    }
                    else
                    {
                        if( uGF.bit.Btn2Pressed )
                        {
                            // Button just released
                            uGF.bit.Btn2Pressed  = 0;
                            uGF.bit.ChangeSpeed = !uGF.bit.ChangeSpeed;
                            uGF.bit.ChangeDir = !uGF.bit.ChangeDir;
                        }
                    }
                }
            }
            while(pinButton1);                  //when button 1 is released 
            #endif

            SetupParm();
            uGF.bit.RunMotor = 1;               //then start motor

                
        }

        // Run the motor
        uGF.bit.ChangeMode = 1;	// Ensure variable initialization when open loop is
								// executed for the first time

        //Run Motor loop
        while(1)
        {

            #ifdef RTDM
            RTDM_ProcessMsgs();			//RTDM process incoming and outgoing messages
            #endif

            // The code that polls the buttons executes every 100 msec.
            if(iADCisrCnt >= BUTPOLLOOPCNT)
            {

                if (uGF.bit.RunMotor == 0)
                    break;

                #ifdef DMCI_DEMO
                if(!DMCIFlags.StartStop)
                {
                    uGF.bit.RunMotor = 0;
                    trans_counter = 0;                 //initialize transition counter

                    break;
                }
                #else

                // Button 1 starts or stops the motor
                if(pinButton1)
                {
                    DebounceDelay();
                    if(pinButton1)
                    {
                        if( !uGF.bit.Btn1Pressed )
                        uGF.bit.Btn1Pressed  = 1;
                    }
                    else
                    {
                        if( uGF.bit.Btn1Pressed )
                        {
                            // Button just released
                            uGF.bit.Btn1Pressed  = 0;
                            // begin stop sequence
                            uGF.bit.RunMotor = 0;
                            trans_counter = 0;                 //initialize transition counter

                            break;
                        }
                    }
                }
				#endif

				//while running button 2 will double/half the speed
                if(pinButton2)
                {
                    DebounceDelay();
                    if(pinButton2)
                    {
                        if( !uGF.bit.Btn2Pressed )
                            uGF.bit.Btn2Pressed  = 1;
                    }
                    else
                    {
                        if( uGF.bit.Btn2Pressed )
                        {
                            // Button just released
                            uGF.bit.Btn2Pressed  = 0;
                       //     uGF.bit.ChangeSpeed = !uGF.bit.ChangeSpeed;
                            uGF.bit.ChangeDir = !uGF.bit.ChangeDir;
                        }
                    }
                }
            }  // end of button polling code              
        }   // End of Run Motor loop
    } // End of Main loop
    // should never get here
    while(1){}
}

//---------------------------------------------------------------------
// Executes one PI itteration for each of the three loops Id,Iq,Speed,

inline void DoControl( void )
{
	CORCONbits.SATA = 1;
	CORCONbits.SATB = 1;
	CORCONbits.ACCSAT = 0;      // 0: 1.31, 1: 9.31 saturation
	#ifndef	DMCI_DEMO
        #ifndef ENVOLTRIPPLE
        	ReadSignedADC0( &ReadADCParm );
        #endif
  	#endif

    #ifdef ENVOLTRIPPLE
        if(uGF.bit.ADCH0_PotOrVdc == 0)
        {
            ReadSignedADC0( &ReadADCParm );
            AD1CHS0bits.CH0SA = 10;         // Selects DCBUS as CHO Input for next conversion
            uGF.bit.ADCH0_PotOrVdc = 1;
        }
        else if(uGF.bit.ADCH0_PotOrVdc == 1)
        {
	        ReadADC0_VDC();
            AD1CHS0bits.CH0SA = 13;         // Selects POT as CHO Input for next conversion
            uGF.bit.ADCH0_PotOrVdc = 0;
        }
    #endif



    // Closed Loop Vector Control

		// Pressing one of the push buttons, speed reference (or torque reference
		// if enabled) will be doubled. This is done to test transient response
		// of the controllers
        /*
        if( ++count == SPEEDDELAY )
        {
            #ifdef DMCI_DEMO
            VelReq = FracMpy(SpeedReference, DQK) + Q15((OMEGA10 + OMEGA1)/2.0);
            #else
               // VelReq = ReadADCParm.qADValue + Q15((OMEGA10 + OMEGA0)/2.0);
            VelReq = ReadADCParm.qADValue + 16000;
            if(VelReq < 0)
                VelReq = 0;
                #endif
                if( uGF.bit.ChangeDir )
                    VelReq = -VelReq;

                if(CtrlParm.qVelRef <= VelReq) // 2x speed
                {
                    CtrlParm.qVelRef += SPEEDDELAY;
                }
                else
                    CtrlParm.qVelRef -= SPEEDDELAY ;
                count = 0;
                }
         */
        
        VelReq = ReadADCParm.qADValue + 16000;  
        if(VelReq < 0)
            VelReq = 0;
        if( uGF.bit.ChangeDir )
            VelReq = -VelReq;        
        CtrlParm.qVelRef = 	VelReq/2;	
        // When it first transition from open to closed loop, this If statement is
        // executed


        // Check to see if new velocity information is available by comparing
        // the number of interrupts per velocity calculation against the
        // number of velocity count samples taken.  If new velocity info
        // is available, calculate the new velocity value and execute
        // the speed control loop.

      //  if(AccumThetaCnt == 0)
        if(uGF.bit.FindHallStart)
        {
            CtrlParm.qVqRef = REFINAMPS(INITIALTORQUE);
        }
        else if (uGF.bit.EnTorqueMod)
            CtrlParm.qVqRef = CtrlParm.qVelRef;        
        else if(SpeedLoopCnt >= 20)
        {
            // Execute the velocity control loop
           // PIParmW.qInMeas = smc1.Omega;
            if(abs(CtrlParm.qVelRef) < Q15(0.05))
                 CtrlParm.qVelRef = 0;   
            PIParmW.qInMeas = Speed;
            PIParmW.qInRef  = CtrlParm.qVelRef;

            CalcPI(&PIParmW);
            CtrlParm.qVqRef = PIParmW.qOut;
            SpeedLoopCnt = 0;
        }
         
        // If the application is running in torque mode, the velocity
        // control loop is bypassed.  The velocity reference value, read
        // from the potentiometer, is used directly as the torque 
        // reference, VqRef. This feature is enabled automatically only if
        // #define TORQUEMODE is defined in UserParms.h. If this is not
        // defined, uGF.bit.EnTorqueMod bit can be set in debug mode to enable
        // torque mode as well.



        // Get Id reference from Field Weakening table. If Field weakening
        // is not needed or user does not want to enable this feature,
        // let NOMINALSPEEDINRPM be equal to FIELDWEAKSPEEDRPM in
        // UserParms.h

        CtrlParm.qVdRef = FieldWeakening(_Q15abs(CtrlParm.qVelRef));
        //CtrlParm.qVdRef = 0;
        // PI control for D
        PIParmD.qInMeas = ParkParm.qId;
        PIParmD.qInRef  = CtrlParm.qVdRef;

        CalcPI(&PIParmD);

        // If voltage ripple compensation flag is set, adjust the output
        // of the D controller depending on measured DC Bus voltage. This
        // feature is enabled automatically only if #define ENVOLTRIPPLE is
        // defined in UserParms.h. If this is not defined, uGF.bit.EnVoltRipCo
        // bit can be set in debug mode to enable voltage ripple compensation.
        //
        // NOTE:
        //
        // If Input power supply has switching frequency noise, for example if a
        // switch mode power supply is used, Voltage Ripple Compensation is not
        // recommended, since it will generate spikes on Vd and Vq, which can
        // potentially make the controllers unstable.
      //  if(uGF.bit.EnVoltRipCo)
      //      ParkParm.qVd = VoltRippleComp(PIParmD.qOut);
      //  else
            ParkParm.qVd = PIParmD.qOut;

        // Vector limitation
        // Vd is not limited
        // Vq is limited so the vector Vs is less than a maximum of 95%.
        // Vs = SQRT(Vd^2 + Vq^2) < 0.95
        // Vq = SQRT(0.95^2 - Vd^2)
        qVdSquared = FracMpy(ParkParm.qVd, ParkParm.qVd);
       	PIParmQ.qOutMax = Q15SQRT(Q15(0.95*0.95) - qVdSquared);
        PIParmQ.qOutMin = -PIParmQ.qOutMax;

        // PI control for Q
        PIParmQ.qInMeas = ParkParm.qIq;
        PIParmQ.qInRef  = CtrlParm.qVqRef;

        CalcPI(&PIParmQ);

        // If voltage ripple compensation flag is set, adjust the output
        // of the Q controller depending on measured DC Bus voltage
     //   if(uGF.bit.EnVoltRipCo)
     //   ParkParm.qVq = VoltRippleComp(PIParmQ.qOut);
     //   else
        ParkParm.qVq = PIParmQ.qOut;

        // Limit, if motor is stalled, stop motor commutation
#ifdef BiDir
#else
        if (smc1.OmegaFltred < 0)
        {
                uGF.bit.RunMotor = 0;
        }
#endif

}


//---------------------------------------------------------------------
// The ADC ISR does speed calculation and executes the vector update loop.
// The ADC sample and conversion is triggered by the PWM period.
// The speed calculation assumes a fixed time interval between calculations.
//---------------------------------------------------------------------

void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void)
{    
    //_LATC10 = 1;
    IFS0bits.AD1IF = 0;        
    SpeedLoopCnt++;
    // Increment count variable that controls execution
    // of display and button functions.
    iADCisrCnt++;
 
    if( uGF.bit.RunMotor )
    {
         
            // Calculate qIa,qIb
            MeasCompCurr();
            
            // Calculate commutation angle using estimator
            //CalculateParkAngle();
            CalculateParkAngleHall();
            // Calculate qId,qIq from qSin,qCos,qIa,qIb
            ClarkePark();
                           
            // Calculate control values
            DoControl();
			
            // Calculate qSin,qCos from qAngle
            SinCos();

            // Calculate qValpha, qVbeta from qSin,qCos,qVd,qVq
            InvPark();    

            // Calculate Vr1,Vr2,Vr3 from qValpha, qVbeta 
            CalcRefVec();

            // Calculate and set PWM duty cycles from Vr1,Vr2,Vr3
            CalcSVGen();
            
    }    

	#ifdef RTDM
    /********************* DMCI Dynamic Data Views  ***************************/
	/********************** RECORDING MOTOR PHASE VALUES ***************/
	if(DMCIFlags.Recorder)
	{
		SnapShotDelayCnt++;
		if(SnapShotDelayCnt == SnapShotDelay)
		{
			SnapShotDelayCnt = 0;
			*PtrRecBuffer1++ 	= SNAP1;
			*PtrRecBuffer2++	= SNAP2;
			*PtrRecBuffer3++	= SNAP3;
			*PtrRecBuffer4++	= SNAP4;
			
			if(PtrRecBuffer4 > RecBuffUpperLimit)
			{
				PtrRecBuffer1 = RecorderBuffer1;
				PtrRecBuffer2 = RecorderBuffer2;
		        PtrRecBuffer3 = RecorderBuffer3;
		        PtrRecBuffer4 = RecorderBuffer4;
		        DMCIFlags.Recorder = 0;
		    }   
		}
	}
	#endif	
	//_LATC10 = 0;
    OldHallState = HALL_A + ((unsigned int)HALL_B * 2) + ((unsigned int)HALL_C * 4);
}

//---------------------------------------------------------------------
bool SetupParm(void)
{
    _NSTDIS = 0;        // nest interrupt
    ReadHall.word = 0;
    // Turn saturation on to insure that overflows will be handled smoothly.
    CORCONbits.SATA  = 1;

    // Setup required parameters
 
// ============= Open Loop ======================
	// Motor End Speed Calculation
	// MotorParm.EndSpeed = ENDSPEEDOPENLOOP * POLEPAIRS * LOOPTIMEINSEC * 65536 * 65536 / 60.0;
	// Then, * 65536 which is a right shift done in "void CalculateParkAngle(void)"
	// ParkParm.qAngle += (int)(Startup_Ramp >> 16);
	MotorParm.EndSpeed = ENDSPEEDOPENLOOP * POLEPAIRS * LOOPTIMEINSEC * 65536 * 65536 / 60.0;
    MotorAlignLockTime = MotorParm.EndSpeed;
	MotorParm.LockTime = LOCKTIME;

// ============= ADC - Measure Current & Pot ======================

    // Scaling constants: Determined by calibration or hardware design.
    ReadADCParm.qK      = DQK;    

    MeasCurrParm.qKa    = DQKA;    
    MeasCurrParm.qKb    = DQKB;   

// ============= SVGen ===============
    // Set PWM period to Loop Time 
    SVGenParm.iPWMPeriod = LOOPINTCY;      

   // Initialise OPAMP/Comparator 
   // OpAmp 1,2,3 for Signal Conditioning Currents & Comparator 4 for Fault Generation

                                // C1IN1+ :IBUS+ ; C1IN1- : IBUS- 
    CM1CON = 0x8C00;		// OpAmp1- OA1OUT is connected to pin,operates as an Op amp,Inverting I/P of Op amp is  C1IN1- pin
                                // C2IN1+ :IA+ ; C2IN1- : IBUS+ 
    CM2CON = 0x8C00;		// OpAmp2- OA2OUT is connected to pin,operates as an Op amp,Inverting I/P of Op amp is  C2IN1- pin
                                // C3IN1+ :IB+ ; C3IN1- : IBUS+ 
    CM3CON = 0x8C00;		// OpAmp3- OA3OUT is connected to pin,operates as an Op amp,Inverting I/P of Op amp is  C3IN1- pin


    CM4CON = 0x8011;            // cmp output non inverted
                                // VIN+ input connects to internal CVREFIN voltage
                                // VIN- input connects to CMP1 (source Ibus) 
 
    CVRCON = 0x008F;            // CVREF = (0.1031)*CVR + 0.825, CVR = 15
    CM4FLTR = 0x000F;           // max filtering


   // ============= Motor PWM ======================

    // Center aligned PWM.
    // Note: The PWM period is set to dLoopInTcy/2 but since it counts up and 
    // and then down => the interrupt flag is set to 1 at zero => actual 
    // interrupt period is dLoopInTcy

	PHASE1 = LOOPINTCY;
	PHASE2 = LOOPINTCY;
	PHASE3 = LOOPINTCY;
	PTPER = 2*LOOPINTCY+1;		//one trigger per PWM period

	PWMCON1 = 0x0204;	// Enable PWM output pins and configure them as 
	PWMCON2 = 0x0204;	// complementary mode
	PWMCON3 = 0x0204;

	//I/O pins controlled by PWM
	IOCON1 = 0xC000;
	IOCON2 = 0xC000;
	IOCON3 = 0xC000;

	DTR1 = 0x0000;
	DTR2 = 0x0000;
	DTR3 = 0x0000;

	ALTDTR1 = DDEADTIME;	// 700ns of dead time
	ALTDTR2 = DDEADTIME;	// 700ns of dead time
	ALTDTR3 = DDEADTIME;	// 700ns of dead time

	//fault disabled	
	FCLCON1 = 0x0003;
	FCLCON2 = 0x0003;
	FCLCON3 = 0x0003;
	
	PTCON2 = 0x0000;	// Divide by 1 to generate PWM

    /* low side turn on errate workaraund */
        PDC1 = MIN_DUTY;   // PDC cannot be init with 0, please check errata
        PDC2 = MIN_DUTY;
        PDC3 = MIN_DUTY;
    
    IPC23bits.PWM1IP = 4;	// PWM Interrupt Priority 4
	IPC23bits.PWM2IP = 4;	// PWM Interrupt Priority 4
	IPC24bits.PWM3IP = 4;	// PWM Interrupt Priority 4

	IFS5bits.PWM1IF = 0;	//clear PWM interrupt flag
	IEC5bits.PWM1IE = 0;	// Disable PWM interrupts

    PTCON = 0x8000;         // Enable PWM for center aligned operation

    // SEVTCMP: Special Event Compare Count Register 
    // Phase of ADC capture set relative to PWM cycle: 0 offset and counting up
	SEVTCMP = 0;

    // Signed fractional (DOUT = sddd dddd dd00 0000)
    AD1CON1bits.FORM = 3;    
	// Timer3 overflow ends sampling and starts conversion
	AD1CON1bits.SSRC = 3;
	AD1CON1bits.SSRCG = 0;
    // Simultaneous Sample Select bit (only applicable when CHPS = 01 or 1x)
    // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
    // Samples CH0 and CH1 simultaneously (when CHPS = 01)
    AD1CON1bits.SIMSAM = 1;  
    // Sampling begins immediately after last conversion completes. 
    // SAMP bit is auto set.
    AD1CON1bits.ASAM = 1;  


    AD1CON2 = 0;
    // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
    AD1CON2bits.CHPS = 2;  


    AD1CON3 = 0;
    // A/D Conversion Clock Select bits = 6 * Tcy
    AD1CON3bits.ADCS = 6;  


     /* ADCHS: ADC Input Channel Select Register */
    AD1CHS0 = 0;
    // CH0 is AN13 for POT
    AD1CHS0bits.CH0SA = 13;

   // CH1 positive input is CMP0, CH2 positive input is CMP1, CH3 positive input is CMP2
    AD1CHS123bits.CH123SA = 1;
  
   /* ADCSSL: ADC Input Scan Select Register */
    AD1CSSL = 0;

    // Turn on A/D module
    AD1CON1bits.ADON = 1;

    #ifdef ENVOLTRIPPLE

        // CH0 is AN10 for VDC
        AD1CHS0bits.CH0SA = 10;
    	// Wait until first conversion takes place to measure offsets.
    	DebounceDelay();
        // Target DC Bus, without sign.
        TargetDCbus = ((SFRAC16)ADC1BUF0 >> 1) + Q15(0.5);

        // CH0 is AN13 for POT
        AD1CHS0bits.CH0SA = 13;
        uGF.bit.ADCH0_PotOrVdc = 0;

    #endif

	// Wait until first conversion takes place to measure offsets.
	DebounceDelay();

    //fault enabled	
    //    FCLCON1 = 0x005C; //Fault enabled Fault SRC - Comparator 4 O/P
//	FCLCON2 = 0x005C; //Fault enabled Fault SRC - Comparator 4 O/P
//	FCLCON3 = 0x005C; //Fault enabled Fault SRC - Comparator 4 O

    // Initial Current offsets
	InitMeasCompCurr( ADC1BUF2, ADC1BUF3 );	 
    
    // Input Capture
    //------------------------------------------------------------------------
    IFS0bits.IC1IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC1IE = 0; // Disable IC1 interrupts
    IPC0bits.IC1IP = 4; // Set module interrupt priority as 3
    IC1CON1 = 0x1C01; // Turn on Input Capture 1 Module
    IC1CON1bits.ICTSEL = 1; // Select timer2
    IC1CON1bits.ICM = 1;    // Rising and falling
    IC1CON2 = 0x0000; //
    IEC0bits.IC1IE = 0;
    //-------------------------------------------------------------------------
    IFS0bits.IC2IF = 0; // Clear the IC2 interrupt status flag
    IEC0bits.IC2IE = 0; // Disable IC2 interrupts
    IPC1bits.IC2IP = 4; // Set module interrupt priority as 3
    IC2CON1bits.ICTSEL = 1; // Select timer2
    IC2CON1bits.ICM = 1;    // Rising and falling
    IC2CON2 = 0x0000; //
    IEC0bits.IC2IE = 0;
     //-------------------------------------------------------------------------
    IFS2bits.IC3IF = 0; // Clear the IC2 interrupt status flag
    IEC2bits.IC3IE = 0; // Disable IC2 interrupts
    IPC9bits.IC3IP = 4; // Set module interrupt priority as 3
    IC3CON1bits.ICTSEL = 1; // Select timer2
    IC3CON1bits.ICM = 1;    // Rising and falling
    IC3CON2 = 0x0000; //
    IEC2bits.IC3IE = 0;
    // Setup Timer2-------------------------------------------------------------
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b11; // Select 1:256 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = 65535; //
    IPC1bits.T2IP = 2; // Set Timer 2 Interrupt Priority Level
    IFS0bits.T2IF = 0; // Clear Timer 1 Interrupt Flag
    IEC0bits.T2IE = 1; // Enable Timer2 interrupt
    T2CONbits.TON = 1; // Start Timer    
    
    //--------------------------------------------------------------------------
    HALL_A_CNIE = 1;
    HALL_B_CNIE = 1;   
    HALL_C_CNIE = 1;
    _CNIP = 6;
    _CNIE = 1;              // enable CNINT
    return False;
}

void SetupControlParameters(void)
{

// ============= PI D Term ===============      
    PIParmD.qKp = DKP;       
    PIParmD.qKi = DKI;              
    PIParmD.qKc = DKC;       
    PIParmD.qOutMax = DOUTMAX;
    PIParmD.qOutMin = -PIParmD.qOutMax;

    InitPI(&PIParmD);

// ============= PI Q Term ===============
    PIParmQ.qKp = QKP;    
    PIParmQ.qKi = QKI;
    PIParmQ.qKc = QKC;
    PIParmQ.qOutMax = QOUTMAX;
    PIParmQ.qOutMin = -PIParmQ.qOutMax;

    InitPI(&PIParmQ);

// ============= PI W Term ===============
    PIParmW.qKp = WKP;       
    PIParmW.qKi = WKI;       
    PIParmW.qKc = WKC;       
    PIParmW.qOutMax = WOUTMAX;   
    PIParmW.qOutMin = -PIParmW.qOutMax;

    InitPI(&PIParmW);
	return;
}

void DebounceDelay(void)
{
	long i;
	for (i = 0;i < 100000;i++)
		;
	return;
}

// NOTE:
//
// If Input power supply has switching frequency noise, for example if a
// switch mode power supply is used, Voltage Ripple Compensation is not
// recommended, since it will generate spikes on Vd and Vq, which can
// potentially make the controllers unstable.



void __attribute__ ((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    int AngleLatch;
    int TMR2Latch;
    AngleLatch = ParkParm.qAngle;
    TMR2Latch = TMR2;
    //_LATC10 = 1;
    _LATC10 = !_LATC10;
    if(uGF.bit.FindHallStart)
    {        
        HallState = 0;
        HallState = HALL_A + ((unsigned int)HALL_B * 2) + ((unsigned int)HALL_C * 4);
        if(OldHallState != HallState)
        {
            FindHallAngle.Pos[HallState] = AngleLatch; 
            GetHallAngleDirAuto_Inline();
            OldHallState = HallState;        
            if(++FindHallAngleCnt >= 12)
            {
                uGF.bit.FindHallStart = 0; 
                FindHallAngleCnt = 0;
                HallAngle = FindHallAngle.Pos[HallState] + 5461 + 16384;
                ParkParm.qAngle = HallAngle;  // 30 degrees shift           
            }            
        }

    }
    else
    {
        ReadHall.word = 0;
        HallState = 0;
        HallState = HALL_A + ((unsigned int)HALL_B * 2) + ((unsigned int)HALL_C * 4);
        if(OldHallState != HallState)
        {
            TMR2 = 0;             
            T2INTCnt = 0;
            Temp16 = IC3BUF;
            GetHallAngleAuto_Inline(); 
            OldHallState = HallState;
            Period = TMR2Latch;
            //Period = FracMpy(Period, Q15(0.05)) + FracMpy(TMR2Latch,Q15(0.95));
   
            PulseCnts++;

            if(Period > 32767)
            {
                Period = 32767; 
                Speed = 0;
                _LATC10 = !_LATC10;  
            }  
            if((Period >= MinPeriod) && (T2INTCnt == 0))
                SpeedCalculation();
            else if(Period < MinPeriod)
            {
                Speed = 32767;
                Period = MinPeriod;
                _LATC10 = !_LATC10;     // Error check
            }            

            if(uGF.bit.Direction != uGF.bit.DirectionAuto)
                Speed = -Speed;            
            }
        
    }


    IFS1bits.CNIF = 0;
    //_LATC10 = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
/* Interrupt Service Routine code goes here */
    IFS0bits.T2IF = 0; //Clear Timer2 interrupt flag
    if(T2INTCnt++ >= 2)
    {
        CapNew = 32767;
         Speed = 0;
         T2INTCnt = 2;       
    }

}
