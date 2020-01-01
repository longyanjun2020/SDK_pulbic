////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/**
 * @file    dev_nxp5760.h
 * @brief   This file defines the common constant of FM radio driver
 */
#ifndef __FMR_DRV_HC_
#define __FMR_DRV_HC_


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

#define INTREG_R        0
#define FRQSET_R        1
#define TNCTRL_R        2
#define FRQCHK_R        3
#define TUNCHK_R        4
#define TESTREG_R       5
#define MANID_R         6
#define CHIPID_R        7


#define INTREG_W        0
#define FRQSET_W        1
#define TNCTRL_W        2
#define TESTREG_W       3


/**
 * \brief Register INTEREG 
 */
#define INTREG_IFFLAG_POS		  12					
#define INTREG_IFFLAG_MSK		  (0x1 << INTREG_IFFLAG_POS)

#define INTREG_LEVFLAG_POS	  11				
#define INTREG_LEVFLAG_MSK		(0x1 << INTREG_LEVFLAG_POS)

#define INTREG_FRRFLAG_POS	  9					
#define INTREG_FRRFLAG_MSK	  (0x1 << INTREG_FRRFLAG_POS)

#define INTREG_BLFLAG_POS		  8					
#define INTREG_BLFLAG_MSK		  (0x1 << INTREG_BLFLAG_POS)

#define INTREG_IFMSK_POS		  4					
#define INTREG_IFMSK_MSK		  (0x1 << INTREG_IFMSK_POS)

#define INTREG_LEVMSK_POS	    3					
#define INTREG_LEVMSK_MSK		  (0x1 << INTREG_LEVMSK_POS)

#define INTREG_FRRMSK_POS	    1					
#define INTREG_FRRMSK_MSK	    (0x1 << INTREG_FRRMSK_POS)

#define INTREG_BLMSK_POS		  0				
#define INTREG_BLMSK_MSK		  (0x1 << INTREG_BLMSK_POS)


/**
 * \brief FRQSET register
 */
#define FRQSET_SUD_POS		  15			
#define FRQSET_SUD_MSK		  (0x1 << FRQSET_SUD_POS)

#define FRQSET_SM_POS		    14			
#define FRQSET_SM_MSK		    (0x1 << FRQSET_SM_POS)

#define FRQSET_FR_POS		    0					
#define FRQSET_FR_MSK		    (0x3FFF << FRQSET_FR_POS)


/**
 * \brief TNCTRL register
 */
#define TNCTRL_PUPD_POS		  14					
#define TNCTRL_PUPD_MSK		  (0x1 << TNCTRL_PUPD_POS)

#define TNCTRL_BLIM_POS		  13					
#define TNCTRL_BLIM_MSK		  (0x1 << TNCTRL_BLIM_POS)

#define TNCTRL_SWPM_POS		  12					
#define TNCTRL_SWPM_MSK		  (0x1 << TNCTRL_SWPM_POS)

#define TNCTRL_IFCTC_POS	  11					
#define TNCTRL_IFCTC_MSK	  (0x1 << TNCTRL_IFCTC_POS)

#define TNCTRL_AFM_POS		  10				
#define TNCTRL_AFM_MSK		  (0x1 << TNCTRL_AFM_POS)

#define TNCTRL_SMUTE_POS	  9					
#define TNCTRL_SMUTE_MSK	  (0x1 << TNCTRL_SMUTE_POS)

#define TNCTRL_SNC_POS		  8					
#define TNCTRL_SNC_MSK		  (0x1 << TNCTRL_SNC_POS)

#define TNCTRL_MU_POS		    7					
#define TNCTRL_MU_MSK		    (0x1 << TNCTRL_MU_POS)

#define TNCTRL_SSL_POS		  5					
#define TNCTRL_SSL_MSK		  (0x3 << TNCTRL_SSL_POS)

#define TNCTRL_HLSI_POS		  4				
#define TNCTRL_HLSI_MSK		  (0x1 << TNCTRL_HLSI_POS)

#define TNCTRL_MST_POS	    3					
#define TNCTRL_MST_MSK	    (0x1 << TNCTRL_MST_POS)

#define TNCTRL_SWP_POS		  2				
#define TNCTRL_SWP_MSK		  (0x1 << TNCTRL_SWP_POS)

