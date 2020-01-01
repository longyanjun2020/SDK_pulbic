#include "ven_dbg.h"

#define DALVIK_DEBUG
#define DALVIK_DEBUG_SENDTRACE

/*Trace group and level */
#define _DALVIK	VEN_DBG_GROUP_0

/* Define levels by functionality */
#define _DVM_TASK	_DALVIK | VEN_DBG_LEVEL_0	//TASK
#define _DVM_VM	_	_DALVIK | VEN_DBG_LEVEL_1	//VM
#define _DVM_MSG	_DALVIK | VEN_DBG_LEVEL_2	//message parsing
#define _DVM_LIBC	_DALVIK | VEN_DBG_LEVEL_3	//C library
#define _DVM_JAVA	_DALVIK | VEN_DBG_LEVEL_4	//java class
#define _DVM_AMS	_DALVIK | VEN_DBG_LEVEL_5	//ams
/* porting layer */
#define _DVM_GRA	_DALVIK | VEN_DBG_LEVEL_6	//2D graphics
#define _DVM_MMAPI	_DALVIK | VEN_DBG_LEVEL_7	//mmapi
#define _DVM_MEDIA	_DALVIK | VEN_DBG_LEVEL_8	//media control
#define _DVM_NET	_DALVIK | VEN_DBG_LEVEL_9	//network
#define _DVM_WMA	_DALVIK | VEN_DBG_LEVEL_10	//WMA
#define _DVM_PUSH	_DALVIK | VEN_DBG_LEVEL_11	//PUSH registry
#define _DVM_3D		_DALVIK | VEN_DBG_LEVEL_12	//java 3D
#define _DVM_UTIL	_DALVIK | VEN_DBG_LEVEL_13	//utility functions
#define _DVM_KBD	_DALVIK | VEN_DBG_LEVEL_14	//keypad/touch screen
#define _DVM_OTA	_DALVIK | VEN_DBG_LEVEL_15	//OTA
/* porting layer */


#if defined (DALVIK_DEBUG)
	#if defined (DALVIK_DEBUG_SENDTRACE)
		extern s8 UartSendTrace(const char* strFormat, ...);
		#define DVM_TRACE_LIBC(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_TASK(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_VM(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_MSG(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_JAVA(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_AMS(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_GRA(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_MMAPI(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_MEDIA(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_NET(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_WMA(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_PUSH(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_3D(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_UTIL(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_KBD(...) UartSendTrace(__VA_ARGS__)
		#define DVM_TRACE_OTA(...) UartSendTrace(__VA_ARGS__)
	#else
		#define DVM_TRACE_LIBC(...) dbg_trace(_DVM_LIBC, __VA_ARGS)
		#define DVM_TRACE_TASK(...) dbg_trace(_DVM_TASK, __VA_ARGS)
		#define DVM_TRACE_VM(...) dbg_trace(_DVM_VM, __VA_ARGS)
		#define DVM_TRACE_MSG(...) dbg_trace(_DVM_MSG, __VA_ARGS)
		#define DVM_TRACE_JAVA(...) dbg_trace(_DVM_JAVA, __VA_ARGS)
		#define DVM_TRACE_AMS(...) dbg_trace(_DVM_AMS, __VA_ARGS)
		#define DVM_TRACE_GRA(...) dbg_trace(_DVM_GRA, __VA_ARGS)
		#define DVM_TRACE_MMAPI(...) dbg_trace(_DVM_MMAPI, __VA_ARGS)
		#define DVM_TRACE_MEDIA(...) dbg_trace(_DVM_MEDIA, __VA_ARGS)
		#define DVM_TRACE_NET(...) dbg_trace(_DVM_NET, __VA_ARGS)
		#define DVM_TRACE_WMA(...) dbg_trace(_DVM_WMA, __VA_ARGS)
		#define DVM_TRACE_PUSH(...) dbg_trace(_DVM_PUSH, __VA_ARGS)
		#define DVM_TRACE_3D(...) dbg_trace(_DVM_3D, __VA_ARGS)
		#define DVM_TRACE_UTIL(...) dbg_trace(_DVM_UTIL, __VA_ARGS)
		#define DVM_TRACE_KBD(...) dbg_trace(_DVM_KBD, __VA_ARGS)
		#define DVM_TRACE_OTA(...) dbg_trace(_DVM_OTA, __VA_ARGS)
	#endif
#else
	#define DVM_TRACE_LIBC(...)
	#define DVM_TRACE_TASK(...)
	#define DVM_TRACE_VM(...)
	#define DVM_TRACE_MSG(...)
	#define DVM_TRACE_JAVA(...)
	#define DVM_TRACE_AMS(...)
	#define DVM_TRACE_GRA(...)
	#define DVM_TRACE_MMAPI(...)
	#define DVM_TRACE_MEDIA(...)
	#define DVM_TRACE_NET(...)
	#define DVM_TRACE_WMA(...)
	#define DVM_TRACE_PUSH(...)
	#define DVM_TRACE_3D(...)
	#define DVM_TRACE_UTIL(...)
	#define DVM_TRACE_KBD(...)
	#define DVM_TRACE_OTA(...)
#endif
