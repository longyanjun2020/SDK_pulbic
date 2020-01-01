/*
 *	平台私有预定义
 */

#ifndef MCFCOMMON_PRIV_H
#define MCFCOMMON_PRIV_H
#ifdef __cplusplus   
extern "C"{   
#endif // __cplusplus
#include "McfCommon.h"
#include "adaptVendor.h"
	//=====================全局结构定义开始=================================
	typedef struct
	{
		MVOID *GdiGlobalVar; //图像模块全局结构
		MVOID *LogGlobalVar; //日志模块
		MVOID *TimerGlobalVar; //Timer全局结构;
		MVOID *AudioGlobalVar; // AUDIO全局结构
		MVOID *KeyGlobalVar;//keypad全局变量
		MVOID *SocketGlobalVar;//socket全局结构指针
		MVOID *PenGlobalVar;// Pen(Touch) 全局变量;
		MVOID *IdleGlobalVar;//Idle(Icon)全局变量
		MVOID *SmsGlobalVar;//Sms全局变量
		MVOID *DtcntGlobalVar; //Dtcnt全局变量
	}GlobalVar;
    //=====================全局结构定义结束=================================
 
	//=====================模块初始化函数申明===============================
	extern MINT McfGdi_Init(MVOID); //gdi模块初始化函数	
	extern MBOOL McfTimerInit(MVOID);	
	extern MBOOL McfLogInit(MVOID);	
	extern MBOOL McfAudioInit(MVOID);	
	extern MBOOL McfKeyInit(MVOID);	
	extern MVOID McfSocketInit(MVOID);	
	extern MBOOL McfPenInit(MVOID);
	extern MBOOL McfIdleInit(MVOID);
	extern MBOOL McfSmsInit(MVOID);
	extern MBOOL McfDtcntInit(MVOID);
	extern MBOOL McfFileInit(MVOID);
	extern MBOOL McfSim_Init(MVOID);	
	//=====================模块初始化函数申明结束===========================

	//=====================模块反初始化函数申明===============================
	extern MVOID McfGdi_UnInit(MVOID);
	extern MVOID McfTimerUninit(MVOID);
	extern MVOID McfLogUninit(MVOID);
	extern MVOID McfAudioUninit(MVOID);
	extern MVOID McfKeyUninit(MVOID);
	extern MVOID McfSocketUninit(MVOID);
	extern MVOID McfPenUninit(MVOID);
	extern MVOID McfIdleUninit(MVOID);
	extern MVOID McfSmsUninit(MVOID);
	extern MVOID McfDtcntUninit(MVOID);
	extern MVOID McfFileUninit(MVOID);
	extern MVOID McfSim_Uninit(MVOID);
	//=====================模块反初始化函数申明结束===========================





	//==========================公用助手函数================================

	/*
		
		*	路径处理助手函数 
		*   如：D：/picture  ->  /NOR_FLASH_0/pictrue , E:/pic -> /CARD/pic
		*	ppnFullPath 需外部释放
	*/
	extern MINT  Filepath_Format(const MWCHAR* oldpathname,MWCHAR **ppnFullPath);
	MUINT		McfCmn_GetVenHandle();
	void	McfCmn_CloseVenHandle();
	//============================Porting初始化/反初始化接口============================
	MVOID McfCmn_priv_Init(MVOID);
	MVOID McfCmn_priv_Uninit(MVOID);


#ifdef __cplusplus   
}   
#endif // __cplusplus
#endif//#ifndef MCRCOMMON_H
