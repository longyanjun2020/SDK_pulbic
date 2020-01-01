
#ifndef HTTP_CLIENT_WRAPPER
#define HTTP_CLIENT_WRAPPER



// Generic types
typedef unsigned int                 UINT32;
typedef int                          INT32;


///////////////////////////////////////////////////////////////////////////////
//
// Section      : Functions that are not supported by the AMT stdc framework
//                So they had to be specificaly added.
// Last updated : 01/09/2005
//
///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus 
extern "C" { 
#endif

    // STDC Wrapper implimentation
    int HTTPWrapperIsAscii(int c);
    int HTTPWrapperToUpper(int c);
    int HTTPWrapperToLower(int c);
    int HTTPWrapperIsAlpha(int c);
    int HTTPWrapperIsAlNum(int c);
    char* HTTPWrapperItoa(char *buff,int i);
    void HTTPWrapperInitRandomeNumber(void);
    long HTTPWrapperGetUpTime(void);
    int  HTTPWrapperGetRandomeNumber(void);
    int  HTTPWrapperGetSocketError(int s);
unsigned long HTTPWrapperGetHostByName(UINT32 handle, char *name,unsigned int *address);
    int HTTPWrapperShutDown(int s,int in);  
    // Global wrapper Functions
#define                             IToA                            HTTPWrapperItoa
#define                             GetUpTime                       HTTPWrapperGetUpTime
#define                             SocketGetErr                    HTTPWrapperGetSocketError 
#define                             HostByName                      HTTPWrapperGetHostByName
#define                             InitRandomeNumber               HTTPWrapperInitRandomeNumber
#define                             GetRandomeNumber                HTTPWrapperGetRandomeNumber
    //os init
    UINT32 HTTPOSInit(UINT32 nState);

#ifdef __cplusplus 
}
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Section      : Global type definitions
// Last updated : 01/09/2005
//
///////////////////////////////////////////////////////////////////////////////

#define VOID                         void
#ifndef NULL
#define NULL                         0
#endif
#define TRUE                         1
#define FALSE                        0
typedef char                         CHAR;
typedef unsigned short               UINT16;
typedef int                          BOOL;
typedef unsigned long                ULONG;

// Global socket structures and definitions
#define                              HTTP_INVALID_SOCKET (0)
typedef struct sockaddr_in           HTTP_SOCKADDR_IN;
typedef struct timeval               HTTP_TIMEVAL; 
typedef struct hostent               HTTP_HOSTNET;
typedef struct sockaddr              HTTP_SOCKADDR;
typedef struct in_addr               HTTP_INADDR;


#endif // HTTP_CLIENT_WRAPPER

