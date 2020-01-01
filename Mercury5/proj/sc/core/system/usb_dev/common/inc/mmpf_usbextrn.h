//************************************************************************
// usbint.c
//************************************************************************
#if 1 //def  exUSBINT

/** @addtogroup MMPF_USB
@{
*/

MMP_ULONG   dwTotalSec;
MMP_ULONG   USBDescBufAddr;
MMP_ULONG   USBEP0TxBufAddr;
MMP_ULONG   CBWRxBufAddr;
MMP_ULONG   CSWTxBufAddr;

MMP_ULONG   USBEP0TxAddr;
MMP_ULONG   USBEP0RxAddr;

MMP_UBYTE   m_ubCmdAtInPhase;
MMP_UBYTE   m_ubCmdAtOutPhase;
MMP_UBYTE   USBDevAddr;
MMP_UBYTE   USBMSDCPhase;
MMP_UBYTE   USBVendCmd;
MMP_ULONG   glUsbCurrentConfig;
MMP_UBYTE   USBAlterSetting;

MMP_USHORT  USBFrameNum;
MMP_USHORT  gsUsbDeviceStatus;

MMP_ULONG   USBBulkTxAddr;
MMP_UBYTE   PCC_Interface_Num;

MMP_UBYTE   USBCmd;
MMP_UBYTE   USBMSDCStatus;
MMP_UBYTE   SMWPFlag;
MMP_UBYTE   UpdateFlag;
MMP_UBYTE   ReadReg;
MMP_UBYTE   USBConfig1Len;
MMP_UBYTE   USBConfig2Len;

MMP_UBYTE  PCCamInitED;
MMP_UBYTE   ResolID;
MMP_UBYTE   PCCam_Data_CanSend;
MMP_UBYTE   PCCamModeEnable;

void    usb_ep0_setup_done(void);
void    usb_ep0_in_done(void);
void    usb_ep0_out_done(void);
void    usb_ep1_done(void);
void    usb_ep2_done(void);
void    usb_ep3_done(void);
void    usb_plug_det(void);
void    usb_reset_event(void);
void    usb_sof_event(void);
void    usb_error(void);
void    usb_ep0_error(void);
void    usb_ep1_error(void);
void    usb_ep2_error(void);
void    usb_ep3_error(void);
void    usb_ep4_error(void);
void    clear_ep1_sequence(void);
void    clear_ep2_sequence(void);
void    usb_ep2_ack(void);
void    usb_ep2_nak(void);
void    usb_bulk_tx_start(void);
void    usb_bulk_txrx_start(void);
void    MMPF_USB_HandleClassReq(void);
void    MMPF_USB_HandleClsInReq(void);
void    MMPF_USB_HandleClsOutReq(void);
void    class_reset(void);
void    class_in_reset(void);
void    class_out_reset(void);
void    class_get_max_lun(void);
void    class_in_get_max_lun(void);
void    class_out_get_max_lun(void);
void    MMPF_USB_FinishEp0NullOut(void);
void    MMPF_USB_FinishEp0NullIn(void);
void    MMPF_USB_XferEp0ByteIn(void);
void    MMPF_USB_HandleEp0In(void);
void    usb_reset_module3(void);
#if (SUPPORT_MTP_FUNC==1)||(SUPPORT_DPS_FUNC==1)
void    class_in_mtp_get_device_status(void);
void    class_out_mtp_get_device_status(void);
void    class_in_mtp_cancel_request(void);
void    class_out_mtp_cancel_request(void);
void    class_mtp_cancel_request(void);
void    class_mtp_get_device_status(void);
#endif
#else

extern  MMP_ULONG   dwTotalSec;


extern  MMP_ULONG   USBDescBufAddr;
extern  MMP_ULONG   USBEP0TxBufAddr;
extern  MMP_ULONG   CBWRxBufAddr;
extern  MMP_ULONG   CSWTxBufAddr;

extern  MMP_ULONG   USBEP0TxAddr;
extern  MMP_ULONG   USBEP0RxAddr;

extern  MMP_UBYTE   m_ubCmdAtInPhase;
extern  MMP_UBYTE   m_ubCmdAtOutPhase;
extern  MMP_UBYTE   USBDevAddr;
extern  MMP_UBYTE   USBMSDCPhase;
extern  MMP_UBYTE   USBVendCmd;
extern  MMP_ULONG   glUsbCurrentConfig;
extern  MMP_UBYTE   USBAlterSetting;

