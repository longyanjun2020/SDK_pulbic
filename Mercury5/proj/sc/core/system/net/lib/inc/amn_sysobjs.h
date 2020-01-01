/*
*********************************************************************************************************
*                   AIT Multimedia Network -- AIT Kernel Driver System Objects
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: definitions of System Objects of AIT's uC/OS MMPF/MMPS/AHC components for Network layer
*
*/

#ifndef __AMN_SYSTEM_OBJECTS_FOR_NETWORK_DEFINITIONS__
#define __AMN_SYSTEM_OBJECTS_FOR_NETWORK_DEFINITIONS__

// Definitions for Config Manager
//*******************************************************************************************************
#include "amn_osal.h"
#include "amn_config.h"

#define FAKE_MJPEG 0//using 2 fake JPEG for testing

#define CFGSPACE_VALTYP__STR          255
#define CFGSPACE_VALTYP__INT          254
#define CFGSPACE_VALTYP__CHOICE       253
#define CFGSPACE_SUPPORT_AUTH 0 //Set 1 to support authentication checking
#define	CFGSPACE_RUNTIME			  1
#define CFGSPACE_XML                  2 //long text with XML
#define	CFGSPACE_PLAIN   			  4 //long text with plain text

#define choice_val max_strlen  /* The value of CHOICE */
struct amn_cfgspace_value_t {
	u8_t  type;
	u8_t  max_strlen;      // For the STR type, maximum string length
	u8_t  cur_strlen;      // For the STR type, the string length in use
	u8_t  attr;			   // Attrib [RUNTIME VALUE or NO]
	union {
		char *strVal;
		int   intVal;
		void *choice_set;  // Pointer to the set of CHOICE type
	} v;
};

struct amn_system_config_space_t {
	char *cfg_name;
	struct amn_cfgspace_value_t *cfg_val;
};

// Helper macros for retrieving COMMA seperated values. Ex. "123, abc, 999"
//---------------------------------------------------------------------------
#define PARSEBUF_DIM  32
#define PARSEBUF_LEN  256

#ifdef __AMN_DEFINES_FOR_CONFIGSPACE_STATICS__
int  __parsebuf_idx = 0;
char __parsebuf[PARSEBUF_DIM][PARSEBUF_LEN];
#else
extern int  __parsebuf_idx;
extern char __parsebuf[PARSEBUF_DIM][PARSEBUF_LEN];
#endif

static INLINE char* amn_get_parsebuf()
{
	char *ptr = __parsebuf[__parsebuf_idx];
	__parsebuf_idx = (__parsebuf_idx + 1) % PARSEBUF_DIM;
	return ptr;
}

#define amn_cfgval_sfields2( cvgval, f1, f2 ) do { \
	char *buf = amn_get_parsebuf(); \
	strncpy( buf, cvgval->v.strVal, PARSEBUF_LEN ); \
	f1 = strtok( buf, ", "); \
	if (f1) f2 = strtok( NULL, ", "); \
	else    f2 = NULL; \
} while (0)

#define amn_cfgval_sfields3( cvgval, f1, f2, f3 ) do { \
	amn_cfgval_sfields2( cvgval, f1, f2 ); \
	if (f2) f3 = strtok( NULL, ", "); \
	else    f3 = NULL; \
} while (0)

#define atox(i,s)  do { \
	if (!strncmp(s,"0x",2)) sscanf( s, "0x%x", &(i) ); \
	else                    sscanf( s, "%d", &(i) ); \
} while (0)

#define amn_cfgval_ifields2( cvgval, i1, i2 ) do { \
	char *s1, *s2; \
	amn_cfgval_sfields2( cvgval, s1, s2 ); \
	if (s1) atox( i1, s1 ); \
	if (s2) atox( i2, s2 ); \
} while (0)

#define amn_cfgval_ifields3( cvgval, i1, i2, i3 ) do { \
	char *s1, *s2, *s3; \
	amn_cfgval_sfields3( cvgval, s1, s2, s3 ); \
	if (s1) atox( i1, s1 ); \
	if (s2) atox( i2, s2 ); \
	if (s3) atox( i3, s3 ); \
} while (0)