#define TNCTRL_DTC_POS	    1					
#define TNCTRL_DTC_MSK	    (0x1 << TNCTRL_DTC_POS)

#define TNCTRL_AHLSI_POS	  0				
#define TNCTRL_AHLSI_MSK	  (0x1 << TNCTRL_AHLSI_POS)



/**
 * \brief Register FRQCHK
 */
#define FRQCHK_PLL_POS		  0					
#define FRQCHK_PLL_MSK		  (0x3FFF << FRQCHK_PLL_POS)



/**
 * \brief Register TUNCHK
 */

#define TUNCHK_IF_POS		    9				
#define TUNCHK_IF_MSK		    (0x7F << TUNCHK_IF_POS)

#define TUNCHK_TUNTO_POS		8					
#define TUNCHK_TUNTO_MSK		(0x1 << TUNCHK_TUNTO_POS)

#define TUNCHK_LEV_POS	    4				
#define TUNCHK_LEV_MSK	    (0xF << TUNCHK_LEV_POS)

#define TUNCHK_LD_POS		    3				
#define TUNCHK_LD_MSK		    (0x1 << TUNCHK_LD_POS)

#define TUNCHK_STEREO_POS	  2				
#define TUNCHK_STEREO_MSK	  (0x1 << TUNCHK_STEREO_POS)


/**
 * \brief Register TESTREG 
 */
#define TESTREG_LHM_POS		    15				
#define TESTREG_LHM_MSK		    (0x1 << TESTREG_LHM_POS)

#define TESTREG_RHM_POS		    14				
#define TESTREG_RHM_MSK		    (0x1 << TESTREG_RHM_POS)

#define TESTREG_TUN_POS		    10				
#define TESTREG_TUN_MSK		    (0x1 << TESTREG_TUN_POS)

#define TESTREG_RFAGC_POS		  9					/**< RFAGC on/off */
#define TESTREG_RFAGC_MSK		  (0x1 << TESTREG_RFAGC_POS)

#define TESTREG_INTCTRL_POS	  8					/**< no interrupt generated on INTX */
#define TESTREG_INTCTRL_MSK	  (0x1 << TESTREG_INTCTRL_POS)

#define TESTREG_SNCLEV_POS	  5					/**< starting point mono/stereo blending */
#define TESTREG_SNCLEV_MSK	  (0x1 << TESTREG_SNCLEV_POS)

#define TESTREG_TM_POS		    4					/**< normal operation */
#define TESTREG_TM_MSK		    (0x1 << TESTREG_TM_POS)

#define TESTREG_TB_POS		    0					/**< test bits, refer TEA5760UK spec */
#define TESTREG_TB_MSK		    (0xF << TESTREG_TB_POS)


/**
 * \brief Register MANID
 */
#define MANID_VERSION_POS		  12				/**< version code */
#define MANID_VERSION_MSK		  (0xF << MANID_VERSION_POS)

#define MANID_MAN_ID_POS		  1					/**< manufacturer ID code */
#define MANID_MAN_ID_MSK		  (0x3FF << MANID_MAN_ID_POS)

#define MANID_IDAV_POS		    0					/**< chip has manufacturer ID or not*/
#define MANID_IDAV_MSK		    (0x1 << MANID_IDAV_POS)


/**
 * \brief Register CHIPID
 */
#define CHIPID_CHIP_ID_POS		0					/**< TEA5760UK chip identification code */
#define CHIPID_CHIP_ID_MSK		(0xFFFF << CHIPID_CHIP_ID_POS)





#if 0

#define DEVICEID    0x00
#define CHIPID      0x01
#define POWERCFG    0x02
#define CHANNEL     0x03
#define SYSCONFIG1  0x04
#define SYSCONFIG2  0x05
#define SYSCONFIG3  0x06
#define TEST1       0x07
#define TEST2       0x08
#define BOOTCONFIG  0x09
#define STATUSRSSI  0x0A
#define READCHAN    0x0B
#define RDSA        0x0C
#define RDSB        0x0D
#define RDSC        0x0E
#define RDSD        0x0F


#define DEVICEID_PN_POS         12
#define DEVICEID_PN_MSK         (0xF << DEVICEID_PN_POS)

