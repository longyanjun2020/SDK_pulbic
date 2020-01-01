#include "includes_fw.h"
#if BIND_MOTOR_R2A30423NP

#include "mmpf_pio.h"
#include "OS_Wrap.h"

#include "mmp_lib.h"
#include "R2A30423NP.h"
#include "MotorCtrlFunc.h"
#include "mmpf_timingmark.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================
extern void ZoomMotor_Step_ISR(void);
extern void FocusMotor_Step_ISR(void);
//extern void ZoomMotor_PR_ISR(void);
//extern void FocusMotor_PR_ISR(void);
MMP_UBYTE R2A30423NP_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize);
void R2A30423NP_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata);
void R2A30423NP_SetPICallBack(MMP_GPIO_PIN piopin, GpioCallBackFunc *CallBackFunc );


//==============================================================================
//
//                              DEFINITION
//
//==============================================================================
#define   MT_SPI_CLK                   LENS_MOTOR_DRV_MT_SPI_CLK 
#define   MT_SPI_DATA                  LENS_MOTOR_DRV_MT_SPI_DATA
#define   MT_SPI_CS                    LENS_MOTOR_DRV_MT_SPI_CS  
#define   MT_RESET                     LENS_MOTOR_DRV_MT_RESET   
#define   MT_MOB1                      LENS_MOTOR_DRV_MT_MOB1    
#define   MT_MOB2                      LENS_MOTOR_DRV_MT_MOB2    
#define   MT_EXT1                      LENS_MOTOR_DRV_MT_EXT1
#define   MT_EXT2                      LENS_MOTOR_DRV_MT_EXT2
#define   F_OUT                        LENS_MOTOR_DRV_F_OUT      
#define   Z_OUT                        LENS_MOTOR_DRV_Z_OUT
#if (ENABLE_MOTOR_DRV_POWER_CTRL)
#define   MT_POW_EN                    LENS_MOTOR_DRV_MT_POW_EN
#endif


//#define TH_OUT         MMP_GPIO86
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
MMP_UBYTE   ubZoomDir = DRV_FORWARD;
MMP_UBYTE   ubFocusDir = DRV_FORWARD;
MMP_USHORT  ubPowerState = 0;
MMP_UBYTE   ubZoomPower = 0;
MMP_UBYTE   ubFocusPower = 0;
MMP_USHORT  usZoomMaxSpdAcc;
static MMPF_OS_SEMID m_MotorRegSemID = 0xFF;

void R2A30423NP_Wait_ticks(MMP_USHORT usTicks)
{
    while(usTicks--);
}

void R2A30423NP_Reset(void)
{
    MMPF_PIO_SetData(MT_RESET, GPIO_LOW, MMP_TRUE);
    R2A30423NP_Wait_ticks(100);
    MMPF_PIO_SetData(MT_RESET, GPIO_HIGH, MMP_TRUE);
}

void R2A30423NP_GPIO_Setting(void)   
{
    
    MMPF_PIO_EnableOutputMode(MT_SPI_CS, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_LOW, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_SPI_CLK, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_SPI_DATA, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_RESET, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_RESET, GPIO_LOW, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_EXT1, MMP_FALSE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_EXT2, MMP_FALSE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(F_OUT, MMP_FALSE, MMP_TRUE); 
    MMPF_PIO_EnableOutputMode(Z_OUT, MMP_FALSE, MMP_TRUE); 

//  MMPF_PIO_EnableTrigMode(Z_OUT, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
//  MMPF_PIO_EnableTrigMode(Z_OUT, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);

    if ((MT_MOB1 >= MMP_LGPIO0) && (MT_MOB1 <= MMP_LGPIO30))
    {
        MMPF_PIO_EnableOutputMode(MT_MOB1,MMP_FALSE,MMP_TRUE);
    }

    MMPF_PIO_EnableTrigMode(MT_MOB1, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableTrigMode(MT_MOB2, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);

#if 0
    MMPF_PIO_EnableTrigMode(MT_MOB2, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)MOB3_Called, MMP_TRUE);
#endif    

    MMPF_PIO_EnableInterrupt(MT_MOB1, MMP_TRUE, 0, (GpioCallBackFunc *)ZoomMotor_Step_ISR, MMP_TRUE);
#if 1
    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)FocusMotor_Step_ISR, MMP_TRUE);