//---------------------------------------------------------------------------
struct amn_config_space_handler_t {
	char *cfg_name;
	u8_t namelen;
	int (*set_cb) (char* key, struct amn_cfgspace_value_t *cfg, char *val);     // call-back handler for SET action
	int (*act_cb) ();     // call-back handler for other actions
};

#define MAX_CONFIG_SPACE_HANDLER   CONFIG_SPACE_NUMBER
extern struct amn_config_space_handler_t amn_ConfigSpaceHandler[MAX_CONFIG_SPACE_HANDLER];

//---------------------------------------------------------------------------
void init_config_manager(void);
void amn_config_reset_wlocate(void);
int amn_config_wlocate( char *key );
int amn_config_locate( char *key );
struct amn_cfgspace_value_t *amn_config_get( int space_type, char *key );
struct amn_cfgspace_value_t *amn_config_wget( int space_type, char *key, char **cfg_name );
int amn_config_set( int space_type, char *key, char *val );
int amn_config_iset( int space_type, char *key, int val );
int amn_config_register_handlers( char *cfgname, int (*setcb)(char* key, struct amn_cfgspace_value_t *cfg, char *val), int (*actcb)() );
unsigned char net_config_changed(void);
unsigned char apply_user_net_setting(int type, char* path);

//---------------------------------------------------------------------------
#ifdef __AMN_OS_LINUX__
typedef struct _MenuInfo {
    char uiIMGSize;
    char uiIMGQuality;
    char uiIMGStabilize;
    char uiFlashMode;
	struct amn_config_space_storage_t amnConfigSpace;
} MenuInfo, *pMenuInfo;

#endif

#define amn_factConfig_get(key)       amn_config_get( CONFIG_SPACE_TYPE_FACTORY, key )
#define amn_factConfig_set(key,val)   // ==> no permission

#define amn_currConfig_get(key)       amn_config_get( CONFIG_SPACE_TYPE_CURRENT, key )
#define amn_currConfig_set(key,val)   amn_config_set( CONFIG_SPACE_TYPE_CURRENT, key, val )
#define amn_currConfig_iset(key,val)  amn_config_iset(CONFIG_SPACE_TYPE_CURRENT, key, val )

// The <key> is in wildcard, we need to let known the current <cfgname>
#define amn_currConfig_wget(key,cfg_val, cfg_name) do { \
		cfg_val = amn_config_wget( CONFIG_SPACE_TYPE_CURRENT, key, &(cfg_name) ); \
} while (0)

static INLINE struct amn_cfgspace_value_t* amn_currConfig_get_enum( char *key, int idx )
{
	char *buf = amn_get_parsebuf();
	snprintf( buf, PARSEBUF_LEN, key, idx );
	return amn_currConfig_get(buf);
}

static INLINE int amn_currConfig_set_enum( char *key, int idx, char *val )
{
	char *buf = amn_get_parsebuf();
	snprintf( buf, PARSEBUF_LEN, key, idx );
	return amn_currConfig_set(buf, val);
}

static INLINE int amn_currConfig_iset_enum( char *key, int idx, int val )
{
	char *buf = amn_get_parsebuf();
	snprintf( buf, PARSEBUF_LEN, key, idx );
	return amn_currConfig_iset(buf, val);
}


//ncgi_ret web_config_act(char *key, char *val, char *buf);
#define amn_webConfig_get(key)       amn_config_get( CONFIG_SPACE_TYPE_CURRENT, key )
#define amn_webConfig_set(key,val)   amn_config_set(CONFIG_SPACE_TYPE_CURRENT, key, val )
#define amn_webConfig_iset(key,val)  amn_config_iset(CONFIG_SPACE_TYPE_CURRENT, key, val )

int web_config_act_s(char *key, char *val, char *buf);

// The <key> is in wildcard, we need to let known the current <cfgname>
struct NS_ON_CGI_BUF_PARAM;
int web_config_wget(char *key, struct amn_cfgspace_value_t **val, char **name, struct NS_ON_CGI_BUF_PARAM *cgi_param);
extern struct amn_config_space_storage_t *amn_ConfigSpace_Storages[];


// Definitions for Authority Manager
//*******************************************************************************************************
struct amn_authority_control_t {
	struct list_head   link;
	osal_thread_pid_t  pid;
	char               *uname;
	int                uclass;
};

