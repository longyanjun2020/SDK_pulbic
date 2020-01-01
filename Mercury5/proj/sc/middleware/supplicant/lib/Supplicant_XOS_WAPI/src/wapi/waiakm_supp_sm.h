#ifndef WAIAKM_SUPP_SM_H
#define WAIAKM_SUPP_SM_H

#include "supp_defs.h"

//**********************************************************************************
//                Constant Define
//**********************************************************************************
// Key
#define WAI_BK_LEN                      16
#define WAI_BK_CHALLENGE_LEN            32
//**********************************************************************************
//                Structure Define
//**********************************************************************************
struct wpa_bk {
    u8 bk[WAI_BK_LEN + WAI_BK_CHALLENGE_LEN]; /* WAI-KEY Unicast Encryption Key (UEK) */
    u8 challenge[WAI_BK_CHALLENGE_LEN]; /* Challenge */
} STRUCT_PACKED;

/**
 * struct waiakm_config - Per network configuration for WAIAKM state machines
 */
struct waiakm_config {

	/**
	 * workaround - Whether WAI workarounds are enabled
	 */
	unsigned int workaround;

	/**
	 * wai_disabled - Whether WAI is disabled
	 */
	int wai_disabled;
};
struct wai_reassemble {
    be16 seqence;
    u8 frag;
    struct wpabuf *buf; /* for EAP */
};
/**
 * struct waiakm_sm - Internal data for WAI AKM state machines
 */
struct waiakm_sm {

//  struct eap_sm *eap;
    struct wai_peer_config *config;
    struct wpabuf *waiReqData; /* for EAP */
    struct wpabuf *waiRespData; /* for EAP */
    struct wai_reassemble reaasemble;

    struct waiakm_config conf;
    struct waiakm_ctx *ctx;
    struct akm_method *m;
    struct wpa_bk bksa;
    void *akm_ctx;
    void *priv;

    unsigned int dot1xSuppWAIAKMFramesRx;
    unsigned int dot1xSuppInvalidWAIAKMFramesRx;
    unsigned int dot1xSuppWAILengthErrorFramesRx;
    unsigned int dot1xSuppLastWAIAKMFrameVersion;
    unsigned char SuppLastWAIAKMFrameSource[6];

};

struct akm_method {
    const char *name;
    void * (*init)(struct waiakm_sm *sm);
	void (*deinit)(struct waiakm_sm *sm, void *priv);
#if 0
    struct wpabuf * (*process)(struct eap_sm *sm, void *priv,
                   struct eap_method_ret *ret,
                   const struct wpabuf *reqData);
#endif
};
/**
 * struct waiakm_ctx - Global (for all networks) WAIAKM state machine context
 */
struct waiakm_ctx {
	/**
	 * ctx - Pointer to arbitrary upper level context
	 */
	void *ctx;


	/**
	 * cb - Function to be called when EAPOL negotiation has been completed
	 * @eapol: Pointer to EAPOL state machine data
	 * @success: Whether the authentication was completed successfully
	 * @ctx: Pointer to context data (cb_ctx)
	 *
	 * This optional callback function will be called when the EAPOL
	 * authentication has been completed. This allows the owner of the
	 * EAPOL state machine to process the key and terminate the EAPOL state
	 * machine. Currently, this is used only in RSN pre-authentication.
	 */
	void (*cb)(struct waiakm_sm *waiakm, int success, void *ctx);

	/**
	 * cb_ctx - Callback context for cb()
	 */
	void *cb_ctx;

	/**
	 * msg_ctx - Callback context for wpa_msg() calls
	 */
	void *msg_ctx;


	/**
	 * waiakm_send_ctx - Callback context for eapol_send() calls
	 */
	void *waiakm_send_ctx;

	/**
	 * waiakm_done_cb - Function to be called at successful completion
	 * @ctx: Callback context (ctx)
	 *
	 * This function is called at the successful completion of EAPOL
	 * authentication. If dynamic WEP keys are used, this is called only
	 * after all the expected keys have been received.
	 */
	void (*waiakm_done_cb)(void *ctx);

	/**
	 * waiakm_send - Send WAI AKM packets
	 * @ctx: Callback context (eapol_send_ctx)
	 * @type: WAI type (WAI_AUTH_*)
	 * @buf: Pointer to EAPOL payload
	 * @len: Length of the EAPOL payload
	 * Returns: 0 on success, -1 on failure
	 */
	int (*waiakm_send)(void *ctx, int type, const u8 *buf, size_t len);

	/**
	 * wps - WPS context data
	 *
	 * This is only used by EAP-WSC and can be left %NULL if not available.
	 */
	struct wps_context *wps;


};

extern int waiakm_sm_rx_wai(struct waiakm_sm *sm, const u8 *src, const u8 *buf,
              size_t len);
extern int waiakm_sm_tx_wai(struct waiakm_sm *sm);
extern void waiakm_sm_auth_complete(struct waiakm_sm *sm);
extern int waiakm_sm_get_key(struct waiakm_sm *sm, u8 *key, size_t len);
extern struct waiakm_sm *waiakm_sm_init(struct waiakm_ctx *ctx);
#endif /* WAIAKM_SUPP_SM_H */
