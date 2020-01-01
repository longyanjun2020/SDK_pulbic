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
#ifndef AKM_H
#define AKM_H

//**********************************************************************************
//                Constant Define
//**********************************************************************************
#define AKM_RANDOM_LEN 32
#define AKM_MASTER_SECRET_LEN 48
#define AKM_SESSION_ID_MAX_LEN 32
#define WAI_TLV_SIGNATURE               1
#define WAI_TLV_CERT_VERIFY_RESULT      2
#define WAI_TLV_IDENTITY_LIST           3

//**********************************************************************************
//                Structure Define
//**********************************************************************************
struct wai_identity {
    u16 identifier;
    u16 len;
    u8  *data;
    struct x509_name subject;
    struct x509_name issuer;
    unsigned long serial_number;
}STRUCT_PACKED;

struct wai_certificate {
    u16 identifier;
    u16 len;
    struct x509_certificate *cert;
}STRUCT_PACKED;

struct wai_ecc_param {
    u8 pad[1];                         //for alignment issue
    u8 identifier;
    u16 len;
    u8 *data;
    struct asn1_oid oid;
}STRUCT_PACKED;

struct wai_key_data {
    u8 len;
    u8 compress;
    u8 key_data[ECC_PUBLIC_KEY_LEN];
};
struct wai_sign_algorithm {
    u16 len;
    u8  hash_id;
    u8  sign_id;
    u8  ecc_id;
    u16 param_len;
    u8  *param_data;
};
struct wai_sign_value {
    u16 len;
    u8 data[ECC_SIGNATURE_LEN];
};
struct wai_sign_attribute {
    u8 type;
    u16 len;
    struct wai_identity *identity;
    struct wai_sign_algorithm *sign_algo;
    struct wai_sign_value *sign_value;
};
struct wai_cert_attribute {
    u8 type;
    u16 len;
    u8 *ae_challenge;
    u8 *asue_challenge;
    u8 asue_verify_result;
    u16 asue_cert_id;
    u16 asue_cert_len;
    u8 *asue_cert;
    u8 ae_verify_result;
    u16 ae_cert_id;
    u16 ae_cert_len;
    u8 *ae_cert;
};


struct akm_connection {
    enum {
        AE_ACTIVATION, ASUE_REQUEST,
    } state;

    u8 *asue_cert_der;
    u8 auth_identifier[AUTH_IDENTIFIER_LEN];
    u8 asue_challenge[ASUE_CHALLENGE_LEN];
    u8 ae_challenge[ASUE_CHALLENGE_LEN];
    struct wai_identity asu_identity;
    struct wai_identity ae_identity;
    struct wai_identity asue_identity;
    struct wai_certificate ae_cert;
    struct wai_certificate asue_cert;
    struct wai_ecc_param ecdh_param;
    struct wai_sign_algorithm  sign_alg;
    struct wai_sign_value      auth_req_sign;
    struct wai_sign_value      ae_cert_sign;	
    struct wai_key_data dh_px;
    struct wai_key_data dh_py;
    struct wai_sign_attribute asue_sign;

    u8 dh_x[ECC_PRIVATE_KEY_LEN];                   //DHCP temporary key
    u8 dh_key_x[ECC_PUBLIC_KEY_XY_LEN];
    u8 dh_key_y[ECC_PUBLIC_KEY_XY_LEN];
    u8 session_id[AKM_SESSION_ID_MAX_LEN];
    size_t session_id_len;
    u8 client_random[AKM_RANDOM_LEN];
    u8 server_random[AKM_RANDOM_LEN];
    u8 master_secret[AKM_MASTER_SECRET_LEN];


#if 0
#define MAX_CIPHER_COUNT 30
    u16 cipher_suites[MAX_CIPHER_COUNT];
    size_t num_cipher_suites;

    u16 prev_cipher_suite;

    u8 *client_hello_ext;
    size_t client_hello_ext_len;