//------------------------------------------------------------------------------
//  Function    : amn_register_authority
//------------------------------------------------------------------------------
/**
 * @brief                 To register the current thread with the specified user class
 *                        Note how to authenticate (by username && password) is irrelevant here
 *
 * @param[in ] uname      The user name. Most of the Configuration Space items aren't user specific.
 *                        However, the user's own data: 'User.Account.%d.Xxx', will be for himself only.
 * @param[in ] uclass     The user class
 *
 * @retval 0              Success
 * @retval < 0            Fail
 */
int amn_register_authority( char *uname, int uclass );


//------------------------------------------------------------------------------
//  Function    : amn_unregister_authority
//------------------------------------------------------------------------------
/**
 * @brief                 To unregister the current thread
 *
 * @retval 0              Success
 * @retval < 0            Fail
 */
int amn_unregister_authority(void);


//------------------------------------------------------------------------------
//  Function    : amn_check_authority
//------------------------------------------------------------------------------
/**
 * @brief                 To check the user class running on the current thread, whether it has sufficient
 *                        authority to perform the specified \a action on the specified \a key, or not.
 *
 * @param[in ] key        The name of the Configuration Space item being accessed.
 * @param[in ] action     The activity to be applied to the \a key.
 *
 * @retval 0              Success
 * @retval < 0            Fail
 */
int amn_check_authority( char *key, int action );


// Definitions for File Manager
//*******************************************************************************************************

#ifdef __AMN_OS_LINUX__
//-------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define osal_fopen     fopen
#define osal_fread     fread
#define osal_fwrite    fwrite
#define osal_fseek     fseek
#define osal_fseeko    fseeko
#define osal_fclose    fclose
#define osal_stat      stat
#define osal_stat_t    stat
#define OSAL_FILE      FILE
#define OSAL_DIR_O     DIR

typedef struct _FS_FILETIME {
	u16_t Year;      ///< Represents the year. The year must be greater than 1980.
	u16_t Month;     ///< Represents the month, where January = 1, February = 2, ...
	u16_t Day;       ///< Represents the day of the month(1-31).
	u16_t Hour;      ///< Represents the hour of the day(0-23).
	u16_t Minute;    ///< Represents the minute of the day(0-59).
	u16_t Second;    ///< Represents the second(0-59)
} FS_FILETIME;
#define MMP_FS_FILETIME     FS_FILETIME

#else
//-------------------------------------------------------------------
// this is for ARM-ADS C compiler
#include "fs_api.h"

typedef long off_t;
typedef int ssize_t;
typedef unsigned int size_t;

typedef unsigned long OSAL_FILE;

OSAL_FILE *osal_fopen(const char *path, const char *mode);
size_t osal_fread(void *ptr, size_t size, size_t nmemb, OSAL_FILE *stream);
size_t osal_fwrite(const void *ptr, size_t size, size_t nmemb, OSAL_FILE *stream);
int osal_fseek(OSAL_FILE *stream, long offset, int whence);
int osal_fseeko(OSAL_FILE *stream, off_t offset, int whence);
size_t osal_ftell(OSAL_FILE *stream);
int osal_fclose(OSAL_FILE *fp);
unsigned int osal_getfilesize(OSAL_FILE *fp);
//not exactly an file system. And it is chip dependent, not OS dependent.
extern void MMPF_MMU_InvalidateDCacheMVA(unsigned int ulRegion, unsigned int ulSize);
extern void MMPF_MMU_FlushDCache(void);
void printc( char* szFormat, ... );
#if 0
//since MMPF_MMU_InvalidateDCacheMVA has been modified. the error checking does not required any more.
#define	osal_invalidate_dcache(p, s)	if ((int)p & (MEM_ALIGNMENT_HEAP - 1))	\
											printc("%s %d Invalidate DCache is not at 32 bytes alignment!!\r\n", __func__, __LINE__);	\
										MMPF_MMU_InvalidateDCacheMVA((unsigned long)p, (unsigned long)s)
#else
#define	osal_invalidate_dcache(p, s) MMPF_MMU_InvalidateDCacheMVA((unsigned long)p, (unsigned long)s)
#endif

#define	osal_flush_dcache(p,s)				MMPF_MMU_FlushDCacheMVA(p,s)
//void osal_invalidate_dcache(void *const ptr, size_t size);

