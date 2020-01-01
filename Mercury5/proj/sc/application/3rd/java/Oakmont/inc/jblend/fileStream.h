
#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__



/* Aplix header - begin */
#include "JkMediaStream.h"
#include "AmMediaControl.h"
#include "AMMemory.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "jap_head.h"
#include "util_ucs2.hi"
#include "protocolStream.h"
#include "ven_file.h"
/* Mstar header - end */

#ifdef __cplusplus
extern "C" {
#endif

void* getFileStreamInstance( JKSint32 id );
extern ProtocolStream_T fileStream;

/**
 * The parameter structure
 */
typedef struct sFileStream {
    void* pNext;  
    JKSint32 m_nID;
    JKWChar* m_pFileName; 
    JKSint32 m_nFileNameLen;
    JKWChar* m_pMimeType;
    JKSint32 m_nMimeTypeLen;
} FileStream_T;

#ifdef __cplusplus
}
#endif

#endif /* !__FILE_STREAM_H__ */