extern  MMP_USHORT  USBFrameNum;
extern  MMP_USHORT   gsUsbDeviceStatus;

extern  MMP_ULONG   USBBulkTxAddr;
extern  MMP_UBYTE   PCC_Interface_Num;

extern  MMP_UBYTE   USBCmd;
extern  MMP_UBYTE   USBMSDCStatus;
extern  MMP_UBYTE   SMWPFlag;
extern  MMP_UBYTE   HostMode;
extern  MMP_UBYTE   UpdateFlag;
extern  MMP_UBYTE   ReadReg;
extern  MMP_UBYTE   USBConfig1Len;
extern  MMP_UBYTE   USBConfig2Len;


extern MMP_UBYTE   PCCamInitED;
extern MMP_UBYTE    ResolID;
extern MMP_UBYTE    PCCam_Data_CanSend;
extern MMP_UBYTE    PCCamModeEnable;
extern  MMP_UBYTE   gbJPEGResol;

extern  void    usb_isr(void);
extern  void    usb_ep0_setup_done(void);
extern  void    usb_ep0_in_done(void);
extern  void    usb_ep0_out_done(void);
extern  void    usb_ep1_done(void);
extern  void    usb_ep2_done(void);
extern  void    usb_ep3_done(void);
extern  void    usb_plug_det(void);
extern  void    usb_reset_event(void);
extern  void    usb_sof_event(void);
extern  void    usb_error(void);
extern  void    usb_ep0_error(void);
extern  void    usb_ep1_error(void);
extern  void    usb_ep2_error(void);
extern  void    usb_ep3_error(void);
extern  void    usb_ep4_error(void);
extern  void    clear_ep1_sequence(void);
extern  void    clear_ep2_sequence(void);
extern  void    clear_ep3_sequence(void);
extern  void    usb_ep2_ack(void);
extern  void    usb_ep2_nak(void);
extern  void    usb_bulk_tx_start(void);
extern  void    usb_bulk_txrx_start(void);
extern  void    MMPF_USB_HandleClassReq(void);
extern  void    MMPF_USB_HandleClsInReq(void);
extern  void    MMPF_USB_HandleClsOutReq(void);
extern  void    class_reset(void);
extern  void    class_in_reset(void);
extern  void    class_out_reset(void);
extern  void    class_get_max_lun(void);
extern  void    class_in_get_max_lun(void);
extern  void    class_out_get_max_lun(void);
extern  void    MMPF_USB_FinishEp0NullOut(void);
extern  void    MMPF_USB_FinishEp0NullIn(void);
extern  void    MMPF_USB_FinishEp0NullInStalled(void);
extern  void    MMPF_USB_XferEp0ByteIn(void);
extern  void    MMPF_USB_HandleEp0In(void);
extern  void    usb_reset_module3(void);
extern  void    mtp_bulk_in(int TxByte);
extern  void    mtp_bulk_out(int RxByte);
extern  void    mtp_interrupt_in(int TxByte);
extern  void    mtp_stall_bulk_in(void);
extern  void    mtp_stall_bulk_out(void);
extern  void    mtp_stall_interrupt_in(void);
extern void    MSDC_Enable_ReadyFlag(void);     //Ted update
extern void    MSDC_Reset_ReadyFlag(void);      //Ted update
#endif

