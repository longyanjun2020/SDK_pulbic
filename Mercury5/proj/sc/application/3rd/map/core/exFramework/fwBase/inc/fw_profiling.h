#ifndef FW_PROFILING_H
#define FW_PROFILING_H

/* enumeration for profiling tag */
typedef enum ProfilingTag_e
{
    E_PROTAG_SY=0,    /* profiling tag for all system                */
    E_PROTAG_DB,      /* profiling tag for DB                        */
    E_PROTAG_GE,      /* profiling tag for graphic engine            */
    E_PROTAG_RT,      /* profiling tag for routing                   */
    E_PROTAG_GU,      /* profiling tag for guidance                  */
    E_PROTAG_PO,      /* profiling tag for POI searching             */
    E_PROTAG_HO,      /* profiling tag for house no                  */
    E_PROTAG_FL,      /* profiling tag for file access               */
    E_PROTAG_UD,      /* profiling tag for user-defined              */
    E_PROTAG_RFF,     /* profiling tag for file access under routing */
    E_PROTAG_RFR,     /* profiling tag for total routing duration    */
    E_PROTAG_MAX      /* maximal value                               */
} ProfilingTag_et;

#ifdef SUPPORT_PROFILING

/* extern */
#ifdef __cplusplus
extern "C" {
#endif    /* end of #ifdef __cplusplus */

    MVOID mfProOpen(MVOID);
    MVOID mfProClose(MVOID);
    MVOID mfProReset(MVOID);
    MVOID mfProStart(ProfilingTag_et eTag,PS8 szTagStr);
    MVOID mfProEnd(ProfilingTag_et eTag,PS8 szTagStr);

#ifdef __cplusplus
}
#endif    /* end of #ifdef __cplusplus */

#else    /* !defined(SUPPORT_PROFILING) */

    #define mfProOpen()                  {}
    #define mfProClose()                 {}
    #define mfProReset()                 {}
    #define mfProStart(eTag,szTagStr)    {}
    #define mfProEnd(eTag,szTagStr)      {}

#endif    /* end of #ifdef SUPPORT_PROFILING */

#endif    /* end of #ifndef FW_PROFILING_H */