#define DEVICEID_MFGID_POS      0
#define DEVICEID_MFGID_MSK      (0xFFF << DEVICEID_MFGID_POS)

#define CHIPID_REV_POS          10
#define CHIPID_REV_MSK          (0x3F << CHIPID_REV_POS)

#define CHIPID_DEV_POS          6
#define CHIPID_DEV_MSK          (0xF << CHIPID_DEV_POS)

#define CHIPID_FIRMWARE_POS     0
#define CHIPID_FIRMWARE_MSK     (0x3F << CHIPID_FIRMWARE_POS)

#define POWERCFG_DSMUTE_POS     15
#define POWERCFG_DSMUTE_MSK     (0x1 << POWERCFG_DSMUTE_POS)

#define POWERCFG_DMUTE_POS      14
#define POWERCFG_DMUTE_MSK      (0x1 << POWERCFG_DMUTE_POS)

#define POWERCFG_MONO_POS       13
#define POWERCFG_MONO_MSK       (0x1 << POWERCFG_MONO_POS)

#define POWERCFG_RDSM_POS       11
#define POWERCFG_RDSM_MSK       (0x1 << POWERCFG_RDSM_POS)

#define POWERCFG_SKMODE_POS     10
#define POWERCFG_SKMODE_MSK     (0x1 << POWERCFG_SKMODE_POS)

#define POWERCFG_SEEKUP_POS     9
#define POWERCFG_SEEKUP_MSK     (0x1 << POWERCFG_SEEKUP_POS)

#define POWERCFG_SEEK_POS       8
#define POWERCFG_SEEK_MSK       (0x1 << POWERCFG_SEEK_POS)

#define POWERCFG_DISABLE_POS    6
#define POWERCFG_DISABLE_MSK    (0x1 << POWERCFG_DISABLE_POS)

#define POWERCFG_ENABLE_POS     0
#define POWERCFG_ENABLE_MSK     (0x1 << POWERCFG_ENABLE_POS)

#define CHANNEL_TUNE_POS        15
#define CHANNEL_TUNE_MSK        (0x1 << CHANNEL_TUNE_POS)

#define CHANNEL_CHAN_POS        0
#define CHANNEL_CHAN_MSK        (0x3FF << CHANNEL_CHAN_POS)


#define SYSCONFIG1_RDSIEM_POS   15
#define SYSCONFIG1_RDSIEM_MSK   (0x1 << SYSCONFIG1_RDSIEM_POS)

#define SYSCONFIG1_STCIEM_POS   14
#define SYSCONFIG1_STCIEM_MSK   (0x1 << SYSCONFIG1_STCIEM_POS)

#define SYSCONFIG1_RDS_POS      12
#define SYSCONFIG1_RDS_MSK      (0x1 << SYSCONFIG1_RDS_POS)


#define SYSCONFIG1_DE_POS       11
#define SYSCONFIG1_DE_MSK       (0x1 << SYSCONFIG1_DE_POS)

#define SYSCONFIG1_AGCD_POS     10
#define SYSCONFIG1_AGCD_MSK     (0x1 << SYSCONFIG1_AGCD_POS)

#define SYSCONFIG1_BLNDADJ_POS  6
#define SYSCONFIG1_BLNDADJ_MSK  (0x3 << SYSCONFIG1_BLNDADJ_POS)

#define SYSCONFIG1_GPIO3_POS    4
#define SYSCONFIG1_GPIO3_MSK    (0x3 << SYSCONFIG1_GPIO3_POS)

#define SYSCONFIG1_GPIO2_POS    2
#define SYSCONFIG1_GPIO2_MSK    (0x3 << SYSCONFIG1_GPIO2_POS)

#define SYSCONFIG1_GPIO1_POS    0
#define SYSCONFIG1_GPIO1_MSK    (0x3 << SYSCONFIG1_GPIO1_POS)


#define SYSCONFIG2_SEEKTH_POS   8
#define SYSCONFIG2_SEEKTH_MSK   (0xFF << SYSCONFIG2_SEEKTH_POS)

#define SYSCONFIG2_BAND_POS     6
#define SYSCONFIG2_BAND_MSK     (0x3 << SYSCONFIG2_BAND_POS)

#define SYSCONFIG2_SPACE_POS    4
#define SYSCONFIG2_SPACE_MSK    (0x3 << SYSCONFIG2_SPACE_POS)

