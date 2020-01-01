#ifndef __MMI_ON_OFF_APP_CFG__H__
#define __MMI_ON_OFF_APP_CFG__H__

//liuping add for Animation same as Melody 2010/05/18 -begin-
enum
{
	ONOFFAPP_ANIMATION_PRIORITY = 0, //以动画时间为主
	ONOFFAPP_MELODY_PRIORITY,        //以铃声时间为主
};
typedef u8 ONOFFAPP_AniMel_Priority_e;
typedef struct _ONOFFAPP_AniMel_Set_t
{
	u16       aniTime;                     //Gif:播放的时间,毫秒ms;No gif: 循环播放次数             
	boolean   bIsGif;                      //是否为gif图片
	ONOFFAPP_AniMel_Priority_e  amPriority;//动画还是铃声为主设置	
} ONOFFAPP_AniMel_Set_t;

#define CONFIG_AMR_ONOFFSETTING_LIST      CONFIG_DEFINE(CFGIT_ON_SETTING_AM_SAME, ONOFFAPP_AniMel_Set_t, 1, {6, FALSE, ONOFFAPP_ANIMATION_PRIORITY})

#define ONOFFAPP_AMR_ALL_CONFIG \
	    CONFIG_AMR_ONOFFSETTING_LIST

//liuping add for Animation same as Melody 2010/05/18 -end-

#endif //__MMI_ON_OFF_APP_CFG__H__

