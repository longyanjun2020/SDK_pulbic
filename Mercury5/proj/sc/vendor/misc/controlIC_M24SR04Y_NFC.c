//==============================================================================
//
//  File        : controlIC_M24SR04Y_NFC.c
//  Description : NFC Control Interface
//  Author      : Sunny Chang 
//  Revision    : 1.0
//
//==============================================================================

#include "os_wrap.h"
#include "config_fw.h"
#include "mmpf_typedef.h"
#include "lib_retina.h"
#include "mmp_err.h"
#include "mmpf_pio.h"
#include "mmpf_i2cm.h"
#include "UartShell.h"
#include "controlIC_M24SR04Y_NFC.h" 

static MMP_I2CM_ATTR gI2cmAttribute_M24SR04Y_NFC = {
	MMP_I2CM0,			//i2cmID
	NFC_DEVICE_ID, 		//ubSlaveAddr
	0, 					//ubRegLen
	8, 					//ubDataLen
	0x2, 				//ubDelayTime
	MMP_FALSE, 			//bDelayWaitEn
	MMP_FALSE, 			//bInputFilterEn
	MMP_FALSE, 			//b10BitModeEn
	MMP_FALSE, 			//bClkStretchEn
	0, 					//ubSlaveAddr1
	0, 					//ubDelayCycle
	2, 					//ubPadNum
	200000 /*200KHZ*/, 	//ulI2cmSpeed
	MMP_TRUE, 			//bOsProtectEn
	NULL, 				//sw_clk_pin
	NULL, 				//sw_data_pin
	MMP_FALSE,			//bRfclModeEn 
	MMP_FALSE,			//bWfclModeEn
	MMP_FALSE,			//bRepeatModeEn
	0                   //ubVifPioMdlId
};

static MMP_I2CM_ATTR gI2cmAttribute_M24SR04Y_NFC_SW = {
	MMP_I2CM_GPIO,		//i2cmID
	NFC_DEVICE_ID << 1, //ubSlaveAddr
	8, 					//ubRegLen
	8, 					//ubDataLen
	0x2, 				//ubDelayTime
	MMP_FALSE, 			//bDelayWaitEn
	MMP_FALSE, 			//bInputFilterEn
	MMP_FALSE, 			//b10BitModeEn
	MMP_FALSE, 			//bClkStretchEn
	0, 					//ubSlaveAddr1
	0, 					//ubDelayCycle
	2, 					//ubPadNum
	200000 /*200KHZ*/, 	//ulI2cmSpeed
	MMP_TRUE, 			//bOsProtectEn
	GPIO_M24SR_I2C_SCL,	//sw_clk_pin
	GPIO_M24SR_I2C_SDA,	//sw_data_pin
	MMP_FALSE,			//bRfclModeEn 
	MMP_FALSE,			//bWfclModeEn
	MMP_FALSE,			//bRepeatModeEn
    0                   //ubVifPioMdlId
};

static C_APDU           sI2CCommand;
static MMP_UBYTE        byI2CDataBuffer[0xFF];
static MMP_UBYTE        uM24SRbuffer[0xFF];
static MMP_UBYTE        uDIDbyte = 0x00;


/**
  * @brief  This function will convert UBYTE to USHORT
  */
void UByteToUShort( MMP_UBYTE* pbySrcData, MMP_USHORT* pusDesData, MMP_USHORT usDataCnt )
{
    MMP_USHORT i;
    for( i=0; i<usDataCnt; i++ )
        pusDesData[i] = (MMP_USHORT)pbySrcData[i] & 0x00FF;
}
/**
  * @brief  This function will convert USHORT to UBYTE
  */
void UShortToUByte( MMP_USHORT* pusSrcData, MMP_UBYTE* pbyDesData, MMP_USHORT usDataCnt )
{
    MMP_USHORT i;
    for( i=0; i<usDataCnt; i++ )
        pbyDesData[i] = (MMP_UBYTE)(pusSrcData[i] & 0x00FF);
}

void M24SR_I2cm_StartSemProtect( void )
{
    MMPF_I2cm_StartSemProtect( &gI2cmAttribute_M24SR04Y_NFC_SW );
    MMPF_I2cm_StartSemProtect( &gI2cmAttribute_M24SR04Y_NFC );
}

void M24SR_I2cm_EndSemProtect( void )
{
    MMPF_I2cm_EndSemProtect( &gI2cmAttribute_M24SR04Y_NFC );
    MMPF_I2cm_EndSemProtect( &gI2cmAttribute_M24SR04Y_NFC_SW );
}


/**
  * @brief  This function polls ACK of I2C device by SW
  * @param  i2cm_attribute: I2C attribute
  * @retval Error status
  */
MMP_ERR M24SR_I2cm_PollI2C_SW( MMP_I2CM_ATTR* i2cm_attribute )
{
    MMP_ERR status = MMP_ERR_NONE;

    M24SR_I2cm_StartSemProtect();

    MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_TRUE );
    MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_TRUE );

    MMPF_I2cm_Initialize( i2cm_attribute );

    MMPF_SwI2cm_Start( i2cm_attribute );    
    MMPF_SwI2cm_WriteData( i2cm_attribute, i2cm_attribute->ubSlaveAddr | NFC_WRITE );
    status = MMPF_SwI2cm_GetACK( i2cm_attribute );
    RTNA_WAIT_US( i2cm_attribute->ubDelayTime );
    MMPF_SwI2cm_Stop( i2cm_attribute );

    MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_FALSE );
    MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_FALSE );

    M24SR_I2cm_EndSemProtect();

    return status;
}

/**
  * @brief  This function will send I2C write command
  * @param  pbyData  : data to write
  * @param  usDataCnt: number of data bytes
  * @param  bSW_I2C  : use SW or HW I2C
  * @retval Error status
  */
MMP_ERR M24SR_I2cm_WriteBurstData( MMP_UBYTE* pbyData, MMP_USHORT usDataCnt, MMP_BOOL bSW_I2C )
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_USHORT i = 0;

#ifdef M24SR_DEBUG_MODE
    printc("M24SR_I2cm_WriteBurstData: ");
    for( i = 0; i < usDataCnt; i++ )
        printc("0x%02x ", pbyData[i]);
    printc("\n\r");
#endif

    if( bSW_I2C )
    {
        MMP_I2CM_ATTR* i2cm_attribute = &gI2cmAttribute_M24SR04Y_NFC_SW;
        
        M24SR_I2cm_StartSemProtect();

        MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_TRUE );
        MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_TRUE );
        
        MMPF_I2cm_Initialize( i2cm_attribute );
        
        MMPF_SwI2cm_Start( i2cm_attribute );    
        MMPF_SwI2cm_WriteData( i2cm_attribute, i2cm_attribute->ubSlaveAddr | NFC_WRITE );
        status = MMPF_SwI2cm_GetACK( i2cm_attribute );

        for( i = 0; i < usDataCnt; i++ )
        {
            MMPF_SwI2cm_WriteData( i2cm_attribute, pbyData[i] );
            status |= MMPF_SwI2cm_GetACK( i2cm_attribute );
        }
        
        RTNA_WAIT_US( i2cm_attribute->ubDelayTime );
        MMPF_SwI2cm_Stop( i2cm_attribute );

        MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_FALSE );
        MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_FALSE );
        
        M24SR_I2cm_EndSemProtect();
    }
    else
    {
        MMP_USHORT pusMMPFI2CDataBuffer[0xFF] = {0}; // For MMPF I2C Data Buffer
        MMP_USHORT usReg = 0;    
        MMP_USHORT *pusCommandData = NULL;
        
        UByteToUShort( pbyData, pusMMPFI2CDataBuffer, usDataCnt );
        
        usReg = pusMMPFI2CDataBuffer[0];    
        pusCommandData = pusMMPFI2CDataBuffer + 1;

        gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 8;

        status = MMPF_I2cm_WriteBurstData( &gI2cmAttribute_M24SR04Y_NFC, usReg, pusCommandData, (MMP_UBYTE)(usDataCnt-1), MMP_TRUE );
    }
    return status;

}

/**
  * @brief  This function will send I2C read command
  * @param  pbyData  : data to write
  * @param  usDataCnt: number of data bytes
  * @param  bSW_I2C  : use SW or HW I2C
  * @retval Error status
  */
MMP_ERR M24SR_I2cm_ReadBurstData(MMP_UBYTE* pbyData, MMP_USHORT usDataCnt, MMP_BOOL bSW_I2C)
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_USHORT i = 0;

    M24DbgPrint("M24SR_I2cm_ReadBurstData: usDataCnt = %d \n\r", usDataCnt);

    if( bSW_I2C )
    {
        MMP_I2CM_ATTR* i2cm_attribute = &gI2cmAttribute_M24SR04Y_NFC_SW;
        
        M24SR_I2cm_StartSemProtect();

        MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_TRUE );
        MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_TRUE );
        
        MMPF_I2cm_Initialize( i2cm_attribute );
        
        MMPF_SwI2cm_Start( i2cm_attribute );    
        MMPF_SwI2cm_WriteData( i2cm_attribute, i2cm_attribute->ubSlaveAddr | NFC_READ );
        status = MMPF_SwI2cm_GetACK( i2cm_attribute );
        RTNA_WAIT_US( i2cm_attribute->ubDelayTime );

        for( i = 0; i < usDataCnt; i++ )
        {
            pbyData[i] = MMPF_SwI2cm_ReadData( i2cm_attribute );
            if (/*(usTempCounter > 1) && */(i != usDataCnt-1)) 
            {
                status |= MMPF_SwI2cm_SendACK( i2cm_attribute );
            }
            RTNA_WAIT_US( i2cm_attribute->ubDelayTime );
        }
	    status |= MMPF_SwI2cm_SendNACK( i2cm_attribute );
        
        RTNA_WAIT_US( i2cm_attribute->ubDelayTime );
        MMPF_SwI2cm_Stop( i2cm_attribute );

        MMPF_PIO_Enable( i2cm_attribute->sw_clk_pin,  MMP_FALSE );
        MMPF_PIO_Enable( i2cm_attribute->sw_data_pin, MMP_FALSE );

        M24SR_I2cm_EndSemProtect();
    }
    else
    {
        MMP_USHORT pusResponseData[0xFF] = {0};

        // Read data from device
        gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 0;
        status = MMPF_I2cm_ReadNoRegMode( &gI2cmAttribute_M24SR04Y_NFC, pusResponseData, (MMP_UBYTE)usDataCnt );

        UShortToUByte( pusResponseData, pbyData, usDataCnt );
    }
    
#ifdef M24SR_DEBUG_MODE
    printc("M24SR_I2cm_ReadBurstData: ");
    for( i = 0; i < usDataCnt; i++ )
        printc("0x%02x ", pbyData[i]);
    printc("\n\r");
