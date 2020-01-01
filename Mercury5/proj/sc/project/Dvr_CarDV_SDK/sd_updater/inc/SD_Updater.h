
#ifndef _SD_UPDATER_H_
#define _SD_UPDATER_H_

#include "net_cfg.h"

#define	MD5_LENGTH  16
#define	SDTAG       {'A', 'I', 'T', 'S'}
#define	SDVER       0x0001
#define	PRECODE     "VDRAC999"

#define BOOTROMSIZE	0x5000 // 20k Byte
#define MBR_OFFSET	0x8000 // 32k Byte

#define SD_UPDATER_TEMP_BUF_LENGTH  (0x1000)
#define FW_USER_DATA_INDEX          (0xA)

#define POI_UPDATE_DECRYPT			(0)

// For Mercury v2
#define CHECKSDFWHEADER			(0)
#define	SDUPDATEDRAWPROGRESS	(1)

typedef enum _SD_UPDATER_ERR{
    SD_UPDATER_ERR_NONE = 0,
    SD_UPDATER_ERR_FILE,
    SD_UPDATER_ERR_LOG,
    SD_UPDATER_ERR_FAIL
    
}SD_UPDATER_ERR;

typedef enum _IDX_TABLE_TYPE{
    IDX_TABLE_TYPE_FIRST,
    IDX_TABLE_TYPE_SECOND

}IDX_TABLE_TYPE;

typedef struct _SDBIN {
	char    sbTag[4];           // File tag, 4byte
	int     sbVer;              // BIN Version, 4byte
	char    sbID[8];           	// Reserved, 8byte
	char    sbMD5[MD5_LENGTH];  // MD5, 16byte
	// FW body
} SDBIN;

typedef struct _PROJID_{
	char	sbVerify;			//Check ProjID or not
	char	sbIDLen;			//Length of ProjID
	char	sbOldNewVerChk[14];	//Check old new version, 14byte
	char	sbIDFlagRSV[16];	//Reserved, 16byte
	char	sbProjID[64];		//Project ID, 64 byte
}PROJID;

SD_UPDATER_ERR SDUpdateReadBinFile(MMP_ULONG SDFileId);
SD_UPDATER_ERR SDUpdateCheckFileExisted(MMP_BYTE* bFileName);
SD_UPDATER_ERR SDUpdateCheckWPExisted(MMP_BYTE* bFileName);
SD_UPDATER_ERR SDUpdateCheckWpFsExisted(MMP_BYTE *bFileName);
SD_UPDATER_ERR SDDumpWpAreaBak(MMP_BYTE* bFileName);
SD_UPDATER_ERR SDUpdateGetStatus(void);
MMP_BOOL SDUpdateIsFWExisted(void);

MMP_BOOL	SDUpdateBackupNetUserConf(void);
MMP_BOOL	SDUpdateWriteBackNetUserConf(void);
#if(WIFI_PORT && (SD_MAC_UPDATER_BURNIN || SD_MAC_POWERON_BURNIN))
MMP_BOOL	SDUpdateBackupMAC(char* path);
void		SDUpdateBurnInMAC(void);
#endif

MMP_BOOL	SDUpdateBackupRTCBaseTime(void);
MMP_BOOL	SDUpdateWriteBackRTCBaseTime(void);

#if (SD_UPDATE_FW_EN)
void        AHC_SDUpdateMode(void);
#endif

#endif
