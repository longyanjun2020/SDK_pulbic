//#define   CBW_RX_BUF              0x7C00

/** @addtogroup MMPF_USB
@{
*/

#define USB_MSDC_DBG_LV				3

#define CBW_dCBWSignature           0
#define CBW_dCBWTag                 CBW_dCBWSignature + 0x04
#define CBW_dCBWDataTransferLength  CBW_dCBWTag     + 0x04
#define CBW_bmCBWFlags              CBW_dCBWDataTransferLength + 0x04
#define CBW_bCBWLUN                 CBW_bmCBWFlags  + 0x01
#define CBW_bCBWLength              CBW_bCBWLUN     + 0x01
#define CBW_CBWCB                   CBW_bCBWLength  + 0x01
//  ; Inquiry Command (12h)
#define     CBW_CBWCB_12_OP_Code        CBW_CBWCB
#define     CBW_CBWCB_12_Alloc_Length   CBW_CBWCB + 0x04
//  ; Read Command (28h)
#define     CBW_CBWCB_28_OP_Code        CBW_CBWCB
#define     CBW_CBWCB_28_LBA3           CBW_CBWCB + 0x02
#define     CBW_CBWCB_28_LBA2           CBW_CBWCB + 0x03
#define     CBW_CBWCB_28_TxLen_MSB      CBW_CBWCB + 0x07
#define     CBW_CBWCB_28_TxLen_LSB      CBW_CBWCB + 0x08
//  ; Write Command (2Ah)
#define     CBW_CBWCB_2A_OP_Code        CBW_CBWCB
#define     CBW_CBWCB_2A_LBA3           CBW_CBWCB + 0x02
#define     CBW_CBWCB_2A_LBA2           CBW_CBWCB + 0x03
#define     CBW_CBWCB_2A_RxLen_MSB      CBW_CBWCB + 0x07
#define     CBW_CBWCB_2A_RxLen_LSB      CBW_CBWCB + 0x08

//#define   CSW_TX_BUF              0x7E00
#define CSW_dCSWSignature           0
#define CSW_dCSWTag                 CSW_dCSWSignature + 0x04
#define CSW_dCSWDataResidue         CSW_dCSWTag + 0x04
#define CSW_dCSWStatus              CSW_dCSWDataResidue + 0x04

//===============================================================
#define CMD_TEST_UNIT_READY         0x00
#define CMD_REZERO              0x01
#define CMD_REQUEST_SENSE           0x03
#define CMD_FORMAT_UNIT             0x04
#define CMD_INQUIRY             0x12
#define CMD_MODE_SELECT_15              0x15
#define CMD_MODE_SENSE_1A           0x1A
#define CMD_START_STOP_UNIT         0x1B
#define CMD_SEND_DIAGNOSTIC         0x1D
#define CMD_PREVENT_ALLOW_MEDIUM_REMOVAL    0x1E
#define CMD_READ_FORMAT_CAPACITY        0x23
#define CMD_READ_CAPACITY           0x25
#define CMD_READ_10             0x28
#define CMD_WRITE_10                0x2A
#define CMD_SEEK_10             0x2B
#define CMD_WRITE_AND_VERIFY            0x2E
#define CMD_VERIFY              0x2F
#define CMD_MODE_SELECT_55              0x55
#define CMD_MODE_SENSE_5A           0x5A
#define CMD_READ_12             0xA8
#define CMD_WRITE_12                0xAA

/*-----------------------------------
    SENSE_DATA
-----------------------------------*/
/*---- valid ----*/
#define SENSE_VALID             0x80    /* Sense data is valid as SCSI2     */
#define SENSE_INVALID           0x00    /* Sense data is invalid as SCSI2   */

/*---- error code ----*/
#define CUR_ERR                 0x70    /* current error                    */
#define DEF_ERR                 0x71    /* specific command error           */

/*---- sense key Infomation ----*/
#define SNSKEYINFO_LEN          3       /* length of sense key infomation   */

