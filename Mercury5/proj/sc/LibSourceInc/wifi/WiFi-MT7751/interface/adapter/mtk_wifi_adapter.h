/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/


#ifndef _MTK_WIFI_ADAPTER_H
#define _MTK_WIFI_ADAPTER_H

void wlan_get_mac_addr(unsigned char* mac_addr);

char* wlan_get_version(void);

int wlan_get_mode(void);

void wlan_tx_pkt(struct pbuf *p);

int wlan_get_assoc_list(char* buf, unsigned int buf_size);

extern unsigned int kalGetTxAvaliableFrameCount(void);

void wlan_config_func_pin(unsigned char function, unsigned char pin);

void wlan_config_cal_data(unsigned char calibrateType, void *data);


/**************** MTK_MFG ********************/
#ifndef kal_bool
typedef unsigned char 			kal_bool;
#endif
#ifndef kal_uint8
typedef unsigned char           kal_uint8;
#endif
#ifndef kal_int8
typedef signed char             kal_int8;
#endif
#ifndef kal_uint16
typedef unsigned short int      kal_uint16;
#endif
#ifndef kal_int16
typedef signed short int        kal_int16;
#endif
#ifndef kal_uint32
typedef unsigned int            kal_uint32;
#endif
#ifndef kal_int32
typedef signed int              kal_int32;
#endif

typedef enum
{
   WNDRV_TEST_RATE_1M = 0,     /* 1M          */
   WNDRV_TEST_RATE_2M,         /* 2M          */
   WNDRV_TEST_RATE_5_5M,       /* 5.5M        */
   WNDRV_TEST_RATE_11M,        /* 11M         */
   WNDRV_TEST_RATE_6M,         /* 6M          */
   WNDRV_TEST_RATE_9M,         /* 9M          */
   WNDRV_TEST_RATE_12M,        /* 12M         */
   WNDRV_TEST_RATE_18M,        /* 18M         */
   WNDRV_TEST_RATE_24M,        /* 24M         */
   WNDRV_TEST_RATE_36M,        /* 36M         */
   WNDRV_TEST_RATE_48M,        /* 48M         */
   WNDRV_TEST_RATE_54M,        /* 54M         */
   WNDRV_TEST_MOD_MCS0,        /* 802.11n MSC 0 */
   WNDRV_TEST_MOD_MCS1,        /* 802.11n MSC 1 */
   WNDRV_TEST_MOD_MCS2,        /* 802.11n MSC 2 */
   WNDRV_TEST_MOD_MCS3,        /* 802.11n MSC 3 */
   WNDRV_TEST_MOD_MCS4,        /* 802.11n MSC 4 */
   WNDRV_TEST_MOD_MCS5,        /* 802.11n MSC 5 */
   WNDRV_TEST_MOD_MCS6,        /* 802.11n MSC 6 */
   WNDRV_TEST_MOD_MCS7,        /* 802.11n MSC 7 */
   WNDRV_TEST_MOD_MCS32,       /* 802.11n MSC 32 */
   WNDRV_TEST_RATE_COUNT       /* Total count */
} wndrv_test_rate_enum;

typedef enum
{  WNDRV_TX_ALL_ZEROS = 0,
   WNDRV_TX_ALL_ONES,
   WNDRV_TX_ALTERNATE_BITS,
   WNDRV_TX_PSEUDO_RANDOM
} wndrv_test_pkt_tx_pattern_enum;

typedef enum
{
   WNDRV_TEST_BW_20MHZ = 0,
   WNDRV_TEST_BW_40MHZ,
   WNDRV_TEST_BW_U20MHZ,
   WNDRV_TEST_BW_L20MHZ,
   WNDRV_TEST_BW_COUNT
} wndrv_test_bandwidth_enum;
typedef enum
{
   WNDRV_TEST_TX_GI_400NS = 0,
   WNDRV_TEST_TX_GI_800NS,
   WNDRV_TEST_TX_GI_COUNT
} wndrv_test_guard_intval_enum;
typedef enum
{
   WNDRV_TEST_TX_GREEN_FIELD = 0,
   WNDRV_TEST_TX_MIX_MODE,
   WNDRV_TEST_TX_MODE_COUNT
} wndrv_test_mode_sel_enum;

#ifndef WNDRV_PACKET_SIZE_COUNT
#define WNDRV_PACKET_SIZE_COUNT   (6)
#endif
#ifndef WNDRV_PACKET_TYPE_COUNT
#define WNDRV_PACKET_TYPE_COUNT   (3)
#endif

