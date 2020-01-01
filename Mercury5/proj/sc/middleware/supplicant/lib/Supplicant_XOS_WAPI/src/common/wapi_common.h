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
 *      Project : WAPI
 *      Module  : NDIS interface
 *      Abstract: Header file define for NDIS interface
 *
 *  History:
 *      By            Date      Ver. Description
 *      ------------- --------  ---- -----------------------------------------
 *      Peter Lin     20110225  1.0  initial version
 *
 *****************************************************************************/
#ifndef WAPI_COMMON_H
#define WAPI_COMMON_H

/* IEEE Std 802.1X-2004 */

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

struct wai_hdr {
	be16 version;
	u8 type;
    u8 sub_type;
    be16 reserved;
	be16 length;
    be16 seqence;
    u8 frag;
    u8 flag;
	/* followed by length octets of data */
} STRUCT_PACKED;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */

#define WAI_VERSION 1
#define WAI_TYPE_WAI 1
#define WAI_FLAG_MORE_FRAG      1

enum {
    WAI_PRE_AUTH            = 1,
    WAI_STA_KEY_REQ         = 2,
    WAI_AUTH_ACTIVATION     = 3,
    WAI_ACCESS_AUTH_REQ     = 4,
    WAI_ACCESS_AUTH_RESP    = 5,
    WAI_CERT_AUTH_REQ       = 6,
    WAI_CERT_AUTH_RESP      = 7,
    WAI_UNI_KEY_REQ         = 8,
    WAI_UNI_KEY_RESP        = 9,
    WAI_UNI_KEY_CONFIRM     = 10,
    WAI_MUL_KEY_ANNOUNCE    = 11,
    WAI_MUL_KEY_RESP        = 12
};

//Flag
#define WAI_IND_FLAG_BK_REKEY       0x01
#define WAI_IND_FLAG_PRE_AUTH       0x02
#define WAI_IND_FLAG_CERT_REQ       0x04
#define WAI_IND_FLAG_OPT            0x08
#define WAI_IND_FLAG_USK_REKEY      0x10
#define WAI_IND_FLAG_KEY_NEGO       0x20
#define WAI_IND_FLAG_KEY_REVOKE     0x40

#endif /* WAPI_COMMON_H */
