//==============================================================================
//
//  File        : mmp_component_ctl.h
//  Description : INCLUDE File for the Component Control Driver Function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_COMPONENT_CTL_H_
#define _MMP_COMPONENT_CTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "aitu_calendar.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

#define COMP_MAX_OUTBUF_NUM     (5)

#define MAX_OUTPUT_COMP_NUM     (5)

#define COMP_CHK_IDLE_STATE(p)  MMP_CompCtl_CheckIdleStatus(p)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_COMPONENT_STATE
{
    MMP_COMPONENT_STATE_INVALID = 0,// UnInit Stage
    MMP_COMPONENT_STATE_LOADED,     // Loaded but not initialized (Init Stage, Close Stage)
    MMP_COMPONENT_STATE_IDLE,       // Private data are initialized (Open Stage)
    MMP_COMPONENT_STATE_BUSY,       // The component is executing some operation 
    MMP_COMPONENT_STATE_NUM
} MMP_COMPONENT_STATE;

typedef enum _MMP_COMPONENT_MEMORY_MODE
{
    MMP_COMPONENT_MEMORY_AUTO = 0,
    MMP_COMPONENT_MEMORY_RING,
    MMP_COMPONENT_MEMORY_NEARRING,
    MMP_COMPONENT_MEMORY_CUSTOMER,
    MMP_COMPONENT_MEMORY_INTERNAL,
    MMP_COMPONENT_MEMORY_NUM
} MMP_COMPONENT_MEMORY_MODE;

typedef enum _MMP_COMPONENT_PORT_STATE
{
    PORT_NONE = 0,
    PORT_INITIAL,
    PORT_OPEN,
    PORT_CLOSE,
    PORT_INVALID
} MMP_COMPONENT_PORT_STATE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMP_COMPONENT_BUFFER_INFO
{
    MMP_ULONG                   ulBufAddr;      // Buffer address (Virtual)
    MMP_ULONG                   ulBufAddr1;
    MMP_ULONG                   ulBufAddr2;
    MMP_ULONG64                 u64BufPhyAddr;  // Buffer address (Physical)
    MMP_ULONG64                 u64BufPhyAddr1;
    MMP_ULONG64                 u64BufPhyAddr2;
    MMP_ULONG64                 u64BufMiuAddr;  // Buffer address (MIU)
    MMP_ULONG64                 u64BufMiuAddr1;
    MMP_ULONG64                 u64BufMiuAddr2;

    union {
        struct {
            MMP_UBYTE           ubBufUsage;     // Use for count buffer usage. Free -> ubBufUsage = 0; Empty buffer done will minus this value.
            MMP_UBYTE           ubBufOrderUsage;    // Use for count special order buffer usage. Free -> ubBufUsage_Idx = 0; Empty buffer done will minus this value.
            MMP_UBYTE           ubBufCurOrder;      // use for keep current order value.
            MMP_BOOL            bBufUsing[COMP_MAX_OUTBUF_NUM];
        } frm;
        struct {
            MMP_ULONG           ulWL;           // Ring buffer write index (0 ~ buffer size - 1)
            MMP_ULONG           ulWH;           // Ring buffer write wrap
            MMP_ULONG           ulRL;           // Ring buffer read index (0 ~ buffer size - 1)
            MMP_ULONG           ulRH;           // Ring buffer read wrap
        } ring;
    } bufctl;
    
    MMP_UBYTE                   ubPortIndex;    // Corresponding output port index
    MMP_UBYTE                   ubBufOrder;     // For select the buffer use order.
    MMP_ULONG                   ulTime;         // Buffer time
    MMP_ULONG                   ulSize;         // Buffer size
    MMP_ULONG                   ulFrmType;      // Buffer frame type
    //-----------------------------------------------------------------
    #define COMP_BUF_FRM_TYPE_YUV420    (0)
    #define COMP_BUF_FRM_TYPE_YUV422    (1)
    #define COMP_BUF_FRM_TYPE_MJPEG     (2)
    #define COMP_BUF_FRM_TYPE_H264_I    (3)
    #define COMP_BUF_FRM_TYPE_H264_P    (4)
    #define COMP_BUF_INVALID_FRM_TYPE   (0xFFFFFFFF)
    //-----------------------------------------------------------------
    AUTL_DATETIME               stDateTime;     // Sticker Date Time Information
    MMP_ULONG                   ulBufBias;      // Memory active region Bias: Unit Memory.
} MMP_COMPONENT_BUFFER_INFO;
typedef struct _MMP_COMPONENT_BUFORDER_INFO
{
    MMP_BOOL                    bBurOder;
    MMP_UBYTE                   ubMinBufOrder;
    MMP_UBYTE                   ubMaxBufOrder;
} MMP_COMPONENT_BUFORDER_INFO;

