
#ifndef  USB_DPS_H
#define USB_DPS_H

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;
typedef int s_int;
typedef short s_short;
typedef char s_char;
typedef struct
{
  u_int  retsize;
  u_char isinput;
  u_char tagID;
  u_char numofpara;
  u_short paraID[16];
  u_char paravalue[16][32];
} XML_Tag_Info;

extern MMP_ULONG DPS_GetDeviceInfo_TX( MMP_ULONG addr_tmp  );
extern void DPS_OpenSession_CMD(void);
extern MMP_ULONG DPS_GetObjectInfo_TX(MMP_ULONG addr_tmp,MMP_ULONG hdl);
extern void dps_xml_encode(u_char *pxml,u_char enable);
extern MMP_USHORT dps_xml_parser(u_char *pxml);
extern void dpsOpenSession(void);
extern void dps_StartDPSPrintJob(void);
extern void dps_AbortDPSPrintJob(void);
extern void dps_ContinueDPSPrintJob(void);
extern MMP_USHORT GetPrinterStatus(void);
extern MMP_ULONG DPSGetbufAddr(MMP_ULONG buftype);
extern void dps_special_bulk_in(void );
extern void dps_ep_config(void);
extern void ui8toa16(MMP_UBYTE value,MMP_UBYTE str[2]);





extern MMP_UBYTE gbTriggerEvent;
extern MMP_ULONG DPSDealXmlBufAddr;
extern MMP_ULONG DPSXmlBufAddrPtr;
extern MMP_ULONG HostDataBufAddr;
extern MMP_ULONG DPSBufEndAddr;
extern MMP_UBYTE gbNotifyTag;
extern MMP_USHORT gsDPSPrinterStatus;
extern MMP_USHORT gsLastDPSPrinterStatus;
extern MMP_USHORT gsDPSPrinterOP;
extern MMP_UBYTE gbOutOfValue;
extern MMP_UBYTE gbErrorjobEnd;

extern MMP_UBYTE d1;

extern MMP_ULONG preDPShandleID;

typedef struct
{
  u_int   fileID;
  u_int   copies;

  u_char  quality;
  u_char  papersize;
  u_char  papertype;
  u_char  filetype;
  u_char  dateprint;
  u_char  filenameprint;
  u_char  imageoptimize;
  u_char  layout;
  u_char  fixedsize;
  char  filepath[100];
} DPS_PRINT_INFO;



#define DPSOpSupNum 17
extern MMP_USHORT DPSOpSupported[];
#define DPSEvSupNum 1
extern MMP_USHORT DPSEvSupported[];
#define DPSPropSupNum 0 /*1*/
extern MMP_USHORT DPSPropSupported[];
#define DPSCapFmtNum 2
extern MMP_USHORT DPSCaptureFormats[];
#define DPSImgFmtNum 5
extern MMP_USHORT DPSImageFormats[];

//brian061025. virtual file "handle ID" in DPS
#define DDISCVRY_DPS_ID 0xFFFF0001
#define HDISCVRY_DPS_ID 0xFFFF0002
#define DREQUEST_DPS_ID 0xFFFF0003
#define HRSPONSE_DPS_ID 0xFFFF0004
#define HREQUEST_DPS_ID 0xFFFF0005
#define DRSPONSE_DPS_ID 0xFFFF0006


#define dpsPrintServiceStatus_mask      0xFFF0
#define dpsPrintServiceStatus_Printing  0x0001
#define dpsPrintServiceStatus_Idle      0x0002
#define dpsPrintServiceStatus_Paused    0x0004

#define errorStatus_mask                0xFF0F
#define errorStatus_No                  0x0010
#define errorStatus_Warning             0x0020
#define errorStatus_Fatal               0x0040

#define errorReason_mask                0xF0FF
#define errorReason_No                  0x0000
#define errorReason_Paper               0x0100
#define errorReason_Ink                 0x0200
#define errorReason_Hadrware            0x0400
#define errorReason_File                0x0800

#define newJobOK_mask                   0x0FFF
#define newJobOK_False                  0x1000
#define newJobOK_True                   0x2000

#define inputXML "<?xml version=\"1.0\"?><dps xmlns=\"http://www.cipa.jp/dps/schema/\"><input>"
#define outputXML "<?xml version=\"1.0\"?><dps xmlns=\"http://www.cipa.jp/dps/schema/\"><output>"
#define inputTailXML "</input></dps>"
#define outputTailXML "</output></dps>"


