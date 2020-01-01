#define ApBegin(thmId, apid) typedef u8 apid##_RS_STRUCT_START;

#define WndBegin(wid) typedef struct wid##_t_ {

#define WdgBegin(wdgClsid, wdgName) struct wdgName##_t_ { //u32 nWdgStartFlag; u32 nWdgSize; u32 nWdgId;

#define ChildBegin(wdgClsid, order, childName) struct childName##_t_ {


#define ChildEnd(wdgClsid, order, childName) }childName;

#define VTMWdgBegin(wdgClsid, WdgId, wdgName) struct wdgName##_t_ {


#define VTMWdgEnd(wdgClsid, WdgId, wdgName) }wdgName;


#define WdgEnd(wdgClsid, wdgName) }wdgName;

#define WndEnd(wid) } wid##_t;

#define ApEnd(thmId, apid) typedef u8 apid##_RS_STRUCT_END;


#define DynamicStructBegin(name) struct name##_t_ {

#define DynamicStructEnd(name) }t##name;

#if defined(__PC_SIMULATOR__)
//#define __RS_USE_SCRIPT__ 1		// enable this value let simulator support read rs data from rs file ( no need to build CUS file ).
#endif

//including rs_gen_struct.h will cause redefine effect
#if 0
//This header file is for VC editor using
#include "rs_gen_struct.h"
#endif

