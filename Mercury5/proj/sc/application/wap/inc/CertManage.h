/**
* @file CertManage.h
*
* Author: will.wang
* Class Id: CLSID_CDWAPAPP
* @version $Id$
*/

#ifndef __CERTIFICATE_MANAGE_H__
#define __CERTIFICATE_MANAGE_H__

#include "ncccert.h"

#define MAX_CERT_COUNT				20	 //bad! just for test
#define MAX_CERT_INFO_SIZE			4096 //bad! just for test
#define MAX_CERT_SERIAL_NUM_SIZE	1024
#define MAX_CERT_SUBJECT_SIZE		1024
#define MAX_CERT_ISSUER_SIZE		1024
#define MAX_CERT_SIGALG_SIZE		128
#define MAX_CERT_PUBKEY_SIZE		2048
#define MAX_CERT_PUBKEY_ALG_SIZE	128
#define MAX_CERT_VAILD_TIME_SIZE	128
#define MAX_CERT_VERSION_SIZE		8



/*store Certificate information*/
typedef struct
{
	uint8_t version[MAX_CERT_VERSION_SIZE];			/* certificate version */
	uint8_t validFrom[MAX_CERT_VAILD_TIME_SIZE];	/* valid start time */
	uint8_t validTo[MAX_CERT_VAILD_TIME_SIZE];		/* valid end time */
	uint8_t serialNum[MAX_CERT_SERIAL_NUM_SIZE];	/* serial number */
	uint8_t subject[MAX_CERT_SUBJECT_SIZE];			/* subject */
	uint8_t issuer[MAX_CERT_ISSUER_SIZE];			/* certificate issuer */
	uint8_t sigAlg[MAX_CERT_SIGALG_SIZE];			/* signature algorithm */
	uint8_t publicKey[MAX_CERT_PUBKEY_SIZE];		/* public key */
	uint8_t publicKeyAlg[MAX_CERT_PUBKEY_ALG_SIZE];	/* public key algorithm */
}CertInfo;

typedef struct
{
	uint32_t index;
	uint32_t subLen;
	CERT_STORE_TYPE csid;
	uint8_t sub[MAX_CERT_SUBJECT_SIZE]; // cert subject
}CertContext;

/* certificate list information */
typedef struct
{
	uint32_t count;									/* certificate count which to be list */
	CERT_STORE_TYPE csid;							/* certificate list store type */
	CertContext certItem[MAX_CERT_COUNT];			/* store a certificate item's base info */
}CertListInfo;


/* used in get certificate information(eg; get, delete, import and export certificate) */
typedef struct
{
	CERT_STORE_TYPE csid;							/* certificate store type */
	CERT_CERT_TYPE	certType;						/* certificate cert type */
	int32_t		certItemIndex;					/* item index, same to item id */
	uint32_t		extDataLen;						/* external data length */
	uint8_t			extData[MAX_CERT_INFO_SIZE];	/* external data buffer */
}CertAccessAttr;

/**
* Get certificates info for show certificate list
* \param  pCertList(output) stored certificate list info
* \param  csid(input) cert store type
* \return
*   CERT_OK     succeed
*   error code defined in ncccert.h
*/
int32_t get_cert_list_subject(CertListInfo	*pCertList, CERT_STORE_TYPE csid);


#if 1 //unused
/**
* Import certificate specified by the param fileName
* \param  fileName(input) certificate file name which you want to import
* \param  csid(input) certificate store type
*   CERT_OK, CERT_EXIST		succeed
*   error code defined in ncccert.h
*/
int32_t import_cert(uint8_t *fileName, CERT_STORE_TYPE csid);
#endif

/**
* Export certificate specified by the param index
* \param  exportToFile(input) export to
* \param  csid(input) certificate store type
* \param  certType(input) certificate type
* \param  index(input) index number
* \return
*   CERT_OK, CERT_EXIST success
*   error code defined in ncccert.h
*/
int32_t export_cert(const uint8_t *exportToFile, CERT_STORE_TYPE csid,
					CERT_CERT_TYPE certType, int32_t index);

/**
* get certificate information
* \param  pCertInfo(output) store certificate information
* \param  csid(input) certificate store type
* \param  certType(input) certificate type
* \param  index(input) index number
* \return
*   CERT_OK    success
*   error code defined in ncccert.h
*/
int32_t get_cert_info(CertInfo *pCertInfo, CERT_STORE_TYPE csid, CERT_CERT_TYPE certType, int32_t index);

#if 1 //unused
/**
* delete certificate
* \param  csid(input) certificate store type
* \param  certType(input) certificate type
* \param  index(input) index number
* \return
*   CERT_OK success
*   error code defined in ncccert.h
*/
int32_t delete_cert(CERT_STORE_TYPE csid, CERT_CERT_TYPE certType, int32_t index);
#endif

#endif