// DPF Tag
// Print Service OP
#define DPS_TagID_ConfigurePrintService   0x01
#define DPS_Tag_ConfigurePrintService      "<configurePrintService>"
#define DPS_Tag_Tail_ConfigurePrintService "</configurePrintService>"
#define DPS_TagID_GetCapability           0x02
#define DPS_Tag_GetCapability              "<getCapability>"
#define DPS_Tag_Tail_GetCapability         "</getCapability>"
#define DPS_TagID_GetJobStatus            0x03
#define DPS_Tag_GetJobStatus               "<getJobStatus>"
#define DPS_Tag_Tail_GetJobStatus          "</getJobStatus>"
#define DPS_TagID_GetDeviceStatus         0x04
#define DPS_Tag_GetDeviceStatus            "<getDeviceStatus>"
#define DPS_Tag_Tail_GetDeviceStatus       "</getDeviceStatus>"
#define DPS_TagID_StartJob                0x05
#define DPS_Tag_StartJob                   "<startJob>"
#define DPS_Tag_Tail_StartJob              "</startJob>"
#define DPS_TagID_AbortJob                0x06
#define DPS_Tag_AbortJob                   "<abortJob>"
#define DPS_Tag_Tail_AbortJob              "</abortJob>"
#define DPS_TagID_ContinueJob             0x07
#define DPS_Tag_ContinueJob                "<continueJob>"
#define DPS_Tag_Tail_ContinueJob           "<continueJob/>"

// Print Service EVENT
#define DPS_TagID_NotifyJobStatus         0x11
#define DPS_Tag_NotifyJobStatus            "<notifyJobStatus>"
#define DPS_Tag_Tail_NotifyJobStatus       "<notifyJobStatus/>"
#define DPS_TagID_NotifyDeviceStatus      0x12
#define DPS_Tag_NotifyDeviceStatus         "<notifyDeviceStatus>"
#define DPS_Tag_Tail_NotifyDeviceStatus    "<notifyDeviceStatus/>"

// Storage Service OP
#define DPS_TagID_GetFileID               0x21
#define DPS_Tag_GetFileID                  "<getFileID>"
#define DPS_Tag_Tail_GetFileID             "</getFileID>"
#define DPS_TagID_GetFileInfo             0x22
#define DPS_Tag_GetFileInfo                "<getFileInfo>"
#define DPS_Tag_Tail_GetFileInfo           "</getFileInfo>"
#define DPS_TagID_GetFile                 0x23
#define DPS_Tag_GetFile                    "<getFile>"
#define DPS_Tag_Tail_GetFile               "</getFile>"
#define DPS_TagID_GetPartialFile          0x24
#define DPS_Tag_GetPartialFile             "<getPartialFile>"
#define DPS_Tag_Tail_GetPartialFile        "</getPartialFile>"
#define DPS_TagID_GetFileList             0x25
#define DPS_Tag_GetFileList                "<getFileList>"
#define DPS_Tag_Tail_GetFileList           "</getFileList>"
#define DPS_TagID_GetThumb                0x26
#define DPS_Tag_GetThumb                   "<getThumb>"
#define DPS_Tag_Tail_GetThumb              "</getThumb>"

// DPS Tag Parameter
// result
#define DPS_ParaID_result                        0x1100
#define DPS_Para_result                          "<result>"
#define DPS_Para_Tail_result                     "</result>"

// DPS_ConfigurePrintService
#define DPS_ParaID_printServiceAvailable         0x0101
#define DPS_Para_printServiceAvailable           "<printServiceAvailable>"
#define DPS_Para_Tail_printServiceAvailable      "</printServiceAvailable>"

#define DPS_ParaID_dpsVersions                   0x0102
#define DPS_Para_dpsVersions                     "<dpsVersions>"
#define DPS_Para_Tail_dpsVersions                "</dpsVersions>"

#define DPS_ParaID_vendorName                    0x0103
#define DPS_Para_vendorName                      "<vendorName>"
#define DPS_Para_Tail_vendorName                 "</vendorName>"

