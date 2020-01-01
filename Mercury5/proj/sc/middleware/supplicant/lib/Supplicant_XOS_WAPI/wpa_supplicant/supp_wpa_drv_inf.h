/*****************************************************************************
 *
 *  Copyright (c) 2008-2009 MStar Semiconductor, Inc.  All rights reserved.
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
 *  --------------------------------------------------------------------------
 *
 *      Project : Kona
 *      Module  : NDIS interface
 *      Abstract: Header file define for NDIS interface
 *
 *  History:
 *      By            Date      Ver. Description
 *      ------------- --------  ---- -----------------------------------------
 *      Peter Lin     20090727  1.0  initial version
 *
 *****************************************************************************/
#ifndef _WPA_DRV_INF
#define _WPA_DRV_INF
//**********************************************************************************
//                Constant Define
//**********************************************************************************
#define WIFI_DEV_STATUS_EVENT                       0x00000001
#define WIFI_DEV_L2_EVENT                           0x00000002
// DEVICE L2 EVENT
// DEVICE STATUS EVENT
#if 0
#define NDISUIO_NOTIFICATION_RESET_START            0x00000001
#define NDISUIO_NOTIFICATION_RESET_END              0x00000002
#define NDISUIO_NOTIFICATION_MEDIA_CONNECT          0x00000004
#define NDISUIO_NOTIFICATION_MEDIA_DISCONNECT       0x00000008
#define NDISUIO_NOTIFICATION_BIND                   0x00000010
#define NDISUIO_NOTIFICATION_UNBIND                 0x00000020
#define NDISUIO_NOTIFICATION_ADAPTER_ARRIVAL        0x00000040
#define NDISUIO_NOTIFICATION_ADAPTER_REMOVAL        0x00000080
#define NDISUIO_NOTIFICATION_DEVICE_POWER_UP        0x00000200
#define NDISUIO_NOTIFICATION_DEVICE_POWER_DOWN      0x00000400
#define NDISUIO_NOTIFICATION_MEDIA_SPECIFIC_NOTIFICATION 0x00000800
#endif
//TI EVENT DEFINITION
enum
{
    IPC_EVENT_ASSOCIATED = 0,
    IPC_EVENT_DISASSOCIATED,
    IPC_EVENT_LINK_SPEED,
    IPC_EVENT_AUTH_SUCC,
    IPC_EVENT_SCAN_REPORT,
    IPC_EVENT_SCAN_COMPLETE,
    IPC_EVENT_SCAN_STOPPED,
    IPC_EVENT_CCKM_START,
    IPC_EVENT_MEDIA_SPECIFIC,
    IPC_EVENT_MAX_OS_EVENT = IPC_EVENT_MEDIA_SPECIFIC,
    IPC_EVENT_EAPOL,
    IPC_EVENT_BOUND,
    IPC_EVENT_UNBOUND,
    IPC_EVENT_PREAUTH_EAPOL,
    IPC_EVENT_RESERVED2,
    IPC_EVENT_LOW_RSSI,
    IPC_EVENT_TSPEC_STATUS,
    IPC_EVENT_TSPEC_RATE_STATUS,
    IPC_EVENT_MEDIUM_TIME_CROSS,
    IPC_EVENT_ROAMING_COMPLETE,
    IPC_EVENT_EAP_AUTH_FAILURE,
    IPC_EVENT_WPA2_PREAUTHENTICATION,
    IPC_EVENT_TRAFFIC_INTENSITY_THRESHOLD_CROSSED,
    IPC_EVENT_SCAN_FAILED,
    IPC_EVENT_WPS_SESSION_OVERLAP,
    IPC_EVENT_RSSI_SNR_TRIGGER_0,
    IPC_EVENT_RSSI_SNR_TRIGGER_1,
	IPC_EVENT_LOGGER,
    IPC_EVENT_NOT_ASSOCIATED,
    IPC_EVENT_BSS_LOSS,
    IPC_EVENT_REASSOCIATION_RESP,
    IPC_EVENT_IMMEDIATE_SCAN_REPORT,
    IPC_EVENT_CONTINUOUS_SCAN_REPORT,
    IPC_EVENT_RSSI_SNR_TRIGGER,
    IPC_EVENT_AP_DISCONNECT,
    IPC_EVENT_TX_RETRY_FALIURE,
    IPC_EVENT_RE_AUTH_STARTED,
    IPC_EVENT_RE_AUTH_COMPLETED,
    IPC_EVENT_RE_AUTH_TERMINATED,
    IPC_EVENT_TIMEOUT,
    IPC_EVENT_GWSI,
    IPC_EVENT_MAX
};

//**********************************************************************************
//                Structure Define
//**********************************************************************************
typedef struct {
  unsigned int type;
  unsigned int buf_offset;
  unsigned int buf_size;
} WIFI_DEVICE_NOTIFICATION, *PWIFI_DEVICE_NOTIFICATION;
//**********************************************************************************
//                Extern Function Declaration
// **********************************************************************************
extern void wifi_driver_notify(unsigned int type, unsigned char *data, unsigned int len);
extern void wifi_drv_init(void);
extern void wifi_drv_close(void);
extern int MStar_IOCTL_Get(unsigned int Oid,	void *in_data, long *in_len);
extern int MStar_IOCTL_Set(unsigned int Oid,	void *in_data, long in_len);
#endif
