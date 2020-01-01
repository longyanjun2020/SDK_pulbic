#ifndef __MDL_VFS_STRUCT_H__
#define __MDL_VFS_STRUCT_H__

#include "vm_types.ht"

#define VFS_FAT_SPEC_FULLPATH_LEN   (262 + 1) /* (13 unicodes per LFN entry) * 2, including the '\0' char       */
#define VFS_FAT_SPEC_FULLNAME_LEN   (255 + 1) /* max u8 length of file/path name without volume name            */

#define VFS_NB_FILES_MAX            (20)      /* maximum number of files that could be handled simultaneously   */
#define MAX_EXT_NAME_LEN            (3)       /* max u8 length of extension name                                */
#define MAX_PATH_LEN                (VFS_FAT_SPEC_FULLPATH_LEN * 2)  /* max u8 length of full file name                  */
#define MAX_CHAR_LFN                VFS_FAT_SPEC_FULLPATH_LEN

#define VFS_FILE_ID_SIZE            (8)       /* size of unique file ID in bytes                                */
#define VFS_CID_REG_SIZE            (16)      /* 126 bits */

#define VFS_M_FILES (VFS_VOL_MAX + 1)

typedef enum
{
  VFS_VOL_NOR = 0,
  VFS_VOL_SD, /* Default card */
  VFS_VOL_NAND,
  VFS_VOL_SD2,
  VFS_VOL_SD1,
  VFS_VOL_HIDN,
  VFS_VOL_MAX,  
} VFS_VOL_TYPE;

typedef enum
{
  VFS_DEV_NOR = 0,
  VFS_DEV_SD, /* Slot 1 */
  VFS_DEV_NAND,
  VFS_DEV_SD2,  /* Slot 2 */
  VFS_DEV_HIDN,
  VFS_DEV_MAX
} VFS_DevType_e;

typedef enum
{
  VFS_ASYNC_COPY_PROGRESS,
  VFS_ASYNC_MOVE_PROGRESS,
  VFS_ASYNC_WRITE_PROGRESS,
  VFS_ASYNC_READ_PROGRESS,
  VFS_ASYNC_FORMAT_PROGRESS,
  VFS_ASYNC_CHKSUM_PROGRESS,
  VFS_ASYNC_DELETE_PROGRESS,
  VFS_ASYNC_CHKDSK_PROGRESS,
  VFS_ASYNC_DELETE_ALL_PROGRESS, // Joe Su
  VFS_ASYNC_FILE_NUM_UPDATE,
  VFS_ASYNC_MONITOR_PATH,
} VFS_NotifyType_e;

typedef enum
{
  VFS_ACC_NORMAL = 0,     /* support read/write access */
  VFS_ACC_READONLY,   /* support read-only access */
  VFS_ACC_EIO_2_RO,   /* support read-only access, casued by io error */
} VFS_ACC_e;

typedef enum
{
  VFS_DISK_NORMAL = 0,      /* support read/write access */
  VFS_DISK_DIRTY,           /* disk not umount complete */
  VFS_DISK_IOERR,           /* IO access error encounter */
} VFS_DiskStatus_e;

typedef enum
{
  VFS_CHKDSK_STOP_FS_NORMAL,  /**< Used when power-up after normal power-off, or disable mass storage                   */
  VFS_CHKDSK_QUICK_CHECK,     /**< Used when power-up after abnormal power-off, or insert one SD card                   */
  VFS_CHKDSK_RECOVERY,        /**< Used when VFS_CHKDSK_STOP_FS_NORMAL, or VFS_CHKDSK_QUICK_CHECK find something error  */
} VFS_ChkdskOp_e;


typedef struct
{
  u32 count;            /**< Number of extension should be compared                                      */
  u16 *pExtList;         /**< Extension list in Unicode, please separate with '|' in wide character, too  */
} VFS_ExtensionFilter_t;


typedef struct
{
  u32 minSize;          /**< Define the min-size of filter  */
  u32 maxSize;          /**< Define the max-size of filter  */
} VFS_SizeFilter_t;


typedef enum
{
  VFS_ATTR_FILTER_IGNORE, /**< Even what the value of the entry attribute, keep this entry    */
  VFS_ATTR_FILTER_KEEP,   /**< If the attribute is equal the condition, keep this entry       */
  VFS_ATTR_FILTER_OUT     /**< If the attribute is equal the condition, skip this entry       */
} VFS_AttributeFilter_e;


typedef struct
{
  VFS_AttributeFilter_e rdOnlySwitch;   /**< Used to switch if need to filter RD-Only attribute */
  VFS_AttributeFilter_e hiddenSwitch;   /**< Used to switch if need to filter Hidden attribute  */
  VFS_AttributeFilter_e systemSwitch;   /**< Used to switch if need to filter System attribute  */
  VFS_AttributeFilter_e folderSwitch;   /**< Used to switch if need to filter Folder attribute  */
  VFS_AttributeFilter_e archiveSwitch;  /**< Used to switch if need to filter Archive attribute */
} VFS_AttributeFilter_t;


typedef struct
{
  VFS_ExtensionFilter_t extFilter;  /**< Filter with extension name, if the count=0, this filter would be ignored                             */
  VFS_SizeFilter_t sizeFilter; /**< Filter with file size, if min=0 & max=0xFFFFFFFF, this filter would be ignored                       */
  VFS_AttributeFilter_t attrFilter; /**< Filter with attribute, if all switches are VFS_ATTR_FILTER_IGNORE, this filter would be ignored  */
} VFS_PartialListFilter_t;


typedef struct
{
  u8 content[VFS_FILE_ID_SIZE];
} VFS_FileID_t;


