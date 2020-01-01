/*****************************************************************************
 *
 *  Copyright (c) 2010 MStar Semiconductor, Inc.  All rights reserved.
 *  4F-1, No. 26, Tai-Yuan St., ChuPei, Hsinchu Hsien, Taiwan 302, R.O.C.
 *
 *  THE DELIVERY OF THIS SOFTWARE AS WELL AS THE HEREBY GRANTED
 *  NON-EXCLUSIVE, WORLDWIDE LICENSE TO USE, COPY, MODIFY, DISTRIBUTE
 *  AND SUBLICENSE THIS SOFTWARE IS FREE OF CHARGE.
 *
 *  THE LICENSED SOFTWARE IS PROVIDED "AS IS" AND MSTAR EXPRESSLY
 *  DISCLAIMS ALL REPRESENTATIONS AND WARRANTIES, WHETHER EXPRESS OR
 *  IMPLIED, INCLUDING WITHOUT LIMITATION, WARRANTIES OR REPRESENTATIONS
 *  OF WORKMANSHIP, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 *  DURABILITY, THAT THE OPERATING OF THE LICENSED SOFTWARE WILL BE ERROR
 *  FREE OR FREE OF NY THIRD PARTY CALIMS, INCLUDING WITHOUT LIMITATION
 *  CLAIMS OF THIRD PARTY INTELLECTUAL PROPERTY INFRINGEMENT.
 *
 *  EXCEPT FOR ANY LIABILITY DUE TO WILFUL ACTS OR GROSS NEGLIGENCE AND
 *  EXCEPT FOR ANY PERSONAL INJURY MSTAR SHALL IN NO EVENT BE LIABLE
 *  FOR ANY CLAIM OR DAMAGES OF ANY KIND, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

/*
* @file    wlan_pif.h
* @version
* @brief   WLAN PIF header file
*/

#ifndef _WLAN_PIF_H_
#define _WLAN_PIF_H_


/************************************************************************
 * Constant
 ************************************************************************/
#define MAX_PIF_LENGTH                  0x10000

#define POLL_MIU_XIU_DONE               1

/* Flag definition */
#define SPIF_FLAG_DAR                   0x1     /* bit0 indicate if the DAR status */

#define LOAD_FW_CHECK                   1

#define SDIO_BLK_SIZE                   512


/********************************************************
 * PIF Access Definition
 ********************************************************/
#define AQUA_PIF_SLAVE_ID               SLAVE_3
#define AQUA_PIF_DEVICE_ID              MPIF2

#define PIF_CHECKSUM                    1
#define PIF_RETRX_LIMIT                 2
#define PIF_TURN_AROUND_CYCLE           1
#define PIF_WAIT_ACK_CYCLE              1
#define PIF_MAX_WAIT                    4
#define PIF_PAGE_SIZE                   0

/********************************************************
 * SPIF Registers
 ********************************************************/
#define SPIF_R_LC1A_MIU_POLLING_ENABLE_ADDR     0x6
#define SPIF_R_LC1A_MIU_POLLING_ENABLE_OFFSET   0
#define SPIF_R_LC1A_MIU_POLLING_ENABLE_VAL      0x1

#define SPIF_R_LC1A_MIU_WRITE_DONE_ADDR         0x7
#define SPIF_R_LC1A_MIU_WRITE_DONE_LEN          1
#define SPIF_R_LC1A_MIU_WRITE_DONE_OFFSET       0
#define SPIF_R_LC1A_MIU_WRITE_DONE_VAL          0x01

#define SPIF_R_LC1A_XIU_WRITE_DONE_ADDR         0x7
#define SPIF_R_LC1A_XIU_WRITE_DONE_LEN          1
#define SPIF_R_LC1A_XIU_WRITE_DONE_OFFSET       1
#define SPIF_R_LC1A_XIU_WRITE_DONE_VAL          0x02

/*----- register reg113 -----*/
#define SPIF_R_REG113_ADDR              0x71

#define SPIF_R_SPIF_ID_ADDR             0x71
#define SPIF_R_SPIF_ID_LEN              2
#define SPIF_R_SPIF_ID_OFFSET           0

