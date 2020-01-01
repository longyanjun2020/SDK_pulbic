//sdk
#include "ven_sdk.h"
#include "ven_ui.h"

//dialog
enum{
	DVK_DLG_CONFIRMATION,
	DVK_DLG_INFORMATION,
	DVK_DLG_WARNING,
	
	DVK_DLG_TYPE_SUM
};
typedef u32 dvk_dlg_type_t;

enum
{
    // Softkey type of dialog/menu/text viewer
    DVK_SK_X_X_X,
    DVK_SK_X_X_CANCEL,
    DVK_SK_X_OK_CANCEL,
    DVK_SK_X_X_BACK,
    DVK_SK_X_OK_BACK,
    DVK_SK_X_OK_X,
    DVK_SK_OK_OK_CANCEL,

	DVK_SK_TYPE_SUM
};
typedef u32 dvk_sk_type_t;

enum
{
	DVK_STR_PERMISSION_FILE_READ = 0,
	DVK_STR_PERMISSION_FILE_WRITE,
	DVK_STR_PERMISSION_SMS_READ,
	DVK_STR_PERMISSION_SMS_WRITE,
	DVK_STR_PERMISSION_HTTP,
	DVK_STR_PERMISSION_SOCKET,
	DVK_STR_PERMISSION_DATAGRAM,
	DVK_STR_PERMISSION_PUSHREGISTRY,
	DVK_STR_ERROR_OOM,
	DVK_STR_SUM
};
typedef u32 dvk_str_type_t;

enum
{
	DVK_LANG_ENG = 0,
	DVK_LANG_CHT,
	DVK_LANG_CHS,

	DVK_LANG_SUM
};
typedef u32 dvk_lang_type_t;