#else
    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)MOB2_Called, MMP_TRUE);
    
#endif
//  MMPF_PIO_EnableInterrupt(Z_OUT  , MMP_TRUE, 0, (GpioCallBackFunc *)ZoomMotor_PR_ISR, MMP_TRUE);
//  MMPF_PIO_EnableInterrupt(F_OUT  , MMP_TRUE, 0, (GpioCallBackFunc *)FocusMotor_PR_ISR, MMP_TRUE);



}


void R2A30423NP_PowerControl(MMP_UBYTE ubCh, MMP_BOOL bOnOff)
{
    if( MMP_TRUE == bOnOff )
    {
        if( DRV_POWER_CH1_CH2 == ubCh )
        {
            ubPowerState |= DRV_PS12_STATE(DRV_CH12_ON);
        }
        else
        {
            ubPowerState |= DRV_PS34_STATE(DRV_CH34_ON);
        }
    }
    else
    {
        if( DRV_POWER_CH1_CH2 == ubCh )
        {
            ubPowerState &= ~(DRV_PS12_STATE(DRV_CH12_ON));
        //  R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH1_CH2) | DRV_DEC2STOP_CH(DRV_DEC_CH1_CH2));
        }
        else
        {
            ubPowerState &= ~(DRV_PS34_STATE(DRV_CH34_ON));
        //  R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH3_CH4) | DRV_DEC2STOP_CH(DRV_DEC_CH3_CH4));
        }
    }
    if( 0 == (ubPowerState&DRV_PS12_STATE(DRV_CH12_ON)) &&
		0 == (ubPowerState&DRV_PS34_STATE(DRV_CH34_ON)) )
    {
        ubPowerState &= ~(DRV_PS_STATE(DRV_POWER_ON));
    }
    else
    {
        ubPowerState |= DRV_PS_STATE(DRV_POWER_ON);
    }

    R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , ubPowerState );

}


MMP_BOOL R2A30423NP_ZoomDetectPR()
{
    MMP_UBYTE  ubVal = 0;
    
    MMPF_PIO_GetData(Z_OUT, &ubVal);

#if MOTOR_PI_INVERT
    if(ubVal) 
		return MMP_FALSE;
    else
        return MMP_TRUE;
#else
    if(ubVal) 
		return MMP_TRUE;
    else
        return MMP_FALSE;
#endif
}

void R2A30423NP_ZoomEnablePR(MMP_BOOL OnOff)
{
    
    if( MMP_TRUE == OnOff )
    {
        R2A30423NP_RegWrite(REG_COMMON, REGC_PI_SETTING , DRV_PI2_STATE(DRV_PI_OUTPUT_LOW_LEVEL) );
    }
    else
    {
        R2A30423NP_RegWrite(REG_COMMON, REGC_PI_SETTING, DRV_PI2_STATE(DRV_PI_OUTPUT_HIGH_Z) );
    }

}

void R2A30423NP_ZoomEnableExcite(MMP_BOOL OnOff)
{
    MMP_UBYTE ubOn = DRV_OP_DISABLE;

    if( MMP_TRUE == OnOff )
        ubOn = DRV_OP_ENABLE;

    R2A30423NP_RegWrite(REG_CH1_CH2, REG_OP_CTRL_REG   , DRV_EXCITE_EN(ubOn) );

}

MMP_BOOL R2A30423NP_FocusDetectPR(void)
{
    MMP_UBYTE  ubVal = 0;
    
    MMPF_PIO_GetData(F_OUT, &ubVal);

#if MOTOR_PI_INVERT
    if(ubVal) 
		return MMP_FALSE;
    else
        return MMP_TRUE;
#else

    if(ubVal) 
		return MMP_TRUE;
    else
        return MMP_FALSE;
#endif
}


void R2A30423NP_FocusEnablePR(MMP_BOOL OnOff)
{

    if( MMP_TRUE == OnOff )
    {
        R2A30423NP_RegWrite(REG_COMMON, REGC_PI_SETTING , DRV_PI1_STATE(DRV_PI_OUTPUT_LOW_LEVEL) );
    }
    else
    {
        R2A30423NP_RegWrite(REG_COMMON, REGC_PI_SETTING, DRV_PI1_STATE(DRV_PI_OUTPUT_HIGH_Z) );
    }
}