#define SPIF_R_SPIF_CW_ADDR             0x71
#define SPIF_R_SPIF_CW_LEN              2
#define SPIF_R_SPIF_CW_OFFSET           4

#define SPIF_R_SPIF_DW_ADDR             0x71
#define SPIF_R_SPIF_DW_LEN              2
#define SPIF_R_SPIF_DW_OFFSET           6

#define SPIF_R_SPIF_TR_CNT_ADDR         0x71
#define SPIF_R_SPIF_TR_CNT_LEN          2
#define SPIF_R_SPIF_TR_CNT_OFFSET       8

#define SPIF_R_SPIF_WT_CNT_ADDR         0x71
#define SPIF_R_SPIF_WT_CNT_LEN          2
#define SPIF_R_SPIF_WT_CNT_OFFSET       10

/*----- register reg114 -----*/
#define SPIF_R_REG114_ADDR              0x72

#define SPIF_R_PIF_CLK_DLY_ADDR         0x72
#define SPIF_R_PIF_CLK_DLY_LEN          4
#define SPIF_R_PIF_CLK_DLY_OFFSET       0

#define SPIF_R_PIF_CLK_INV_ADDR         0x72
#define SPIF_R_PIF_CLK_INV_LEN          1
#define SPIF_R_PIF_CLK_INV_OFFSET       4

#define SPIF_R_PIF_CLK_INV_DLY_ADDR     0x72
#define SPIF_R_PIF_CLK_INV_DLY_LEN      4
#define SPIF_R_PIF_CLK_INV_DLY_OFFSET   8

#define SPIF_R_PIF_CLK_INV_INV_ADDR     0x72
#define SPIF_R_PIF_CLK_INV_INV_LEN      1
#define SPIF_R_PIF_CLK_INV_INV_OFFSET   12


/********************************************************
 * SDIO Registers
 ********************************************************/
#define SDIO_R_MBOX1                    0x26
#define SDIO_R_MBOX3                    0x27


/************************************************************************
 * Data Type
 ************************************************************************/
typedef enum
{
    PIF_1_BIT_WIDTH=0,
    PIF_2_BIT_WIDTH=1,
    PIF_4_BIT_WIDTH=2,

} BIT_WIDTH_e;

typedef enum
{
    AQUA_STS_BOOT           = 0x00,
    AQUA_STS_LOAD_FW_DONE   = 0x01,
    AQUA_STS_OS_DONE        = 0x02,

    //add following status for wakeup and watchdog recovery
    AQUA_STS_INIT_SDIO_DONE = 0x10,
    AQUA_STS_OS_START       = 0x11,
    AQUA_STS_PM_SUSPEND     = 0x13,
    AQUA_STS_PM_RESUME      = 0x14,

} AQUA_STATUS_e;


/************************************************************************
 * Function Prototype
 ************************************************************************/
u8 aqua_spif_reg_read(u32 u32Addr, u32 *pu32Val);
u8 aqua_spif_reg_write(u32 u32Addr, u32 u32Val);
u8 aqua_sdio_reg_read(u32 u32Addr, u32 *pu32Val);
u8 aqua_sdio_reg_write(u32 u32Addr, u32 u32Val);
u8 aqua_xiu_reg_read(u32 bank, u32 u32Addr, u32 *pu32Val);
u8 aqua_xiu_reg_write(u32 bank, u32 u32Addr, u32 u32Val);

BOOL aqua_pif_init(void);
void aqua_pif_deinit(void);
BOOL pif_load_firmware(void);
BOOL pif_load_debug_firmware(void);

BOOL wait_aquarius_ready(void);
struct sk_buff* wifi_pif_rx(RX_RESULT_e *pResult);
BOOL get_aqua_qos_status(u8 *pU8data);
BOOL wifi_pif_tx(struct sk_buff *pSkb, SKB_DATA_TYPE_e data_type);
BOOL sdio_wait_rxtd_ready(u8 block_num);

#if PIF_TD_TEST
BOOL TD_LC3B_to_LC3B_test(void);
#endif


#endif //_WLAN_PIF_H_
