/**
 *
 * @file    test_throughput.h
 * @brief   This file is the common define file for the test throughput
 *
 * @author  Kenping.Wang
 * @version $Id:$
 *
 */
 
#ifndef __TEST_THROUGHPUT_H__
#define __TEST_THROUGHPUT_H__

#include "ven_sdk.h"
#include "ven_dbg.h"


#define _THROUGHPUT VEN_DBG_GROUP_0

#define _THROUGHPUT_GENERAL _THROUGHPUT | VEN_DBG_LEVEL_30

#define _THROUGHPUT_IPERF_TX_PORT 5001
#define _THROUGHPUT_IPERF_RX_PORT 5002

#define DATA_SIZE_PER_SEND 2920


enum 
{ 
    TEST_THROUGHPUT_TCP_TX = 0, 
    TEST_THROUGHPUT_TCP_RX = 1,
    TEST_THROUGHPUT_TCP_TXRX = 2,
    TEST_THROUGHPUT_UDP_TX = 3, 
    TEST_THROUGHPUT_UDP_RX = 4 
};

#endif /* __TEST_THROUGHPUT_H__ */

