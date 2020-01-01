//This head file is used for Eclipse indexing.
//It should be included in Eclipse project, typically in C/C++ General->Preprocessor Include Paths, Macros, etc->GNU C
//->CDT User Setting Entries->Add...->Preprocessor Macros File  Check 'Show built-in 'Treat as built-in'.
//This could avoid indexing the whole Eclipse project while changing config.
//Make system might be too complex for indexing
//sync wit common_options PP_OPT_COMMON Mercury V5 section
#define WIFI_PORT (1)
#define TARGETOS_car
#define _ENABLE_UPNP_
//These are not included in make system
//#define USE_LWIP //should be obsoleted
#define LWIP_DEBUG
#define __AMNSS_DEBUG__
#define __UPNP_DEBUG__