#define DPS_ParaID_vendorSpecificVersion         0x0104
#define DPS_Para_vendorSpecificVersion           "<vendorSpecificVersion>"
#define DPS_Para_Tail_vendorSpecificVersion      "</vendorSpecificVersion>"

#define DPS_ParaID_productName                   0x0105
#define DPS_Para_productName                     "<productName>"
#define DPS_Para_Tail_productName                "</productName>"

#define DPS_ParaID_serialNo                      0x0106
#define DPS_Para_serialNo                        "<serialNo>"
#define DPS_Para_Tail_serialNo                   "</serialNo>"

// DPS_GetCapability
#define DPS_ParaID_capability                    0x0200
#define DPS_Para_capability                      "<capability>"
#define DPS_Para_Tail_capability                 "</capability>"

#define DPS_ParaID_qualities                     0x0201
#define DPS_Para_qualities                       "<qualities>"
#define DPS_Para_Tail_qualities                  "</qualities>"

#define DPS_ParaID_paperSizes                    0x0202
#define DPS_Para_paperSizes                      "<paperSizes>"
#define DPS_Para_Tail_paperSizes                 "</paperSizes>"

#define DPS_ParaID_paperTypes                    0x0203
#define DPS_Para_paperTypes                      "<paperTypes>"
#define DPS_Para_Tail_paperTypes                 "</paperTypes>"

#define DPS_ParaID_fileTypes                     0x0204
#define DPS_Para_fileTypes                       "<fileTypes>"
#define DPS_Para_Tail_fileTypes                  "</fileTypes>"

#define DPS_ParaID_datePrints                    0x0205
#define DPS_Para_datePrints                      "<datePrints>"
#define DPS_Para_Tail_datePrints                 "</datePrints>"

#define DPS_ParaID_fileNamePrints                0x0206
#define DPS_Para_fileNamePrints                  "<fileNamePrints>"
#define DPS_Para_Tail_fileNamePrints             "</fileNamePrints>"

#define DPS_ParaID_imageOptimizes                 0x0207
#define DPS_Para_imageOptimizes                  "<imageOptimizes>"
#define DPS_Para_Tail_imageOptimizes             "</imageOptimizes>"

#define DPS_ParaID_layouts                       0x0208
#define DPS_Para_layouts                         "<layouts>"
#define DPS_Para_Tail_layouts                    "</layouts>"

#define DPS_ParaID_fixedSizes                    0x0209
#define DPS_Para_fixedSizes                      "<fixedSizes>"
#define DPS_Para_Tail_fixedSizes                 "</fixedSizes>"

#define DPS_ParaID_croppings                     0x020a
#define DPS_Para_croppings                       "<croppings>"
#define DPS_Para_Tail_croppings                  "</croppings>"

// DPS_StartJob
// jobConfig
#define DPS_ParaID_jobConfig                     0x0500
#define DPS_Para_jobConfig                       "<jobConfig>"
#define DPS_Para_Tail_jobConfig                  "</jobConfig>"

#define DPS_ParaID_quality                       0x0501
#define DPS_Para_quality                         "<quality>"
#define DPS_Para_Tail_quality                    "</quality>"

#define DPS_ParaID_paperType                     0x0502
#define DPS_Para_paperType                       "<paperType>"
#define DPS_Para_Tail_paperType                  "</paperType>"

#define DPS_ParaID_paperSize                     0x0503
#define DPS_Para_paperSize                       "<paperSize>"
#define DPS_Para_Tail_paperSize                  "</paperSize>"

#define DPS_ParaID_fileType                      0x0504
#define DPS_Para_fileType                        "<fileType>"
#define DPS_Para_Tail_fileType                   "</fileType>"

#define DPS_ParaID_datePrint                     0x0505
#define DPS_Para_datePrint                       "<datePrint>"
#define DPS_Para_Tail_datePrint                  "</datePrint>"

#define DPS_ParaID_fileNamePrint                 0x0506
#define DPS_Para_fileNamePrint                   "<fileNamePrint>"
#define DPS_Para_Tail_fileNamePrint              "</fileNamePrint>"

#define DPS_ParaID_imageOptimize                 0x0507
#define DPS_Para_imageOptimize                   "<imageOptimize>"
#define DPS_Para_Tail_imageOptimize              "</imageOptimize>"