//************************************************************************
// usbmsdc.c
//************************************************************************
#ifdef  exUSBMSDC
void    msdc_ep1_cbw_phase(void);
void    msdc_ep1_tx_phase(void);
void    msdc_ep1_csw_phase(void);
void    msdc_ep1_tx_done(void);
void    msdc_cmd_start(void);
void    msdc_ep2_cbw_phase(void);
void    msdc_ep2_rx_phase(void);
void    msdc_ep2_csw_phase(void);
void    msdc_ep2_rx_done(void);
void    msdc_set_rx_cmd_buffer(void);
void    msdc_set_rx_data_buffer(void);
void    msdc_set_tx_buffer(void);
void    msdc_rx_cbw(void);
void    msdc_set_csw_header(MMP_UBYTE cCSWStatus);
void    msdc_tx_csw(void);
void    msdc_process_command(void);
void    msdc_cmd_formatunit(void);
void    msdc_cmd_rezero(void);
void    msdc_cmd_verify(void);
void    msdc_cmd_seek(void);
void    msdc_cmd_senddiagnostic(void);
void    msdc_cmd_startstopunit(void);
void    msdc_cmd_writeandverify(void);
void    msdc_cmd_testunitready(void);
void    msdc_cmd_inquiry(void);
void    msdc_cmd_readformatcapacity(void);
void    msdc_cmd_readcapacity(void);
void    msdc_cmd_modeselect(void);
void    msdc_cmd_preventallowmediumremoval(void);
void    msdc_cmd_modesense1A(void);
void    msdc_cmd_modesense5A(void);
void    msdc_cmd_requestsense(void);
void    msdc_read_data(void);
void    msdc_ep1_csw_phase_start(void);
void    msdc_ep1_csw_phase_end(void);
void    msdc_ep2_csw_phase_start(void);
void    usb_ep1_stall(void);
void    msdc_cmd_write(void);
void    msdc_cmd_read10(void);
void    msdc_cmd_write10(void);
void    msdc_cmd_write12(void);
void        MMPF_MSDC_SetMaxUnits(MMP_UBYTE ubMaxUnits);
MMP_UBYTE   MMPF_MSDC_GetMaxUnits(void);
void        MMPF_MSDC_SetSenseData(MMP_UBYTE errCode, MMP_UBYTE SenseKey, MMP_ULONG info,
                            MMP_UBYTE asc, MMP_UBYTE ascq, MMP_UBYTE snsKeyInfo0, MMP_UBYTE snsKeyInfo1);
MMP_USHORT  MMPF_MSDC_CheckDeviceStatus(void);
MMP_USHORT  MMPF_MSDC_CheckDeviceExist(void);
MMP_USHORT  MMPF_MSDC_CheckDeviceWP(void);
void        MMPF_MSDC_CheckCardSize(MMP_ULONG *sectCount, MMP_ULONG *sectSize);
#else
extern  void    msdc_ep1_cbw_phase(void);
extern  void    msdc_ep1_tx_phase(void);
extern  void    msdc_ep1_csw_phase(void);
extern  void    msdc_ep1_tx_done(void);
extern  void    msdc_cmd_start(void);
extern  void    msdc_ep2_cbw_phase(void);
extern  void    msdc_ep2_rx_phase(void);
extern  void    msdc_ep2_csw_phase(void);
extern  void    msdc_ep2_rx_done(void);
extern  void    msdc_set_rx_cmd_buffer(void);
extern  void    msdc_set_rx_data_buffer(void);
extern  void    msdc_set_tx_buffer(void);
extern  void    msdc_rx_cbw(void);
extern  void    msdc_set_csw_header(MMP_UBYTE cCSWStatus);
extern  void    msdc_tx_csw(void);
extern  void    msdc_process_command(void);
extern  void    msdc_cmd_formatunit(void);
extern  void    msdc_cmd_rezero(void);
extern  void    msdc_cmd_verify(void);
extern  void    msdc_cmd_seek(void);
extern  void    msdc_cmd_senddiagnostic(void);
extern  void    msdc_cmd_startstopunit(void);
extern  void    msdc_cmd_writeandverify(void);
extern  void    msdc_cmd_testunitready(void);
extern  void    msdc_cmd_inquiry(void);
extern  void    msdc_cmd_readformatcapacity(void);
extern  void    msdc_cmd_readcapacity(void);
extern  void    msdc_cmd_modeselect(void);
extern  void    msdc_cmd_preventallowmediumremoval(void);
extern  void    msdc_cmd_modesense1A(void);
extern  void    msdc_cmd_modesense5A(void);
extern  void    msdc_cmd_requestsense(void);
extern  void    msdc_read_data(void);
extern  void    msdc_ep1_csw_phase_start(void);
extern  void    msdc_ep1_csw_phase_end(void);
extern  void    msdc_ep2_csw_phase_start(void);
extern  void    usb_ep1_stall(void);
extern  void    msdc_cmd_write(void);
extern  void    msdc_cmd_read10(void);
extern  void    msdc_cmd_write10(void);
extern  void    msdc_cmd_write12(void);
extern  void        MMPF_MSDC_SetMaxUnits(MMP_UBYTE ubMaxUnits);
extern  MMP_UBYTE   MMPF_MSDC_GetMaxUnits(void);
extern  void        MMPF_MSDC_SetSenseData(MMP_UBYTE errCode, MMP_UBYTE SenseKey, MMP_ULONG info,
                            MMP_UBYTE asc, MMP_UBYTE ascq, MMP_UBYTE snsKeyInfo0, MMP_UBYTE snsKeyInfo1);
