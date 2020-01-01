//==============================================================================
//
//  File        : ahc_usb.h
//  Description : INCLUDE File for the AHC USB function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_USB_H_
#define _AHC_USB_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "AHC_Config_SDK.h"

#include "mmpf_usbh_cfg.h"
#include "mmps_usb.h"
#include "mmpf_usbvend.h"

#define	USB_PRODUCT_STR_LEN				    14
#define USB_DESCRIPTOR_VENDOR_LENGTH        8
#define USB_DESCRIPTOR_PRODUCT_LENGTH       16
#define USB_DETECTION_DISABLE_TIMEOUT_CNT (0xffff)

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _AHC_USB_OP_MODE
{
	AHC_USB_MODE_NONE = 0,
	AHC_USB_MODE_WEBCAM,
	AHC_USB_MODE_MASS_STORAGE,
	AHC_USB_MODE_DPS_MODE,
	AHC_USB_MODE_PTP_MODE,
	AHC_USB_MODE_PCSYNC_MODE,
	AHC_USB_MODE_MTP_MODE,
	AHC_USB_MODE_DETECT_MODE,
	AHC_USB_MODE_ISOTEST_MODE,
	AHC_USB_MODE_ADAPTER_MODE,	
	AHC_USB_MODE_MAX
} AHC_USB_OP_MODE;

typedef enum _AHC_USB_STATUS
{
	AHC_USB_NORMAL,
	AHC_USB_ISADAPTER,
	AHC_USB_IDLE
} AHC_USB_STATUS;

typedef enum _AHC_USB_GET_PHASE_STAGE
{
    AHC_USB_GET_PHASE_CURRENT=0,
    AHC_USB_GET_PHASE_NEXT,
    AHC_USB_GET_PHASE_MAX
} AHC_USB_GET_PHASE_STAGE;

typedef struct tagINQUIRY_TABLE_START
{
    BYTE byPeripheralDeviceType;
    BYTE byRemovaleMediaBit;
    BYTE byAnsiEcmaIsoVersion;
    BYTE byResponseDataFormat;
    UINT uiAdditionalLength;
    char szVendorInfo[USB_DESCRIPTOR_VENDOR_LENGTH];
    char szProductId[USB_DESCRIPTOR_PRODUCT_LENGTH];
    char chProductRevisionLevel[4];
} SINQUIRYTABLESTART, *PSINQUIRYTABLESTART;

typedef enum _USB_DETECT_PHASE {
    USB_DETECT_PHASE_INIT = 0,
    USB_DETECT_PHASE_CHECK_VBUS,
    USB_DETECT_PHASE_CHECK_USBID,
    USB_DETECT_PHASE_OTG_SESSION,
    USB_DETECT_PHASE_CHECK_CONN,

    USB_DETECT_PHASE_VBUS_ACTIVE, 
    USB_DETECT_PHASE_REAR_CAM, 
#if USB_DETECTION_CUSTOM
    USB_DETECT_PHASE_REAR_CAM_DISCONN, 
#endif
    USB_DETECT_PHASE_NG, 
    USB_DETECT_PHASE_MAX
} USB_DETECT_PHASE ;

struct USB_DETECT_ROUTINE{
    UINT16 cur_phase;        
    UINT16 next_phase;        
    UINT32 timer_interval;
    UINT16 timeout; //If timeout count down to 0, don't detect rear cam anymore until timeout count is reset.    
    UINT16 timeout_init_val; 
    UINT8 Vbus_states;
    UINT8 pause_detection;
    void *pCallback;
    void *pCallbackArg;
    void (* usb_routine) (void *proutine, UINT8 stage);    
};

struct USB_DETECT_TYPE {
    const void *usb_detect_routine; /* must be first */
    UINT16 usb_phase;
    void (* routine_func) (void *ptype, void *ptmr, void *parg, UINT8 stage); //mandatory
    void (* detect_func) (void *ptype); //mandatory
    void (* exec_func) (void *ptype); //optional
    void (* notify_func) (void *ptype);   //optional
};

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

AHC_BOOL AHC_SetUsbMode(AHC_USB_OP_MODE byMode);
AHC_BOOL AHC_GetUsbMode(AHC_USB_OP_MODE *puiMode);
AHC_BOOL AHC_USB_WaitUntilFirstRoundDone(UINT32 ulTimeoutMs);
void AHC_USB_PauseDetection(UINT8 bPauseDetection);
void     AHC_USB_SetDetectBDeviceTimeout(UINT32 ulMs);
AHC_USB_STATUS AHC_USB_GetLastStatus(void);
AHC_BOOL AHC_IsUsbConnect(void);
AHC_BOOL AHC_IsUsbBooting(void);
AHC_BOOL AHC_IsDCInBooting(void);
AHC_BOOL AHC_IsDcCableConnect(void);
UINT8    AHC_GetBootingSrc(void);