typedef struct VFS_FILE_INFO
{
  u16   Long_File_Name[MAX_PATH_LEN / 2];     /* unicode string           */
  s8    File_Name[12];
  s8    File_Extension[MAX_EXT_NAME_LEN + 1];
  u32   Creation_Date;                        /* time & date lastmodified */
  u32   Last_Write_Date;                      /* time & date lastmodified */
  u32   Size;                                 /* File size in bytes       */
  u8    Attributes;                           /* Attributes bits          */
  u8    format83;
} VFS_File_Info_t;


typedef struct VFS_VOL_INFO
{
  u32   clusterSize;                          /* Cluster size in volume   */
} VFS_Vol_Info_t;

/* Backward compatible for SDK v1 */
typedef struct FILE_INFO
{
  u8    Long_File_Name[MAX_PATH_LEN + 3];     /* MMK UCS2 string          */
  u32   Creation_Date;                        /* time & date lastmodified */
  u32   Last_Write_Date;                      /* time & date lastmodified */
  u32   Size;                                 /* File size in bytes       */
  u8    Attributes;                           /* Attributes bits          */
  u8    format83;
} File_Info_t;


typedef struct
{
#if 1
  u16               longName[262];           /**< Filename in Unicode with terminal character                               */
  VFS_FileID_t      uniqueId;                /**< The entry ID generated by MMP                                             */
  u32               createdDate;             /**< Date-time to create the entry, the detail can be reference VFS_DateTime_t */
  u32               modifiedDate;            /**< Date-time to modify the entry, the detail can be reference VFS_DateTime_t */
  u32               size;                    /**< Item size in bytes, if the entry is a folder, the value will be 0         */
  u8                attr;                    /**< Entry attributes, the detail can be reference VFS_Attribute_t             */
//u8                padding[3];              /**< Padding space for memory alignment, this would be improved in future      */  

  u32               unixCTime;
  u32               unixMTime;
  u8                shortName[12 + 1];
  u8                extention[MAX_EXT_NAME_LEN + 1];  
  u8                padding[3];  
#else
  u16               longName[262];           /**< Filename in Unicode with terminal character                               */
  VFS_FileID_t      uniqueId;                /**< The entry ID generated by MMP                                             */
  VFS_DateTime_t    createdDate;             /**< Date-time to create the entry                                             */
  VFS_DateTime_t    modifiedDate;            /**< Date-time to modify the entry                                             */
  u32               size;                    /**< Item size in bytes, if the entry is a folder, the value will be 0         */
  VFS_Attribute_t   attr;                    /**< Entry attributes                                                          */
  u8                padding[3];              /**< Padding space for memory alignment                                        */
#endif
} VFS_PartialListFileInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
  u32 writtenLength;
  u8 *pBuffer;
} VFS_WriteNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
  u32 readLength;
  u8 *pBuffer;
} VFS_ReadNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
  /* The following two fileds are for MMI progress update, not accessed by VFS */
  u32 fileNum;
  u32 fileIndex;
} VFS_CopyNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
  /* The following two fileds are for MMI progress update, not accessed by VFS */
  u32 fileNum;
  u32 fileIndex;
} VFS_MoveNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
  /* The following two fileds are for MMI progress update, not accessed by VFS */
  u32 fileNum;
  u32 fileIndex;
} VFS_DeleteNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 fileNum;
} VFS_FileNumberNotifyInfo_t;


typedef struct
{
  VFS_FileNumberNotifyInfo_t fileNumInfo;
} VFS_ListNotifyInfo_t;


typedef struct
{
  VFS_FileNumberNotifyInfo_t fileNumInfo;
} VFS_SortNotifyInfo_t;


typedef struct
{
  VFS_FileNumberNotifyInfo_t fileNumInfo;
} VFS_SearchNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  u32 progress;
} VFS_FormatNotifyInfo_t;


typedef struct
{
  u32 size;
  u8 *pBuffer;
} VFS_CheckSum_t;


typedef struct
{
  s32 sessionID;
  VFS_CheckSum_t *pChksum;
  u32 progress;
} VFS_ChksumNotifyInfo_t;


typedef struct
{
  s32 sessionID;
  bool isAnyUpdate;  /* Indicate if there is any file been deleted. If yes, this field is TRUE. */
} VFS_AsyncDeleteNotifyInfo_t;


typedef struct
{
  s32               sessionID;
} VFS_ChkdskNotifyInfo_t;


typedef struct
{
    u16 *pStrPath;
    u32 eMode;
    u8 nVolumeID;
    bool IsAccess;
} VFS_MonitorPathNotifyInfo_t;


typedef struct
{
  s32 notifyType;
  s32 status;
  union
  {
    VFS_WriteNotifyInfo_t writeInfo;
    VFS_ReadNotifyInfo_t readInfo;
    VFS_CopyNotifyInfo_t copyInfo;
    VFS_MoveNotifyInfo_t moveInfo;
    VFS_DeleteNotifyInfo_t deleteInfo;
    VFS_ListNotifyInfo_t listInfo;
    VFS_SortNotifyInfo_t sortInfo;
    VFS_SearchNotifyInfo_t searchInfo;
    VFS_FormatNotifyInfo_t formatInfo;
    VFS_ChksumNotifyInfo_t chksumInfo;
    VFS_FileNumberNotifyInfo_t fileNumInfo;
    VFS_AsyncDeleteNotifyInfo_t asyncDeleteInfo;
    VFS_ChkdskNotifyInfo_t      chkdskInfo;
    VFS_MonitorPathNotifyInfo_t monitorPathInfo;
  } info;
} VFS_NotifyInfo_t;


typedef struct
{
  u8 cidReg[VFS_CID_REG_SIZE];    /* 128 bits */
} VFS_DevSerial_t;

#endif /* __MDL_VFS_STRUCT_H__ */