#endif

    return status;
}


#define M24SR_POLLING_BY_SW  

/**
  * @brief  This functions will poll M24SR to see if host can send next command
            (Timeout is about 7*50 ms)
  */
static void M24SR_PollI2C( MMP_USHORT usParam )
{
#ifdef M24SR_POLLING_BY_SW
    MMP_ERR ACKstatus = MMP_ERR_NONE;
    MMP_USHORT usCounter = 0;
    MMP_ULONG ulTickCount = 0, ulTickCount2 = 0;
    MMPF_OS_GetTime(&ulTickCount);

    do{
        MMPF_OS_Sleep_MS( 1 );
        ACKstatus = M24SR_I2cm_PollI2C_SW( &gI2cmAttribute_M24SR04Y_NFC_SW );
	} while ( ( ACKstatus != MMP_ERR_NONE ) && ( ++usCounter < 50) );

    if( usCounter > 1 ) // If run more than 2 loops
    {
        MMPF_OS_GetTime(&ulTickCount2);
        printc( FG_RED("M24SR_PollI2C(): Wait = %d ms (Counter = %d)\n\r"), ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC, usCounter);
    }

#else
    // OS sleep. Note: below function can not over 5000 ms.
    // RTNA_WAIT_MS( usParam );
    MMPF_OS_Sleep_MS( usParam );
#endif

}


/**
  * @brief  This function updates the CRC 
  */
static MMP_USHORT M24SR_UpdateCrc (MMP_UBYTE byData, MMP_USHORT *pusCrc)
{
    byData = (byData^(MMP_UBYTE)((*pusCrc) & 0x00FF));
    byData = (byData^(byData<<4));
    *pusCrc = (*pusCrc >> 8)^((MMP_USHORT)byData << 8)^((MMP_USHORT)byData<<3)^((MMP_USHORT)byData>>4);

    return(*pusCrc);
}


/**
  * @brief  This function returns the CRC 16 
  * @param  byData   : pointer on the data used to compute the CRC16
  * @param  byLength : number of byte of the data
  * @retval CRC16 
  */
static MMP_USHORT M24SR_ComputeCrc(uc8 *byData, MMP_UBYTE byLength)
{
    MMP_UBYTE byBlock;
    MMP_USHORT usCrc = 0x6363; // ITU-V.41

    do {
        byBlock = *byData++;
        M24SR_UpdateCrc( byBlock, &usCrc );
    } while ( --byLength );

    return usCrc ;
}


/**  
  * @brief    This function computes the CRC16 residue as defined by CRC ISO/IEC 13239
  * @param    byData  :   input to data 
  * @param    byLength:   Number of bits of DataIn
  * @retval   usStatusCode (SW1&SW2):  CRC16 residue is correct
  * @retval   I2C_CRC_ERROR :  CRC16 residue is false
  */
static MMP_USHORT M24SR_IsCorrectCRC16Residue(uc8 *byData, uc8 byLength)
{
    MMP_USHORT usResCRC = 0;
    MMP_USHORT usStatusCode = 0;

    /* check the CRC16 Residue */
    if ( byLength != 0 )
        usResCRC = M24SR_ComputeCrc(byData, byLength);

    if ( usResCRC == I2C_CRC_SUCCESS )
    {
        //printf("Good CRC!!!! \r\n");
        /* Good CRC, record status from M24SR */
        usStatusCode = ((byData[byLength-UB_STATUS_OFFSET]<<8) & 0xFF00) | (byData[byLength-LB_STATUS_OFFSET] & 0x00FF); 
    }
    else
    {
        usResCRC = M24SR_ComputeCrc(byData, 5);
        if ( usResCRC == I2C_CRC_SUCCESS )
        {
            /* Good CRC, record status from M24SR */
            usStatusCode = ((byData[1]<<8) & 0xFF00) | (byData[2] & 0x00FF); 
        }
        else
        {
            /* Bad CRC */
            printc( FG_RED("Bad CRC!!!! \r\n"));
            return M24SR_I2C_CRC_ERROR;        
        }
    }

    return usStatusCode;
   
}

/**
  * @brief  Initialize the command and response structure 
  * @param  None
  * @retval None
  */
static void M24SR_InitStructure ( void )
{
    /* build the command */
    sI2CCommand.Header.CLA = 0x00;
    sI2CCommand.Header.INS = 0x00;
    /* copy the offset */
    sI2CCommand.Header.P1 = 0x00 ;
    sI2CCommand.Header.P2 = 0x00 ;
    /* copy the number of byte of the data field */
    sI2CCommand.Body.LC = 0x00 ;
    /* copy the number of byte to read */
    sI2CCommand.Body.LE = 0x00 ;
    sI2CCommand.Body.pData = byI2CDataBuffer; 
}

/**
  * @brief  This functions creates an I block command according to the structures CommandStructure and Command. 
  * @param  CommandStructure : structure that contain the structure of the command (if the different field are presnet or not 
  * @param  Command : structue which contains the field of the different parameter
  * @param  NbByte : number of byte of the command
  * @param  pCommand : pointer of the command created
  */
static void M24SR_BuildIBlockCommand ( uc16 CommandStructure, C_APDU Command, MMP_USHORT *NbByte, MMP_UBYTE *pCommand )
{
    MMP_USHORT    uCRC16; 
    static MMP_UBYTE BlockNumber = 0x01;

    (*NbByte) = 0;

    /* add the PCD byte */
    if ((CommandStructure & M24SR_PCB_NEEDED) !=0)
    {
        /* toggle the block number */
        BlockNumber = TOGGLE( BlockNumber );
        /* Add the I block byte */
        pCommand[(*NbByte)++] = 0x02 | BlockNumber; 
    }

    /* add the DID byte */
    if ((BlockNumber & M24SR_DID_NEEDED) !=0)
    {
        /* Add the I block byte */
        pCommand[(*NbByte)++] = uDIDbyte; 
    }

    /* add the Class byte */
    if ((CommandStructure & M24SR_CLA_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Header.CLA ;
    }
    /* add the instruction byte byte */
    if ( (CommandStructure & M24SR_INS_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Header.INS ;
    }
    /* add the Selection Mode byte */
    if ((CommandStructure & M24SR_P1_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Header.P1 ;
    }
    /* add the Selection Mode byte */
    if ((CommandStructure & M24SR_P2_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Header.P2 ;
    }
    /* add Data field lengthbyte */
    if ((CommandStructure & M24SR_LC_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Body.LC ;
    }
    /* add Data field  */
    if ((CommandStructure & M24SR_DATA_NEEDED) !=0)
    {
        memcpy( &(pCommand[(*NbByte)]), Command.Body.pData, Command.Body.LC ) ;
        (*NbByte) += Command.Body.LC ;
    }
    /* add Le field  */
    if ((CommandStructure & M24SR_LE_NEEDED) !=0)
    {
        pCommand[(*NbByte)++] = Command.Body.LE ;
    }
    /* add CRC field  */
    if ((CommandStructure & M24SR_CRC_NEEDED) !=0)
    {
        uCRC16 = M24SR_ComputeCrc (pCommand, (MMP_UBYTE)(*NbByte));
        /* append the CRC16 */
        pCommand [(*NbByte)++] = GETLSB( uCRC16 ) ;
        pCommand [(*NbByte)++] = GETMSB( uCRC16 ) ;
    }

}

#if 0
/**  
  * @brief  	This function return M24SR_STATUS_SUCCESS if the pBuffer is an I-block
  * @param  	pBuffer		:	pointer of the data
  * @retval 	M24SR_STATUS_SUCCESS  :  the data is a I-Block
  * @retval 	M24SR_ERROR_DEFAULT   :  the data is not a I-Block
  */
static MMP_UBYTE IsIBlock (uc8 *pBuffer)
{

	if ((pBuffer[M24SR_OFFSET_PCB] & M24SR_MASK_BLOCK) == M24SR_MASK_IBLOCK)
	{
		return M24SR_STATUS_SUCCESS;
	}
	else 
	{	
		return M24SR_ERROR_DEFAULT;
	}
}

/**  
  * @brief  	This function return M24SR_STATUS_SUCCESS if the pBuffer is an R-block
  * @param  	pBuffer		:	pointer of the data
  * @retval 	M24SR_STATUS_SUCCESS  :  the data is a R-Block
  * @retval 	M24SR_ERROR_DEFAULT   :  the data is not a R-Block
  */
static MMP_UBYTE IsRBlock (uc8 *pBuffer)
{

	if ((pBuffer[M24SR_OFFSET_PCB] & M24SR_MASK_BLOCK) == M24SR_MASK_RBLOCK)
	{
		return M24SR_STATUS_SUCCESS;
	}
	else 
	{	
		return M24SR_ERROR_DEFAULT;
	}
	
}
#endif
    
/**  
  * @brief  	This function return M24SR_STATUS_SUCCESS if the pBuffer is an s-block
  * @param  	pBuffer		:	pointer of the data
  * @retval 	M24SR_STATUS_SUCCESS  :  the data is a S-Block
  * @retval 	M24SR_ERROR_DEFAULT   :  the data is not a S-Block
  */
static MMP_UBYTE IsSBlock (uc8 *pBuffer)
{

	if ((pBuffer[M24SR_OFFSET_PCB] & M24SR_MASK_BLOCK) == M24SR_MASK_SBLOCK)
	{
		return M24SR_STATUS_SUCCESS;
	}
	else 
	{	
		return M24SR_ERROR_DEFAULT;
	}
	
}

/**
  * @brief  This function sends the FWT extension command (S-Block format)
  * @param	FWTbyte : FWT value
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  * @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
static MMP_USHORT M24SR_FWTExtension( MMP_UBYTE FWTbyte )
{
    MMP_UBYTE 	pBuffer[M24SR_STATUSRESPONSE_NBBYTE];
    MMP_USHORT	status = 0; 
    MMP_USHORT	NthByte = 0;
    MMP_USHORT	uCRC16 = 0;
    MMP_USHORT    M24SRstatus = 0; 

    M24DbgPrint("M24SR_FWTExtension: FWTbyte = %d \r\n", FWTbyte);

	/* create the response */
	pBuffer[NthByte++] = 0xF2 ;	
	pBuffer[NthByte++] = FWTbyte ;
	/* compute the CRC */
	uCRC16 = M24SR_ComputeCrc (pBuffer,0x02);
	/* append the CRC16 */
	pBuffer [NthByte++] = GETLSB	(uCRC16 ) ;
	pBuffer [NthByte++] = GETMSB	(uCRC16 ) ;	

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NthByte, I2C_HW_MODE );

    // Wait until write finished!!
    //M24SR_PollI2C();
    M24DbgPrint("Waiting %d ms ........\r\n", FWTbyte * 10);
    MMPF_OS_Sleep_MS( FWTbyte * 10 );

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, M24SR_STATUSRESPONSE_NBBYTE, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_FWTExtension() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, M24SR_STATUSRESPONSE_NBBYTE ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_FWTExtension() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
    
    return M24SRstatus;
    
}

#if 0
/**
  * @brief  This function sends the GetSession command to the M24SR device
  * @param  None
  * @return It reports the status of the operation.
  */
static MMP_ERR M24SR_GetSession ( void )
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_USHORT usReg = M24SR_OPENSESSION;

    M24DbgPrint("M24SR_GetSession \r\n");
    
    gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 8;
    status = MMPF_I2cm_WriteBurstData(&gI2cmAttribute_M24SR04Y_NFC, usReg, NULL, 0);

    if (status != MMP_ERR_NONE) {
        printc( FG_RED("M24SR_GetSession() failed !!! (0x%x) \r\n"), status );
    }

    return status;
}
#endif

/**
  * @brief  This function sends the KillSession command to the M24SR device
  * @param  None
  * @return It reports the status of the operation.
  */
static MMP_ERR M24SR_KillSession ( void )
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_USHORT usReg = M24SR_KILLSESSION;

    M24DbgPrint("M24SR_KillSession \r\n");

    gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 8;
    status = MMPF_I2cm_WriteBurstData(&gI2cmAttribute_M24SR04Y_NFC, usReg, NULL, 0, MMP_TRUE);

    if (status != MMP_ERR_NONE) {
        printc( FG_RED("M24SR_KillSession() failed !!! (0x%x) \r\n"), status );
    }

    return status;
}


/**
  * @brief  This function initialize the M24SR device
  * @retval None 
  */
void M24SR_Init( void )
{
    M24SR_InitStructure();

    M24SR_KillSession();
    
    M24SR_PollI2C(1); // Add this command to avoid coming next command too soon
}

/**
  * @brief  This function sends the Deselect command (S-Block format)
  * @param  None
  * @return It reports the status of the operation.
  */
static MMP_ERR M24SR_Deselect ( void )
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_USHORT usReg = 0xC2;    
    MMP_USHORT usCRC[2] = { 0xE0, 0xB4 };
    MMP_USHORT pusResponseData[3] = {0};

    M24DbgPrint("M24SR_Deselect \r\n");

    gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 8;
    status = MMPF_I2cm_WriteBurstData(&gI2cmAttribute_M24SR04Y_NFC, usReg, usCRC, 2, MMP_TRUE);

    M24SR_PollI2C(1);
    
    gI2cmAttribute_M24SR04Y_NFC.ubRegLen = 0;
    status |= MMPF_I2cm_ReadNoRegMode( &gI2cmAttribute_M24SR04Y_NFC, pusResponseData, 3 );

    //printc("M24SR04Y_NFC_DeSelect(): response usCRC = 0x%x \r\n", (pusResponseData[1]<<8)|(pusResponseData[2]&0xFF));

    if (status != MMP_ERR_NONE) {
        printc( FG_RED("M24SR_Deselect() failed !!! (0x%x) \r\n"), status );
    }
    
    return status;
}


