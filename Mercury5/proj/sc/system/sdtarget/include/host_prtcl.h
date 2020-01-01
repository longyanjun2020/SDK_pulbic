////////////////////////////////////////////////////////////////////////////////
// File name: host_prtcl.h
// Copyright: MStar Semiconductor Inc.
// Description: Host communication protocol header file
////////////////////////////////////////////////////////////////////////////////
#ifndef _HOST_PRTCL_H
#define _HOST_PRTCL_H

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* protocl header character define */
#define HEADER_PACKET_SIZE          0x01    // SOH
#define HEADER_CONFIG               0x02    // STX
#define HEADER_ENDING               0x04    // EOT
#define HEADER_SET_RECORD_POS       0x05    // ENQ
#define HEADER_GETID                0x07    // BEL
#define HEADER_DATA_LOAD            0x16    // SYN
#define HEADER_DEBUG_CFG            0x2B    // PLUS
#define HEADER_IMG_LOAD             0x2C    // COMMA
#define HEADER_MIU_CFG              0x2E    // DOT
#define HEADER_MIU_VALIDATE         0x2F    // Slash
#define HEADER_BOOTLDR_ERR          0x2D    // MINUS
#define HEADER_DWL_WINTARGET        0x30
#define HEADER_CHIPTYPE_STRING      0x31
#define HEADER_FLASH_TYPE           0x32



/* error character define */
#define ACK                         0x06    // ACK
#define MCP_TEST_DONE               0x07
#define NAK                         0x15    // NAK
#define CAN                         0x18    // CAN
#define EM                          0x19
#define XON                         0x11
#define XOFF                        0x13
#define NAK_ERRLOG                  0x22
#define QUERY_INFO                  0x55
#define QUERY_EXIT                  0x66
#define NAK_ERRSTR                  0x23
#define CMD_NOT_SUPPORT             0x77


/*quere status type*/
#define FAT_INFO                    0x31
#define FAT_HIDDEN_INFO                    0x32


/* Return storage init. status */
#define DWL_STORAGE_NOT_SUPPORT     0x22
#define DWL_STORAGE_BAD_PARTTBL     0x23
#define DWL_STORAGE_NO_PARTTBL      0x24

#define DWL_STORAGE_UNKNOWN_FLASH   0x25

/* Resync. */
#define HOST_RESYNC_CHAR            0x5A
#define TARGET_RESYNC_CHAR          0xA5

/* Upload related constants */
#define DWL_UPLOAD_OK               0xA0
#define DWL_UPLOAD_FAIL             0xA5
#define DWL_UPLOAD_READY            0xAA
#define DWL_UPLOAD_BEGIN            0xAF
#define DWL_UPLOAD_END              0xAE
#define DWL_UPLOAD_TERMINAL_LENGTH  0xEFEFEFEF
#define DWL_UPLOAD_TIMEOUT          (10000)
#define DWL_UPLOAD_WRITE_TIMEOUT    (10000)

/* Reading related constants */
#define DWL_READ_OK                 0
#define DWL_READ_TIMEOUT            -1
#define DWL_READ_CHKSUM_ERR         -2

/* Upload type */
#define UPLD_TYPE_WHOLE             0xB1
#define UPLD_TYPE_CIS               0xB2
#define UPLD_TYPE_IMG               0xB3
#define UPLD_TYPE_PRT               0xB4
#define UPLD_TYPE_E2P               0xB5
#define UPLD_TYPE_CUSP              0xB6    /* CUS Partition */
#define UPLD_TYPE_TRC               0xB7    /* Backtrace */
#define UPLD_TYPE_RAIP              0xB8    /* RAI partition */
#define UPLD_TYPE_FATU              0xB9    /* User FAT */
#define UPLD_TYPE_FACIMG            0xBA    /* Upload NAND factory image for NAND programmer */
#define UPLD_TYPE_FACIMG_TBL        0xBB    /* Upload NAND factory image table for NAND programmer */

#define UPLD_TYPE_FATU              0xB9    /* User FAT */
#define UPLD_TYPE_FATU_HIDDEN            0xA1

/* RTC sync with PC related constants */
#define DWL_BEGIN_SYNC_RTC          0x4E

/* Erasure related constants */
#define DWL_ERASE_BEGIN             0xE0
#define DWL_ERASE_READY             0xE9
#define DWL_ERASE_READY_LONG        0xEA
#define DWL_ERASE_END               0xEF

/* Status report */
#define DWL_OP_DURATION             0xE0
#define DWL_OP_FAILURE              0xEE
#define DWL_OP_COMPLETE             0xEF
#define DWL_OPNUM_SHORT             0xE9
#define DWL_OPNUM_LONG              0xEA

#define DWL_TERMINAL_LENGTH         0x5AA5
#define DWL_END_OF_DOWNLOAD         0xAB

/* Programming answers */
#define DWL_PROG_OK                 0xD0
#define DWL_PROG_FAIL               0xD5
#define DWL_PROG_READY              0xDA
#define DWL_PROG_UNCOMP_ERROR       0xD4
#define DWL_PROG_RUNNING            0xD8
#define DWL_SIZE_CHANGE_HEADER      0x54
#define DWL_PROG_DATA_HEADER        0x52
#define DWL_MEDIUM_READY            0xC1
#define DWL_MEDIUM_NOTREADY         0xC2

/* EEPROM related constants */
#define DWL_E2P_INFO                0xF2
#define DWL_E2P_DWLD                0xF3
#define DWL_E2P_UPLD                0xF4
#define DWL_E2P_STOP                0x1F

/* Customization related constants */
#define DWL_BEGIN_SENSOR_CUSTO      0xC8
#define DWL_BEGIN_LCM_CUSTO         0x4C    // 'L'
#define DWL_FAIL_CUSTO              0xC9
#define DWL_OVERFLOW_CUSTO          0xCA
#define DWL_BEGIN_JAVACUSTO         0xCB
#define DWL_BEGIN_LANPACK           0xCC
#define DWL_VERIFY_CHKSUM_CUSTO     0xCD
#define DWL_BEGIN_CUS_PHASE         0xCE
#define DWL_END_CUS_PHASE           0xCF
#define DWL_ERROR_INCORRECT_CUS_SEQUENCE    0xC0
#define DWL_ERROR_UNKONWN_CUS_TYPE          0xC1
#define DWL_UNKNOWN_CUS             0x00
#define DWL_BEGIN_DLM_CUSTO         0x44   // 'D' download dynamic link module
#define DWL_BEGIN_SLDLM_CUSTO         0x53   // 'D' download dynamic link module
#define DWL_BEGIN_PAGE_CUSTO        0x50
#define DWL_BEGIN_NETWORK_SETTING   0x4E

#define DWL_BEGIN_CUST0        0x45
#define DWL_BEGIN_CUST1        0x46
#define DWL_BEGIN_CUST2        0x47
#define DWL_BEGIN_CUST3        0x48

#define DWL_BEGIN_MPRM		   0x4D // 'M' reserved for "MPRM"

/* Downlaod end signal to the other part */
#define DWL_END_RESET_SIG           0x5A
#define DWL_END_REBOOT_SIG          0xA5

/* NAND CIS create operation */
#define DWL_CIS_PROLOGUE            0xC6
#define DWL_CIS_INFO                0xC7
#define DWL_CIS_HOST_CREATE         0xDC
#define DWL_CIS_TARGET_CREATE       0xDD

/* misc */
#define  UNKNOWN_ORDER              0x19

#endif  // _HOST_PRTCL_H
