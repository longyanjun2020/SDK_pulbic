#ifndef _MMPD_AUDIODB_H_
#define	_MMPD_AUDIODB_H_

#include "mmp_lib.h"
#include "mmpd_audio.h"
//#include "ait_utility.h"
#include "mmpd_id3.h" 

#define MAXFILESUPPORT  1010

#define	AUDIODB_MAX_FILE_NAME_SIZE	     (256)
#define	AUDIODB_GENRE_SIZE				 (36)

#define AudioNameDB                      (1)
#define AudioInfoDB                      (2)

typedef struct _MMPD_AUDIODB_AUDIOINFO {
    MMP_UBYTE               ubFullFileName[AUDIODB_MAX_FILE_NAME_SIZE*2];
    MMP_BYTE                bArtist[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE                bAlbum[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE                bTitle[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE                bGenre[AUDIODB_GENRE_SIZE];
    MMP_ULONG               ulPlayCount;
    MMP_UBYTE               ubRating;
    MMP_UBYTE               ubDirty;
    MMP_BYTE                bReserve[TEXT_FRAME_MAX_LEN*2-AUDIODB_GENRE_SIZE-6];
} MMPD_AUDIODB_AUDIOINFO;

typedef struct _MMPD_AUDIODB_BTNODE {
    MMP_BYTE                        data[512];    // File name length = 512
	MMP_ULONG                       ulFileOffset;
	struct _MMPD_AUDIODB_BTNODE     *left;
	struct _MMPD_AUDIODB_BTNODE     *right;
	MMP_USHORT						usLifeTime;
} MMPD_AUDIODB_BTNODE;
 
typedef struct _MMPD_AUDIODB_BFNODE {
	MMP_BYTE                        data[512];
	MMP_USHORT                      usTreeNodeNumber;
    MMP_USHORT                      usMetadataCount;
    MMPD_AUDIODB_BTNODE             *root;
	struct _MMPD_AUDIODB_BFNODE     *left;
    struct _MMPD_AUDIODB_BFNODE     *right;
	MMPD_AUDIODB_BTNODE             *metadata_root;
} MMPD_AUDIODB_BFNODE;

typedef enum _MMPD_AUDIODB_OBJECT_PROPERTY {
    MMPD_AUDIODB_OBJECT_NAME = 0,     ///< file name
    MMPD_AUDIODB_ALBUM,               ///< album
    MMPD_AUDIODB_ARTIST,              ///< artist
    MMPD_AUDIODB_GENRE,               ///< genre
    MMPD_AUDIODB_RATING,              ///< rating
    MMPD_AUDIODB_PLAYCNT              ///< play count
} MMPD_AUDIODB_OBJECT_PROPERTY;

typedef struct _MMPD_AUDIO_DB_TRACK {
	MMP_USHORT	usTitleName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usFullPathName[TEXT_FRAME_MAX_LEN];
} MMPD_AUDIO_DB_TRACK;

typedef MMP_ERR MMPD_AUDIODB_BTACTION(MMPD_AUDIODB_BTNODE *node);
typedef MMP_ERR MMPD_AUDIODB_BFACTION(MMPD_AUDIODB_BFNODE *node);
//==============================================================================
//
//                               FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPD_AUDIODB_MemAlloc(void);
MMP_ERR MMPD_AUDIODB_MemFree(void);
MMP_ERR MMPD_AUDIODB_SetParseCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize);
MMP_ERR MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath);
MMP_ERR MMPD_AUDIODB_Initialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_BYTE *bMode);
MMP_ERR MMPD_AUDIODB_Finish(void);
MMP_ERR MMPD_AUDIODB_CreateInitialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen);
MMP_ERR MMPD_AUDIODB_SetWriteCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize);
MMP_ERR MMPD_AUDIODB_CreateFinish(void);
MMP_ERR MMPD_AUDIODB_AddNewObject(MMPD_AUDIODB_AUDIOINFO AudInfo);
MMP_ERR MMPD_AUDIODB_ListAudioInfo(void);
MMP_ERR MMPD_AUDIODB_SearchAudioInfo(MMP_BYTE* bFileName, MMP_ULONG *ulInfoPos);
MMP_ERR MMPD_AUDIODB_DirtyFile(MMPD_AUDIODB_AUDIOINFO  *infobuf, MMPD_AUDIODB_BTNODE *node);
MMP_ERR MMPD_AUDIODB_DeleteDatabase(MMP_BYTE *bFileName, MMP_ULONG ulNameLen);
MMP_ERR MMPD_AUDIODB_AddMusic(MMP_BYTE* bFullFileName, MMP_ULONG ulFileID);
MMP_ERR MMPD_AUDIODB_CheckDatabaseDirty(MMP_ULONG *ulFileSize);