#if (MTP_FUNC == 1)
AHC_BOOL AHC_PtpInitialize(USB_STATE* pState);
AHC_BOOL AHC_PtpCheckCommand(USB_STATE *pState);
AHC_BOOL AHC_PtpReceiveData(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT32 *pCount, USB_TRANSFER *state);
AHC_BOOL AHC_PtpSendData(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT32 *pCount, USB_TRANSFER state);
AHC_BOOL AHC_PtpSendEvent(USB_STATE *pState, UINT8 *pBuffer, UINT32 size, UINT16 *count);
AHC_BOOL AHC_PtpDisconnect(USB_STATE *pState);
AHC_BOOL AHC_PtpConnect(USB_STATE *pState);
AHC_BOOL AHC_PtpReset(USB_STATE *pState);
AHC_BOOL AHC_PtpStall(USB_STATE *pState);
AHC_BOOL AHC_PtpUnstall(USB_STATE *pState);
AHC_BOOL AHC_PtpIsConnected(USB_STATE *pState);
#endif

void AHC_USBGetStates(USB_DETECT_PHASE *pUSBPhase, AHC_USB_GET_PHASE_STAGE sUSBPhaseStage);
void AHC_USBDetectRoutine(void *proutine, UINT8 stage);
void AHC_USB_INIT_Detect(void *ptype);
void AHC_USB_INIT_Exec(void *ptype);
void AHC_USB_INIT_Notify(void *ptype);
void AHC_USB_Check_VBUS_Detect(void *ptype);
void AHC_USB_Check_VBUS_Exec(void *ptype);
void AHC_USB_Check_VBUS_Notify(void *ptype);
void AHC_USB_Check_USBID_Detect(void *ptype);
void AHC_USB_Check_USBID_Exec(void *ptype);
void AHC_USB_Check_USBID_Notify(void *ptype);
void AHC_USB_OTG_Session_Detect(void *ptype);
void AHC_USB_OTG_Session_Exec(void *ptype);
void AHC_USB_OTG_Session_Notify(void *ptype);
#if USB_DETECTION_CUSTOM
//Custom flow++
void AHC_USB_Check_VBUS_Custom_Detect(void *ptype);
void AHC_USB_Check_VBUS_Custom_Exec(void *ptype);
void AHC_USB_Check_VBUS_Custom_Notify(void *ptype);
void AHC_USB_Check_USBID_Custom_Detect(void *ptype);
void AHC_USB_Check_USBID_Custom_Exec(void *ptype);
void AHC_USB_Check_USBID_Custom_Notify(void *ptype);
void AHC_USB_Check_Connect_Custom_Detect(void *ptype);
void AHC_USB_RearCam_Disconn_Custom_Detect(void *ptype);
void AHC_USB_RearCam_Disconn_Custom_Exec(void *ptype);
void AHC_USB_RearCam_Disconn_Custom_Notify(void *ptype);
#endif
void AHC_USB_Check_Connect_Detect(void *ptype);
void AHC_USB_Check_Connect_Exec(void *ptype);
void AHC_USB_Check_Connect_Notify(void *ptype);
void AHC_USB_VBUS_Active_Detect(void *ptype);
void AHC_USB_VBUS_Active_Exec(void *ptype);
void AHC_USB_VBUS_Active_Notify(void *ptype);
void AHC_USB_Rearcam_Notify(void *ptype);
void AHC_USB_SubRoutine(void *ptype, void *ptmr, void *parg, UINT8 stage);
UINT32 AHC_USBGetTypeNum(void);
void *AHC_USBGetCurTypeObj(UINT16 type_num);    
UINT16 AHC_USBGetCurTypePhase(void *pdet_type);    
void AHC_USBRoutine(void *ptype, void *ptmr, void *parg, UINT8 stage);    
void AHC_USB_Do(void *ptype);    
void AHC_USBSetPhase(void *ptype, UINT16 phase);
UINT16 AHC_USBGetPhase(void *ptype, UINT8 cur_or_next);
UINT8 AHC_USBGetVBUS(void *ptype);
void AHC_USBDetectTimerCB(void *ptmr, void *parg);
void AHC_USBDetectHandler(void);
AHC_BOOL AHC_DisconnectDevice(void);

void AHC_USBDetectSetPriority(AHC_BOOL bHighPriority);

#if (MSDC_SUPPORT_SECRECY_LOCK)
AHC_BOOL AHC_SetMsdcSecrecyLock(AHC_BOOL bLockMode);
AHC_BOOL AHC_GetMsdcSecrecyLock(void);
#endif

#if (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) 
AHC_BOOL AHC_AitScsiCustomerCmd_Register_CB(MSDC_AIT_SCSI_CUSTOMER_CB cb);
#endif

#endif