#define SKSV                    0x80
#define CDB_ILLEGAL             0x40
#define DAT_ILLEGAL             0x00
#define BPV                     0x08
#define BIT_ILLEGAL0            0       /* bit0 is illegal                  */
#define BIT_ILLEGAL1            1       /* bit1 is illegal                  */
#define BIT_ILLEGAL2            2       /* bit2 is illegal                  */
#define BIT_ILLEGAL3            3       /* bit3 is illegal                  */
#define BIT_ILLEGAL4            4       /* bit4 is illegal                  */
#define BIT_ILLEGAL5            5       /* bit5 is illegal                  */
#define BIT_ILLEGAL6            6       /* bit6 is illegal                  */
#define BIT_ILLEGAL7            7       /* bit7 is illegal                  */

/*---- ASC ----*/
#define ASC_NO_INFO             0x00
#define ASC_MISCMP              0x1d
#define ASC_INVLD_CDB           0x24
#define ASC_INVLD_PARA          0x26
#define ASC_LU_NOT_READY        0x04
#define ASC_WRITE_ERR           0x0c
#define ASC_READ_ERR            0x11
#define ASC_LOAD_EJCT_ERR       0x53
#define ASC_MEDIA_NOT_PRESENT   0x3A
#define ASC_MEDIA_CHANGED       0x28
#define ASC_MEDIA_IN_PROCESS    0x04
#define ASC_WRITE_PROTECT       0x27

/*---- ASQC ----*/
#define ASCQ_NO_INFO            0x00
#define ASCQ_MEDIA_IN_PROCESS   0x01
#define ASCQ_MISCMP             0x00
#define ASCQ_INVLD_CDB          0x00
#define ASCQ_INVLD_PARA         0x02
#define ASCQ_LU_NOT_READY       0x02
#define ASCQ_WRITE_ERR          0x02
#define ASCQ_READ_ERR           0x00
#define ASCQ_LOAD_EJCT_ERR      0x00
#define ASCQ_WRITE_PROTECT      0x00


/*---- sense key ----*/
#define ILI                     0x20    /* ILI bit is on                    */

#define NO_SENSE                0x00    /* not exist sense key              */
#define RECOVER_ERR             0x01    /* Target/Logical unit is recoverd  */
#define NOT_READY               0x02    /* Logical unit is not ready        */
#define MEDIA_ERR               0x03    /* medium/data error                */
#define HW_ERR                  0x04    /* hardware error                   */
#define ILGAL_REQ               0x05    /* CDB/parameter/identify msg error */
#define UNIT_ATTENTION          0x06    /* unit attention condition occur   */
#define DAT_PRTCT               0x07    /* read/write is desable            */
#define BLNC_CHK                0x08    /* find blank/DOF in read           */
                                        /* write to unblank area            */
#define CPY_ABRT                0x0a    /* Copy/Compare/Copy&Verify illgal  */
#define ABRT_CMD                0x0b    /* Target make the command in error */
#define EQUAL                   0x0c    /* Search Data end with Equal       */
#define VLM_OVRFLW              0x0d    /* Some data are left in buffer     */
#define MISCMP                  0x0e    /* find inequality                  */

#define READ_ERR                -1
#define WRITE_ERR               -2

#define FIRST_RESET             0x01
#define USED_EXIST              0x02

#define CARD_EXIST              0x01

//========== Interrupt Status ===========//
#define MSDC_STATUS_USB_INT_ON    0x0001

#define MSDC_CHECK_CARD_STATUS    0x0100
#define MSDC_CHECK_CARD_SIZE      0x0200
#define MSDC_CHECK_CARD_WP        0x0400
#define MSDC_CHECK_READ_CARD      0x1000
#define MSDC_CHECK_WRITE_CARD     0x2000

void MMPF_MSDC_Init(void);
void MMPF_MSDC_Uninit(void);
MMP_USHORT MMPF_MSDC_Polling(void);

#if (defined(MSDC_SUPPORT_SECRECY_LOCK) && MSDC_SUPPORT_SECRECY_LOCK)
void MMPF_MSDC_SetSecrecyLock(MMP_BOOL isLock);
MMP_BOOL MMPF_MSDC_GetSecrecyLock(void);
#endif

typedef enum {
    MSDC_IDLE,
    MSDC_WRITE,
    MSDC_READ
} MSDC_MEM_WRSTATUS;
/// @}