void R2A30423NP_FocusEnableExcite(MMP_BOOL OnOff)
{
    MMP_UBYTE ubOn = DRV_OP_DISABLE;
    
    if( MMP_TRUE == OnOff )
        ubOn = DRV_OP_ENABLE;

    R2A30423NP_RegWrite(REG_CH3_CH4, REG_OP_CTRL_REG   , DRV_EXCITE_EN(ubOn) );
}

void R2A30423NP_SetPICallBack(MMP_GPIO_PIN piopin, GpioCallBackFunc *CallBackFunc )
{
    MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *)CallBackFunc, MMP_TRUE);
}

void R2A30423NP_Initialize(void)
{

    if( 0xFF == ( m_MotorRegSemID = MMPF_OS_CreateSem(1) ))
    {
        printc("motor sem create error!!\n");
        return;
    }

	#if (USE_PWM_AS_MOTOR_OSC) //PWM (clock for Motor)
    AHC_SetPWMforMotor();
    #endif

  #if (ENABLE_MOTOR_DRV_POWER_CTRL)
    MMPF_PIO_EnableOutputMode(MT_POW_EN, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_POW_EN, GPIO_HIGH, MMP_TRUE);
  #endif
#if 0
  // Reset CH1 & CH2 for stepping motor(Zoom)
    R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH1_CH2)      | 
                                                      DRV_DEC2STOP_CH(DRV_DEC_CH1_CH2) |
                                                      DRV_RST_CH(DRV_RST_CH3_CH4)      |  
                                                      DRV_DEC2STOP_CH(DRV_DEC_CH3_CH4)  );

  // Reset CH1 & CH2 Power Setting.
    R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , DRV_PS_STATE(DRV_POWER_OFF)   | 
                                                      DRV_PS12_STATE(DRV_CH12_OFF)  |
                                                      DRV_PS34_STATE(DRV_CH34_OFF) );



#else
  // Reset CH1 & CH2 for stepping motor(Zoom)
    R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH1_CH2) | DRV_DEC2STOP_CH(DRV_DEC_CH1_CH2));

  // Reset CH3 & CH4 for DC motor(Focus)
    R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH3_CH4) | DRV_DEC2STOP_CH(DRV_DEC_CH3_CH4));


#endif
  // Initialize GPIO
    R2A30423NP_GPIO_Setting();

  // Reset CH1 & CH2 Power Setting.
    R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , DRV_PS_STATE(DRV_POWER_OFF) | DRV_PS12_STATE(DRV_CH12_OFF));

  // Reset CH3 & CH4 Power Setting.
    R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , DRV_PS_STATE(DRV_POWER_OFF) | DRV_PS34_STATE(DRV_CH34_OFF));

    R2A30423NP_Reset();

  // Enable Zoom/Focus PR
    R2A30423NP_RegWrite(REG_COMMON, REGC_PI_SETTING , DRV_PI1_STATE(DRV_PI_OUTPUT_HIGH_Z) | 
                                                      DRV_PI2_STATE(DRV_PI_OUTPUT_HIGH_Z) );


    R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , DRV_PS_STATE(DRV_POWER_ON)| DRV_PS12_STATE(DRV_CH12_ON) | DRV_PS34_STATE(DRV_CH34_ON));

    MMPF_OS_Sleep(300);
}

void R2A30423NP_ZoomPowerOn(MMP_BOOL OnOFF)
{
#if 0
    if( MMP_TRUE == OnOFF )
    {
        ubZoomPower = 1;
        ubPowerState |= DRV_PS_STATE(DRV_POWER_ON) | DRV_PS12_STATE(DRV_CH_ON);

      //Reset CH1 & CH2 Power Setting.
        R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , ubPowerState );
    }
    else
    {
        if(1 == ubFocusPower)
            ubPowerState = DRV_PS_STATE(DRV_POWER_ON) | DRV_PS34_STATE(DRV_CH_ON);
        else
            ubPowerState = DRV_PS_STATE(DRV_POWER_OFF) | DRV_PS12_STATE(DRV_CH_OFF) |DRV_PS34_STATE(DRV_CH_OFF);

        ubZoomPower = 0;
      //Reset CH1 & CH2 Power Setting.
        R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , ubPowerState );
      //Reset CH1 & CH2 for stepping motor(Zoom)
        R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH1_CH2) | DRV_DEC2STOP_CH(DRV_DEC_CH1_CH2));
    }
