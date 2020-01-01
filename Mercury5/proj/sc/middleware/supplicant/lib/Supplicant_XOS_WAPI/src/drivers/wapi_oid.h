/*
 * wapi_oid.h
 *
 *  Created on: 2009/6/24
 *      Author: peter-jc.lin
 */

#ifndef WAPI_OID_H_
#define WAPI_OID_H_

/**********************************************************************************
                Constant Define
 **********************************************************************************/
#define OID_802_11_WAPI_AUTHENTICATION_MODE                 0x0D019000
#define OID_802_11_WAPI_ENCRYPTION_STATUS                   0x0D019001
#define OID_802_11_WAPI_CAPABILITY                          0x0D019002

/**********************************************************************************
                Macro Define
 **********************************************************************************/
/**********************************************************************************
                Type Define
 **********************************************************************************/
enum NDIS_802_11_WAPI_AUTHENTICATION_MODE {
	Ndis802_11AuthWapiNone,
	Ndis802_11AuthWapiPSK,
	Ndis802_11AuthWapiCERT
};

enum ndis_80211_wapi_encr_status {
	Ndis802_11EncryptionSMS4Enabed,
	Ndis802_11EncryptionSMS4Disabled
};

typedef struct _NDIS_802_11_WAPI_CAPABILITY
{
  ULONG  Length;
  ULONG  Version;
  ULONG  NoOfBKIDs;
  ULONG  NoOfAuthEncryptPairsSupported;
  NDIS_802_11_AUTHENTICATION_ENCRYPTION AuthenticationEncryptionSupported[1];
} NDIS_802_11_WAPI_CAPABILITY, *PNDIS_802_11_WAPI_CAPABILITY;

#endif /* WAPI_OID_H_ */
