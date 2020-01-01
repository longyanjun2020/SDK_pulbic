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
 *      Module  : WAPI AKM interface
 *      Abstract: Header file define for WAPI interface
 *
 *  History:
 *      By            Date      Ver. Description
 *      ------------- --------  ---- -----------------------------------------
 *      Peter Lin     20110225  1.0  initial version
 *
 *****************************************************************************/
#ifndef WAI_AKM_H
#define WAI_AKM_H
//**********************************************************************************
//                Constant Define
//**********************************************************************************
#define WAI_FIX_FLAG_LEN        1
#define WAI_FIX_CTX_ID          2
#define WAI_FIX_CTX_LEN         2
#define WAI_PKEY_PARAM_LEN      1
#define WAI_ECDH_PARAM_ID       1
#define WAI_ECDH_PARAM_LEN      2
#define WAI_ATTRIBUTE_ID        1
#define WAI_ATTRIBUTE_LEN       2
#define AUTH_IDENTIFIER_LEN     32
#define ASUE_CHALLENGE_LEN      32
#define AE_CHALLENGE_LEN        32
#define ECC_PRIVATE_KEY_LEN     24
#define ECC_PUBLIC_KEY_LEN      48
#define ECC_PUBLIC_KEY_XY_LEN   24
#define ECC_SIGNATURE_LEN       48
#define ECC_PUBLIC_KEY_COM_LEN  1

//Format
#define WAI_USE_FORMAT_X509V3       1
#define WAI_USE_FORMAT_GBW          2
#define WAI_USE_FORMAT_OID          1
#define WAI_HASH_SHA_256            1
#define WAI_SIGN_ECDSA_192          1
//Access Result
#define WAI_ACCESS_RESULT_SUCCESS       0
#define WAI_ACCESS_RESULT_CERT_FAIL     1
#define WAI_ACCESS_RESULT_CERT_ERROR    2
#define WAI_ACCESS_RESULT_ERROR         3

//
#define WAI_VERIFY_CERT_SUCCESS                 0
#define WAI_VERIFY_CERT_UNKNOWN_ISSUER          1
#define WAI_VERIFY_CERT_UNTRUSTED_ROOT          2
#define WAI_VERIFY_CERT_INVALID_TIME            3
#define WAI_VERIFY_CERT_INVALID_SIGNATURE       4
#define WAI_VERIFY_CERT_REVOKED                 5
#define WAI_VERIFY_CERT_INVALID_USAGE           6
#define WAI_VERIFY_CERT_FAIL_UNKNOW             7
//**********************************************************************************
//                Structure Define
//**********************************************************************************
struct wai_auth_activation {
    u8 indicate_flag;
    u8 *auth_identifier;
    struct wai_identity *asu_identity;
    struct wai_certificate *ae_certificate;
    struct wai_ecc_param *ecdh_param;
};


/**
 * struct eap_ssl_data - TLS data for EAP methods
 */
struct wai_akm_data {
	/**
	 * conn - TLS connection context data from tls_connection_init()
	 */
	struct akm_connection *conn;

	/**
	 * tls_out - TLS message to be sent out in fragments
	 */
	u8 *akm_out;

	/**
	 * tls_out_len - Total length of the outgoing TLS message
	 */
	size_t akm_out_len;

	/**
	 * tls_out_pos - The current position in the outgoing TLS message
	 */
	size_t akm_out_pos;

	/**
	 * tls_out_limit - Maximum fragment size for outgoing TLS messages
	 */
	size_t akm_out_limit;

	/**
	 * tls_in - Received TLS message buffer for re-assembly
	 */
	u8 *akm_in;

	/**
	 * tls_in_len - Number of bytes of the received TLS message in tls_in
	 */
	size_t akm_in_len;

	/**
	 * tls_in_left - Number of remaining bytes in the incoming TLS message
	 */
	size_t akm_in_left;

	/**
	 * tls_in_total - Total number of bytes in the incoming TLS message
	 */
	size_t akm_in_total;

	/**
	 * phase2 - Whether this TLS connection is used in EAP phase 2 (tunnel)
	 */
	int phase2;

	/**
	 * include_tls_length - Whether the TLS length field is included even
	 * if the TLS data is not fragmented
	 */
	int include_akm_length;

	/**
	 * tls_ia - Whether TLS/IA is enabled for this TLS connection
	 */
	int akm_ia;

	/**
	 * eap - Pointer to EAP state machine allocated with eap_peer_sm_init()
	 */
	struct waiakm_sm *wai;
};
void wai_akm_process_auth_activation(struct waiakm_sm *sm, const struct wpabuf *req);
void wai_akm_process_access_auth_resp(struct waiakm_sm *sm, const struct wpabuf *req);
struct akm_method * wai_akm_get_method(void);
#endif /* WAI_AKM_H */
