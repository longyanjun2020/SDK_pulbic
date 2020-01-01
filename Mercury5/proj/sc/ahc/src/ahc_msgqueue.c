//==============================================================================
//
//  File        : AHC_msgqueue.c
//  Description : AHC message queue function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_msgqueue.h"
#include "ahc_os.h"
#include "AHC_Config_SDK.h"
#include "ahc_parameter.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

AHC_OS_MQID                     AHC_MSG_QId = MMPF_OS_ERR_CREATE_MSG_Q;
void                            *AHC_MsgQueue[AHC_MSG_QUEUE_SIZE] = {0};
AHC_OS_MQID                     AHC_HP_MSG_QId = MMPF_OS_ERR_CREATE_MSG_Q;
void                            *AHC_HPMsgQueue[AHC_HP_MSG_QUEUE_SIZE] = {0};

static AHC_QUEUE_MESSAGE        m_MessageQueue[AHC_MSG_QUEUE_SIZE] = {0};
static MMP_ULONG                m_MessageQueueIndex_W = 0;
static MMP_ULONG                m_MessageQueueIndex_R = 0;

static AHC_QUEUE_MESSAGE        m_HPMessageQueue[AHC_HP_MSG_QUEUE_SIZE] = {0};
static MMP_ULONG                m_HPMessageQueueIndex_W = 0;
static MMP_ULONG                m_HPMessageQueueIndex_R = 0;

static AHC_OS_SEMID             m_AHLMessageSemID;
static AHC_OS_SEMID             m_AHLMessageCountSemID;
static AHC_OS_SEMID             m_AHLHPMessageSemID;
static AHC_OS_SEMID             m_AHLHPMessageCountSemID;

static AHC_BOOL                 m_bSendAHLMessage = AHC_TRUE;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_PARAM    glAhcParameter;

extern UINT32       m_u32CurMsgId;
extern UINT32       m_u32CurMsgParam1;
extern UINT32       m_u32CurMsgParam2;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

