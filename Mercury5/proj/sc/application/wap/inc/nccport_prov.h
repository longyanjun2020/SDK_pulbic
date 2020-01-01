
/**
 * @file
 * Prov Porting Layer
 *
 * Basic support functions that are needed by provission.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_prov Interface
 * - NCCPort_prov_checkPin()
 * - NCCPort_brwprov_getInstallRes()
 * - NCCPort_brwprov_convertCharEntity()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_PROV_H__
#define __NCCPORT_PROV_H__

#ifndef UAPP_PUSH_PROV
//#error "PROV had been disabled"
#endif /* UAPP_PUSH_PROV */

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Get installation information from user.
 */
int32_t NCCPort_brwprov_getInstallRes();

/**
 * Convert charactor entity to a platform specified charactor
 * \param str Charactor entity
 * \return Converted charactor.
 */
int8_t* NCCPort_brwprov_convertCharEntity(int8_t *str);

void NCCPort_wapprov_algHMACInit(void *ctx, const void *key, int len, unsigned int id);

unsigned char *NCCPort_wapprov_algHMAC( unsigned int id, const void *key, int key_len,
    const unsigned char *d, int n, unsigned char *md, unsigned int *md_len);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPORT_PROV_H__ */