    /* The prime modulus used for Diffie-Hellman */
    u8 *dh_p;
    size_t dh_p_len;
    /* The generator used for Diffie-Hellman */
    u8 *dh_g;
    size_t dh_g_len;
    /* The server's Diffie-Hellman public value */
    u8 *dh_ys;
    size_t dh_ys_len;
#endif
    struct akm_credentials *cred;

 //   tlsv1_client_session_ticket_cb session_ticket_cb;
    void *session_ticket_cb_ctx;
    u8 asue_verify_result;
    u8 ae_verify_result;
};

struct akm_keys {
	const u8 *master_key; /* TLS master secret */
	size_t master_key_len;
	const u8 *client_random;
	size_t client_random_len;
	const u8 *server_random;
	size_t server_random_len;
	const u8 *inner_secret; /* TLS/IA inner secret */
	size_t inner_secret_len;
};

struct akm_config {
	const char *opensc_engine_path;
	const char *pkcs11_engine_path;
	const char *pkcs11_module_path;
};

/**
 * struct tls_connection_params - Parameters for TLS connection
 * @ca_cert: File or reference name for CA X.509 certificate in PEM or DER
 * format
 * @ca_cert_blob: ca_cert as inlined data or %NULL if not used
 * @ca_cert_blob_len: ca_cert_blob length
 * @ca_path: Path to CA certificates (OpenSSL specific)
 * @subject_match: String to match in the subject of the peer certificate or
 * %NULL to allow all subjects
 * @altsubject_match: String to match in the alternative subject of the peer
 * certificate or %NULL to allow all alternative subjects
 * @client_cert: File or reference name for client X.509 certificate in PEM or
 * DER format
 * @client_cert_blob: client_cert as inlined data or %NULL if not used
 * @client_cert_blob_len: client_cert_blob length
 * @private_key: File or reference name for client private key in PEM or DER
 * format (traditional format (RSA PRIVATE KEY) or PKCS#8 (PRIVATE KEY)
 * @private_key_blob: private_key as inlined data or %NULL if not used
 * @private_key_blob_len: private_key_blob length
 * @private_key_passwd: Passphrase for decrypted private key, %NULL if no
 * passphrase is used.
 * @dh_file: File name for DH/DSA data in PEM format, or %NULL if not used
 * @dh_blob: dh_file as inlined data or %NULL if not used
 * @dh_blob_len: dh_blob length
 * @engine: 1 = use engine (e.g., a smartcard) for private key operations
 * (this is OpenSSL specific for now)
 * @engine_id: engine id string (this is OpenSSL specific for now)
 * @ppin: pointer to the pin variable in the configuration
 * (this is OpenSSL specific for now)
 * @key_id: the private key's id when using engine (this is OpenSSL
 * specific for now)
 * @cert_id: the certificate's id when using engine
 * @ca_cert_id: the CA certificate's id when using engine
 * @tls_ia: Whether to enable TLS/IA (for EAP-TTLSv1)
 *
 * TLS connection parameters to be configured with tls_connection_set_params()
 * and tls_global_set_params().
 *
 * Certificates and private key can be configured either as a reference name
 * (file path or reference to certificate store) or by providing the same data
 * as a pointer to the data in memory. Only one option will be used for each
 * field.
 */
struct akm_connection_params {
	const char *ca_cert;
	const u8 *ca_cert_blob;
	size_t ca_cert_blob_len;
	const char *ca_path;
	const char *subject_match;
	const char *altsubject_match;
	const char *client_cert;
	const u8 *client_cert_blob;
	size_t client_cert_blob_len;
	const char *private_key;
	const u8 *private_key_blob;
	size_t private_key_blob_len;
	const char *private_key_passwd;
	const char *dh_file;
	const u8 *dh_blob;
	size_t dh_blob_len;
	int tls_ia;

};
extern struct akm_connection * akm_connection_init(void *akm_ctx);
extern void akm_connection_deinit(struct akm_connection *conn);
extern int akm_connection_set_params(void *akm_ctx, struct akm_connection *conn,
                  const struct akm_connection_params *params);
#endif /* AKM_H */
