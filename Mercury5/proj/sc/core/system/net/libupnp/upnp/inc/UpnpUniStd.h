#ifndef UPNPUNISTD_H
#define UPNPUNISTD_H

#ifdef __AMN_OS_LINUX__
#ifdef WIN32
	/* Do not #include <unistd.h> on WIN32. */
#else /* WIN32 */
	#include <unistd.h> /* for close() */
#endif /* WIN32 */
#endif

#endif /* UPNPUNISTD_H */
