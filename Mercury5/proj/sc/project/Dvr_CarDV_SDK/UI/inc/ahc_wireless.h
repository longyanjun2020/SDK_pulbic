
#ifndef _AHC_WIRELESS_H_
#define _AHC_WIRELESS_H_

// Support Download Queue feature
#define SUPPORT_DLQ (1)

typedef enum _QUERY_STATUS_TYPE {
	QUERY_TYPE_WIFI_STREAMABLE,
	QUERY_TYPE_STREAM_SUPPORT
}QUERY_STATUS_TYPE;

#if SUPPORT_DLQ
#define DFILEINFO_LEN (48)
typedef struct
{
	char szFilePath[DFILEINFO_LEN];
} DFILEINFO, *PDFILEINFO;

int DLQ_PushQueue(PDFILEINFO fi);
int DLQ_FindQueueItem(PDFILEINFO fi);
#else
#define DLQ_PushQueue(fi) (0)
#define DLQ_FindQueueItem(fi) (0)
#endif

void 	 uiRefreshLastCgiTick(void);
AHC_BOOL uiIsAppTimeOut(void);
//handle wireless message,communication between UI and network
AHC_BOOL uiQueryStatusInfo(QUERY_STATUS_TYPE ulCmd, void* InPara1, void* InPara2, void* OutPara);
AHC_BOOL uiRegisterNetworkCallback(void);

#endif // _AHC_AUDIO_H_