/**
  * @brief  This function sends the SelectApplication command
  * @retval M24SR_ACTION_COMPLETED : the function is succesful. 
  * @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_SelectApplication ( void )
{
    MMP_UBYTE   *pBuffer = uM24SRbuffer;
    MMP_UBYTE   NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_UBYTE   uLc = 0x07;
    MMP_UBYTE   pData[] = {0xD2,0x76,0x00,0x00,0x85,0x01,0x01};
    MMP_UBYTE   uLe = 0x00;
    MMP_USHORT  uP1P2 = 0x0400;
    MMP_USHORT  NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_SelectApplication \r\n");

    /* build the command */
    sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
    sI2CCommand.Header.INS = C_APDU_SELECT_FILE;
    /* copy the offset */
    sI2CCommand.Header.P1 = GETMSB( uP1P2 ) ;
    sI2CCommand.Header.P2 = GETLSB( uP1P2 ) ;
    /* copy the number of byte of the data field */
    sI2CCommand.Body.LC = uLc ;
    /* copy the data */
    memcpy(sI2CCommand.Body.pData, pData, uLc);
    /* copy the number of byte to read */
    sI2CCommand.Body.LE = uLe ;
    /* build the I-Block command */
    M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_SELECTAPPLICATION, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_SelectApplication() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_SelectApplication() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
    
    return M24SRstatus;
}


/**
  * @brief  This function sends the SelectCCFile command
  * @retval M24SR_ACTION_COMPLETED : the function is succesful. 
  * @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  * @retval Status (SW1&SW2) : if operation does not complete for another reason.
  */
MMP_USHORT M24SR_SelectCCfile( void )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE	NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_UBYTE	uLc = 0x02;
    MMP_USHORT	status; 
    MMP_USHORT	uP1P2 = 0x000C;
    MMP_USHORT	uNbFileId = CC_FILE_ID;
    MMP_USHORT	NbByte;
    MMP_USHORT  M24SRstatus = 0; 

    M24DbgPrint("M24SR_SelectCCfile \r\n");
    
	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_SELECT_FILE;
	/* copy the offset */
	sI2CCommand.Header.P1 = GETMSB	(uP1P2 ) ;
	sI2CCommand.Header.P2 = GETLSB	(uP1P2 ) ;
	/* copy the number of byte of the data field */
	sI2CCommand.Body.LC = uLc ;
	/* copy the File Id */
	sI2CCommand.Body.pData[0] = GETMSB	(uNbFileId ) ;
	sI2CCommand.Body.pData[1] = GETLSB	(uNbFileId ) ;
	/* build the I-Block command */
	M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_SELECTCCFILE, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_SelectCCfile() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_SelectCCfile() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
    
    return M24SRstatus;

}


/**
  * @brief  This function sends the SelectSystemFile command
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  * @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_SelectSystemfile( void )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE 	NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_UBYTE	uLc = 0x02;
    MMP_USHORT	status = 0; 
    MMP_USHORT	uP1P2 =0x000C;
    MMP_USHORT	uNbFileId =SYSTEM_FILE_ID;
    MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 

    M24DbgPrint("M24SR_SelectSystemfile \r\n");
	
	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_SELECT_FILE;
	/* copy the offset */
	sI2CCommand.Header.P1 = GETMSB	(uP1P2 ) ;
	sI2CCommand.Header.P2 = GETLSB	(uP1P2 ) ;
	/* copy the number of byte of the data field */
	sI2CCommand.Body.LC = uLc ;
	/* copy the File Id */
	sI2CCommand.Body.pData[0] = GETMSB	(uNbFileId ) ;
	sI2CCommand.Body.pData[1] = GETLSB	(uNbFileId ) ;
	/* build the I-Block command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_SELECTCCFILE, sI2CCommand, &NbByte, pBuffer );
    
    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_SelectSystemfile() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_SelectSystemfile() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
    
    return M24SRstatus;
    
}


/**
  * @brief  This function sends the SelectNDEFfile command
  * @param  NDEFfileId: For M24SR04-Y, it only can be "1".
  * @retval M24SRstatus (SW1&SW2) : Status of the operation to complete.
  * @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_SelectNDEFfile ( uc16 NDEFfileId )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE	NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_UBYTE	uLc = 0x02;
    MMP_USHORT	uP1P2 = 0x000C;
    MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_SelectNDEFfile \r\n");

    /* build the command */
    sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
    sI2CCommand.Header.INS = C_APDU_SELECT_FILE;
    /* copy the offset */
    sI2CCommand.Header.P1 = GETMSB	( uP1P2 ) ;
    sI2CCommand.Header.P2 = GETLSB	( uP1P2 ) ;
    /* copy the number of byte of the data field */
    sI2CCommand.Body.LC = uLc ;
    /* copy the offset */
    sI2CCommand.Body.pData[0] = GETMSB	( NDEFfileId ) ;
    sI2CCommand.Body.pData[1] = GETLSB	( NDEFfileId ) ;
    /* build the I-Block command */
    M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_SELECTNDEFFILE, sI2CCommand, &NbByte , pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_SelectNDEFfile() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_SelectNDEFfile() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }

    return M24SRstatus;
	
}

/**
  * @brief  This function sends a read binary command
  * @param	Offset : first byte to read
  * @param	NbByteToRead : number of byte to read
  * @param	pBufferRead : pointer of the buffer read from the M24SR device
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_ReadBinary( uc16 Offset, uc8 NbByteToRead, MMP_UBYTE *pBufferRead, MMP_BOOL bSW_I2C )
{
	MMP_UBYTE 	*pBuffer = uM24SRbuffer ;
	MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_ReadBinary: Offset = %d, NbByteToRead = %d \r\n", Offset, NbByteToRead);

    if( bSW_I2C )
    {
    
    }
    else if( NbByteToRead > M24SR_RX_DATA_LENGTH )
    {
        MMP_UBYTE   pbyReadBuffer[M24SR_RX_DATA_LENGTH] = {0};
        MMP_UBYTE   byRxByte = NbByteToRead;
        MMP_USHORT  usRxOffset = Offset;
        MMP_UBYTE   usDataOffset = 0;

        while( byRxByte > M24SR_RX_DATA_LENGTH ) 
        {
            M24SRstatus = M24SR_ReadBinary( usRxOffset, M24SR_RX_DATA_LENGTH, pbyReadBuffer, I2C_HW_MODE );
            if( M24SRstatus != M24SR_ACTION_COMPLETED )
            {
                return M24SRstatus;
            }
            memcpy( &pBufferRead[usDataOffset], pbyReadBuffer, M24SR_RX_DATA_LENGTH );
            
            usRxOffset   += M24SR_RX_DATA_LENGTH;
            byRxByte     -= M24SR_RX_DATA_LENGTH;
            usDataOffset += M24SR_RX_DATA_LENGTH;
        }
        M24SRstatus = M24SR_ReadBinary( usRxOffset, byRxByte, pbyReadBuffer, I2C_HW_MODE );
        memcpy( &pBufferRead[usDataOffset], pbyReadBuffer, M24SR_RX_DATA_LENGTH );
        
        return M24SRstatus;
    }

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_READ_BINARY;
	/* copy the offset */
	sI2CCommand.Header.P1 = GETMSB	( Offset ) ;
	sI2CCommand.Header.P2 = GETLSB	( Offset ) ;
	/* copy the number of byte to read */
	sI2CCommand.Body.LE = NbByteToRead ;

	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_READBINARY, sI2CCommand, &NbByte ,pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(20);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead + M24SR_STATUSRESPONSE_NBBYTE, bSW_I2C ); //Add one byte: PCB

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_ReadBinary() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

	M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead + M24SR_STATUSRESPONSE_NBBYTE ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_ReadBinary() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }

	/* retrieve the data without SW1 & SW2 as provided as return value of the function */
	memcpy( pBufferRead ,&pBuffer[1], NbByteToRead );

    return M24SRstatus;
	
}