extern  MMP_USHORT  MMPF_MSDC_CheckDeviceStatus(void);
extern  MMP_USHORT  MMPF_MSDC_CheckDeviceExist(void);
extern  MMP_USHORT  MMPF_MSDC_CheckDeviceWP(void);
extern  void        MMPF_MSDC_CheckCardSize(MMP_ULONG *sectCount, MMP_ULONG *sectSize);
#endif

//************************************************************************
// usbstd.c
//************************************************************************
#ifdef  exUSBSTD
void    std_request_setup(void);
void    std_request_in(void);
void    std_request_out(void);
void    send_getstatus_data(void);
void    std_setup_getstatus(void);
void    std_in_getstatus(void);
void    std_out_getstatus(void);
void    send_clrfeature_data(void);
void    std_setup_clearfeature(void);
void    std_in_clearfeature(void);
void    std_out_clearfeature(void);
void    send_setfeature_data(void);
void    std_setup_setfeature(void);
void    std_in_setfeature(void);
void    std_out_setfeature(void);
void    std_setup_setaddress(void);
void    std_in_setaddress(void);
void    std_out_setaddress(void);
void    std_setup_setdescriptor(void);
void    std_in_setdescriptor(void);
void    std_out_setdescriptor(void);
void    std_setup_getconfiguration(void);
void    std_in_getconfiguration(void);
void    std_out_getconfiguration(void);
void    std_setup_setconfiguration(void);
void    std_in_setconfiguration(void);
void    std_out_setconfiguration(void);
void    std_setup_getinterface(void);
void    std_in_getinterface(void);
void    std_out_getinterface(void);
void    std_setup_setinterface(void);
void    std_in_setinterface(void);
void    std_out_setinterface(void);
void    std_setup_synchframe(void);
void    std_in_syncframe(void);
void    std_out_syncframe(void);
void    std_setup_getdevicedescriptor(void);
void    std_in_getdevicedescriptor(void);
void    std_out_getdevicedescriptor(void);
void    std_setup_getstringdescriptor(void);
void    std_in_getstringdescriptor(void);
void    std_out_getstringdescriptor(void);
void    std_setup_getconfigurationdescriptor(void);
void    std_in_getconfigurationdescriptor(void);
void    std_out_getconfigurationdescriptor(void);
#else
extern  void    std_request_setup(void);
extern  void    std_request_in(void);
extern  void    std_request_out(void);
extern  void    send_getstatus_data(void);
extern  void    std_setup_getstatus(void);
extern  void    std_in_getstatus(void);
extern  void    std_out_getstatus(void);
extern  void    send_clrfeature_data(void);
extern  void    std_setup_clearfeature(void);
extern  void    std_in_clearfeature(void);
extern  void    std_out_clearfeature(void);
extern  void    send_setfeature_data(void);
extern  void    std_setup_setfeature(void);
extern  void    std_in_setfeature(void);
extern  void    std_out_setfeature(void);
extern  void    std_setup_setaddress(void);
extern  void    std_in_setaddress(void);
extern  void    std_out_setaddress(void);
extern  void    std_setup_setdescriptor(void);
extern  void    std_in_setdescriptor(void);
extern  void    std_out_setdescriptor(void);
extern  void    std_setup_getconfiguration(void);
extern  void    std_in_getconfiguration(void);
extern  void    std_out_getconfiguration(void);
extern  void    std_setup_setconfiguration(void);
extern  void    std_in_setconfiguration(void);
extern  void    std_out_setconfiguration(void);
extern  void    std_setup_getinterface(void);
extern  void    std_in_getinterface(void);
extern  void    std_out_getinterface(void);
extern  void    std_setup_setinterface(void);
extern  void    std_in_setinterface(void);
extern  void    std_out_setinterface(void);
extern  void    std_setup_synchframe(void);
extern  void    std_in_syncframe(void);
extern  void    std_out_syncframe(void);
extern  void    std_setup_getdevicedescriptor(void);
extern  void    std_in_getdevicedescriptor(void);
extern  void    std_out_getdevicedescriptor(void);
extern  void    std_setup_getstringdescriptor(void);
extern  void    std_in_getstringdescriptor(void);
extern  void    std_out_getstringdescriptor(void);
extern  void    std_setup_getconfigurationdescriptor(void);
extern  void    std_in_getconfigurationdescriptor(void);
extern  void    std_out_getconfigurationdescriptor(void);
#endif