typedef struct _MMP_COMPONENT_MEMORY_INFO 
{
    MMP_UBYTE                   ubBufNum;       // Buffer count
    
    union {
        struct {
            MMP_UBYTE           ubWBufIndex;    // Frame buffer write index (0 ~ buffer count - 1)
            MMP_UBYTE           ubRBufIndex;    // Frame buffer read index (0 ~ buffer count - 1)
        } frm;
        struct {
            MMP_ULONG           ulWL;           // Ring buffer write index (0 ~ buffer size - 1)
            MMP_ULONG           ulWH;           // Ring buffer write wrap
            MMP_ULONG           ulRL;           // Ring buffer read index (0 ~ buffer size - 1)
            MMP_ULONG           ulRH;           // Ring buffer read wrap
        } ring;
    } memctl;
    
    MMP_ULONG                   ulBufSize;      // Ring buffer : total buffer size. Frame buffer : single buffer size.
    MMP_ULONG                   ulBufBias;      // Offset for real buffer offset, MFE need this information.
    MMP_COMPONENT_MEMORY_MODE   MemMode;        // Handle memory method.
    MMP_ULONG                   ulNearRingThd;  // Near ring buffer threshold.
    MMP_COMPONENT_BUFORDER_INFO ulBufOrderInfo; // Buffer ordering information.
} MMP_COMPONENT_MEMORY_INFO;

