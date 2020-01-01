#include "stdlib.h"

#define msAllocMem					malloc
#define msAllocMem_woCheck(_X_)		_memMgrAllocMem(_X_, TRUE, FALSE)
#define msAllocMem_noSWI(_X_)		_memMgrAllocMem(_X_, FALSE, TRUE)
#define msFreeMem					free
#define msFreeMem_noSWI(_X_)		_memMgrFreeMem((void*)(_X_), FALSE)
#define msFreeMemNull(_X_)          {free(_X_); _X_ = NULL;}
#define msFreeMemNull_noSWI(_X_)	_memMgrFreeMemNull((void**)(&(_X_)), FALSE)
#define msIsPoolMem(_X_)			_memMgrIsPoolMem((void*)(_X_), TRUE)
#define msIsPoolMem_noSWI(_X_)		_memMgrIsPoolMem((void*)(_X_), FALSE)
#define msIsHeapMem(_X_)			_memMgrIsHeapMem((void*)(_X_), TRUE)
#define msIsHeapMem_noSWI(_X_)		_memMgrIsHeapMem((void*)(_X_), FALSE)
#define msLinkMem(_X_)				_memMgrLinkMem((void*)(_X_), TRUE)
#define msLinkMem_noSWI(_X_)		_memMgrLinkMem((void*)(_X_), FALSE)
#define msMemset					memset
#define msMemcpy					memcpy
#define msMemcmp					memcmp
#define msMemmove					memmove

#define VFS_SEM			           (19)	/* semaphore for VFS layer */