#if 0
void _____MessageQ_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AIHC_InitMsgQueue
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_InitMsgQueue(void)
{
    MEMSET(m_MessageQueue, 0, sizeof(m_MessageQueue));
    
    m_MessageQueueIndex_W = 0;
    m_MessageQueueIndex_R = 0;

    MEMSET(m_HPMessageQueue, 0, sizeof(m_HPMessageQueue));

    m_HPMessageQueueIndex_W = 0;
    m_HPMessageQueueIndex_R = 0;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SendAHLMessageEnable
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_SendAHLMessageEnable(AHC_BOOL bEnable)
{
    m_bSendAHLMessage = bEnable;
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SendAHLMessage
//  Description : This function sends an AHL message.
//  Notes       : Message Queue can store (AHC_MSG_QUEUE_SIZE - 1) messages
//------------------------------------------------------------------------------
/**
 @brief This function sends an AHL message.
 Parameters:
 @param[in] ulMsgID : Message ID
 @param[in] ulParam1 : The first parameter. sent with the operation.
 @param[in] ulParam2 : The second parameter sent with the operation.
 @retval TRUE or FALSE. // TRUE: Success, FALSE: Fail
*/
AHC_BOOL AHC_SendAHLMessage(UINT32 u32MsgID, UINT32 u32Param1, UINT32 u32Param2)
{
    UINT8 u8OsRet = 0;

    static AHC_BOOL bShowDBG = AHC_TRUE;

    if (AHC_MSG_QId == MMPF_OS_ERR_CREATE_MSG_Q) {
        return AHC_TRUE;
    }

    if (m_bSendAHLMessage == AHC_FALSE) {
        return AHC_TRUE;
    }

    if (AHC_OS_AcquireSem(m_AHLMessageSemID, 0) != MMPF_OS_ERR_NONE) {
        AHC_DBG_ERR(1, "SendAHLMessage AcquireSem Fail\r\n");
        return AHC_FALSE;
    }

    if ((glAhcParameter.AhlMsgUnblock != glAhcParameter.AhlMsgBlock) && 
        (u32MsgID == glAhcParameter.AhlMsgBlock)) {
        // Message ID blocked !
        AHC_OS_ReleaseSem(m_AHLMessageSemID);
        return AHC_TRUE;
    }
    
    if (m_MessageQueueIndex_R == (m_MessageQueueIndex_W + AHC_MSG_QUEUE_VIP_SIZE + 1) % AHC_MSG_QUEUE_SIZE) {
        // Message Queue Full !
        if (bShowDBG) {
            #if (AHC_MESSAGE_QUEUE_OVF)
            UINT8 i;
            #endif

            bShowDBG = AHC_FALSE;

            AHC_DBG_ERR(1, BG_YELLOW("XXX : AHC MsgQ Full! Cur[%d][%d][%d]")"\r\n",
                        m_u32CurMsgId,
                        m_u32CurMsgParam1,
                        m_u32CurMsgParam2);

            #if (AHC_MESSAGE_QUEUE_OVF)
            AHC_DBG_ERR(1, "Dump Message Queue from Index_R to Index_W\r\n");
            for (i = m_MessageQueueIndex_R; i < AHC_MSG_QUEUE_SIZE; i++) {
                AHC_DBG_ERR(1, "%3d:: %4d     %4d     %4d\r\n", i, m_MessageQueue[i].ulMsgID, m_MessageQueue[i].ulParam1,m_MessageQueue[i].ulParam2);
            }
            AHC_DBG_ERR(1, "------------------------------\r\n");
            for (i = 0; i < m_MessageQueueIndex_W; i++) {
                AHC_DBG_ERR(1, "%3d:: %4d     %4d     %4dX\r\n", i, m_MessageQueue[i].ulMsgID, m_MessageQueue[i].ulParam1,m_MessageQueue[i].ulParam2);
            }
            #endif
        }
        AHC_OS_ReleaseSem(m_AHLMessageSemID);
        return AHC_FALSE;
    }

    m_MessageQueue[m_MessageQueueIndex_W].ulMsgID = u32MsgID;
    m_MessageQueue[m_MessageQueueIndex_W].ulParam1 = u32Param1;
    m_MessageQueue[m_MessageQueueIndex_W].ulParam2 = u32Param2;

    u8OsRet = AHC_OS_PutMessage(AHC_MSG_QId, (void *)(&m_MessageQueue[m_MessageQueueIndex_W]));

    if (u8OsRet != 0) {
        AHC_DBG_ERR(1, "AHC_OS_PutMessage Err [%d]\r\n", u8OsRet);
        AHC_OS_ReleaseSem(m_AHLMessageSemID);
        return AHC_FALSE;
    }

    bShowDBG = AHC_TRUE;

    m_MessageQueueIndex_W = (m_MessageQueueIndex_W + 1) % AHC_MSG_QUEUE_SIZE;

    AHC_OS_ReleaseSem(m_AHLMessageSemID);

    if (AHC_OS_AcquireSem(m_AHLMessageCountSemID, 0) != MMPF_OS_ERR_NONE) {
        AHC_DBG_ERR(1, "AcquireSem m_AHLMessageCountSemID Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SendAHLMessage_HP
//  Description : This function sends an AHL message.
//  Notes       : Message Queue can store (AHC_MSG_QUEUE_SIZE - 1) messages
//------------------------------------------------------------------------------
/**
 @brief This function sends an AHL message.
 Parameters:
 @param[in] ulMsgID : Message ID
 @param[in] ulParam1 : The first parameter. sent with the operation.
 @param[in] ulParam2 : The second parameter sent with the operation.
 @retval TRUE or FALSE. // TRUE: Success, FALSE: Fail
*/
AHC_BOOL AHC_SendAHLMessage_HP(UINT32 ulMsgID, UINT32 ulParam1, UINT32 ulParam2)
{
    UINT8 u8OsRet = 0;

    static AHC_BOOL bShowDBG = AHC_TRUE;

    if (AHC_HP_MSG_QId == MMPF_OS_ERR_CREATE_MSG_Q) {
        return AHC_TRUE;
    }    

    if (AHC_OS_AcquireSem(m_AHLHPMessageSemID, 0) != MMPF_OS_ERR_NONE) {
        AHC_DBG_ERR(1, "SendAHLMessage_HP AcquireSem Fail\r\n");
        return AHC_FALSE;
    }

    if (m_HPMessageQueueIndex_R == (m_HPMessageQueueIndex_W + 1) % AHC_HP_MSG_QUEUE_SIZE) {
        // Message Queue Full !
        if (bShowDBG) {
            #if (AHC_MESSAGE_QUEUE_OVF)
            UINT8 i;
            #endif

            bShowDBG = AHC_FALSE;

            AHC_DBG_ERR(1, BG_YELLOW("XXX : AHC HP_MsgQ Full! Cur[%d][%d][%d]")"\r\n",
                        m_u32CurMsgId,
                        m_u32CurMsgParam1,
                        m_u32CurMsgParam2);

            #if (AHC_MESSAGE_QUEUE_OVF)
            AHC_DBG_ERR(1, "Dump Message Queue from Index_R to Index_W\r\n");
            for (i = m_HPMessageQueueIndex_R; i < AHC_HP_MSG_QUEUE_SIZE; i++) {
                AHC_DBG_ERR(1, "%3d:: %4d     %4d     %4d\r\n", i, m_HPMessageQueue[i].ulMsgID, m_HPMessageQueue[i].ulParam1, m_HPMessageQueue[i].ulParam2);
            }
            AHC_DBG_ERR(1, "------------------------------\r\n");
            for (i = 0; i < m_HPMessageQueueIndex_W; i++) {
                AHC_DBG_ERR(1, "%3d:: %4d     %4d     %4dX\r\n", i, m_HPMessageQueue[i].ulMsgID, m_HPMessageQueue[i].ulParam1, m_HPMessageQueue[i].ulParam2);
            }
            #endif
        }
        AHC_OS_ReleaseSem(m_AHLHPMessageSemID);
        return AHC_FALSE;
    }

    m_HPMessageQueue[m_HPMessageQueueIndex_W].ulMsgID = ulMsgID;
    m_HPMessageQueue[m_HPMessageQueueIndex_W].ulParam1 = ulParam1;
    m_HPMessageQueue[m_HPMessageQueueIndex_W].ulParam2 = ulParam2;

    u8OsRet = AHC_OS_PutMessage(AHC_HP_MSG_QId, (void *)(&m_HPMessageQueue[m_HPMessageQueueIndex_W]));

    if (u8OsRet != 0) {
        AHC_DBG_ERR(1, "HP AHC_OS_PutMessage Err [%d]\r\n", u8OsRet);
        AHC_OS_ReleaseSem(m_AHLHPMessageSemID);
        return AHC_FALSE;
    }

    bShowDBG = AHC_TRUE;

    m_HPMessageQueueIndex_W = (m_HPMessageQueueIndex_W + 1) % AHC_HP_MSG_QUEUE_SIZE;

    AHC_OS_ReleaseSem(m_AHLHPMessageSemID);

    if (AHC_OS_AcquireSem(m_AHLHPMessageCountSemID, 0) != MMPF_OS_ERR_NONE) {
        AHC_DBG_ERR(1, "AcquireSem m_AHLHPMessageCountSemID Fail\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAHLMessage
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetAHLMessage(UINT32* pu32MsgID, UINT32* pu32Param1, UINT32* pu32Param2)
{
    void *pMessageAddr = NULL;
    AHC_QUEUE_MESSAGE *pstMsg = NULL;

    if (AHC_OS_GetMessage(AHC_MSG_QId, (void*)(&pMessageAddr), AHC_AHL_MSGQ_TIMEOUT) != 0) {

        if (AHC_AHL_MSGQ_TIMEOUT == 0) {
            AHC_DBG_ERR(0, "GetAHLMessage OS_ERR\r\n");
        }
        *pu32MsgID  = NULL;
        *pu32Param1 = NULL;
        *pu32Param2 = NULL;
        return AHC_FALSE;
    }
    else {

        pstMsg = (AHC_QUEUE_MESSAGE *)(pMessageAddr);

        *pu32MsgID  = pstMsg->ulMsgID;
        *pu32Param1 = pstMsg->ulParam1;
        *pu32Param2 = pstMsg->ulParam2;

        if (AHC_OS_AcquireSem(m_AHLMessageSemID, 0) != MMPF_OS_ERR_NONE) {
            AHC_DBG_ERR(1, "GetAHLMessage AcquireSem Fail\r\n");
            return AHC_FALSE;
        }

        m_MessageQueueIndex_R = (m_MessageQueueIndex_R + 1) % AHC_MSG_QUEUE_SIZE;
        
        AHC_OS_ReleaseSem(m_AHLMessageSemID);

        AHC_OS_ReleaseSem(m_AHLMessageCountSemID);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAHLMessage_HP
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetAHLMessage_HP(UINT32* pu32MsgID, UINT32* pu32Param1, UINT32* pu32Param2)
{
    void *pMessageAddr = NULL;
    AHC_QUEUE_MESSAGE *pstMsg = NULL;

    if (AHC_OS_GetMessage(AHC_HP_MSG_QId, (void*)(&pMessageAddr), 0x1) != 0) {
        *pu32MsgID  = NULL;
        *pu32Param1 = NULL;
        *pu32Param2 = NULL;
        return AHC_FALSE;
    }
    else {

        pstMsg = (AHC_QUEUE_MESSAGE *)(pMessageAddr);

        *pu32MsgID  = pstMsg->ulMsgID;
        *pu32Param1 = pstMsg->ulParam1;
        *pu32Param2 = pstMsg->ulParam2;

        if (AHC_OS_AcquireSem(m_AHLHPMessageSemID, 0) != MMPF_OS_ERR_NONE) {
            AHC_DBG_ERR(1, "GetAHLMessage_HP AcquireSem Fail\r\n");
            return AHC_FALSE;
        }
        
        m_HPMessageQueueIndex_R = (m_HPMessageQueueIndex_R + 1) % AHC_HP_MSG_QUEUE_SIZE;
        
        AHC_OS_ReleaseSem(m_AHLHPMessageSemID);

        AHC_OS_ReleaseSem(m_AHLHPMessageCountSemID);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAHLMessageCount
//  Description :
//------------------------------------------------------------------------------
void AHC_GetAHLMessageCount(UINT16 *pu16Count)
{
    AHC_OS_QuerySem(m_AHLMessageCountSemID, pu16Count);
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetAHLMessageCount_HP
//  Description :
//------------------------------------------------------------------------------
void AHC_GetAHLMessageCount_HP(UINT16 *pu16Count)
{
    AHC_OS_QuerySem(m_AHLHPMessageCountSemID, pu16Count);
}

//------------------------------------------------------------------------------
//  Function    : AHC_InitAHLMessage
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_InitAHLMessage(void)
{
    m_AHLMessageCountSemID  = AHC_OS_CreateSem(AHC_MSG_QUEUE_SIZE);
    m_AHLMessageSemID       = AHC_OS_CreateSem(1);
    
    AHC_MSG_QId = AHC_OS_CreateMQueue(AHC_MsgQueue, AHC_MSG_QUEUE_SIZE);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_InitAHLMessage_HP
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_InitAHLMessage_HP(void)
{
    m_AHLHPMessageCountSemID = AHC_OS_CreateSem(AHC_HP_MSG_QUEUE_SIZE);
    m_AHLHPMessageSemID      = AHC_OS_CreateSem(1);
    
    AHC_HP_MSG_QId = AHC_OS_CreateMQueue(AHC_HPMsgQueue, AHC_HP_MSG_QUEUE_SIZE);

    return AHC_TRUE;
}