#define DPS_ParaID_layout                        0x0508
#define DPS_Para_layout                          "<layout>"
#define DPS_Para_Tail_layout                     "</layout>"

#define DPS_ParaID_fixedSize                     0x0509
#define DPS_Para_fixedSize                       "<fixedSize>"
#define DPS_Para_Tail_fixedSize                  "</fixedSize>"

#define DPS_ParaID_cropping                      0x050a
#define DPS_Para_cropping                        "<cropping>"
#define DPS_Para_Tail_cropping                   "</cropping>"

// printInfo
#define DPS_ParaID_printInfo                     0x0510
#define DPS_Para_printInfo                       "<printInfo>"
#define DPS_Para_Tail_printInfo                  "</printInfo>"

#define DPS_ParaID_croppingArea                  0x0511
#define DPS_Para_croppingArea                    "<croppingArea>"
#define DPS_Para_Tail_croppingArea               "</croppingArea>"

#define DPS_ParaID_fileID                        0x0512
#define DPS_Para_fileID                          "<fileID>"
#define DPS_Para_Tail_fileID                     "</fileID>"

#define DPS_ParaID_fileName                      0x0513
#define DPS_Para_fileName                        "<fileName>"
#define DPS_Para_Tail_fileName                   "</fileName>"

#define DPS_ParaID_date                          0x0514
#define DPS_Para_date                            "<date>"
#define DPS_Para_Tail_date                       "</date>"

#define DPS_ParaID_copies                        0x0515
#define DPS_Para_copies                          "<copies>"
#define DPS_Para_Tail_copies                     "</copies>"

#define DPS_ParaID_prtPID                        0x0516
#define DPS_Para_prtPID                          "<prtPID>"
#define DPS_Para_Tail_prtPID                     "</prtPID>"

#define DPS_ParaID_filePath                      0x0517
#define DPS_Para_filePath                        "<filePath>"
#define DPS_Para_Tail_filePath                   "</filePath>"

#define DPS_ParaID_copyID                        0x0518
#define DPS_Para_copyID                          "<copyID>"
#define DPS_Para_Tail_copyID                     "</copyID>"

// DPS_AbortJob
#define DPS_ParaID_abortStyle                    0x0601
#define DPS_Para_abortStyle                      "<abortStyle>"
#define DPS_Para_Tail_abortStyle                 "</abortStyle>"


// DPS_NotifyDeviceStatus
#define DPS_ParaID_dpsPrintServiceStatus         0x1101
#define DPS_Para_dpsPrintServiceStatus           "<dpsPrintServiceStatus>"
#define DPS_Para_Tail_dpsPrintServiceStatus      "</dpsPrintServiceStatus>"

#define DPS_ParaID_jobEndReason                  0x1102
#define DPS_Para_jobEndReason                    "<jobEndReason>"
#define DPS_Para_Tail_jobEndReason               "</jobEndReason>"

#define DPS_ParaID_errorStatus                   0x1103
#define DPS_Para_errorStatus                     "<errorStatus>"
#define DPS_Para_Tail_errorStatus                "</errorStatus>"

#define DPS_ParaID_errorReason                   0x1104
#define DPS_Para_errorReason                     "<errorReason>"
#define DPS_Para_Tail_errorReason                "</errorReason>"

#define DPS_ParaID_disconnectEnable              0x1105
#define DPS_Para_disconnectEnable                "<disconnectEnable>"
#define DPS_Para_Tail_disconnectEnable           "</disconnectEnable>"

#define DPS_ParaID_capabilityChanged             0x1106
#define DPS_Para_capabilityChanged               "<capabilityChanged>"
#define DPS_Para_Tail_capabilityChanged          "</capabilityChanged>"

#define DPS_ParaID_newJobOK                      0x1107
#define DPS_Para_newJobOK                        "<newJobOK>"
#define DPS_Para_Tail_newJobOK                   "</newJobOK>"

// DPS_NotifyJobStatus
#define DPS_ParaID_progress                      0x1204
#define DPS_Para_progress                        "<progress>"
#define DPS_Para_Tail_progress                   "</progress>"



#define DPS_STARTJOB         0x1001
#define DPS_ABORTJOB         0x1002
#define DPS_CONTINUEJOB      0x1003

#define DPSHOSTBUF  0x0001
#define DPSBUFEND   0x0002

#define SICDC_TRACE

#endif