/**
  * @brief  This function sends a ST read binary command (no error if access is not inside NDEF file)
  * @param	Offset : first byte to read
  * @param	NbByteToRead : number of byte to read
  * @param	pBufferRead : pointer of the buffer read from the M24SR device
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_STReadBinary ( uc16 Offset, uc8 NbByteToRead, MMP_UBYTE *pBufferRead )
{
	MMP_UBYTE 	*pBuffer = uM24SRbuffer ;
	MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_STReadBinary: Offset = %d, NbByteToRead = %d \r\n", Offset, NbByteToRead);
	
	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_ST;
	sI2CCommand.Header.INS = C_APDU_READ_BINARY;
	/* copy the offset */
	sI2CCommand.Header.P1 = GETMSB	(Offset ) ;
	sI2CCommand.Header.P2 = GETLSB	(Offset ) ;
	/* copy the number of byte to read */
	sI2CCommand.Body.LE = NbByteToRead ;

	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_READBINARY, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(20);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead + M24SR_STATUSRESPONSE_NBBYTE, I2C_SW_MODE ); //Add one byte: PCB

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_STReadBinary() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

	M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead + M24SR_STATUSRESPONSE_NBBYTE ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_STReadBinary() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }

	/* retrieve the data without SW1 & SW2 as provided as return value of the function */
	memcpy( pBufferRead ,&pBuffer[1], NbByteToRead );

    return M24SRstatus;

}

/**
  * @brief  This function sends a Update binary command
  * @param	Offset : first byte to read
  * @param	NbByteToWrite : number of byte to write
  * @param	pDataToWrite : pointer of the buffer of data to write to M24SR device
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_UpdateBinary( uc16 Offset ,uc8 NbByteToWrite, uc8 *pDataToWrite, MMP_BOOL bSW_I2C )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_USHORT	status = 0; 
    MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    
    M24DbgPrint("M24SR_UpdateBinary: Offset = %d, NbByteToWrite = %d \r\n", Offset, NbByteToWrite);

    if( bSW_I2C )
    {
    
    }
    else if( NbByteToWrite > M24SR_TX_DATA_LENGTH )
    {
        MMP_UBYTE   pbyWriteBuffer[M24SR_TX_DATA_LENGTH] = {0};
        MMP_UBYTE   byTxByte = NbByteToWrite;
        MMP_USHORT  usTxOffset = Offset;
        MMP_UBYTE   usDataOffset = 0;

        while( byTxByte > M24SR_TX_DATA_LENGTH ) 
        {
            memcpy( pbyWriteBuffer, &pDataToWrite[usDataOffset], M24SR_TX_DATA_LENGTH );
            M24SRstatus = M24SR_UpdateBinary( usTxOffset, M24SR_TX_DATA_LENGTH, pbyWriteBuffer, I2C_HW_MODE );
            if( M24SRstatus != M24SR_ACTION_COMPLETED )
            {
                return M24SRstatus;
            }
            
            usTxOffset   += M24SR_TX_DATA_LENGTH;
            byTxByte     -= M24SR_TX_DATA_LENGTH;
            usDataOffset += M24SR_TX_DATA_LENGTH;
        }
        memcpy( pbyWriteBuffer, &pDataToWrite[usDataOffset], byTxByte );
        M24SRstatus = M24SR_UpdateBinary( usTxOffset, byTxByte, pbyWriteBuffer, I2C_HW_MODE );
        
        return M24SRstatus;
    }

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_UPDATE_BINARY;
	/* copy the offset */
	sI2CCommand.Header.P1 = GETMSB	(Offset ) ;
	sI2CCommand.Header.P2 = GETLSB	(Offset ) ;
	/* copy the number of byte of the data field */
	sI2CCommand.Body.LC = NbByteToWrite ;
	/* copy the File Id */
	memcpy( sI2CCommand.Body.pData, pDataToWrite, NbByteToWrite );

	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_UPDATEBINARY, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, bSW_I2C );

    M24SR_PollI2C(20);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, M24SR_STATUSRESPONSE_NBBYTE, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_UpdateBinary() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

	/* if the response is a Watiting frame extenstion request */ 
	if ( IsSBlock(pBuffer) == M24SR_STATUS_SUCCESS )
	{
		/*check the CRC */ 
		if ( M24SR_IsCorrectCRC16Residue( pBuffer , M24SR_WATINGTIMEEXTRESPONSE_NBBYTE ) != M24SR_I2C_CRC_ERROR )
		{
			/* send the FrameExension response*/ 
            M24DbgPrint( "M24SR_UpdateBinary(): Got S-Block format!!! \r\n" );
		    M24SRstatus = M24SR_FWTExtension ( pBuffer [M24SR_OFFSET_PCB+1] );
		}
	}
	else
	{	
        M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, M24SR_STATUSRESPONSE_NBBYTE ); 
	}

    return M24SRstatus;

}

/**
  * @brief  This function sends the Verify command
  * @param	uPwdId : PasswordId ( 0x0001 : Read NDEF pwd, or 0x0002 : Write NDEF pwd, or 0x0003 : I2C pwd)
  * @param	NbPwdByte : Number of byte ( 0x00 or 0x10)
  * @param	pPwd : pointer on the passwaord
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_Verify( uc16 uPwdId, uc8 NbPwdByte ,uc8 *pPwd )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE   NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_Verify \r\n");

	/*check the parameters */
	if ( uPwdId > 0x0003 )
	{	
		return M24SR_ERROR_PARAMETER;
	}
	if ( (NbPwdByte != 0x00) && (NbPwdByte != 0x10) )
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_VERIFY;
	/* copy the Password Id */
	sI2CCommand.Header.P1 = GETMSB	(uPwdId ) ;
	sI2CCommand.Header.P2 = GETLSB	(uPwdId ) ;
	/* copy the number of byte of the data field */
	sI2CCommand.Body.LC = NbPwdByte ;

	if ( NbPwdByte == 0x10 ) 
	{
		/* copy the password */
		memcpy(sI2CCommand.Body.pData, pPwd, NbPwdByte);
		/* build the I-Block command */
		M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_VERIFYBINARYWITHPWD, sI2CCommand, &NbByte, pBuffer );
	}
	else 
	{
		/* build the I-Block command */
		M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_VERIFYBINARYWOPWD, sI2CCommand, &NbByte, pBuffer );
	}

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_SW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_Verify() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_Verify() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
	
	M24SRstatus = M24SR_IsCorrectCRC16Residue (pBuffer, M24SR_STATUSRESPONSE_NBBYTE); 
	return M24SRstatus;
	
}

/**
  * @brief  This function sends the ChangeReferenceData command
  * @param	uPwdId : PasswordId ( 0x0001 : Read NDEF pwd or 0x0002 : Write NDEF pwd or 0x0003 : I2C pwd)
  * @param	pPwd : pointer on the passwaord
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_ChangeReferenceData( uc16 uPwdId, uc8 *pPwd )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE   NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_USHORT	NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_ChangeReferenceData \r\n");

	/*check the parameters */
	if (uPwdId > 0x0003)
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_CHANGE;
	/* copy the Password Id */
	sI2CCommand.Header.P1 = GETMSB	(uPwdId ) ;
	sI2CCommand.Header.P2 = GETLSB	(uPwdId ) ;
	/* copy the number of byte of the data field */
	sI2CCommand.Body.LC = M24SR_PASSWORD_NBBYTE ;
	/* copy the password */
	memcpy(sI2CCommand.Body.pData, pPwd, M24SR_PASSWORD_NBBYTE);
	/* build the I-Block command */
	M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_CHANGEREFDATA, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_SW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_ChangeReferenceData() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_ChangeReferenceData() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
	
	M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, M24SR_STATUSRESPONSE_NBBYTE ); 
	return M24SRstatus;

}


/**
  * @brief  This function sends the EnableVerificationRequirement command
  * @param	uReadOrWrite : enable the read or write protection ( 0x0001 : Read or 0x0002 : Write  )
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_EnableVerificationRequirement ( uc16 uReadOrWrite  )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE   NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_USHORT  NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_EnableVerificationRequirement \r\n");

	/*check the parameters */
	if ( (uReadOrWrite != 0x0001) && (uReadOrWrite != 0x0002) )
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_ENABLE;
	/* copy the Password Id */
	sI2CCommand.Header.P1 = GETMSB	(uReadOrWrite ) ;
	sI2CCommand.Header.P2 = GETLSB	(uReadOrWrite ) ;
	/* build the I-Block command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_ENABLEVERIFREQ, sI2CCommand, &NbByte, pBuffer);

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_EnableVerificationRequirement() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_EnableVerificationRequirement() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
	
	M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, M24SR_STATUSRESPONSE_NBBYTE ); 
	return M24SRstatus;
}


/**
  * @brief  This function sends the DisableVerificationRequirement command
  * @param	uReadOrWrite : enable the read or write protection ( 0x0001 : Read or 0x0002 : Write  )
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_DisableVerificationRequirement ( uc16 uReadOrWrite  )
{
    MMP_UBYTE 	*pBuffer = uM24SRbuffer;
    MMP_UBYTE   NbByteToRead = M24SR_STATUSRESPONSE_NBBYTE;
    MMP_USHORT  NbByte = 0;
    MMP_USHORT  M24SRstatus = 0; 
    MMP_ERR     status = MMP_ERR_NONE;

    M24DbgPrint("M24SR_DisableVerificationRequirement \r\n");

	/*check the parameters */
	if ( (uReadOrWrite != 0x0001) && (uReadOrWrite != 0x0002) )
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	sI2CCommand.Header.CLA = C_APDU_CLA_DEFAULT;
	sI2CCommand.Header.INS = C_APDU_DISABLE;
	/* copy the Password Id */
	sI2CCommand.Header.P1 = GETMSB	(uReadOrWrite ) ;
	sI2CCommand.Header.P2 = GETLSB	(uReadOrWrite ) ;
	/* build the I-Block command */
	M24SR_BuildIBlockCommand( M24SR_CMDSTRUCT_DISABLEVERIFREQ, sI2CCommand, &NbByte, pBuffer );

    /* send the request */ 
    status = M24SR_I2cm_WriteBurstData( pBuffer, NbByte, I2C_HW_MODE );

    M24SR_PollI2C(1);

    /* read the response */ 
    status |= M24SR_I2cm_ReadBurstData( pBuffer, NbByteToRead, I2C_HW_MODE );

    if ( status != MMP_ERR_NONE ) {
        printc( FG_RED("M24SR_DisableVerificationRequirement() access failed !!! (0x%x) \r\n"), status );
        return M24SR_I2C_ACCESS_ERROR;
    }

    M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, NbByteToRead ); 

    if ( M24SRstatus == M24SR_I2C_CRC_ERROR ) {
        printc( FG_RED("M24SR_DisableVerificationRequirement() CRC error !!! \r\n") );
        return M24SR_I2C_CRC_ERROR;
    }
	
	M24SRstatus = M24SR_IsCorrectCRC16Residue( pBuffer, M24SR_STATUSRESPONSE_NBBYTE ); 
	return M24SRstatus;
}

