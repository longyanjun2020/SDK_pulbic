/**
 * @file mmi_mae_interface_def.h
 *
 * This header file defines common macros for interface definitions, and the IBase interface.
 *
 * @version $Id: mmi_mae_interface_def.h 611 2009-04-11 14:21:40Z zinc.chen $
 */

#ifndef __MMI_MAE_INTERFACE_DEF_H__
#define __MMI_MAE_INTERFACE_DEF_H__
// verify the definitions
// __MAE_LEAK_DETECTION__ shall be defined only if __MAE_CORE_DIAGNOSIS__ is defined
#ifdef __MAE_LEAK_DETECTION__
#ifndef __MAE_CORE_DIAGNOSIS__
#error __MAE_LEAK_DETECTION shall be defined only if __MAE_CORE_DIAGNOSIS__ is also defined
#endif // __MAE_CORE_DIAGNOSIS__
#endif // __MAE_LEAK_DETECTION__

// __MAE_CYCLIC_DETECTION__ shall be defined only if __MAE_LEAK_DETECTION__ is defined
#ifdef __MAE_CYCLIC_DETECTION__
#ifndef __MAE_LEAK_DETECTION__
#error __MAE_CYCLIC_DETECTION__ shall be defined only if __MAE_LEAK_DETECTION__ is also defined
#endif // __MAE_LEAK_DETECTION__
#endif // __MAE_CYCLIC_DETECTION__

/*=============================================================*/
// header files
/*=============================================================*/
#include "mmi_mae_common_def.h"


//
// macros to define an interface
//
// macro that denotes the name of the function table structure of an interface
#define FUNCTBL(IName)				IName##_Vtbl

// macro to declare the pointer of the function table when defining an interface
#define DECLARE_FUNCTBL(IName)		const IName##_Vtbl *Vtbl_Ptr
// ZINC: obsolete macro for virtual function table and other stuff
#define DECLARE_CMN_COMPNT DECLARE_FUNCTBL

// macro to define the structure of virtual function names and prototypes of an interface
#define DEFINE_FUNCTBL(IName) \
	typedef struct IName##_Vtbl_tag FUNCTBL(IName); \
	struct IName##_Vtbl_tag

//
// NOTE: customize INHERIT_IName before using DEFINE_INTERFACE macro
//
// Macro to define the virtual function table and the base structure of an interface.
// Any object implements an interface shall have that interface structure defined as
// the first member in the object
#define DEFINE_INTERFACE(IName) \
	typedef struct IName##_tag IName; \
	DEFINE_FUNCTBL(IName) \
	{ INHERIT_##IName(IName); }; \
	struct IName##_tag \
	{ DECLARE_FUNCTBL(IName); }


/*=============================================================*/
// IBase interface
/*=============================================================*/
// methods of IBase interface
#define INHERIT_IBase(IName) \
	u32 (*AddRef)(IName*); \
	u32 (*Release)(IName*); \
	MAERet_t (*QueryInterface)(IName*, MAEIId_t, void**, IBase*)


// defines the base structure of an IBase object
DEFINE_INTERFACE(IBase);


//
// macros to use an interface object
//
// macro to retrieve the function table of an interface object
#ifdef __MAE_CORE_DIAGNOSIS__
// the implementation of diagnosis features vary with the design of shell
// the function MAE_GetFuncTbl() will be implemented in mae_shell.c
const void *MAE_GetFuncTbl(IBase *pObj);
#define GET_FUNCTBL(pObj, IName)	((FUNCTBL(IName)*) MAE_GetFuncTbl((IBase*)pObj))
#else
#define GET_FUNCTBL(pObj, IName)	(((IName*)pObj)->Vtbl_Ptr)
#endif // __MAE_CORE_DIAGNOSIS__


// macros for interface objects' lifetime management
#if defined(__MAE_LEAK_DETECTION__) || defined(__MAE_INVALID_OBJ_PROTECT__)
// the implementation of diagnosis features vary with the design of shell
// these functions, MAE_AddObjRef() and MAE_ReleaseObj(), will be implemented in mae_shell.c
u32 MAE_AddObjRef(IBase *pObj, IBase *pOwner);
u32 MAE_ReleaseObj(IBase *pObj, IBase *pOwner);
/* 
 * transform RELEASEIF macro into function call to reduce code size
 *
#define RELEASEIF(pObj, pOwner) do {if (pObj) {MAE_ReleaseObj((IBase*)pObj, (IBase*)pOwner); pObj = 0;}} while (0)
#else
#define RELEASEIF(pObj, pOwner) do {if (pObj) {GET_FUNCTBL(pObj, IBase)->Release((IBase*)pObj); pObj = 0;}} while (0)
*/
u32 releaseIf(void **, void *);
#define ADDREFIF(pObj, pOwner) do {if (pObj) {MAE_AddObjRef((IBase*)pObj, (IBase*)pOwner);}} while (0)
#define RELEASEIF(pObj, pOwner) do {releaseIf((void **) &(pObj), (void *) (pOwner));} while (0)
#define ADDREF(pObj, pOwner) MAE_AddObjRef((IBase*)pObj, (IBase*)pOwner)
#define RELEASE(pObj, pOwner) MAE_ReleaseObj((IBase*)pObj, (IBase*)pOwner)
#else
#define ADDREFIF(pObj, pOwner) do {if (pObj) {GET_FUNCTBL(pObj, IBase)->AddRef((IBase*)pObj);}} while (0)
#define RELEASEIF(pObj, pOwner) do {releaseIf((void **) &(pObj), (void *) (pOwner));} while (0)
#define ADDREF(pObj, pOwner) (GET_FUNCTBL(pObj, IBase)->AddRef((IBase*)pObj))
#define RELEASE(pObj, pOwner) (GET_FUNCTBL(pObj, IBase)->Release((IBase*)pObj))
#endif // __MAE_LEAK_DETECTION__

//
// To monitor the usage of objects and detect leakage, interface objects do not expose
// their AddRef and Release functions. Calling these functions directly is forbidden.
// Use shell's ADDREFIF() and RELEASEIF() macros instead.
//
// #define IBASE_AddRef(pIBase) GET_FUNCTBL(pIBase, IBase)->AddRef(pIBase)
// #define IBASE_Release(pIBase) GET_FUNCTBL(pIBase, IBase)->Release(pIBase)
#define IBASE_QueryInterface(pIBase, IId, ppObj, pOwner) \
	GET_FUNCTBL(pIBase, IBase)->QueryInterface(pIBase, IId, (void**)(ppObj), pOwner)

#endif // __MAE_INTERFACE_DEF_H__
// end of file