//************************************************************************
// usbvend.c
//************************************************************************
#ifdef  exUSBVEND
void    vendor_request_setup(void);
void    vendor_request_in(void);
void    vendor_request_out(void);
void    VendorOutProcess(void);
void    usb_check(void);
void    VendorSetupProcess(void);
void    VendorInProcess(void);
void    SetBuffAddr(void);
void    SetRxBuffAddr(void);
void    usb_get_buff(void);
void    usb_receive_buff(void);
void    vendor_set_buff_access_addr(void);
void    vendor_get_buff_access_size(void);
void    vendor_set_resolution(void);
void    vendor_set_device_mode(void);
void    vendor_update_flash_ATF_area(void);
#else
extern  void    vendor_request_setup(void);
extern  void    vendor_request_in(void);
extern  void    vendor_request_out(void);
extern  void    VendorOutProcess(void);
extern  void    usb_check(void);
extern  void    VendorSetupProcess(void);
extern  void    VendorInProcess(void);
extern  void    SetBuffAddr(void);
extern  void    SetRxBuffAddr(void);
extern  void    usb_get_buff(void);
extern  void    usb_receive_buff(void);
extern  void    vendor_set_buff_access_addr(void);
extern  void    vendor_get_buff_access_size(void);
extern  void    vendor_set_resolution(void);
extern  void    vendor_set_device_mode(void);
extern  void    vendor_update_flash_ATF_area(void);
#endif


#ifdef  exUSBDESCR
MMP_UBYTE   FRAME0_STRING_DATA[0x0E];
MMP_UBYTE   FRAME1_STRING_DATA[0x0E];

MMP_UBYTE   MODE_SENSE_TABLE_START[0x08];
MMP_UBYTE   REQUEST_SENSE_TABLE1_START[0x12];
MMP_UBYTE   REQUEST_SENSE_TABLE2_START[0x0E];
MMP_UBYTE   MODE_SENSE_TABLE00_START[0x02];
MMP_UBYTE   MODE_SENSE_TABLE1C_START[0x0C];
MMP_UBYTE   MODE_SENSE_TABLE3F_START[0x44];

#else

extern  MMP_UBYTE   OS_STRING_DATA[0x12];
extern  MMP_UBYTE   EXTENDED_CONFIGURATION_DATA[0x28];
extern  MMP_UBYTE   FRAME0_STRING_DATA[0x0E];
extern  MMP_UBYTE   FRAME1_STRING_DATA[0x0E];

extern  MMP_UBYTE   MODE_SENSE_TABLE_START[0x08];
extern  MMP_UBYTE   REQUEST_SENSE_TABLE1_START[0x12];
extern  MMP_UBYTE   REQUEST_SENSE_TABLE2_START[0x0E];
extern  MMP_UBYTE   MODE_SENSE_TABLE00_START[0x02];
extern  MMP_UBYTE   MODE_SENSE_TABLE1C_START[0x0C];
extern  MMP_UBYTE   MODE_SENSE_TABLE3F_START[0x44];
#endif


#ifdef  exUSBPUB

void    A810L_InitUSB(void);

void    USBDetectEvent(void);
void    usb_suspend_event(void);
void    usb_snap_cmd(void);
void    vendor_set_reg(void);
void    vendor_get_reg(void);
void    usb_desc_init(void);
void    usb_sw_enum(void);

#else

extern  void    MMPF_InitUSB(void);

extern  void    USBDetectEvent(void);
extern  void    usb_suspend_event(void);
extern  void    usb_snap_cmd(void);
extern  void    vendor_set_reg(void);
extern  void    vendor_get_reg(void);
extern  void    usb_desc_init(void);
extern  void    usb_sw_enum(void);

#endif

extern void MMPF_USB_ResetExtDMA(MMP_UBYTE endpoint);

/// @}