#else
//    if( MMP_FALSE == OnOFF)
//      R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH1_CH2));

    R2A30423NP_PowerControl(DRV_POWER_CH1_CH2, OnOFF );


#endif
}

MMP_USHORT R2A30423NP_ZoomMoveStepsEsti(MMP_ULONG ulDrivingClkHz, MMP_ULONG ulMoveTime)  // 
{     
	static MMP_ULONG ulMaxPosiDiff = 0;
	static MMP_USHORT usZoomMaxSpdAcc_saved = 0;
	static MMP_ULONG ulMoveTime_saved = 0;

	// condition changed, need to re-calculate
	if((usZoomMaxSpdAcc_saved!= usZoomMaxSpdAcc) || (ulMoveTime_saved != ulMoveTime))
	{
		// ulMoveTime is mini second in us16.16 format
		ulMaxPosiDiff = ((MMP_ULONG)usZoomMaxSpdAcc<<(6+16))/ulMoveTime;
		ulMaxPosiDiff = ulDrivingClkHz / ulMaxPosiDiff/1000;

		usZoomMaxSpdAcc_saved = usZoomMaxSpdAcc;
		ulMoveTime_saved = ulMoveTime;
	}

	return (MMP_USHORT)ulMaxPosiDiff;
}

void R2A30423NP_ZoomSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{
    MMP_ULONG Drv_step = 0;


    Drv_step = ulStep*32;

    ubZoomDir = ubDirection;

    if( DRV_SPEED_CONST == ubMode )
    {
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_DRV_CTRL      , DRV_DIR(ubDirection)           | 
                                                             DRV_MODE(DRV_MICRO_STEP)       | 
                                                             DRV_CTRL(DRV_CTRL_NO_ACC_DEC)  );   //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE1      , DRV_nPULSE1(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE2      , DRV_nPULSE2(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_nPULSE_RANGE  , DRV_PULSE_RATE(DRV_PULSE_RATE_RANGE_4) |
                                                             DRV_uSTEP_nSTEP(DRV_nSTEP_256) );
       
		usZoomMaxSpdAcc = 512;
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE    , PULSE_RATE(usZoomMaxSpdAcc) );

    }
    else if ( DRV_SPEED_ACC_LOW == ubMode )
    {
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_DRV_CTRL      , DRV_DIR(ubDirection)           | 
                                                             DRV_MODE(DRV_MICRO_STEP)       | 
                                                             DRV_CTRL(DRV_CTRL_ACC_DEC)     );  //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE1      , DRV_nPULSE1(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE2      , DRV_nPULSE2(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_nPULSE_RANGE  , DRV_PULSE_RATE(DRV_PULSE_RATE_RANGE_4) |
                                                             DRV_uSTEP_nSTEP(DRV_nSTEP_256)  );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(64) );
#if(DRIVE_MOTOR_CLK_HZ == 5000000) // 5MHz clock
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE    , PULSE_RATE(1023) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE1   , PULSE_RATE(768) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE3   , PULSE_RATE(256) );
		usZoomMaxSpdAcc = 225;
#else // 6MMHz clock
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE    , PULSE_RATE(1023) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE1   , PULSE_RATE(922) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE2   , PULSE_RATE(461) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE3   , PULSE_RATE(307) );
		usZoomMaxSpdAcc = 270;