#if 0

/**
  * @brief  This function sends the EnablePermananentState command
	* @param	uReadOrWrite : enable the read or write protection ( 0x0001 : Read or 0x0002 : Write  )
  * @retval Status (SW1&SW2) : Status of the operation to complete.
	* @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_EnablePermanentState ( uc16 uReadOrWrite  )
{
MMP_UBYTE 	*pBuffer = uM24SRbuffer;
MMP_USHORT	status ; 
MMP_USHORT	NbByte;

	/*check the parameters */
	if ( (uReadOrWrite != 0x0001) && (uReadOrWrite != 0x0002))
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	Command.Header.CLA = C_APDU_CLA_ST;
	Command.Header.INS = C_APDU_ENABLE;
	/* copy the Password Id */
	Command.Header.P1 = GETMSB	(uReadOrWrite ) ;
	Command.Header.P2 = GETLSB	(uReadOrWrite ) ;
	/* build the I²C command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_ENABLEVERIFREQ,  Command, &NbByte , pBuffer);

	/* send the request */ 
	errchk( M24SR_SendI2Ccommand ( NbByte , pBuffer ));
	errchk( M24SR_IsAnswerReady ( ));
	/* read the response */ 
	errchk( M24SR_ReceiveI2Cresponse ( M24SR_STATUSRESPONSE_NBBYTE , pBuffer ));

	status = M24SR_IsCorrectCRC16Residue (pBuffer, M24SR_STATUSRESPONSE_NBBYTE); 
	return status;
	
Error :
	return M24SR_ERROR_I2CTIMEOUT;
}

/**
  * @brief  This function sends the DisablePermanentState command
	* @param	uReadOrWrite : enable the read or write protection ( 0x0001 : Read or 0x0002 : Write  )
  * @retval Status (SW1&SW2) : Status of the operation to complete.
	* @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_DisablePermanentState ( uc16 uReadOrWrite  )
{
MMP_UBYTE 	*pBuffer = uM24SRbuffer;
MMP_USHORT	status ; 
MMP_USHORT	NbByte;

	/*check the parameters */
	if ( (uReadOrWrite != 0x0001) && (uReadOrWrite != 0x0002))
	{	
		return M24SR_ERROR_PARAMETER;
	}

	/* build the command */
	Command.Header.CLA = C_APDU_CLA_ST;
	Command.Header.INS = C_APDU_DISABLE;
	/* copy the Password Id */
	Command.Header.P1 = GETMSB	(uReadOrWrite ) ;
	Command.Header.P2 = GETLSB	(uReadOrWrite ) ;
	/* build the I²C command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_DISABLEVERIFREQ,  Command, &NbByte , pBuffer);

	/* send the request */ 
	errchk( M24SR_SendI2Ccommand ( NbByte , pBuffer ));
	errchk( M24SR_IsAnswerReady ( ));
	/* read the response */ 
	errchk( M24SR_ReceiveI2Cresponse ( M24SR_STATUSRESPONSE_NBBYTE , pBuffer ));

	status = M24SR_IsCorrectCRC16Residue (pBuffer, M24SR_STATUSRESPONSE_NBBYTE); 
	return status;
	
Error :
	return M24SR_ERROR_I2CTIMEOUT;
}

/**
  * @brief  This function generates a interrupt on GPO pin
	* @param	None
  * @retval Status (SW1&SW2) : Status of the operation to complete.
	* @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_SendInterrupt ( void  )
{
	MMP_UBYTE 	*pBuffer = uM24SRbuffer;
	MMP_USHORT	uP1P2 =0x001E;
	MMP_USHORT	status ; 
	MMP_USHORT	NbByte;
	
	status = M24SR_ManageI2CGPO( INTERRUPT);
	
	/* build the command */
	Command.Header.CLA = C_APDU_CLA_ST;
	Command.Header.INS = C_APDU_INTERRUPT;
	/* copy the Password Id */
	Command.Header.P1 = GETMSB	(uP1P2 ) ;
	Command.Header.P2 = GETLSB	(uP1P2 ) ;
	Command.Body.LC = 0x00 ;
	/* build the I²C command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_SENDINTERRUPT,  Command, &NbByte , pBuffer);

	/* send the request */ 
	errchk( M24SR_SendI2Ccommand ( NbByte , pBuffer ));
	errchk( M24SR_IsAnswerReady ( ));
	/* read the response */ 
	errchk( M24SR_ReceiveI2Cresponse ( M24SR_STATUSRESPONSE_NBBYTE , pBuffer ));

	status = M24SR_IsCorrectCRC16Residue (pBuffer, M24SR_STATUSRESPONSE_NBBYTE); 
	return status;
	
Error :
	return M24SR_ERROR_I2CTIMEOUT;
}

/**
  * @brief  This function force GPO pin to low state or high Z
	* @param	uSetOrReset : select if GPO must be low (reset) or HiZ
  * @retval Status (SW1&SW2) : Status of the operation to complete.
	* @retval M24SR_ERROR_I2CTIMEOUT : The I2C timeout occured.
  */
MMP_USHORT M24SR_StateControl ( uc8 uSetOrReset )
{
	MMP_UBYTE 	*pBuffer = uM24SRbuffer;
	MMP_USHORT	uP1P2 =0x001F;
	MMP_USHORT	status ; 
	MMP_USHORT	NbByte;
	
	/*check the parameters */
	if ( (uSetOrReset != 0x01) && (uSetOrReset != 0x00))
	{	
		return M24SR_ERROR_PARAMETER;
	}
	
	status = M24SR_ManageI2CGPO( STATE_CONTROL);
	
	/* build the command */
	Command.Header.CLA = C_APDU_CLA_ST;
	Command.Header.INS = C_APDU_INTERRUPT;
	/* copy the Password Id */
	Command.Header.P1 = GETMSB	(uP1P2 ) ;
	Command.Header.P2 = GETLSB	(uP1P2 ) ;
	Command.Body.LC = 0x01 ;
	/* copy the data */
	memcpy(Command.Body.pData , &uSetOrReset, 0x01 );
	//Command.Body.LE = 0x00 ;
	/* build the I²C command */
	M24SR_BuildIBlockCommand ( M24SR_CMDSTRUCT_GPOSTATE,  Command, &NbByte , pBuffer);

	/* send the request */ 
	errchk( M24SR_SendI2Ccommand ( NbByte , pBuffer ));
	errchk( M24SR_IsAnswerReady ( ));
	/* read the response */ 
	errchk( M24SR_ReceiveI2Cresponse ( M24SR_STATUSRESPONSE_NBBYTE , pBuffer ));

	status = M24SR_IsCorrectCRC16Residue (pBuffer, M24SR_STATUSRESPONSE_NBBYTE); 
	return status;
	
Error :
	return M24SR_ERROR_I2CTIMEOUT;
}

/**
  * @brief  This function configure GPO purpose for I2C session
	* @param	GPO_I2Cconfig: GPO configuration to set
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_ManageI2CGPO( uc8 GPO_I2Cconfig)
{
	MMP_USHORT status;
	MMP_UBYTE GPO_config;
	MMP_UBYTE DefaultPassword[16]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
														0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	if( GPO_I2Cconfig > STATE_CONTROL)
	{	
		return M24SR_ERROR_PARAMETER;
	}
	
	/* we must not be in interrupt mode for I2C synchro as we will change GPO purpose */
	M24SR_SetI2CSynchroMode(M24SR_WAITINGTIME_POLLING);
	
	M24SR_SelectApplication();
	M24SR_SelectSystemfile();
	M24SR_ReadBinary ( 0x0004 , 0x01 , &GPO_config );

  /* Update only GPO purpose for I2C */	
	GPO_config = (GPO_config & 0xF0) | GPO_I2Cconfig;
	M24SR_SelectSystemfile();
	M24SR_Verify( I2C_PWD ,0x10 ,DefaultPassword );
	status = M24SR_UpdateBinary ( 0x0004 ,0x01, &(GPO_config) );
	
	/* if we have set interrupt mode for I2C synchro we can enable interrupt mode */
	if ( GPO_I2Cconfig == I2C_ANSWER_READY)
		M24SR_SetI2CSynchroMode(M24SR_WAITINGTIME_GPO);
	
	return status;
}


/**
  * @brief  This function enable or disable RF communication
	* @param	OnOffChoice: GPO configuration to set
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
void M24SR_RFConfig( uc8 OnOffChoice)
{
	M24SR_RFConfig_Hard(OnOffChoice);
}


#endif


/**
  * @brief  This function configure GPO function in M24SR_GPO_MGMT
  * @param	GPO_function: GPO configuration to set
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_ManageRFGPO( uc8 GPO_function)
{
	MMP_USHORT status;
	MMP_UBYTE  GPO_config;
	MMP_UBYTE  DefaultPassword[16]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    M24DbgPrint("M24SR_ManageRFGPO: 0x%x\r\n", GPO_function);

	if( GPO_function > RF_BUSY )
	{	
		return M24SR_ERROR_PARAMETER;
	}
	
	M24SR_SelectSystemfile();
	M24SR_ReadBinary( 0x0004, 0x01, &GPO_config, I2C_HW_MODE );

    /* Update only GPO purpose for I2C */	
	GPO_config = (GPO_config & 0x0F) | (GPO_function<<4);
	M24SR_SelectSystemfile();
	M24SR_Verify( I2C_PWD, M24SR_PASSWORD_NBBYTE, DefaultPassword );
	status = M24SR_UpdateBinary ( 0x0004, 0x01, &(GPO_config), I2C_HW_MODE );
	
	return status;
}


