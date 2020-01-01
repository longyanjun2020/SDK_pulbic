#ifndef UDMA_LIB_H
#define UDMA_LIB_H


#ifdef _BCB_
#include <vcl.h>
#else
#include <windows.h>
#endif
#include <stdio.h>

#if !defined(__cplusplus)
#define BYTE    char
#define BOOL    char
#define DWORD   unsigned long
#endif

//#ifdef __cplusplus
//extern "C" {
//#endif
//ezusbsys.h
#define MAX_INTEL_HEX_RECORD_LENGTH 4096

typedef struct _INTEL_HEX_RECORD
{
   WORD  Length;
   WORD  Address;
   BYTE  Type;
   BYTE  Data[MAX_INTEL_HEX_RECORD_LENGTH];
} INTEL_HEX_RECORD, *PINTEL_HEX_RECORD;

// usb.h
#define BULK_MAXPACKETSIZE   1024
extern HANDLE  ghDevice;
typedef struct
{
    unsigned char cmd;
    unsigned short param1;
    unsigned short param2;
} USBCMD_PARAM;

typedef enum
{
    UDMA_8051_HOLD,
    UDMA_8051_RUN
}UDMA_8051_OP;

extern BOOLEAN USB_OpenDriver (HANDLE * phDeviceHandle, PCHAR devname);
extern void USB_CloseDriver(HANDLE *phDriver);
extern BOOL USB_CheckDevice(HANDLE hdev);
extern BOOL USB_ControlIn(USBCMD_PARAM* pParam, int bytecount, unsigned char* pData);
extern BOOL USB_ControlOut(USBCMD_PARAM* pParam, int bytecount, unsigned char* pData);
extern BOOL GetUsbDeviceDescriptor(HANDLE hUSB_CtrlTransfer);
extern void USB_BulkInfo();
extern BOOL USB_BulkIn(int pipenum, int* psize, unsigned char* pData);
extern BOOL USB_BulkOut(int pipenum, int size, unsigned char* pData);
extern BOOL USB_LoadFirmware(const char* filename, char* device_name = NULL);
extern BOOL USB_8051_ACTION(UDMA_8051_OP op);
extern BOOL USB_DownloadIntelHex(PINTEL_HEX_RECORD pHexRecord);

//bulkloop.h
extern char PIPE_TYPE_STRINGS[4][4];
extern char PIPE_DIRECTION[2][4];

typedef PVOID USBD_PIPE_HANDLE;
typedef PVOID USBD_CONFIGURATION_HANDLE;
typedef PVOID USBD_INTERFACE_HANDLE;

typedef enum _USBD_PIPE_TYPE {
    UsbdPipeTypeControl,
    UsbdPipeTypeIsochronous,
    UsbdPipeTypeBulk,
    UsbdPipeTypeInterrupt
} USBD_PIPE_TYPE;