#endif
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE4   , PULSE_RATE(usZoomMaxSpdAcc) );

    }
    else if ( DRV_SPEED_ACC_MID == ubMode )
    {
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_DRV_CTRL      , DRV_DIR(ubDirection)           | 
                                                             DRV_MODE(DRV_MICRO_STEP)       | 
                                                             DRV_CTRL(DRV_CTRL_ACC_DEC)     );  //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE1      , DRV_nPULSE1(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_N_PULSE2      , DRV_nPULSE2(Drv_step) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_nPULSE_RANGE  , DRV_PULSE_RATE(DRV_PULSE_RATE_RANGE_4) |
                                                             DRV_uSTEP_nSTEP(DRV_nSTEP_256)  );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(64) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE    , PULSE_RATE(1023) );

        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE1   , PULSE_RATE(768) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE3   , PULSE_RATE(128) );
		usZoomMaxSpdAcc = 100;
        R2A30423NP_RegWrite(REG_CH1_CH2, REG_PULSE_RATE4   , PULSE_RATE(usZoomMaxSpdAcc) );
    }
    else if( DRV_SPEED_ACC_HIGH == ubMode )
    {

    }

    ubZoomDir = ubDirection;

}

void R2A30423NP_ZoomDrive()
{
    
    R2A30423NP_RegWrite(REG_CH1_CH2, REG_DRV_VOL_AMP   , DRV_VOL_AMP_CH1_2(DRV_AMP_VOL_36) );

    R2A30423NP_RegWrite(REG_COMMON , REGC_EXT_SETTING  , DRV_EXT_OUTPUT_SEL(DRV_EXT_HIGH_IN_EXCITE) |
                                                         DRV_OUTPUT_PIN_SEL(DRV_EXT_PIN_MOB)             |
                                                         DRV_EXT1_SEL(DRV_EXT1_PIN_EXT12)                 );

//  R2A30423NP_ZoomPowerOn(MMP_TRUE);

    R2A30423NP_RegWrite(REG_CH1_CH2, REG_OP_CTRL_REG   , DRV_OP_EN(DRV_OP_ENABLE)    |
                                                         DRV_EXCITE_EN(DRV_OP_ENABLE) );

}

void R2A30423NP_ZoomStop()
{
    R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_DEC2STOP_CH(DRV_DEC_CH1_CH2));
}

MMP_BOOL R2A30423NP_ZoomExciteState(void)
{
    MMP_UBYTE  ubVal = 0;

    MMPF_PIO_GetData(MT_EXT1,&ubVal);

    if(ubVal) 
        return MMP_TRUE;
    else
        return MMP_FALSE;
}

MMP_UBYTE R2A30423NP_ZoomDirection(void)
{
    return ubZoomDir;
}

void R2A30423NP_FocusPowerOn(MMP_BOOL OnOFF)
{
#if 0
    if( MMP_TRUE == OnOFF )
    {
        ubFocusPower = 1;
        ubPowerState |= DRV_PS_STATE(DRV_POWER_ON) | DRV_PS34_STATE(DRV_CH_ON);
        R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , ubPowerState );
    }
    else
    {

        if(1 == ubZoomPower)
            ubPowerState = DRV_PS_STATE(DRV_POWER_ON) | DRV_PS12_STATE(DRV_CH_ON);
        else
            ubPowerState = DRV_PS_STATE(DRV_POWER_OFF) | DRV_PS12_STATE(DRV_CH_OFF) |DRV_PS34_STATE(DRV_CH_OFF);


        ubFocusPower = 0;
      //Reset CH1 & CH2 for stepping motor(Zoom)
        R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH3_CH4) | DRV_DEC2STOP_CH(DRV_DEC_CH3_CH4));
      //Reset CH1 & CH2 Power Setting.
        R2A30423NP_RegWrite(REG_COMMON, REGC_PS_SETTING , ubPowerState);
    }
#else
    if( MMP_FALSE == OnOFF)
        R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH(DRV_RST_CH3_CH4));

    R2A30423NP_PowerControl(DRV_POWER_CH3_CH4, OnOFF );


#endif
}

void R2A30423NP_FocusSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{
    MMP_ULONG Drv_step = 0;
    MMP_USHORT PulseRate0, PulseRate1, PulseRate2, PulseRate3, PulseRate4;

    Drv_step = ulStep*32;

    ubFocusDir = ubDirection;

    if( DRV_SPEED_CONST == ubMode )
    {
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_DRV_CTRL      , DRV_DIR(ubDirection)        | 
                                                             DRV_MODE(DRV_MICRO_STEP)    | 
                                                             DRV_CTRL(DRV_CTRL_NO_ACC_DEC) ); //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_N_PULSE1      , DRV_nPULSE1(Drv_step) );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_N_PULSE2      , DRV_nPULSE2(Drv_step) );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_nPULSE_RANGE  , DRV_PULSE_RATE(DRV_PULSE_RATE_RANGE_2) |
                                                             DRV_uSTEP_nSTEP(DRV_nSTEP_256)  );

