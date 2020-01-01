#ifndef __UT_VFS_H__
#define __UT_VFS_H__

#include "mdl_vfs_file.ho"

//Predefines session ID table
#define SESSION_ID_START		(7000000)
#define SESSION_ID_ASYNC_COPY	(SESSION_ID_START+100)
#define SESSION_ID_ASYNC_MOVE	(SESSION_ID_START+200)
#define SESSION_ID_ASYNC_QUERY_FOLDER_FILE_NUM	(SESSION_ID_START+300)
#define SESSION_ID_ASYNC_DELETE_ALL	(SESSION_ID_START+400)

typedef struct
{
	u32 file_signature;
	u32 file_reference;
	s32 _flags;     
	u32 file_size;
} FILE_HANDLE_S;

#define FILE_SIGNATURE	0x30507090
#define FILE_FREE (u32) 0xFFFFFFFF

#endif //__UT_VFS_H__