typedef struct
{
   kal_uint32                       ch_freq;/* Frq, units are kHz */
   wndrv_test_rate_enum             tx_rate;
   kal_uint8                        txAnt;  /* 0 for Antenna 0 and 1 for Antenna 1 */
   kal_uint16                       tx_gain_dac;
   wndrv_test_bandwidth_enum        txBw;              /* tx bandwidth */
   wndrv_test_guard_intval_enum     txGI;              /* tx guard interval */
   wndrv_test_mode_sel_enum         txMode;            /* tx preamble mode */
} wndrv_test_tx_struct;

typedef struct
{
   kal_uint32                       ch_freq;           /* Frq, units are kHz */
   wndrv_test_rate_enum             tx_rate;
   kal_uint16                       tx_gain_dac;
   kal_uint32                       pktCount;
   kal_uint32                       pktInterval;       /* interval between each Tx Packet */
   kal_uint32                       pktLength;         /* 24~1500 */
   wndrv_test_pkt_tx_pattern_enum   pattern;           /* content of the Tx Packet */
   kal_uint8                        txAnt;             /* 0 for Antenna 0 and 1 for Antenna 1 */
   kal_bool                         is_short_preamble; /* 0 for long preamble and 1 for short preamble */
   kal_uint8                        mac_header[ 24 ];  /* Frame Ctrl, Duration = 2bytes + 2bytes */
                                                       /* Address 1 = 6 bytes */
                                                       /* Address 2 = 6 bytes */
                                                       /* Address 3 = 6 bytes */
                                                       /* Sequence Ctrl = 2 bytes */
   wndrv_test_bandwidth_enum        txBw;              /* tx bandwidth */
   wndrv_test_guard_intval_enum     txGI;              /* tx guard interval */
   wndrv_test_mode_sel_enum         txMode;            /* tx preamble mode */
} wndrv_test_pkt_tx_struct;

typedef struct
{
   kal_uint32   int_rx_ok_num;          /* number of packets that Rx ok from interrupt (Total Rx count) */
   kal_uint32   int_crc_err_num;        /* number of packets that CRC error from interrupt */
   kal_uint32   pau_rx_pkt_count;       /* number of packets that Rx ok from PAU (Total Rx count) */
   kal_uint32   pau_crc_err_count;      /* number of packets that CRC error from PAU */
   kal_uint32   pau_cca_count;          /* CCA rising edge count */
   kal_uint32   pau_rx_fifo_full_count; /* number of lost packets due to FiFo full */
   kal_uint32   int_long_preamble_num;
   kal_uint32   int_short_preamble_num;
   kal_uint32   int_rate_ok_num[ WNDRV_TEST_RATE_54M+1 ];
   kal_uint32   int_rate_crc_err_num[ WNDRV_TEST_RATE_54M+1 ];
   kal_int32    int_rssi_max;
   kal_int32    int_rssi_min;
   kal_int32    int_rssi_mean;
   kal_int32    int_rssi_variance;
   kal_uint32   packetSize[WNDRV_PACKET_SIZE_COUNT];  /* 0~63, 64~127, 128~255, 256~511, 512~1023, 1024~2047 */
   kal_uint32   packetType[WNDRV_PACKET_TYPE_COUNT];   /* Data, Management, Control */
   kal_uint32   int_rate_ok_num_802_11n[WNDRV_TEST_MOD_MCS7- WNDRV_TEST_RATE_54M ];
   kal_uint32   int_rate_crc_err_num_802_11n[WNDRV_TEST_MOD_MCS7- WNDRV_TEST_RATE_54M ];
} wndrv_test_rx_status_struct;

extern void RFTool_WiFi_EnterTestMode(void);
extern void RFTool_WiFi_Stop(void);
extern void RFTool_WiFi_ContTx(kal_uint8 country_code[2], wndrv_test_tx_struct cont_tx);
extern void RFTool_WiFi_CarrierSupp(kal_uint8 country_code[2], wndrv_test_tx_struct carrier_supp);
extern void RFTool_WiFi_LocalFreq(kal_uint8 country_code[2], wndrv_test_tx_struct local_freq);
extern void RFTool_WiFi_PktTx(kal_uint8 country_code[2], wndrv_test_pkt_tx_struct pkt_tx);
extern void RFTool_WiFi_PktRx(kal_uint32 ch_freq, void (* callback) (wndrv_test_rx_status_struct* result));

#endif  /* _MTK_WIFI_ADAPTER_H */