//      R2A30423NP_RegWrite(REG_CH3_CH4, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(128) );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE    , PULSE_RATE(1000) );
#if 0
      // Set Pulse rate reg 1 ~ 4
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE1   , PULSE_RATE(512) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE3   , PULSE_RATE(384) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE4   , PULSE_RATE(384) );
#endif
    }
    else if ( DRV_SPEED_ACC_LOW  == ubMode  ||
              DRV_SPEED_ACC_MID  == ubMode  ||
              DRV_SPEED_ACC_HIGH == ubMode  )
    {
        if( DRV_SPEED_ACC_LOW  == ubMode )
        {
            PulseRate0 = 976;
            PulseRate1 = 500;
            PulseRate2 = 384;
            PulseRate3 = 200;
            PulseRate4 = 173;

        }
        else if( DRV_SPEED_ACC_MID  == ubMode )
        {
            PulseRate0 = 976;
            PulseRate1 = 500;
            PulseRate2 = 384;
            PulseRate3 = 192;
            PulseRate4 = 130;
        }
        else if( DRV_SPEED_ACC_HIGH  == ubMode )
        {
            PulseRate0 = 400; // 976;  
            PulseRate1 = 200; // 500;
            PulseRate2 = 128; // 256;
            PulseRate3 = 100; // 128;
            PulseRate4 = 100;
        }
        else
        {
        }

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_DRV_CTRL      , DRV_DIR(ubDirection)           | 
                                                             DRV_MODE(DRV_MICRO_STEP)       | 
                                                             DRV_CTRL(DRV_CTRL_ACC_DEC)     );  //|
                                                         //  DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_N_PULSE1      , DRV_nPULSE1(Drv_step) );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_N_PULSE2      , DRV_nPULSE2(Drv_step) );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_nPULSE_RANGE  , DRV_PULSE_RATE(DRV_PULSE_RATE_RANGE_2) |
                                                             DRV_uSTEP_nSTEP(DRV_nSTEP_256)  );

        R2A30423NP_RegWrite(REG_CH3_CH4, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(32) );
        
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE    , PULSE_RATE(PulseRate0) );

      // Set Pulse rate reg 1 ~ 4
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE1   , PULSE_RATE(PulseRate1) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE2   , PULSE_RATE(PulseRate2) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE3   , PULSE_RATE(PulseRate3) );
        R2A30423NP_RegWrite(REG_CH3_CH4, REG_PULSE_RATE4   , PULSE_RATE(PulseRate4) );
    }

}

void R2A30423NP_FocusDrive()
{

    R2A30423NP_RegWrite(REG_CH3_CH4, REG_DRV_VOL_AMP   , DRV_VOL_AMP_CH1_2(DRV_AMP_VOL_36) );

    R2A30423NP_RegWrite(REG_COMMON , REGC_EXT_SETTING  , DRV_EXT_OUTPUT_SEL(DRV_EXT_HIGH_IN_EXCITE) |
                                                         DRV_OUTPUT_PIN_SEL(DRV_EXT_PIN_MOB)             |
                                                         DRV_EXT2_SEL(DRV_EXT2_PIN_EXT34)                 );

//  R2A30423NP_FocusPowerOn(MMP_TRUE);

    R2A30423NP_RegWrite(REG_CH3_CH4, REG_OP_CTRL_REG   , DRV_OP_EN(DRV_OP_ENABLE)    |
                                                         DRV_EXCITE_EN(DRV_OP_ENABLE) );
}

void R2A30423NP_FocusStop()
{
    R2A30423NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_DEC2STOP_CH(DRV_DEC_CH3_CH4));
}

MMP_BOOL R2A30423NP_FocusExciteState()
{
    MMP_UBYTE  ubVal = 0;

    MMPF_PIO_GetData(MT_EXT2,&ubVal);

    if(ubVal) 
        return MMP_TRUE;
    else
        return MMP_FALSE;
}

