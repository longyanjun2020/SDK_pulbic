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
* @file    wlan_debug.h
* @version
* @brief   used for WLAN debug
*/

#ifndef _WLAN_DEBUG_H_
#define _WLAN_DEBUG_H_


/*****************************************************************************
 * Constant
 *****************************************************************************/
#define USE_TRACE_DBG_MSG           1

#define L2_THROUGHPUT_TEST          0

#define PIF_BASIC_TEST    	        0
#define PIF_TD_TEST    			    0 //need enable loopback in Aquarius' sdio.c

//debug level
#define WIFI_DBG_LEVEL_0    _MIXED_050
#define WIFI_DBG_LEVEL_1    _MIXED_051
#define WIFI_DBG_LEVEL_2    _MIXED_052
#define WIFI_DBG_LEVEL_3    _MIXED_053
#define WIFI_DBG_LEVEL_4    _MIXED_054
#define WIFI_DBG_LEVEL_5    _MIXED_055

#define _WIFI               _MIXED1

#if USE_TRACE_DBG_MSG == 0
#define WIFI_DBG_LEVEL      WIFI_DBG_LEVEL_2
#endif


/************************************************************************
 * Macros
 ************************************************************************/
#if USE_TRACE_DBG_MSG
#define wifi_dbg_printf     _TRACE1
#define wifi_err_printf     KER_ERROR_DIAGNOSE
#else
void wifi_dbg_init(void);
void wifi_dbg_printf(u32 level, char *fmt, ...);
void wifi_err_printf(u32 level, char *fmt, ...);
#endif

extern void wpa_printf(u32 level, char *fmt, ...);

extern u32 coex_wifi_get_request_cnt(void);
extern void coex_wifi_clear_request_cnt(void);

#endif //_WLAN_DEBUG_H_