struct osal_stat_t {
	unsigned int    st_mode;        /* File mode.  */
	unsigned int    st_size;        /* Size of file, in bytes.  */
	long            st_mtime;       /* Time of last modification.  */
	// other fields are simply removed
};

int osal_stat(const char *path, struct osal_stat_t *buf);

#define DT_DIR     4
#define DT_REG     8
#define S_ISDIR(mode)     ((mode) & DT_DIR)
#define S_ISREG(mode)     ((mode) & DT_REG)


typedef u32_t OSAL_DIR_O;

#define MAX_OSAL_DOWNLOAD_FN_LEN (64)
struct osal_ev_download_parm
{
	char filename[MAX_OSAL_DOWNLOAD_FN_LEN];
	short start; //1 to start, 0 as finish
	short handled; //if the event handler is processed, set this to 0.
	int offset; //offset of the file in bytes. If it is unassigned, set to 0.
};

struct osal_ev_tx_rpt
{
#define TX_RPT_NA (-1) //don't care this field
	signed short stress; // stress score from 0 to 100(the highest)
	//signed char overflow; //0 for nothing. 1 for overflow
		//TX overflow flags
		enum osal_tx_overflow_t {OSAL_TXF_NONE, OSAL_TXF_OVERFLOW, OSAL_TXF_NORMAL} overflow;
	//signed char reset; //1 for reset
		enum osal_tx_reset_t {OSAL_TXF_RESET = 1, OSAL_TXF_RESET_TCP, OSAL_TXF_RESET_UDP} reset;
};

typedef enum _osal_ev_t {
	OSAL_EV_DOWNLOAD, ///< While web server is serving the file. use struct osal_ev_download_parm
	OSAL_EV_V4L_OVERFLOW, ///< While streaming V4L buffer is about to overflow. use struct osal_ev_tx_rpt.
	OSAL_EV_TX_REPORT, ///< While streaming sending frame needs to report current status. use struct osal_ev_tx_rpt
	OSAL_EV_MAX
}osal_ev_t;

/** Net streaming server event handler.
 *  @param param input parameter. Typically a pointer to a structure, such as NS_ON_CONNECT_PARAM
 *  @return <0 for any error. 0 for success.
 */
typedef int (*osal_ev_cb)(void* eventData, void* userData);

typedef struct _osal_ev_handler {
	osal_ev_cb callback;
	void* userData;
} *osal_ev_handler;

int osal_set_ev_handler(osal_ev_t handler_type, osal_ev_cb callback, void* userData);
int osal_handle_ev(osal_ev_t handler_type, void* eventData);

struct osal_dbg_time;
enum OSAL_DBG_TIME_STAGE {
	ODT_STAGE_SENSOR,
	ODT_STAGE_V4L,
	ODT_STAGE_RTP,
	OSAL_DBG_TIME_STAGE_MAX
};
struct odt_ctrl_t {
	int en;
	int nPrintTh;
	int nIframe;
	enum {
		ODT_NONE,
		ODT_SUMMARY,
		ODT_VERBOSE,
		ODT_DBG_LVL_MAX
	} msg_lvl;
};

typedef enum odt_flag_t{
	ODT_FLAG_NONE = 0,
	ODT_FLAG_I = 0x1
} odt_flag_t;

extern struct odt_ctrl_t odt_ctrl;

int odt_get_idx(void);
void odt_reset(void);
#define ODT_RESET() do {if(odt_ctrl.en) odt_reset();} while(0);
void odt_log(int idx, enum OSAL_DBG_TIME_STAGE stage, unsigned int ts, odt_flag_t flags);
#define ODT_LOG(idx, stage, ts) do {if(odt_ctrl.en) odt_log(idx, stage, ts, ODT_FLAG_NONE);} while(0);
#define ODT_LOGF(idx, stage, ts, flags) do {if(odt_ctrl.en) odt_log(idx, stage, ts, flags);} while(0);

//-------------------------------------------------------------------
#endif

#define MAX_DIRENT_FILEPATH  256
struct osal_dirent_t {
	FS_FILETIME		 d_ftime;
	u32_t            d_fsize;
	unsigned char    d_type;      /* type of file */
	char             d_name[MAX_DIRENT_FILEPATH]; /* filename */
};

