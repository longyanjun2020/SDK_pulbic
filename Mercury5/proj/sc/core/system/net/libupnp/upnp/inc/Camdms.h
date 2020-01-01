#ifndef UPNP_AIT_DMS_UTIL_H
#define UPNP_AIT_DMS_UTIL_H

#include "sample_util.h"

#include "ithread.h"
#include "upnp.h"

#include <stdlib.h>
#include <string.h>

/*! Index of control service */
#define DMS_SERVICE_CONNECT    0

/*! Index of picture service */
#define DMS_SERVICE_DIRECT    1
#define DMS_SERVICE_DIDL    2
#define DMS_SERVICE_UPNP    3
#define DMS_SERVICE_META    4
#define DMS_SERVICE_COMP    5
//#define DMS_SERVICE_DIRECT    6

/* CD: ContentDirctory */
//IN
#define DMS_CD_OID    	0
#define DMS_CD_BRF   	1
#define DMS_CD_FIL    	2
#define DMS_CD_STI    	3
#define DMS_CD_RQC   	4
#define DMS_CD_SCT		5
//OUT
#define DMS_CD_RST    	0
#define DMS_CD_UID    	1
#define DMS_CD_NRT    	2
#define DMS_CD_TTM    	3


int DmsBroweResponse(
	/*! [in] Document of action request. */
	IXML_Document *in,
	/*! [in] Action result. */
	IXML_Document **out,
	/*! [out] ErrorString in case action was unsuccessful. */
	const char **errorString);

#endif
	