/**
  * @brief  This fonction activate the need of a password for next read/write access
  * @param	byPasswordType : Read / Write password
  * @param	pCurrentWritePassword : Write password must be prensented to have the right to modify read/write Password
  * @param	pNewPassword : The password that will be requiered for next write access
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_EnablePasswordProtection( uc16 byPasswordType, uc8* pCurrentWritePassword, uc8* pNewPassword )
{
    MMP_USHORT    M24SRstatus = 0; 

	/* check we have the good password */
	if ( M24SR_Verify( WRITE_PWD, M24SR_PASSWORD_NBBYTE, pCurrentWritePassword )== M24SR_PWD_CORRECT )
	{
		/* Set new password */
		M24SRstatus = M24SR_ChangeReferenceData( byPasswordType, pNewPassword );
		M24SRstatus |= M24SR_EnableVerificationRequirement( byPasswordType );
	}
	else /* we don't have the good password */
	{				
		M24SRstatus = M24SR_I2C_FAIL;
	}
	
	return M24SRstatus;
}	

/**
  * @brief  This fonction desactivate the need of a password for next write access
  * @param	byPasswordType : Read / Write password
  * @param	pCurrentWritePassword : Write password must be prensented to have the right to disable it
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_DisablePasswordProtection( uc16 byPasswordType, uc8* pCurrentWritePassword )
{
    MMP_USHORT    M24SRstatus = 0; 

	if ( M24SR_Verify( WRITE_PWD, M24SR_PASSWORD_NBBYTE, pCurrentWritePassword ) == M24SR_PWD_CORRECT )
	{				
		M24SRstatus = M24SR_DisableVerificationRequirement( byPasswordType );
	}
	else
	{
		/* M24SR already lock but password not known */
		M24SRstatus = M24SR_I2C_FAIL;
	}
			
	return M24SRstatus;
}	

/**
  * @brief  This fonction can enable / disable RF access of NFC
  * @param	bDisable : Set it as "MMP_TRUE" to disable
  */
void M24SR_DisableRfAccess( MMP_BOOL bDisable )
{
    //3 Control RF_disable pin to enable / disable RF access

    if( bDisable == MMP_TRUE)
    {
        M24DbgPrint( "Disable RF access \n\r" );
        MMPF_PIO_SetData( GPIO_RF_DISABLE, GPIO_HIGH, MMP_TRUE );  
    }
    else
    {
        M24DbgPrint( "Enable RF access \n\r" );
        MMPF_PIO_SetData( GPIO_RF_DISABLE, GPIO_LOW, MMP_TRUE );  
    }
    
    MMPF_PIO_EnableOutputMode( GPIO_RF_DISABLE, MMP_TRUE, MMP_TRUE );
}	


/**
  * @brief  This fonction will write data to NDEF file in NFC
  * @param	Offset : first byte to read
  * @param	NbByteToWrite : number of bytes to write
  * @param	pBuffeWrite : The pointer to buffer for write
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_WriteNdefFile( uc16 Offset, uc8 NbByteToWrite, uc8 *pBuffeWrite )
{
    MMP_USHORT    M24SRstatus = 0; 

    if( Offset > M24SR_MAX_NDEF_FILE_SIZE || NbByteToWrite > M24SR_MAX_ACCESS_DATA_SIZE )
    {
        printc( FG_RED("M24SR_WriteNdefFile: Wrong access offset (%d) or size (%d) \r\n"), Offset, NbByteToWrite );
        return M24SR_ERROR_PARAMETER;
    }
    
    M24SR_Init(); // Open I2C Session
    
    M24SR_SelectApplication();
    
    M24SR_SelectNDEFfile( 1 );
    
    M24SRstatus = M24SR_UpdateBinary( Offset, NbByteToWrite, pBuffeWrite, I2C_SW_MODE );
    
    if( M24SRstatus != M24SR_ACTION_COMPLETED )
    {
        printc( FG_RED("Write NDEF file failed !!! (0x%x) \r\n"), M24SRstatus );
    }
    
    M24SR_Deselect();

    return M24SRstatus;
    
}


/**
  * @brief  This fonction will read data from NDEF file in NFC
  * @param	Offset : first byte to read
  * @param	NbByteToRead : number of bytes to read
  * @param	pBufferRead : The pointer to buffer for read
  * @param	bForceToRead : Force to read data even beyond NDEF file
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_ReadNdefFile( uc16 Offset, uc8 NbByteToRead, MMP_UBYTE *pBufferRead, MMP_BOOL bForceToRead )
{
    MMP_USHORT    M24SRstatus = 0; 
    
    if( Offset > M24SR_MAX_NDEF_FILE_SIZE || NbByteToRead > M24SR_MAX_ACCESS_DATA_SIZE )
    {
        printc( FG_RED("M24SR_WriteNdefFile: Wrong access offset (%d) or size (%d) \r\n"), Offset, NbByteToRead );
        return M24SR_ERROR_PARAMETER;
    }
    
    M24SR_Init(); // Open I2C Session
    
    M24SR_SelectApplication();
    
    M24SR_SelectNDEFfile( 1 );

    if( bForceToRead == MMP_TRUE )
    {
        M24SRstatus = M24SR_STReadBinary( Offset, NbByteToRead, pBufferRead );
    }
    else
    {
        M24SRstatus = M24SR_ReadBinary( Offset, NbByteToRead, pBufferRead, I2C_SW_MODE );
    }
    
    if( M24SRstatus != M24SR_ACTION_COMPLETED )
    {
        if( M24SRstatus == 0x6982 ) //3 Need a Read Password
        {
            printc( FG_RED("Read NDEF file failed !!! (Need a Read Password) \r\n") );
        }
        else
        {
            printc( FG_RED("Read NDEF file failed !!! (0x%x) \r\n"), M24SRstatus );
        }
    }
    
    M24SR_Deselect();

    return M24SRstatus;
    
}


/**
  * @brief  This fonction will store Write Password in NFC
  * @param	pPassword : The pointer to buffer of password
  * @param	bNewPWD   : Decide to write password to position of new or current password in NFC
  */
void M24SR_SetWritePassword( uc8* pPassword, MMP_BOOL bNewPWD )
{
    MMP_USHORT    M24SRstatus = 0; 
    MMP_USHORT    usPasswordOffset = ( bNewPWD == MMP_TRUE ) ? M24SR_NEW_WRITE_PASSWORD_OFFSET : M24SR_CURRENT_WRITE_PASSWORD_OFFSET;

    M24SRstatus = M24SR_WriteNdefFile( usPasswordOffset, M24SR_PASSWORD_NBBYTE, pPassword );

    if( M24SRstatus != M24SR_ACTION_COMPLETED )
    {
        printc( FG_RED("Failed to set Write Password !!! (0x%x) \r\n"), M24SRstatus );
    }
}

/**
  * @brief  This fonction will read Write Password in NFC
  * @param	pPassword : The pointer to buffer for read
  * @param	bNewPWD   : Decide to read password from position of new or current password in NFC
  */
void M24SR_GetWritePassword( MMP_UBYTE *pBufferRead, MMP_BOOL bNewPWD )
{
    MMP_USHORT    M24SRstatus = 0; 
    MMP_USHORT    usPasswordOffset = ( bNewPWD == MMP_TRUE ) ? M24SR_NEW_WRITE_PASSWORD_OFFSET : M24SR_CURRENT_WRITE_PASSWORD_OFFSET;
    
    M24SRstatus = M24SR_ReadNdefFile( usPasswordOffset, M24SR_PASSWORD_NBBYTE, pBufferRead, MMP_TRUE );

    if( M24SRstatus != M24SR_ACTION_COMPLETED )
    {
        printc( FG_RED("Failed to get Write Password !!! (0x%x) \r\n"), M24SRstatus );
    }
}


/**
  * @brief  This fonction will lock/unlock NDEF file with WRITE password
  * @param	bLockFile : Set it as "MMP_TRUE" to lock NDEF file
  */
void M24SR_LockNdefFile( MMP_BOOL bLockFile )
{
    MMP_USHORT    M24SRstatus = 0; 
    MMP_UBYTE pbyCurrentPWD[M24SR_PASSWORD_NBBYTE] = {0};
    MMP_UBYTE pbyNewPWD[M24SR_PASSWORD_NBBYTE] = {0};
    
    M24SR_Init(); // Open I2C Session
    
    M24SRstatus = M24SR_SelectApplication();
    
    M24SRstatus |= M24SR_SelectNDEFfile( 1 );
    
    if( M24SRstatus != M24SR_ACTION_COMPLETED )
    {
        printc( FG_RED("Select a NDEF file: Fail !!! (0x%x) \r\n"), M24SRstatus );
        M24SR_Deselect();
        return;
    }

    M24SRstatus = M24SR_STReadBinary( M24SR_CURRENT_WRITE_PASSWORD_OFFSET, M24SR_PASSWORD_NBBYTE, pbyCurrentPWD );
    
    if( bLockFile == MMP_FALSE ) //3 Unlock a NDEF file
    {
        // Unlock a NDEF file
        M24SRstatus |= M24SR_DisablePasswordProtection( WRITE_PWD, pbyCurrentPWD );
        
        if( M24SRstatus != M24SR_ACTION_COMPLETED )
        {
            printc( FG_RED("Unlock a NDEF file: Fail !!! (0x%x) \r\n"), M24SRstatus );
        }
    }
    else //3 Lock a NDEF file
    {
        M24SRstatus = M24SR_STReadBinary( M24SR_NEW_WRITE_PASSWORD_OFFSET, M24SR_PASSWORD_NBBYTE, pbyNewPWD );

        // Copy new PWD to current PWD
        M24SRstatus |= M24SR_UpdateBinary( M24SR_CURRENT_WRITE_PASSWORD_OFFSET, M24SR_PASSWORD_NBBYTE, pbyNewPWD, I2C_SW_MODE );
        
        // Lock a NDEF file
        M24SRstatus |= M24SR_EnablePasswordProtection( WRITE_PWD, pbyCurrentPWD, pbyNewPWD );
        
        if( M24SRstatus != M24SR_ACTION_COMPLETED )
        {
            printc( FG_RED("Lock a NDEF file: Fail !!! (0x%x) \r\n"), M24SRstatus );
        }
        else
        {
            MMP_UBYTE i;
            printc( FG_PURPLE("Lock NDEF file: PWD = "));
            for( i=0; i<16; i++ )
                printc("%02x", pbyNewPWD[i]);
            printc("\n\r");
        }
    }
    
    M24SR_Deselect();

}




/**
  * @brief  This fonction will insert SSID and Password into WiFi Handover Select Message
  * @param	
  */