typedef struct {
	OSAL_DIR_O       *d_dirp;
	char             d_path[MAX_DIRENT_FILEPATH]; /* pathname */
	struct osal_dirent_t dirent;
} OSAL_DIR;

OSAL_DIR *osal_opendir(const char *name);
struct osal_dirent_t *osal_readdir(OSAL_DIR *dirp);
int osal_closedir(OSAL_DIR *dirp);


// Definitions for Session Manager
//*******************************************************************************************************
#ifndef __AMN_OS_LINUX__
// this is for ARM-ADS C compiler
#include "UpnpInet.h"
#endif

// HTTP Cookies session && variables:
//      Set-Cookie: name1=value1; Max-Age=600
//      Set-Cookie: name2=value2; Expires=Wed, 09-Jun-2021 10:18:14 GMT
//---------------------------------------------------------------------------
#define COOKIE_SESSION_T \
	struct sockaddr_storage foreign_sockaddr;  /* to identify this cookie really belong who claims it !! */

struct cookie_session_t {
	COOKIE_SESSION_T
};


//---------------------------------------------------------------------------
#define USER_CLASS__AIT       11
#define USER_CLASS__ADMIN     22
#define USER_CLASS__USER      33
#define USER_CLASS__GUEST     44
#define USER_CLASS__NOBODY    55

#define MAX_ACTIVE_USERS   1

struct user_session_t {
	COOKIE_SESSION_T
	char   *uname;  // user name
	char   *upass;  // user password
	int    uclass;  // user class
};

//---------------------------------------------------------------------------
void random_bytes( unsigned char *dest, int len );
void random_id( char *dest, int len );
struct amn_session_t *_session_new( void *owner, int interval, int (*heartbeat)(void*), int (*teardown)(), char *name );
void session_destroy(struct amn_session_t *s, char *reason);
struct amn_session_t *session_search_id( char *id );
int session_is_valid(struct amn_session_t *s);
struct amn_session_t *session_search_owner( void *owner, int i );
void session_refresh( struct amn_session_t *sess);
void session_event_teardown_resp(void *data);
void session_destroyall(void);

#ifndef STRUCT_SESSION_PROPERTY
#define STRUCT_SESSION_PROPERTY  int __dummy_field__
#endif

#define SESSION_WDOG__HEATBEAT    0
#define SESSION_WDOG__DEMISE      -1

#define session_new( owner, interval, heartbeat, teardown ) \
		_session_new( owner, interval, heartbeat, teardown, cc__func__ )

// each valid session should be well LINK'ed
#define session_is_valid(s) \
		((s) && (((s)->link.next != LIST_POISON1) || ((s)->link.prev != LIST_POISON2)))

#define SESSION_ID_LEN    30
struct amn_session_t {
	struct list_head     link;

	struct timeval start_time;    // start time for this session
	struct timeval refresh_time;  // replenish of this Session's liveness, or it'll die out
	struct ammo_evmsg *wdog;      // watchdog timer object
	int    interval;              // watchdog timer interval, in mini-seconds
	int   (*heartbeat)(void*);    // callback for monitor Client activity, like PING

	int   (*teardown)(struct amn_session_t *s, char *reason); // teardown callback when session is killed by timeout
	char   *name;                 // human readable name
	void   *data;                 // generic pointer, not specified by the Session Manager
	void   *owner;                // Search KEY: owner of this session
	char   id[SESSION_ID_LEN+2];  // Search KEY: SESSION ID
	union {
		char __dummy__[256];     // max size of all users of STRUCT_SESSION_PROPERTY
		STRUCT_SESSION_PROPERTY; /* owner of this session object declare its own structure */
	} u;
};
#define cast_protocol_data(sess, type) ((struct type *)&(sess)->u.__dummy__)

// Simple RESOURCE MANAGER
//*******************************************************************************************************
void register_working_rtsp_session(struct amn_session_t * sess, int num_sess, int max_sess);
void unregister_working_rtsp_session(struct amn_session_t * sess);
// return 0: rtsp is running and not allow to do others
//        1: allow to do
int check_working_rtsp_session(char *foreign_addr);

struct resource_t {
	char  *name;
	u32_t  limit;
	u32_t  value;
};


//*******************************************************************************************************
void init_amn_system(void);

#endif
