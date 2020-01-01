#ifndef _MAE_ELEAK_
#define _MAE_ELEAK_
#ifdef __cplusplus
extern "C" {
#endif

extern void MKernel_SendLeakInfoToUI(void *info, int Len);
extern void MKernel_SendHitToUI(void *info, int Len);
extern void MKernel_SendLeakReleaseToUI(void *info, int Len);
extern void MKernel_SendAPStartToUI(u16 uid);
extern void MKernel_SendAPStopToUI(u16 uid);
extern boolean MKernel_getRecordPoint();
extern void MKernel_DumpInst();
extern void MKernel_DumpCallStack();
extern void MKernel_DumpObj(void *addr);

extern void MKernel_SendCreateToUI(u32 uid);
extern void MKernel_SendDestroyToUI(u32 uid);
extern void MKernel_SendTraceToUI(void* addr, int len);
extern void MKernel_SendSpyToUI(void* addr, int len);

#define SEND_LEAK_INFO(data, length)  do{	\
        MKernel_SendLeakInfoToUI((void *)data, length); \
    } while(0)

#define SEND_LEAK_RELEASE(data, length)  do{	\
        MKernel_SendLeakReleaseToUI((void *)data, length); \
    } while(0)
    
#define SEND_APP_START(uid) do{ \
    	MKernel_SendAPStartToUI(uid);\
	}while(0)

#define SEND_APP_STOP(uid) do{ \
    	MKernel_SendAPStopToUI(uid);\
	}while(0)

#ifdef __cplusplus
}
#endif

#endif
