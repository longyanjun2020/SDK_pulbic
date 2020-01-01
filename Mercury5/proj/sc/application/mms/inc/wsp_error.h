
#ifndef __WSP_ERROR_H__
#define __WSP_ERROR_H__

#include <ncc_types.h>
#include <wsp_conf.h>

#define     WAP_USER_CANCEL         (-1)    /**< User cancel */
#define     WAP_METHODABORT         (-2)    /**< Method abort */
#define     WAP_TIMEOUT             (-3)    /**< Timeout */
#define     WAP_INVALIDURL          (-4)    /**< Invalid URL */
#define     WAP_BIGGERTHANMOR       (-5)    /**< Retransmit number exceed the MOR */
#define     WAP_FIND_NO_DATA        (-6)    /**< Find no data in system buffer */
#define     WAP_SUSPEND             (-7)    /**< suspend.not supported */
#define     WAP_RESUMING            (-8)    /**< Resuming.not supported */
#define     WAP_OCCUR_ERROR         (-9)    /**< Error */
#define     WAP_RECEVING_DATA       (-10)   /**< In data process */
#define     WAP_DISCONNECT_SESSION  (-11)   /**< Disconnect session */
#define     WAP_FETCH_DATA_OK       (-12)   /**< Fetch data success */
#define     WAP_NETWORK_ERROR       (-13)   /**< Network error */
#define     WAP_REDIRECT            (-14)   /**< WSP Redirect */
#define     WAP_REDIRECT_PERMATE    (-15)   /**< WSP Redirect permately */
#define     WAP_CONNECT_FAIL        (-16)   /**< Session create failure*/
#define     WAP_WTLS_CONNECT_FAIL   (-17)   /**< Connect failure when create WTLS session */
#define     WAP_AUTHENTICATION      (-18)   /**< WAP Authentication */

#endif /* __WSP_ERROR_H__ */

