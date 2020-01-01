#ifndef _MS_CONFIG_H_
#define _MS_CONFIG_H_

//#define  _OTG_INVERSE_CLK
//#define MONTAGE_DMA_REG // B2
#define ARM_DMA_REG // B3, B4(Bravo)
//#define UTMIBaseAddress 0xbf811000 // B2
//#define otgRegAddress   0xbf80F000 // B2
//#define USBCBaseAddress 0xbf80B000 // B2
#define UTMIBaseAddress 0x74003E00 // B3
#define otgRegAddress   0x74004000 // B3
#define USBCBaseAddress 0x74003C00 // B3
#define OffShift            1
#define otgNumEPDefs        4
#define OTG_WRITE_1_CLEAR
#define SCSI_BLOCK_NUM      5000
#define SCSI_BLOCK_SIZE     512
#define MONTAGE_EVB
#define MASS_BUFFER_SIZE    (4 * 1024)
#define MAX_DMA_CHANNEL     1

#define DBG_MSG printf
//#define UDC_DBG
// #define UDC_PERFORM_MEASURE     /* performance measurement */

#endif  /* _MS_CONFIG_H_ */
