#ifndef _INC_DEBUG
#define _INC_DEBUG
//#define _DBWIN_ON_

#if defined(_DEBUG ) || defined(_DBWIN_ON_)
void dprintf (char *fmt, ...);
#endif

#if defined(_DEBUG) || defined(_DBWIN_ON_)
	#define _VERIFY(statement) _ASSERT(statement);
#else
	#define _VERIFY(statement) statement;
#endif

#endif
