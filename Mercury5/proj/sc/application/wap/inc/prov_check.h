
/**
 * @file provCheck.h
 *   Header file of prov check function
 *
 */

#ifndef __PROV_CHECK_H__
#define __PROV_CHECK_H__
#ifndef UAPP_PUSH_PROV
//#error "PROV had been disabled"
#endif /* UAPP_PUSH_PROV */

#include <nccprov.h>

#ifdef __cplusplus
extern "C" {
#endif

//Now we can only assume that the PORT 23 is the port we do not supported.
#define UNSUPPORT_PORT 23 /* PORT numer for TELNET */

//PORT-check return value
#define PROV_PORT_INVALID   0    /* 0 invalid PORT characteristic with unsupported SERVICE or PORTNBR */
#define PROV_PORT_NOTDEFINE 1   /* 1 PORT characteristic not defined */
#define PROV_PORT_VALID     2   /* 2 valid PORT characteristic  */

/**
 * ProvCheck - Check the validity of currDoc
 * \param   Doc     Doc is a complete provisioning document include PXLOGICAL/NAPDEF/BOOTSTRAP..., etc.
 *
 * \return  <ul>
 *          <li>return 0 when failed
 *          <li>return 1 when success
 *      </ul>
 *
*/
int32_t ProvCheck(Prov_Doc *Doc);

#ifdef __cplusplus
}
#endif

#endif /* __PROV_CHECK_H__ */

