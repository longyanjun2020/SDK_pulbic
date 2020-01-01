
#ifndef __CACHE_STRUCT_H__
#define __CACHE_STRUCT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef T_MOBILE_CACHE

#include <ncc_types.h>
#include <nccsa.h>
#include <ncccommon.h>
#ifdef NCC_WAP_FS_NOR
#define CACHESPACE   30*1024
#else
#define CACHESPACE   1048558      /* 1024(KB)*1024(byte)-18=524276  18 means the size of cache's version and FileListHead information which stored in configure file  */
#endif
#define FILELISTSIZE 200
#define WRITE_FILE_LIST_LEN 40   /* 40 means sizeof(FileList)-3*sizeof(int8_t *)-sizeof(int32_t) */
#define CACHE_CHARSET_LEN 16 /* 16 means charset length, if this macro changed,the macro "WRITE_FILE_LIST_LEN" must be changed according to this */

/* Record the information of file */
typedef struct _filelist{
    int16_t URLlen;
    int16_t LastURLlen;
    int32_t fileName;
    int32_t fileSize;
    int32_t expiration;
    int32_t lastModify;
    int16_t ETaglen;
    int8_t revalidate;
    int8_t fileType;
    int8_t charset[CACHE_CHARSET_LEN];
    int8_t *URL;
    int8_t *ETag;
    int8_t *LastURL;
    int32_t next;
}FileList;

/* Record the total number of files and the free space */
typedef struct _filelisthead{
    int32_t fileNum;     /* The number of saved files */
    int32_t freeSpace;   /* Free space of cache */
    int32_t fileName;    /* The longest file name in the cache */
}FileListHead;

/* Record the position of free space */
typedef struct _freelist{
    int32_t freeSpacePos;
    struct _freelist *next;
}FreeList;

typedef struct _freelisthead{
    int32_t freePosition;
    int32_t lastPosition;
    int32_t freeNum;
    FreeList *next;
}FreeListHead;

/* The record of FileList which sort by URLlen */
typedef struct _filelistsort{
    int32_t Length;             /* URLlen */
    int32_t nextPos;            /* The position of elements which have the same URLlen in the FileList */
}FileListSort;

typedef struct _sorthead{
    int32_t lenNum;             /* The number of URLlen */
    int32_t listsize;           /* The size of SorrtList at the moment */
    FileListSort *filelistsort;
}SortHead;

/* CONTEXT */
typedef struct _cachecx{
    FileList *filelist;
    FileListHead *fileHead;
    FreeListHead *freelisthead;
    SortHead *sortHead;
}CacheCX;

extern CacheCX *gCx;

#else /* T_MOBILE_CACHE */
#include <ncc_types.h>

#define ITEMLIST_INITSIZE 200 /* ItemList size initialization */
#define ITEM_SIZE_WITHOUT_STR 28   /* 28 means sizeof(T_Cache_ItemList)-3*sizeof(int32_t)-5*sizeof(int8_t *) */
#define CACHE_SIZE_REDUCE 22 /* 22 means cache's version information size and 4*sizeof(int32_t) in the front of cx */

typedef enum Cache_Item_OpenMode {
    ITEM_CLOSE, /* item is closed */
    ITEM_READY, /* item is ready */
    ITEM_READ, /* read mode */
    ITEM_WRITE, /* write mode */
    ITEM_APPEND /* append mode */
}T_CACHE_ITEM_OPENMODE;

/* define item list structure */
typedef struct t_cache_itemlist{
    uint16_t urllen; /* length of item url */
    uint16_t lasturllen; /* length of item lasturl */
    uint16_t etaglen; /* length of etag */
    uint16_t charsetlen; /* length of charset */
    uint16_t mimetypelen; /* length of mimetype */
    int8_t revalidate; /* revalidate flag */
    int8_t itemstatus; /* specifies the item is completed or not */
    int32_t itemname; /* item name */
    int32_t itemsize; /* size of the item */
    int32_t expiration; /* item's expiration time */
    int32_t lastmodify; /* lastmodify flag */
    uint8_t *url; /* item url */
    uint8_t *lasturl; /* item lasturl */
    uint8_t *etag; /* etag string */
    uint8_t *charset; /* character set */
    uint8_t *mimetype; /* MIME type */
    int32_t openmode;  /* close, ready, read, write or append */
    int32_t itemhandle; /* the item handle */
    int32_t next; /* specifies the next item position */
}T_Cache_ItemList;

/* define free list structure to record the position of free space in item list */
typedef struct t_cache_freelist{
    int32_t freespacepos; /* specifies a free position in item list */
    struct t_cache_freelist *next;
}T_Cache_FreeList;

/* define the free list header structure */
typedef struct t_cache_freelisthead{
    int32_t firstposition; /* specifies the first free position in the end of the free space in item list */
    int32_t lastposition; /* specifies the last free position in the end of the free space in item list */
    int32_t freenum; /* specifies the number of free space */
    T_Cache_FreeList *next;
}T_Cache_FreeListHead;

/* The record of FileList which sort by URLlen */
typedef struct t_cache_indextable{
    int32_t length; /* length of url */
    int32_t nextpos; /* the position of elements which have the same URLlen in the ItemList */
}T_Cache_IndexTable;

typedef struct t_cache_indextablehead{
    int32_t number; /* the item number in indextable */
    int32_t listsize; /* the size of IndexTable at the moment */
    T_Cache_IndexTable *indextable; /* pointer to the indextable */
}T_Cache_IndexTableHead;

/* define cache context structure */
struct t_cache_cx{
    int32_t cachesize;   /* cache size */
    int32_t itemnum;     /* the number of saved items */
    int32_t freespace;   /* free space of cache */
    int32_t itemname;    /* the longest item name in the cache */
    T_Cache_ItemList *itemlist; /* pointer to the item list */
    T_Cache_FreeListHead *freelisthead; /* pointer to the free list header */
    T_Cache_IndexTableHead *indextablehead; /* pointer to the indextable header */
};
typedef struct t_cache_cx * T_Cache_CX;

#endif /* T_MOBILE_CACHE */

#ifdef __cplusplus
}
#endif

#endif /* __CACHE_STRUCT_H__ */