MMP_UBYTE R2A30423NP_FocusDirection(void)
{
    return ubFocusDir;
}

void R2A30423NP_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata)
{
    MMP_UBYTE  i;
    MMP_USHORT data; 


    if(MMPF_OS_AcquireSem(m_MotorRegSemID, 0) != MMPF_OS_ERR_NONE) {
		return;
	}

    data = ch << 14 | reg << 10 | wdata;
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_HIGH, MMP_TRUE);

    R2A30423NP_Wait_ticks(1);

    for(i = 0; i < 16; i++)
    {
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_LOW, MMP_TRUE);
        R2A30423NP_Wait_ticks(1);

        if(((data >> (15 - i)) & 0x01)) 
            MMPF_PIO_SetData(MT_SPI_DATA, GPIO_HIGH, MMP_TRUE);
        else
            MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
        
        R2A30423NP_Wait_ticks(1);
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    }
    R2A30423NP_Wait_ticks(1);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_LOW, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);

    MMPF_OS_ReleaseSem(m_MotorRegSemID);

}

MMP_UBYTE R2A30423NP_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize)
{
    MMP_UBYTE  i;
    MMP_USHORT sdata;
    MMP_UBYTE  rdata = 0;
    MMP_UBYTE  serial_data; 


    if(MMPF_OS_AcquireSem(m_MotorRegSemID, 0) != MMPF_OS_ERR_NONE) {
		return 0;
	}

    sdata = ch << 14 | reg << 10 | ch_rd << 8;

    MMPF_PIO_SetData(MT_SPI_CS, GPIO_HIGH, MMP_TRUE);
    R2A30423NP_Wait_ticks(1);

    for(i = 0; i < 16; i++)
    {
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_LOW, MMP_TRUE);
        R2A30423NP_Wait_ticks(1);

        if( i < 8)
        {
            if(((sdata >> (15 - i)) & 0x01)) 
                MMPF_PIO_SetData(MT_SPI_DATA, GPIO_HIGH, MMP_TRUE);
            else
                MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
        }
        else
        {
            if( (15 - i) < BitSize )
            {
                MMPF_PIO_GetData(MT_SPI_DATA, &serial_data);
    
                if( 1 == serial_data )
                rdata |= ( serial_data << (15 - i));
            }
        }

        R2A30423NP_Wait_ticks(1);
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    }
    
    R2A30423NP_Wait_ticks(1);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_LOW, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);

    MMPF_OS_ReleaseSem(m_MotorRegSemID);

    return rdata;
}

void R2A30423NP_IrisDirection(MMP_UBYTE ubDirection)
{
}

void R2A30423NP_TriggerMechanicalShutter(MMP_BOOL bTrigger)
{

}

void R2A30423NP_MechanicalShutterDirection(MMP_BOOL bForwardReverse)
{

}

#if 1
MotorCtrl_FUNCTIION Motor_R2A30423NP_Func =
{
    R2A30423NP_Initialize,
    R2A30423NP_ZoomPowerOn,
    R2A30423NP_ZoomSetParam,
    R2A30423NP_ZoomDrive,
    R2A30423NP_ZoomStop,
    R2A30423NP_ZoomEnablePR,
    R2A30423NP_ZoomEnableExcite,
    R2A30423NP_ZoomMoveStepsEsti,
    R2A30423NP_ZoomDetectPR,
    R2A30423NP_ZoomExciteState,
    R2A30423NP_ZoomDirection,
    R2A30423NP_FocusPowerOn,
    R2A30423NP_FocusSetParam,
    R2A30423NP_FocusDrive,
    R2A30423NP_FocusStop,
    R2A30423NP_FocusEnablePR,
    R2A30423NP_FocusEnableExcite,
    R2A30423NP_FocusDetectPR,
    R2A30423NP_FocusExciteState,
    R2A30423NP_FocusDirection,
    R2A30423NP_RegWrite,
    R2A30423NP_RegRead,
    R2A30423NP_IrisDirection,
    R2A30423NP_TriggerMechanicalShutter,
    R2A30423NP_MechanicalShutterDirection              
};

MotorCtrl_FUNCTIION  *MotorControlModule = &Motor_R2A30423NP_Func;
#endif
#endif