typedef struct _USB_DEVICE_DESCRIPTOR {
    UCHAR bLength;
    UCHAR bDescriptorType;
    USHORT bcdUSB;
    UCHAR bDeviceClass;
    UCHAR bDeviceSubClass;
    UCHAR bDeviceProtocol;
    UCHAR bMaxPacketSize0;
    USHORT idVendor;
    USHORT idProduct;
    USHORT bcdDevice;
    UCHAR iManufacturer;
    UCHAR iProduct;
    UCHAR iSerialNumber;
    UCHAR bNumConfigurations;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;

typedef struct _USBD_PIPE_INFORMATION {
    //
    // OUTPUT
    // These fields are filled in by USBD
    //
    USHORT MaximumPacketSize;  // Maximum packet size for this pipe
    UCHAR EndpointAddress;     // 8 bit USB endpoint address (includes direction)
                               // taken from endpoint descriptor
    UCHAR Interval;            // Polling interval in ms if interrupt pipe

    USBD_PIPE_TYPE PipeType;   // PipeType identifies type of transfer valid for this pipe
    USBD_PIPE_HANDLE PipeHandle;

    //
    // INPUT
    // These fields are filled in by the client driver
    //
    ULONG MaximumTransferSize; // Maximum size for a single request
                               // in bytes.
    ULONG PipeFlags;
} USBD_PIPE_INFORMATION, *PUSBD_PIPE_INFORMATION;

typedef struct _USBD_INTERFACE_INFORMATION {
    USHORT Length;       // Length of this structure, including
                         // all pipe information structures that
                         // follow.
    //
    // INPUT
    //
    // Interface number and Alternate setting this
    // structure is associated with
    //
    UCHAR InterfaceNumber;
    UCHAR AlternateSetting;

    //
    // OUTPUT
    // These fields are filled in by USBD
    //
    UCHAR Class;
    UCHAR SubClass;
    UCHAR Protocol;
    UCHAR Reserved;

    USBD_INTERFACE_HANDLE InterfaceHandle;
    ULONG NumberOfPipes;

    //
    // INPUT/OUPUT
    // see PIPE_INFORMATION
    USBD_PIPE_INFORMATION Pipes[0];

} USBD_INTERFACE_INFORMATION, *PUSBD_INTERFACE_INFORMATION;


// usbcmd.h
#define MIU_ALIGNMENT   8


//----------------------------------------------------------------------------
// USB PIPE NUMBER
//----------------------------------------------------------------------------
#define BULK_IN_PIPE_NUM    0
#define BULK_OUT_PIPE_NUM    2

//----------------------------------------------------------------------------
// REG ADDR
//----------------------------------------------------------------------------
#define DVB_BANK_ADDR       0x4000
#define DVB_REG_ADDR        0x5000

//----------------------------------------------------------------------------
// UDMA REGISTER
//----------------------------------------------------------------------------
#define UDMA_REG_BASE			0xD000  //0x2000
#define UDMA_REG_SIZE			0x600

#define UDMA_REG_STR_ADR_W0_0   UDMA_REG_BASE
#define UDMA_REG_STR_ADR_W0_1   (UDMA_REG_BASE+0x10)
#define UDMA_REG_STR_ADR_W0_2   (UDMA_REG_BASE+0x20)

#define UDMA_REG_STR_ADR_W1_0   (UDMA_REG_BASE+0x30)
#define UDMA_REG_STR_ADR_W1_1   (UDMA_REG_BASE+0x40)
#define UDMA_REG_STR_ADR_W1_2   (UDMA_REG_BASE+0x50)

#define UDMA_REG_STR_ADR_W2_0   (UDMA_REG_BASE+0x60)
#define UDMA_REG_STR_ADR_W2_1   (UDMA_REG_BASE+0x70)
#define UDMA_REG_STR_ADR_W2_2   (UDMA_REG_BASE+0x80)

#define UDMA_REG_STR_ADR_W3_0   (UDMA_REG_BASE+0x90)
#define UDMA_REG_STR_ADR_W3_1   (UDMA_REG_BASE+0xA0)
#define UDMA_REG_STR_ADR_W3_2   (UDMA_REG_BASE+0xB0)

#define UDMA_REG_STR_ADR_R0_0   (UDMA_REG_BASE+0xC0)
#define UDMA_REG_STR_ADR_R0_1   (UDMA_REG_BASE+0xD0)
#define UDMA_REG_STR_ADR_R0_2   (UDMA_REG_BASE+0xE0)

#define UDMA_REG_STR_ADR_R1_0   (UDMA_REG_BASE+0xF0)
#define UDMA_REG_STR_ADR_R1_1   (UDMA_REG_BASE+0x100)
#define UDMA_REG_STR_ADR_R1_2   (UDMA_REG_BASE+0x110)

#define UDMA_REG_STR_ADR_R2_0   (UDMA_REG_BASE+0x120)
#define UDMA_REG_STR_ADR_R2_1   (UDMA_REG_BASE+0x130)
#define UDMA_REG_STR_ADR_R2_2   (UDMA_REG_BASE+0x140)

#define UDMA_REG_STR_ADR_R3_0   (UDMA_REG_BASE+0x150)
#define UDMA_REG_STR_ADR_R3_1   (UDMA_REG_BASE+0x160)
#define UDMA_REG_STR_ADR_R3_2   (UDMA_REG_BASE+0x170)

#define UDMA_REG_END_ADR_R0_0   (UDMA_REG_BASE+0x180)
#define UDMA_REG_END_ADR_R0_1   (UDMA_REG_BASE+0x190)
#define UDMA_REG_END_ADR_R0_2   (UDMA_REG_BASE+0x1A0)

#define UDMA_REG_END_ADR_R1_0   (UDMA_REG_BASE+0x1B0)
#define UDMA_REG_END_ADR_R1_1   (UDMA_REG_BASE+0x1C0)
#define UDMA_REG_END_ADR_R1_2   (UDMA_REG_BASE+0x1D0)

#define UDMA_REG_END_ADR_R2_0   (UDMA_REG_BASE+0x1E0)
#define UDMA_REG_END_ADR_R2_1   (UDMA_REG_BASE+0x1F0)
#define UDMA_REG_END_ADR_R2_2   (UDMA_REG_BASE+0x200)

#define UDMA_REG_END_ADR_R3_0   (UDMA_REG_BASE+0x210)
#define UDMA_REG_END_ADR_R3_1   (UDMA_REG_BASE+0x220)
#define UDMA_REG_END_ADR_R3_2   (UDMA_REG_BASE+0x230)

#define UDMA_REG_HID_B0         (UDMA_REG_BASE+0x240)
#define UDMA_REG_HID_B1         (UDMA_REG_BASE+0x250)
#define UDMA_REG_HID_B2         (UDMA_REG_BASE+0x260)
#define UDMA_REG_HID_B3         (UDMA_REG_BASE+0x270)
#define UDMA_REG_HID_B4         (UDMA_REG_BASE+0x280)
#define UDMA_REG_HID_B5         (UDMA_REG_BASE+0x290)
#define UDMA_REG_HID_B6         (UDMA_REG_BASE+0x2A0)
#define UDMA_REG_HID_B7         (UDMA_REG_BASE+0x2B0)

#define UDMA_REG_CMD_MD         (UDMA_REG_BASE+0x2C0)
#define UDMA_REG_IFCLK          (UDMA_REG_BASE+0x2D0)

#define UDMA_REG_PACKETEND      (UDMA_REG_BASE+0x2F0)

#define UDMA_REG_MVDTSPRESET    (UDMA_REG_BASE+0x340)

typedef enum
{
    UDMA_FIELD_ADDR_W0,
    UDMA_FIELD_ADDR_W1,
    UDMA_FIELD_ADDR_W2,
    UDMA_FIELD_ADDR_W3,

    UDMA_FIELD_ADDR_STAR_R0,
    UDMA_FIELD_ADDR_STAR_R1,
    UDMA_FIELD_ADDR_STAR_R2,
    UDMA_FIELD_ADDR_STAR_R3,

    UDMA_FIELD_ADDR_END_R0,
    UDMA_FIELD_ADDR_END_R1,
    UDMA_FIELD_ADDR_END_R2,
    UDMA_FIELD_ADDR_END_R3,

    UDMA_FIELD_HID_B0,
    UDMA_FIELD_HID_B1,
    UDMA_FIELD_HID_B2,
    UDMA_FIELD_HID_B3,
    UDMA_FIELD_HID_B4,
    UDMA_FIELD_HID_B5,
    UDMA_FIELD_HID_B6,
    UDMA_FIELD_HID_B7,

    UDMA_FIELD_CMD,
    UDMA_FIELD_IFCLK,
    UDMA_FIELD_PACKETEND,
    UDMA_FIELD_NULL,
} UDMA_REG_FIELD;

extern BOOL UDMA_GetHWVersion(unsigned char* pdata);
extern BOOL UDMA_UDMARegRead(unsigned short addr,unsigned char* pData);
extern BOOL UDMA_UDMARegWrite(unsigned short addr, unsigned char data);
extern BOOL UDMA_RIUDataRead(unsigned long addr, unsigned long bytecount, int dtype, unsigned char* pData);
extern BOOL UDMA_RIUDataRead_Byte(unsigned long addr, int bytecount, BYTE mask, int dtype, unsigned char* pdata);
extern BOOL UDMA_RIUDataWrite(unsigned long addr, int bytecount, int dtype, unsigned char* pData);
extern BOOL UDMA_RIUDataWrite_Byte(unsigned long addr, int bytecount, BYTE mask, int dtype, unsigned char* pData);
extern BOOL EEPROM_WriteBytes(unsigned short addr, int bytecount, unsigned char* pData);
extern BOOL EEPROM_ReadBytes(unsigned short addr, int bytecount, unsigned char* pData);
extern BOOL UDMA_DMADataRead(int* psize, unsigned char* pData);
extern BOOL UDMA_DMADataWrite(unsigned long bytecount, unsigned char* pData);
extern BOOL UDMA_RIURead(unsigned short addr,unsigned char* pData);
extern BOOL UDMA_RIUWrite(unsigned short addr, unsigned char data);
#ifdef __cplusplus
extern "C" {
#endif
extern BOOL UDMA_RIURead16(unsigned short addr,unsigned short* pData);
extern BOOL UDMA_RIUWrite16(unsigned short addr, unsigned short data);
#ifdef __cplusplus
}
#endif
extern BOOL SLAVE_I2CRead(unsigned short bank, unsigned short addr, unsigned char* pData);
extern BOOL SLAVE_I2CRead16(unsigned short bank, unsigned short addr, unsigned short* pData);
extern BOOL SLAVE_I2CWrite(unsigned short bank, unsigned short addr, unsigned char data);
extern BOOL SLAVE_I2CWrite16(unsigned short bank, unsigned short addr, unsigned short data);
extern BOOL SLAVE_I2CSRAMCTL(unsigned char data);
extern BOOL I2C_WriteByte(unsigned short bank, unsigned short addr, unsigned char data);
extern BOOL I2C_WriteBytes(unsigned short bank, unsigned short addr, char *data, unsigned short size);
extern BOOL I2C_ReadByte(unsigned short bank, unsigned short addr, unsigned char* pData);
extern BOOL IIC_Running_Entry(void);
extern BOOL IIC_Running_Exit(void);
extern unsigned char& DemodSlaveId(void);
extern void Open_hMutex(void);
extern void Close_hMutex(void);

//dmaengine.h
typedef enum
{
    DMA_ENGINE_DMA_READ,
    DMA_ENGINE_DMA_WRITE
} DMA_ENGINE_TYPE;


class DMA_Engine
{
public:
    DMA_Engine();

    BOOL Start(unsigned long addr, int size, DMA_ENGINE_TYPE type);
    BOOL End();

    BOOL DMAReadFirst(int*, BYTE*);
    BOOL DMAWriteFirst(int, BYTE*);

    BOOL DMARead(int*, BYTE*);
    BOOL DMAWrite(int, BYTE*);

    int ParseBuf(int size, BYTE* pdat);

    void FillHeader(BYTE* pBuf);
    int GetHeaderLen();

    void SetStreamRegion(DWORD iaddr, DWORD paddr, DWORD b1addr, DWORD b2addr);
    void SetStreamSize(int hsize, int vsize);
    void StreamStart(DMA_ENGINE_TYPE type);

private:

private:
    unsigned long m_addr;
    int m_size;
    DMA_ENGINE_TYPE m_type;

    int m_hsize, m_vsize;
    DWORD m_iaddr, m_paddr, m_b1addr, m_b2addr;
};


// udmaop.h
typedef enum
{
	UDMAOP_RET_ERROR = 0,
	UDMAOP_RET_OK,
	UDMAOP_RET_OPENFILEERROR,
	UDMAOP_RET_READFILEERROR,
	UDMAOP_RET_WRITEFILEERROR,
	UDMAOP_RET_USBERROR,
	UDMAOP_RET_HEADERNOTFOUND,
    UDMAOP_RET_COMPARENOTMATCH,
} UDMAOP_RET;

extern BOOL UDMAOP_InitSDRAM();

extern BOOL UDMAOP_ReadMemRIU(DWORD addr, int bytecount, int dtype, BYTE* pData);
extern BOOL UDMAOP_WriteMemRIU(DWORD addr, int bytecount, int dtype, BYTE* pData);

extern BOOL UDMAOP_ReadUDMAReg(UDMA_REG_FIELD field, DWORD* pval);
extern BOOL UDMAOP_WriteUDMAReg(UDMA_REG_FIELD field, DWORD val);

#ifdef __cplusplus
extern "C" {
#endif
extern UDMAOP_RET UDMAOP_DMAPut(char* srcBuf, int srcLen, unsigned long addr, int endian/*, BYTE* pbuf*/);
extern UDMAOP_RET UDMAOP_DMAGet(char* dstBuf, int dstLen, unsigned long addr, int endian/*, char* pbuf*/);
//extern UDMAOP_RET UDMAOP_DMAPut(BYTE* srcBuf, int srcLen, DWORD addr, int endian/*, BYTE* pbuf*/);
//extern UDMAOP_RET UDMAOP_DMAGet(DWORD addr, int size, int endian, BYTE* pbuf);
extern UDMAOP_RET UDMAOP_DMAPutFile(char* filename, DWORD addr, int endian, BYTE* pbuf);
extern UDMAOP_RET UDMAOP_DMAGetFile(char* filename, DWORD addr, int size, int endian, BYTE* pbuf);
#ifdef __cplusplus
}
#endif

extern UDMAOP_RET UDMAOP_DMACompareFile(char* filename, DWORD addr, int endian, BYTE* pbuf);

extern UDMAOP_RET UDMAOP_RIUPutFile(char* filename, DWORD addr, int endian, int dtype, BYTE* pbuf);
extern UDMAOP_RET UDMAOP_RIUGetFile(char* filename, DWORD addr, int size, int endian, int dtype, BYTE* pbuf);
extern UDMAOP_RET UDMAOP_RIUCompareFile(char* filename, DWORD addr, int endian, int dtype, BYTE* pbuf);


// utility.h
extern BOOL SaveMemToFile(char* filename, int size, BYTE* pbuf);
extern void CutLineChar(char* buf);
extern int GetFileLength(char* filename);
extern BOOL CompareFiles(char* srcfilename, char* dstfilename);

//#ifdef __cplusplus
//}
//#endif
#endif // UDMA_LIB_H