void M24SR_ConfigWiFiSelectMessage( MMP_UBYTE *pbySSID, 
                                             MMP_UBYTE bySSIDLength, 
                                             MMP_UBYTE *pbyPWD, 
                                             MMP_UBYTE byPWDLength, 
                                             MMP_UBYTE *pbyAllMessage,
                                             MMP_USHORT *pusAllMessageLength )
{
    MMP_UBYTE byRecordType[] = { 0x61, 0x70, 0x70, 0x6C, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x2F, 
                               0x76, 0x6E, 0x64, 0x2E, 0x77, 0x66, 0x61, 0x2E, 0x77, 0x73, 0x63 };

    MMP_UBYTE byWpsAttribute1[] = { 0x10, 0x4A, 0x00, 0x01, 0x10, 0x10, 0x0E };
    MMP_UBYTE byWpsAttribute2[] = { 0x10, 0x26, 0x00, 0x01, 0x01, 0x10, 0x45 };
    MMP_UBYTE byWpsAttribute3[] = { 0x10, 0x03, 0x00, 0x02, 0x00, 0x20, 0x10, 0x0F, 0x00, 0x02, 0x00, 0x08, 0x10, 0x27 };
    MMP_UBYTE byWpsAttribute4[] = { 0x10, 0x20, 0x00, 0x06, 0xD8, 0x96, 0x85, 0x33, 0x12, 0x43 };

    MMP_USHORT usCredentialLength = sizeof(byWpsAttribute2) + 1 + (MMP_USHORT)bySSIDLength + sizeof(byWpsAttribute3) + 2 + (MMP_USHORT)byPWDLength + sizeof(byWpsAttribute4);
    MMP_USHORT usPayloadLength = sizeof(byWpsAttribute1) + 2 + usCredentialLength;
    MMP_USHORT usByteCounter = 0;

    pbyAllMessage[0] = 0x92; //NDEF record header: MB = 1, ME = 0, CF = 0, SR = 1, IL = 0, TNF = 2
    pbyAllMessage[1] = sizeof(byRecordType); // Record Type length
    pbyAllMessage[2] = (MMP_UBYTE)usPayloadLength;

    usByteCounter = 3;
    
    // Record Type
    memcpy( &pbyAllMessage[usByteCounter], byRecordType, sizeof(byRecordType) );
    usByteCounter += sizeof(byRecordType);

    // Wps Attribute part 1
    memcpy( &pbyAllMessage[usByteCounter], byWpsAttribute1, sizeof(byWpsAttribute1) );
    usByteCounter += sizeof(byWpsAttribute1);

    // Credential length
    pbyAllMessage[usByteCounter  ] = GETMSB( usCredentialLength ); 
    pbyAllMessage[usByteCounter+1] = GETLSB( usCredentialLength ); 
    usByteCounter += 2;
    
    // Wps Attribute part 2
    memcpy( &pbyAllMessage[usByteCounter], byWpsAttribute2, sizeof(byWpsAttribute2) );
    usByteCounter += sizeof(byWpsAttribute2);

    // SSID
    pbyAllMessage[usByteCounter] = bySSIDLength; // Note: only 1 byte for length
    memcpy( &pbyAllMessage[usByteCounter+1], pbySSID, bySSIDLength );
    usByteCounter += bySSIDLength + 1;
    
    // Wps Attribute part 3
    memcpy( &pbyAllMessage[usByteCounter], byWpsAttribute3, sizeof(byWpsAttribute3) );
    usByteCounter += sizeof(byWpsAttribute3);

    // Network Key Length
    pbyAllMessage[usByteCounter  ] = GETMSB( byPWDLength );
    pbyAllMessage[usByteCounter+1] = GETLSB( byPWDLength );
    memcpy( &pbyAllMessage[usByteCounter+2], pbyPWD, byPWDLength );
    usByteCounter += byPWDLength + 2;
    
    // Wps Attribute part 4
    memcpy( &pbyAllMessage[usByteCounter], byWpsAttribute4, sizeof(byWpsAttribute4) );
    usByteCounter += sizeof(byWpsAttribute4);

    *pusAllMessageLength = usByteCounter;

    #if 0 // For debug
    {
        MMP_USHORT i = 0;
        printc( "M24SR_ConfigWiFiSelectMessage = \n\r" );
        for( i = 0; i < usByteCounter; i ++ )
        {
            if( i % 16 == 15 )
                printc(" 0x%02x\n\r", pbyAllMessage[i]);
            else
                printc(" 0x%02x", pbyAllMessage[i]);
        }
    }
    #endif

}



#define M24SR_ADD_DUMMY_DATA

/**
  * @brief  This fonction will write WiFi data (SSID & Password) to NDEF file in NFC
  * @param	pbySSID & pbyPassword: buffers to store SSID & Password
  * @param	bySSIDLength & byPasswordLength: Length of store SSID & Password
  * @retval Status (SW1&SW2) : Status of the operation to complete.
  */
MMP_USHORT M24SR_WriteWiFiData( MMP_UBYTE *pbySSID, MMP_UBYTE bySSIDLength, MMP_UBYTE *pbyPassword, MMP_UBYTE byPasswordLength )
{
    MMP_USHORT    M24SRstatus = 0; 
    
    // AAR for AIT APP (0x2A bytes)
    MMP_UBYTE pbyAAR[] = { 0x54, 0x0F, 0x18, 0x61, 0x6E, 0x64, 0x72, 0x6F, 0x69, 0x64, 0x2E, 0x63, 0x6F, 0x6D, 0x3A, 0x70, 
                           0x6B, 0x67, 0x74, 0x77, 0x2E, 0x63, 0x6F, 0x6D, 0x2E, 0x61, 0x5F, 0x69, 0x5F, 0x74, 0x2E, 0x49, 
                           0x50, 0x43, 0x61, 0x6D, 0x56, 0x69, 0x65, 0x77, 0x65, 0x72 }; 
    
    MMP_UBYTE pbyDummyData[] = { 0x41, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x54, 0x02, 0x65, 0x6E }; 
    
    MMP_UBYTE pbyAllData[0xFF]  = { 0 };
    MMP_USHORT usAllDataLenght = 0;
    MMP_USHORT usMessageLength = 0;
    MMP_USHORT usDummyDataLength = 0;
    
    M24SR_ConfigWiFiSelectMessage( pbySSID, bySSIDLength, pbyPassword, byPasswordLength, &pbyAllData[2], &usMessageLength);
    
#ifdef M24SR_ADD_DUMMY_DATA
    
    usAllDataLenght = M24SR_MAX_NDEF_FILE_SIZE - 4;
    
    pbyAllData[0] = GETMSB( usAllDataLenght );
    pbyAllData[1] = GETLSB( usAllDataLenght );
    
    pbyAAR[0] = 0x14;  // Remove ME bit
    memcpy( &pbyAllData[2+usMessageLength], pbyAAR, sizeof(pbyAAR) );
    
    usDummyDataLength = M24SR_MAX_NDEF_FILE_SIZE - 4 - usMessageLength - sizeof(pbyAAR) - 7;
    
    printc( FG_BLUE( "NDEF: Add dummy data for NFC power on !! (%d bytes)\n\r"), usDummyDataLength );
    
    pbyDummyData[4] = GETMSB( usDummyDataLength );
    pbyDummyData[5] = GETLSB( usDummyDataLength );
    
    memcpy( &pbyAllData[2+usMessageLength+sizeof(pbyAAR)], pbyDummyData, sizeof(pbyDummyData) );
    
    M24SRstatus = M24SR_WriteNdefFile( 0, 2+usMessageLength+sizeof(pbyAAR)+sizeof(pbyDummyData), (uc8*)pbyAllData );
    
#else
    
    usAllDataLenght = usMessageLength + sizeof(pbyAAR);
    
    pbyAllData[0] = GETMSB( usAllDataLenght );
    pbyAllData[1] = GETLSB( usAllDataLenght );
    
    memcpy( &pbyAllData[2+usMessageLength], pbyAAR, sizeof(pbyAAR) );
    
    M24SRstatus = M24SR_WriteNdefFile( 0, 2+usAllDataLenght, (uc8*)pbyAllData );
    
#endif

    return M24SRstatus;
    
}



/**
  * @brief  This fonction is customized monitor commands
  
    nfc ndef -w -start [Data] // Initialize NDEF data
    nfc ndef -w -add [Data]   // Add NDEF data
    nfc ndef -w -end [Data]   // Finish NDEF data. This command will really send I2C command with all data to NFC
    
    nfc ndef -r               // Read NDEF file
    
    nfc pw -w [Data]          // Set "Write Password" of NFC, [Data] is a 128-bit (16 bytes) string
    nfc pw -r                 // Get "Write Password" of NFC
    
    nfc lock                  // Lock NDEF file by "Write Password"
    nfc unlock                // Unlock NDEF file
    
    nfc rf [Data]             // Control RF_Disable pin, [Data] = 0: Disable RF, [Data] = 1: Enable RF.  
    
    nfc wifi [SSID] [Password]  // Set WiFi SSID & Password
    
    nfc reset                 // Reset NFC. Use it when failed to access NFC.
  */