#define SYSCONFIG2_VOLUME_POS   0
#define SYSCONFIG2_VOLUME_MSK   (0xF << SYSCONFIG1_GPIO2_POS)

#define SYSCONFIG2_GPIO1_POS    0
#define SYSCONFIG2_GPIO1_MSK    (0x3 << SYSCONFIG1_GPIO1_POS)



#define SYSCONFIG3_SMUTER_POS   14
#define SYSCONFIG3_SMUTER_MSK   (0x3 << SYSCONFIG3_SMUTER_POS)


#define SYSCONFIG3_SMUTEA_POS   12
#define SYSCONFIG3_SMUTEA_MSK   (0x3 << SYSCONFIG3_SMUTER_POS)

#define SYSCONFIG3_RDSPRF_POS   9
#define SYSCONFIG3_RDSPRF_MSK   (0x1 << SYSCONFIG3_RDSPRF_POS)

#define SYSCONFIG3_VOLEXT_POS   8
#define SYSCONFIG3_VOLEXT_MSK   (0x1 << SYSCONFIG3_VOLEXT_POS)

#define SYSCONFIG3_SKSNR_POS    4
#define SYSCONFIG3_SKSNR_MSK    (0xF << SYSCONFIG3_SKSNR_POS)

#define SYSCONFIG3_SKCNT_POS    0
#define SYSCONFIG3_SKCNT_MSK    (0xF << SYSCONFIG3_SKCNT_POS)


#define TEST1_XOSCEN_POS        15
#define TEST1_XOSCEN_MSK        (0x1 << TEST1_XOSCEN_POS)

#define TEST1_AHIZEN_POS        14
#define TEST1_AHIZEN_MSK        (0x1 << TEST1_AHIZEN_POS)


#define STATUSRSSI_RDSR_POS     15
#define STATUSRSSI_RDSR_MSK     (0x1 << STATUSRSSI_RDSR_POS)

#define STATUSRSSI_STC_POS      14
#define STATUSRSSI_STC_MSK      (0x1 << STATUSRSSI_STC_POS)

#define STATUSRSSI_SFBL_POS     13
#define STATUSRSSI_SFBL_MSK     (0x1 << STATUSRSSI_SFBL_POS)

#define STATUSRSSI_AFCRL_POS    12
#define STATUSRSSI_AFCRL_MSK    (0x1 << STATUSRSSI_AFCRL_POS)

#define STATUSRSSI_RDSS_POS     11
#define STATUSRSSI_RDSS_MSK     (0x1 << STATUSRSSI_RDSS_POS)

#define STATUSRSSI_BLERA_POS    9
#define STATUSRSSI_BLERA_MSK    (0x3 << STATUSRSSI_BLERA_POS)

#define STATUSRSSI_ST_POS       8
#define STATUSRSSI_ST_MSK       (0x1 << STATUSRSSI_ST_POS)

#define STATUSRSSI_RSSI_POS     0
#define STATUSRSSI_RSSI_MSK     (0xFF << STATUSRSSI_RSSI_POS)


#define READCHAN_BLERB_POS      14
#define READCHAN_BLERB_MSK      (0x3 << READCHAN_BLERB_POS)

#define READCHAN_BLERC_POS      12
#define READCHAN_BLERC_MSK      (0x3 << READCHAN_BLERC_POS)

#define READCHAN_BLERD_POS      10
#define READCHAN_BLERD_MSK      (0x3 << READCHAN_BLERD_POS)

#define READCHAN_READCHAN_POS   0
#define READCHAN_READCHAN_MSK   (0x3FF << READCHAN_READCHAN_POS)

#define RDSA_RDSA_POS           0
#define RDSA_RDSA_MSK           (0xFFFF << RDSA_RDSA_POS)

#define RDSA_RDSB_POS           0
#define RDSA_RDSB_MSK           (0xFFFF << RDSA_RDSB_POS)

#define RDSA_RDSC_POS           0
#define RDSA_RDSC_MSK           (0xFFFF << RDSA_RDSC_POS)

#define RDSA_RDSD_POS           0
#define RDSA_RDSD_MSK           (0xFFFF << RDSA_RDSD_POS)

#endif

#endif //ifndef __FM_DRV_HC__