// Binary Tree, 2nd level sort
MMP_ERR MMPD_AUDIODB_BTreeInsert(MMPD_AUDIODB_BTNODE ** tree, MMPD_AUDIODB_BTNODE * item);
MMP_ERR MMPD_AUDIODB_BTreeFree(MMPD_AUDIODB_BTNODE **pnode);
MMP_ERR MMPD_AUDIODB_BTreeWalkForward(MMPD_AUDIODB_BTNODE *node);

MMPD_AUDIODB_BTNODE **MMPD_AUDIODB_BTreeSearch(MMPD_AUDIODB_BTNODE **root, MMP_BYTE *bKey);
MMPD_AUDIODB_BTNODE *MMPD_AUDIODB_DBCreateTree(MMPD_AUDIODB_OBJECT_PROPERTY groupindex, MMP_ULONG *ulNodeCount);
MMP_ERR MMPD_AUDIODB_GetBTreeNodeInfo(MMPD_AUDIODB_AUDIOINFO *infobuf, MMPD_AUDIODB_BTNODE *node);
MMP_ERR MMPD_AUDIODB_SetBTreeWalk(MMP_ULONG ulStart, MMP_ULONG ulEnd, MMPD_AUDIODB_BTACTION *action);
MMP_ERR MMPD_AUDIODB_BTreeWalk(MMPD_AUDIODB_BTNODE *node);
MMP_ERR MMPD_AUDIODB_BTreeFilter(MMPD_AUDIODB_BTNODE *node);
MMPD_AUDIODB_BTNODE **MMPD_AUDIODB_GetBTreeNodeLocator(MMPD_AUDIODB_BTNODE **treenode, MMP_ULONG ulIndex);
MMP_ERR MMPD_AUDIODB_BTreeKillNode(MMPD_AUDIODB_BTNODE **locator, MMP_USHORT *usNodeCount);

// Binary Forest, 1st level sort
MMPD_AUDIODB_BFNODE *MMPD_AUDIODB_DBCreateForest(MMPD_AUDIODB_OBJECT_PROPERTY groupindex, MMP_ULONG *ulNodeCounter);
MMP_ERR MMPD_AUDIODB_BForestFree(MMPD_AUDIODB_BFNODE **pbfnode);
MMP_ERR MMPD_AUDIODB_BForestWriteTree(MMPD_AUDIODB_BFNODE *bfnode);
MMP_ERR MMPD_AUDIODB_SetBForestWalk(MMP_ULONG ulStart, MMP_ULONG ulEnd, MMPD_AUDIODB_BFACTION *action);
MMP_ERR MMPD_AUDIODB_BForestWalk(MMPD_AUDIODB_BFNODE *bfnode);
MMP_ERR MMPD_AUDIODB_DBMetadataCount(MMPD_AUDIODB_BFNODE *forest_root, MMPD_AUDIODB_OBJECT_PROPERTY groupindex, 
                                    MMPD_AUDIODB_OBJECT_PROPERTY itemindex);
MMP_ERR MMPD_AUDIODB_BForestFilter(MMPD_AUDIODB_BFNODE *bfnode);
MMPD_AUDIODB_BFNODE **MMPD_AUDIODB_GetBForestNodeLocator(MMPD_AUDIODB_BFNODE **forestnode, MMP_ULONG ulIndex);
MMP_ERR MMPD_AUDIODB_KillTrack(MMPD_AUDIODB_BTNODE **bt_locator, MMPD_AUDIODB_BFNODE **bf_locator,
                                    MMPD_AUDIODB_OBJECT_PROPERTY itemindex, MMP_USHORT *bfnode_counter, 
                                    MMPD_AUDIODB_AUDIOINFO  *infobuf);
#endif // _MMPD_AUDIODB_H_