void MonitorNfcFunc( char* szParam )
{
    #define MAX_UART_STRING_LENGTH 128
    
    char szArgs[MAX_UART_STRING_LENGTH];
    char* szDelimiter = " ";
    char* szToken;

    if ( strlen( szParam ) > MAX_UART_STRING_LENGTH )
    {
        printc( FG_RED( "Too many input argument: %d \n\r"), strlen( szParam ) );
    }

    strncpy( szArgs, szParam, strlen( szParam ) );

    szToken = strtok( szArgs, szDelimiter );

    if ( strcmp( szToken, "ndef" ) == 0 ) //3 Read / Write NDEF file
    {
        szToken = strtok( NULL, szDelimiter );

        if ( strcmp( szToken, "-w" ) == 0 )
        {
#if 1 // To link data if it's over MAX_STRING_LENGTH (128 bytes)

            static MMP_BYTE byData[ M24SR_MAX_NDEF_FILE_SIZE+2 ] = {0};
            static MMP_USHORT usTotalDataBytes = 0;
            MMP_USHORT usDataBytes = 0;
            MMP_USHORT usDataPointer = 0;
            MMP_USHORT i = 0;
            char HexByte[3] = {0};
            MMP_BOOL bLastData = MMP_FALSE;

            szToken = strtok( NULL, szDelimiter );

            if ( strcmp( szToken, "-start" ) == 0 )
            {
                usTotalDataBytes = 0;
            }
            else if ( strcmp( szToken, "-add" ) == 0 )
            {
                if( usTotalDataBytes == 0 )
                {
                    printc( FG_RED( "Please firstly input 'nfc ndef -w -start' \n\r") );
                    return;
                }
            }
            else if ( strcmp( szToken, "-end" ) == 0 )
            {
                bLastData = MMP_TRUE;
            }
            else
            {
                printc( FG_RED( "Wrong argument: %s \n\r"), szToken );
                return;
            }
            
            szToken = strtok( NULL, szDelimiter );
            if ( strlen( szToken )%2 != 0 )
            {
                printc( FG_RED( "Input data string is not a even number !! (%d) \n\r"), strlen( szToken ) );
                return;
            }
            
            usDataBytes = strlen( szToken ) / 2;
            usDataPointer = usTotalDataBytes + 2;
            
            for( i = 0; i < usDataBytes*2; i += 2 )
            {
                // Assemble a digit pair into the hexbyte string
                HexByte[0] = szToken[i];
                HexByte[1] = szToken[i+1];
                byData[ usDataPointer ] = (MMP_BYTE)strtol(HexByte, NULL, 16);
                usDataPointer++;
            }
            
            usTotalDataBytes += usDataBytes;

            if( bLastData == MMP_TRUE )
            {
                if( usTotalDataBytes > M24SR_MAX_ACCESS_DATA_SIZE /*M24SR_MAX_NDEF_FILE_SIZE*/ )
                {
                    printc( FG_RED( "Sorry! Now we do not support to write NDEF file over %d bytes (%d)\n\r"), M24SR_MAX_ACCESS_DATA_SIZE, usTotalDataBytes );
                    return;
                }
                
                // byData[0] & byData[1] is NDEF file length
                byData[0] = GETMSB( usTotalDataBytes );
                byData[1] = GETLSB( usTotalDataBytes );
                    
                M24SR_WriteNdefFile( 0, usTotalDataBytes+2, (uc8*)byData );

                usTotalDataBytes = 0;
            }

#else

            MMP_BYTE byData[ M24SR_MAX_NDEF_FILE_SIZE+2 ] = {0};
            MMP_USHORT usNdefFileSize = 0;
            MMP_USHORT i = 0;
            char HexByte[3] = {0} ;
        
            szToken = strtok( NULL, szDelimiter );
            if ( strlen( szToken )%2 != 0 )
            {
                printc( FG_RED( "Input data string is not a even number !! (%d) \n\r"), strlen( szToken ) );
                return;
            }

            usNdefFileSize = strlen( szToken ) / 2;

            if( usNdefFileSize > M24SR_MAX_ACCESS_DATA_SIZE /*M24SR_MAX_NDEF_FILE_SIZE*/ )
            {
                printc( FG_RED( "Sorry! Now we do not support to write NDEF file over %d bytes (%d)\n\r"), M24SR_MAX_ACCESS_DATA_SIZE, usNdefFileSize );
                return;
            }

            // byData[0] & byData[1] is NDEF file length
            byData[0] = (MMP_BYTE)((usNdefFileSize & 0xFF00) >> 8);
            byData[1] = (MMP_BYTE)( usNdefFileSize & 0x00FF );
                
            for( i = 0; i < usNdefFileSize*2; i += 2 )
            {
                // Assemble a digit pair into the hexbyte string
                HexByte[0] = szToken[i];
                HexByte[1] = szToken[i+1];
                byData[(i/2)+2] = (MMP_BYTE)strtol(HexByte, NULL, 16);
            }

            M24SR_WriteNdefFile( 0, usNdefFileSize+2, (uc8*)byData );
            
#endif       
        }
        else if ( strcmp( szToken, "-r" ) == 0 )
        {
            MMP_UBYTE     pbyReadBuffer[M24SR_MAX_NDEF_FILE_SIZE] = {0};
            MMP_USHORT    i = 0;
            MMP_USHORT    usNdefFileSize = 0;
            MMP_USHORT    M24SRstatus = 0; 

            // Get NDF file size 
            M24SR_ReadNdefFile( 0, 2, pbyReadBuffer, MMP_FALSE );
            usNdefFileSize = (((MMP_USHORT)pbyReadBuffer[0]<<8)& 0xFF00) | ((MMP_USHORT)pbyReadBuffer[1]&0x00FF);

            if( usNdefFileSize > M24SR_MAX_ACCESS_DATA_SIZE /*M24SR_MAX_NDEF_FILE_SIZE*/ )
            {
                printc( FG_RED( "Sorry! Now we do not support to read NDEF file over %d bytes (%d)\n\r"), M24SR_MAX_ACCESS_DATA_SIZE, usNdefFileSize );
                return;
            }

            M24SRstatus = M24SR_ReadNdefFile( 2, usNdefFileSize, pbyReadBuffer, MMP_FALSE );
            
            if( M24SRstatus != M24SR_ACTION_COMPLETED )
            {
                printc( FG_RED("Read NDEF file failed !!! (0x%x) \r\n"), M24SRstatus );
                return;
            }
            
            printc("NDEF file = ");
            for( i=0; i<usNdefFileSize; i++ )
                printc("%02x", pbyReadBuffer[i]);
            printc("\n\r");

        
        }
        else
        {
            printc( FG_RED( "Wrong argument: %s \n\r"), szToken );
        }
    }
    else if ( strcmp( szToken, "pw" ) == 0 ) //3 Set / Get "Write" password
    {
        szToken = strtok( NULL, szDelimiter );

        if ( strcmp( szToken, "-w" ) == 0 )
        {
            MMP_BYTE byData[ M24SR_PASSWORD_NBBYTE ] = {0};
            MMP_BYTE byDataBytes = M24SR_PASSWORD_NBBYTE;
            MMP_BYTE i = 0;
            char HexByte[3] = {0} ;
        
            szToken = strtok( NULL, szDelimiter );
            if ( strlen( szToken ) != (byDataBytes*2) )
            {
                printc( FG_RED( "Input password is not a valid number !! (%s) \n\r"), szToken );
                return;
            }

            for( i = 0; i < byDataBytes*2; i += 2 )
            {
                // Assemble a digit pair into the hexbyte string
                HexByte[0] = szToken[i];
                HexByte[1] = szToken[i+1];
                byData[i/2] = (MMP_BYTE)strtol(HexByte, NULL, 16);
            }

            M24SR_SetWritePassword( (uc8*) byData, MMP_TRUE );
            
        }
        else if ( strcmp( szToken, "-r" ) == 0 )
        {
            MMP_UBYTE     pbyReadBuffer[M24SR_PASSWORD_NBBYTE] = {0};
            MMP_UBYTE     i = 0;

            M24SR_GetWritePassword( pbyReadBuffer, MMP_TRUE );

            printc("Password = ");
            
            for( i=0; i<M24SR_PASSWORD_NBBYTE; i++ )
                printc("%02x", pbyReadBuffer[i]);
            printc("\n\r");
        }
        else
        {
            printc( FG_RED( "Wrong argument: %s \n\r"), szToken );
        }
    }
    else if ( strcmp( szToken, "lock" ) == 0 )
    {
        M24SR_LockNdefFile( MMP_TRUE );
    }
    else if ( strcmp( szToken, "unlock" ) == 0 )
    {
        M24SR_LockNdefFile( MMP_FALSE );
    }
    else if ( strcmp( szToken, "wifi" ) == 0 ) //3 Set  WiFi SSID & password
    {
        //MMP_UBYTE pbySSID[] = { 0x66, 0x6F, 0x78, 0x63, 0x6F, 0x6E, 0x6E, 0x68, 0x68 }; // foxconnhh
        //MMP_UBYTE pbyPassword[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 }; // 1234567890
        MMP_UBYTE pbySSID[0xFF]     = { 0 };
        MMP_UBYTE pbyPassword[0xFF] = { 0 };
        MMP_UBYTE bySSIDLength = 0;
        MMP_UBYTE byPasswordLength = 0;

        // Get SSID
        szToken = strtok( NULL, szDelimiter );
        bySSIDLength = strlen( szToken );
        if ( bySSIDLength == 0 )
        {
            printc( FG_RED( "WiFi: No SSID !!\n\r") );
            return;
        }

        memcpy( pbySSID, szToken, bySSIDLength );
        
        // Get Password
        szToken = strtok( NULL, szDelimiter );
        byPasswordLength = strlen( szToken );
        if ( byPasswordLength == 0 )
        {
            printc( FG_RED( "WiFi: No Password !! \n\r") );
            return;
        }

        memcpy( pbyPassword, szToken, byPasswordLength );

        M24SR_WriteWiFiData( pbySSID, bySSIDLength, pbyPassword, byPasswordLength );

    }
    else if ( strcmp( szToken, "rf" ) == 0 )
    {
        szToken = strtok( NULL, szDelimiter );

        if ( strcmp( szToken, "0" ) == 0 )
        {
            M24SR_DisableRfAccess( MMP_TRUE );
        }
        else if ( strcmp( szToken, "1" ) == 0 )
        {
            M24SR_DisableRfAccess( MMP_FALSE );
        }
        else
        {
            printc( FG_RED( "Wrong argument: %s \n\r"), szToken );
        }
    }
    else if ( strcmp( szToken, "reset" ) == 0 )
    {
        M24SR_Init(); // Open I2C Session
        M24SR_Deselect(); // Close I2C Session
    }
    else if ( strcmp( szToken, "resetdummy" ) == 0 ) //3 Write dummy data into NDEF data area
    {
        MMP_UBYTE     pbyAllData[M24SR_MAX_ACCESS_DATA_SIZE];
        MMP_USHORT    usDataLength = M24SR_MAX_NDEF_FILE_SIZE;
        MMP_USHORT    usWriteBytes = 0;
        MMP_USHORT    usWriteOffset = 0;
        MMP_USHORT    M24SRstatus = 0; 
        MMP_UBYTE     i = 0;
        MMP_UBYTE     byData = 0;
        
        //memset( pbyAllData, 0x5A, M24SR_MAX_ACCESS_DATA_SIZE );
        for( i=1; i<M24SR_MAX_ACCESS_DATA_SIZE; i++ )
        {
            pbyAllData[i] = pbyAllData[i-1] + 3;
        }
        
        M24SR_Init(); // Open I2C Session
        
        M24SR_SelectApplication();
        
        M24SR_SelectNDEFfile( 1 );

        while( usDataLength )
        {
            if( usDataLength > M24SR_MAX_ACCESS_DATA_SIZE )
            {
                usWriteBytes = M24SR_MAX_ACCESS_DATA_SIZE;
            }
            else
            {
                usWriteBytes = usDataLength;
            }
            
            M24SRstatus = M24SR_UpdateBinary( usWriteOffset, (uc8)usWriteBytes, pbyAllData, I2C_SW_MODE );
            
            if( M24SRstatus != M24SR_ACTION_COMPLETED )
            {
                printc( FG_RED("Write NDEF file failed !!! (0x%x) \r\n"), M24SRstatus );
            }
            
            usDataLength  -= usWriteBytes;
            usWriteOffset += usWriteBytes;
        }
        
        M24SR_Deselect();
    }
    else
    {
        printc( FG_RED( "Wrong argument: %s \n\r"), szToken );
    }
        

}


