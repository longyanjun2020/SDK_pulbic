#define UTMIBaseAddress  0x1F000000+(0x2200*2)
#define otgRegAddress      0x1F000000+(0x2600*2)
#define USBCBaseAddress 0x1F000000+(0x2400*2)

#define UTMI_BASE	0x2200
#define UTMI1_BASE	0x142900

#define UHC_BASE	0x2500
#define UHC1_BASE	0X143200

#define USBC_BASE	0x2400
#define USBC1_BASE	0x143180

#define USBBC_BASE	0x2300
#define USBBC1_BASE	0x143000

#define HW_BASE 	0x1F000000
#define UPLL_BASE	0x2100

#if defined(BOOTROM_VERSION_FPGA)
#define _FPGA
#endif
#define ENABLLE_DPDM_SWAP



#define OffShift            1
#define otgNumEPDefs        4
#define SCSI_BLOCK_NUM      5000
#define SCSI_BLOCK_SIZE     512
#define MONTAGE_EVB
//#define MASS_BUFFER_SIZE    (4 * 1024)
#define MAX_DMA_CHANNEL     1

