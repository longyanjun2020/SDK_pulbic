/**
 * @file mae_clstbl.h
 *
 * This file defines the table of class ids and their constructors.
 *
 * The class ids in MAE platform are separated into several categories. Each category has
 * a base value and forms an id-constructor relation table. These tables are used in shell's
 * CreateInstance() method to allocate and construct an object instance.
 *
 * Note: max allowed class ids in each category is 0x1000 (4096)
 *
 * @version $Id: mae_clstbl.h 1798 2009-09-21 02:37:54Z kenny.wu $
 */

#ifndef __MAE_CLSTBL_H__
#define __MAE_CLSTBL_H__
#include "mmi_mae_clstbl.h"
#if 0
//
// types and definitions
//
// base id value of each class category
#define MAE_CORE_CLASS_BASE			0x0000
#define MAE_BASIC_CLASS_BASE		0x1000
#define MAE_MODEL_CLASS_BASE		0x2000
#define MAE_WIDGET_CLASS_BASE		0x3000

#define MMI_SERVICE_CLASS_BASE		0x4000
#define MMI_APPLET_CLASS_BASE		0x5000
#define MMI_MODEL_CLASS_BASE		0x6000
#define MMI_BASIC_CLASS_BASE		0X7000
#define MMI_TEMPLATE_CLASS_BASE		0X8000

#define MAE_SERVICE_CLASS_BASE		MMI_SERVICE_CLASS_BASE // to be removed
#define MAE_APPLET_CLASS_BASE		MMI_APPLET_CLASS_BASE // to be removed

#define MAE_MAX_CLASS_CATEGORY		16 ///< maximun number of MAE class categories
#define MAE_CLS_MAX_CATEGORY		16 ///< maximun number of MAE class categories

#define MAE_CLASSCAT_TYPE_MASK		0xF000
#define MAE_CLASSCAT_OFFSET_MASK	0x0FFF
#define MAE_CLASSCAT_MAX_CLASS		(MAE_CLASSCAT_OFFSET_MASK + 1)

// macros to convert class id to its category and the offset in its category
#define MAE_CLSID_TO_CAT(_clsid_) (_clsid_ & MAE_CLASSCAT_TYPE_MASK)
#define MAE_CLSID_TO_OFFSET(_clsid_) (_clsid_ & MAE_CLASSCAT_OFFSET_MASK)
// macro to convert class id to catetory index
#define MAE_CLSID_TO_CAT_INDEX(_clsid_) ((u16)(_clsid_) >> 12)

// macros to define class id and the associated new function
#if defined __MAE_CLSTBL_C__

#define DEFINE_CLS_CATEGORY(Cat) \
	extern const MAE_ClassInfo_t Cat[]; \
	const MAE_ClassInfo_t Cat[] =

#define DEFINE_CLSID_BASE(ClsId, Base, Constructor) {Constructor}
#define DEFINE_CLSID(ClsId, Constructor) {Constructor}
#define DEFINE_END_OF_CLSID(ClsId) {0}
#define DECLARE_NEW_FUNC(_func_) extern MAERet_t _func_(MAEClsId_t, void**)

#elif defined __MMI_ENUM_STRING__

#define DEFINE_CLS_CATEGORY(Cat) \
	enum class Cat##_e

#define DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define DEFINE_CLSID(ClsId, Constructor) ClsId
#define DEFINE_END_OF_CLSID(ClsId) ClsId
#elif defined __NAME__

#define DEFINE_CLS_CATEGORY(Cat) \
	extern char Cat##_t[][40];\
	char Cat##_t[][40]=

#define DEFINE_CLSID_BASE(ClsId, Base, Constructor)		#ClsId
#define DEFINE_CLSID(ClsId, Constructor)	#ClsId
#define DEFINE_END_OF_CLSID(ClsId)			#ClsId

#elif defined __ID__
#define DEFINE_CLS_CATEGORY(Cat) \
		enum
#define DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define DEFINE_CLSID(ClsId, Constructor) ClsId
#define DEFINE_END_OF_CLSID(ClsId) ClsId
#else

#define DEFINE_CLS_CATEGORY(Cat) \
	extern const MAE_ClassInfo_t Cat[]; \
	enum

#define DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define DEFINE_CLSID(ClsId, Constructor) ClsId
#define DEFINE_END_OF_CLSID(ClsId) ClsId

#endif // __MAE_CLSTBL_C__ || __MMI_ENUM_STRING__


//
// header file or prototype declaration for the new function of each class
//
#ifdef __MAE_CLSTBL_C__

#include "mae_shell_cls.h"

// system and basic classes
DECLARE_NEW_FUNC(Display_New);
DECLARE_NEW_FUNC(MAESysStat_New);
DECLARE_NEW_FUNC(Font_New);
DECLARE_NEW_FUNC(Image_New);
DECLARE_NEW_FUNC(MAEImageMaker_New);
DECLARE_NEW_FUNC(MAEClock_New);
DECLARE_NEW_FUNC(MAEConfig_New);
DECLARE_NEW_FUNC(MAEBattery_CreateInstance);
DECLARE_NEW_FUNC(Text_New);

#ifdef __TOUCH_SCREEN_MMI__
DECLARE_NEW_FUNC(MAE_TouchSrv_New);
#else
#define MAE_TouchSrv_New NULL
#endif

#ifdef __G_SENSOR_MMI__
DECLARE_NEW_FUNC(MAESensorMgr_New);
DECLARE_NEW_FUNC(MAEMotionDetector_New);
#else
#define MAESensorMgr_New NULL
#define MAEMotionDetector_New NULL
#endif