typedef struct _MMP_COMPONENT_PORT_INFO // Every Port have other handler.
{
    MMP_COMPONENT_PORT_STATE    State;
    MMP_ERR                     (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
    MMP_ERR                     (*pfClose)(void* handle);   // Callback for Close this port.
    MMP_ERR                     (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
    MMP_ERR                     (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                            // This call back should release memory usage. With real Open MAX. This need event task handler.                                                                     // and call next component empty buffer.
    MMP_COMPONENT_BUFFER_INFO   bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
    void                        *pCurComponent;             // For in/out port
    void                        *PrevComponent;             // For in port
    void                        *NextComponent;             // For out port
} MMP_COMPONENT_PORT_INFO;

typedef struct _MMP_COMPONENT_STOREDONE
{
    MMP_ERR                     (*pfUpdateBuffer)(void* handle, MMP_ULONG ulSize, void *BufInfo);   // Function for update store buffer. Use for update current component store addr not use for trigger.(Trigger from empty buffer)
    MMP_ERR                     (*pfEmptyBuffer)(void* handle, MMP_ULONG ulSize, void *BufInfo);    // Function for empty buffer. Use for trigger component.
    MMP_ERR                     (*pfEmptyOrderBuffer)(void* handle, MMP_ULONG ulSize, void *BufInfo);    // Function for empty buffer. Use for trigger component.
    MMP_ERR                     (*pfEmptyBufferDone)(void* handle, MMP_ULONG ulSize, void *BufInfo);// Out memory port done (eq: Device/component work finish).
} MMP_COMPONENT_STOREDONE;

typedef struct _MMP_COMPONENT_BASE
{
    MMP_UBYTE                   name[10];
    MMP_ULONG                   ulState;
    MMP_BOOL                    bRegistered;
    MMP_BOOL                    bByPass;                            // Bypass this component or not
    MMP_UBYTE                   ubOutputPortNum;
    MMP_COMPONENT_MEMORY_INFO   *MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO   *BufferInfo;
    MMP_COMPONENT_PORT_INFO     *pInPort;
    MMP_COMPONENT_PORT_INFO     *pOutPort;

    MMP_COMPONENT_STOREDONE     StoreDoneFunc;
    MMP_ERR                     (*pfInit)(void* handle);            // Use for init this component. Ex: may initial device driver here.
    MMP_ERR                     (*pfOpen)(void* handle);            // Use for open this component. Ex: may setting device driver here.
    MMP_ERR                     (*pfAllocateMemory)(void* handle);  // Use for allocate memory for this component.
    MMP_ERR                     (*pfFreeMemory)(void* handle);      // Use for free memory for this component.
    MMP_ERR                     (*pfUnInit)(void* handle);          // Use for unInit this component.
    MMP_ERR                     (*pfClose)(void* handle);           // Use for close this component.
    MMP_ERR                     (*pfSetParameter)(void* handle, int type, void* param); // use for set parameter to device info
    MMP_ERR                     (*pfGetParameter)(void* handle, int type, void* param); // use for get parameter from device info
    MMP_ERR                     (*pfUpdateBuffer)(void* handle, MMP_ULONG ulSize, void *BufInfo);   // Function for update store buffer. Use for update current component store addr not use for trigger.(Trigger from empty buffer)
    MMP_ERR                     (*pfEmptyBuffer)(void* handle, MMP_ULONG ulSize, void *BufInfo);    // Function for empty buffer. Use for trigger component.
    MMP_ERR                     (*pfEmptyBufferDone)(void* handle, MMP_ULONG ulSize, void *BufInfo);// Out memory port done (eq: Device/component work finish).
    MMP_ERR                     (*pfGetBufferInfo)(void* handle, MMP_ULONG *ulNumber, void *BufInfo);  // Get component output buffer information.
    void                        *DeviceInfo;                        // Use for store device information(setting).
} MMP_COMPONENT_BASE;

//===============================================================================
//
//                               FUNCTION PROTOTYPES
//
//===============================================================================

MMP_ERR MMP_CompCtl_InitMemoryInfo(void *pHandle);
MMP_ERR MMP_CompCtl_AllocateMemory(void* pHandle);
MMP_ERR MMP_CompCtl_FreeMemory(void *pHandle);

MMP_ERR MMP_CompCtl_InitComponent(void* pHandle);
MMP_ERR MMP_CompCtl_OpenComponent(void *pHandle);
MMP_ERR MMP_CompCtl_CloseComponent(void *pHandle);
MMP_ERR MMP_CompCtl_SetParameter(void* pHandle, int type, void* pPara);
MMP_ERR MMP_CompCtl_GetParameter(void* pHandle, int type, void* pPara);
MMP_BOOL MMP_CompCtl_CheckIdleStatus(void *pHandle);

MMP_ERR MMP_CompCtl_StoreBufferDone(MMP_COMPONENT_BASE *pComp,MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_StoreBufferDoneEx(MMP_COMPONENT_BASE    *pComp,
                                      MMP_ULONG             ulSize,
                                      void                  *BufInfo,
                                      MMP_BOOL              bEmptyBuf,
                                      MMP_BOOL              bUpdateBuf,
                                      MMP_BOOL              bEmptyDone);
MMP_ERR MMP_CompCtl_EmptyBufferEx(MMP_COMPONENT_BASE *pComp, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyBufferDoneEx(MMP_COMPONENT_BASE *pComp, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_UpdateBufferEx(MMP_COMPONENT_BASE *pComp, MMP_ULONG ulSize, void *BufInfo);

MMP_ERR MMP_CompCtl_EmptyBuffer_Frm(void *pHandler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyOrderBuffer_Frm(void *pHandle, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR MMP_CompCtl_EmptyBufferDone_Frm(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_UpdateBuffer_Frm(void *pHandler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyBuffer_Ring(void *pHandler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyBufferDone_Ring(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_UpdateBuffer_Ring(void *pHandler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyBuffer_NearRing(void *pHandler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_EmptyBufferDone_NearRing(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR MMP_CompCtl_UpdateBuffer_NearRing(void *pHandler, MMP_ULONG ulSize, void *BufInfo);

MMP_ERR MMP_CompCtl_SyncBufferRing(MMP_COMPONENT_BASE *pHandle, MMP_ULONG ulWL, MMP_ULONG ulWH, MMP_ULONG ulRL, MMP_ULONG ulRH);
MMP_ERR MMP_CompCtl_GetBufferStaticInfo(void* pHandle, MMP_ULONG* pulAddr, MMP_ULONG* pulSize);
MMP_ERR MMP_CompCtl_GetRingBufRuntimeInfo(void* pHandle,
                                          MMP_ULONG* pulWptr, MMP_ULONG* pulWwrap,
                                          MMP_ULONG* pulRptr, MMP_ULONG* pulRwrap);
MMP_ERR MMP_CompCtl_GetFrmBufRuntimeInfo(void* pHandle,
                                         MMP_ULONG* pulWIdx, MMP_ULONG* pulRIdx,
                                         MMP_ULONG* pulAddr, MMP_ULONG* pulSize);
MMP_ERR MMP_CompCtl_GetBufferInfo(void *pHandle, MMP_ULONG *pulBufNum, void *pBufInfo);

MMP_ERR MMP_CompCtl_OpenPortIndex(MMP_COMPONENT_BASE* pComp, MMP_UBYTE ubIdx);
MMP_ERR MMP_CompCtl_ClosePortIndex(MMP_COMPONENT_BASE* pComp, MMP_UBYTE ubIdx);

#endif // _MMP_COMPONENT_CTL_H_
