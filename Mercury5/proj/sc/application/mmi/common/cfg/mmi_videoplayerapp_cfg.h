#ifndef __MMI_VIDEO_PLAYER_APP_CFG__H__
#define __MMI_VIDEO_PLAYER_APP_CFG__H__

#ifdef __MMI_KING_MOVIE__
#define VIDEOPLAYER_PASSWORD_MAX_BYTE_SIZE (32)
#define VIDEOPLAYER_PASSWORD_MAX_WORD_SIZE (VIDEOPLAYER_PASSWORD_MAX_BYTE_SIZE / 2)
#define VIDEOPLAYER_PASSWORD_RECORD_MAX_NUMBER (20)
#define VIDEOPLAYER_MD5HASH_SIZE (16)
#endif

enum
{
    MMI_VPLAYER_DOLBY_ON=0,
    MMI_VPLAYER_DOLBY_OFF=1,
    MMI_VPLAYER_DOLBY_NO=2
};
typedef u8 VPlayer_Dolby_e;

#ifdef __MMI_KING_MOVIE__
typedef struct
{
    u8 nDigest[VIDEOPLAYER_MD5HASH_SIZE + 1];
    char szPassword[VIDEOPLAYER_PASSWORD_MAX_WORD_SIZE + 1];
}VideoPlayerPasswordList_t;
#endif

// Allow Mater Reset
#define CONFIG_AMR_CFGIT_VIDEOPLAYER_VOLUME        CONFIG_DEFINE(CFGIT_VIDEOPLAYER_VOLUME,      u8, 1,       4 )
#define CONFIG_AMR_CFGIT_VIDEOPLAYER_DOLBY         CONFIG_DEFINE(CFGIT_VIDEOPLAYER_DOLBY, VPlayer_Dolby_e, 1, MMI_VPLAYER_DOLBY_OFF )
#define CONFIG_AMR_CFGIT_VIDEOPLAYER_BRIGHTNESS    CONFIG_DEFINE(CFGIT_VIDEOPLAYER_BRIGHTNESS,      u8, 1,       4 )

#define VIDEOPLAYERAPP_AMR_ALL_CONFIG \
                        CONFIG_AMR_CFGIT_VIDEOPLAYER_VOLUME \
                        CONFIG_AMR_CFGIT_VIDEOPLAYER_DOLBY \
                        CONFIG_AMR_CFGIT_VIDEOPLAYER_BRIGHTNESS

#ifdef __MMI_KING_MOVIE__
//Not Allow Mater Reset 
#define CONFIG_NAMR_CFGIT_VIDEOPLAYER_PASSWORD_LIST    CONFIG_DEFINE(CFGIT_VIDEOPLAYER_PASSWORD_LIST, VideoPlayerPasswordList_t, VIDEOPLAYER_PASSWORD_RECORD_MAX_NUMBER, \
{{{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}}, \
 {{""}, {""}} \
})
#else
#define CONFIG_NAMR_CFGIT_VIDEOPLAYER_PASSWORD_LIST
#endif

#define VIDEOPLAYERSRV_NAMR_ALL_CONFIG \
            CONFIG_NAMR_CFGIT_VIDEOPLAYER_PASSWORD_LIST

#endif //__MMI_VIDEO_PLAYER_APP_CFG__H__
