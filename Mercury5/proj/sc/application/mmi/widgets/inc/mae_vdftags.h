/**
 * @file    mae_vdftags.h
 * @brief   The document describes the tags enumeration used in VDF.
 * @author  steve.lee@mstarsemi.com
 * @version $Id: mae_vdftags.h 20863 2009-01-19 10:59:56Z paul.ouyang $
 */
#ifndef __MAE_VDFTAGS_H__
#define __MAE_VDFTAGS_H__

//TBD~
typedef enum VDFElementTags_tag
{
	APP = 0,
	VIEW,
	WIDGET,
	COMPONENT_WIDGET,
	MODEL,
	MODEL_ITEM,
	IMAGE,
	FLAG,
	POSITION,
	PROPERTY,
	STRING,
	BINARY,
	STRUCT,
	MENUITEM,
	SOFTKEY,
	ABILITY
}VDFElementTags_t;

typedef enum VDFPositionType_tag
{
	PROPORTION,
	VISIBLE,
	X_POSITION,
	Y_POSITION,
	FOCUS_ON
}VDFPositionType_t;

typedef enum VDFWidgetAbility_tag
{
	CHANGE_TITLE,
	CHANGE_SOFTKEY
}VDFWidgetAbility_t;

/*
* ONLY vector model care about model item's type!
* Model item in text-model or interface-model will always be regarded as Single Model Item.
* Model item in data-model or menu-model will always be regarded as Struct Model Item.
*/
typedef enum VDFMdlItemType_tag
{
	STRUCT_MDLITEM,
	SINGLE_MDLITEM
} VDFMdlItemType_t;

#endif /* __MAE_VDFTAGS_H__ */