#ifdef __GPS_MMI__
DECLARE_NEW_FUNC(GPS_New);
#else
#define GPS_New NULL
#endif

DECLARE_NEW_FUNC(MAEEventDB_New);
DECLARE_NEW_FUNC(MAELogdb_New);
DECLARE_NEW_FUNC(MAELogDBMgr_New);

#if defined(__MMI_OMA_DRM_V1__)
DECLARE_NEW_FUNC(MAERightsDB_New);
#else
#define MAERightsDB_New NULL
#endif

#ifdef __APP_MMI_TODOLIST__
DECLARE_NEW_FUNC(MAETaskDB_New);
DECLARE_NEW_FUNC(MAETaskDBMgr_New);
#else
#define MAETaskDB_New NULL
#define MAETaskDBMgr_New NULL
#endif

// model classes
DECLARE_NEW_FUNC(Model_New);
DECLARE_NEW_FUNC(ArrayModel_New);
DECLARE_NEW_FUNC(VectorModel_New);
DECLARE_NEW_FUNC(MenuModel_New);
DECLARE_NEW_FUNC(DataModel_New);
DECLARE_NEW_FUNC(InterfaceModel_New);
DECLARE_NEW_FUNC(TextModel_New);
DECLARE_NEW_FUNC(SoftkeyModel_New);
DECLARE_NEW_FUNC(IMEAssistModel_New);

#ifdef __MMI_SCRIPT_EASY_EDITOR__
DECLARE_NEW_FUNC(kmx_TextModel_New);
#endif

#endif // __MAE_CLSTBL_C__ for the declaration of new functions


//
// id and new function of core classes
//
DEFINE_CLS_CATEGORY(MAE_CoreClass)
{
	// CLSID_SHELL is always the first one in core class category
	// event ids with CLSID_SHELL prefix will be handled by the shell first
	DEFINE_CLSID_BASE(CLSID_SHELL, MAE_CORE_CLASS_BASE, MAE_Shell_New),
	DEFINE_CLSID(CLSID_MAE, 0), ///< dummy class for classifying system events
	DEFINE_CLSID(CLSID_MAEDEV, 0), ///< dummy class for classifying system events

	DEFINE_CLSID(CLSID_MAINDISP,		Display_New),
	DEFINE_CLSID(CLSID_SUBDISP,			Display_New),

	DEFINE_CLSID(CLSID_STREAM,			NULL),
	DEFINE_CLSID(CLSID_FSTREAM,			NULL),
	DEFINE_CLSID(CLSID_SYSSTAT,			MAESysStat_New),

	DEFINE_CLSID(CLSID_IMAGEMAKER,      MAEImageMaker_New),

	DEFINE_CLSID(CLSID_EVENTDB,			MAEEventDB_New ),
	DEFINE_CLSID(CLSID_LOGDB,			MAELogdb_New ),
	DEFINE_CLSID(CLSID_LOGDBMGR,		MAELogDBMgr_New ),
	DEFINE_CLSID(CLSID_TASKDB,			MAETaskDB_New ),
	DEFINE_CLSID(CLSID_TASKDBMGR,		MAETaskDBMgr_New ),
    DEFINE_CLSID(CLSID_RIGHTSDB,		MAERightsDB_New ),

	DEFINE_CLSID(CLSID_TOUCHSRV, MAE_TouchSrv_New),
	DEFINE_CLSID(CLSID_CLOCK, MAEClock_New),
	DEFINE_CLSID(CLSID_CONFIG, MAEConfig_New),
	DEFINE_CLSID(CLSID_SENSORMGR, MAESensorMgr_New),
	DEFINE_CLSID(CLSID_MOTIONDETECTOR, MAEMotionDetector_New),
	DEFINE_CLSID(CLSID_IBATTERY,		MAEBattery_CreateInstance),
	DEFINE_CLSID(CLSID_GPS,			GPS_New),
	DEFINE_CLSID(CLSID_RSHEAD,		NULL),
	DEFINE_CLSID(CLSID_RSTHEMES,	NULL),
	DEFINE_END_OF_CLSID(CLSID_END_OF_CORE)
};


//
// id and new function of basic	classes
//
DEFINE_CLS_CATEGORY(MAE_BasicClass)
{
	DEFINE_CLSID_BASE(CLSID_FONT, MAE_BASIC_CLASS_BASE, Font_New),
	DEFINE_CLSID(CLSID_BITMAP,		NULL),
	DEFINE_CLSID(CLSID_IMAGE,		Image_New),
	DEFINE_CLSID(CLSID_NFONT,		Font_New),
	DEFINE_CLSID(CLSID_BFONT,		Font_New),
    DEFINE_CLSID(CLSID_TEXT,        Text_New),

	DEFINE_END_OF_CLSID(CLSID_END_OF_BASIC)
};


//
// id and new function of model	classes
//
DEFINE_CLS_CATEGORY(MAE_ModelClass)
{
	DEFINE_CLSID_BASE(CLSID_MODEL, MAE_MODEL_CLASS_BASE, Model_New),
	DEFINE_CLSID(CLSID_LISTMODEL,		NULL),
	DEFINE_CLSID(CLSID_ARRAYMODEL,		ArrayModel_New),
	DEFINE_CLSID(CLSID_VECTORMODEL,		VectorModel_New),
	DEFINE_CLSID(CLSID_DATAMODEL,		DataModel_New),
	DEFINE_CLSID(CLSID_INTERFACEMODEL,	InterfaceModel_New),

	DEFINE_END_OF_CLSID(CLSID_END_OF_MODEL)
};
#endif

#endif // __MAE_CLSTBL_H__

// end of file
