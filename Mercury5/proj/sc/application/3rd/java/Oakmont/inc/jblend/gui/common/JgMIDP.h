/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Definitions specific to MIDP
 */

#ifndef ___GUI_COMMON_MIDP_H
#define ___GUI_COMMON_MIDP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @internal
 */
#define JG_AS_MIDP_START                        0x00000100

/**
 * @addtogroup GUI_CheckBox
 * @{
 */

/**
 * Component extended information definition.\ This means the component was created 
 * as javax.microedition.lcdui.ChoiceGroup MULTIPLE.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_CHOICEGROUP_MULTIPLE         (JG_AS_MIDP_START + 0x01)

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.List MULTIPLE.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_LIST_MULTIPLE                (JG_AS_MIDP_START + 0x02)

/** @} */

/**
 * @addtogroup GUI_RadioButton
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.ChoiceGroup
 * EXCLUSIVE.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_CHOICEGROUP_EXCLUSIVE        (JG_AS_MIDP_START + 0x03)

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.List
 * EXCLUSIVE.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_LIST_EXCLUSIVE               (JG_AS_MIDP_START + 0x04)

/**
 * Component extended information definition.\
 * This means the component was created as the list of MIDP Permission Dialog.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_PERMISSION_LIST              (JG_AS_MIDP_START + 0x05)

/** @} */

/**
 * @addtogroup GUI_ImplicitList
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.List IMPLICIT.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_LIST_IMPLICIT                (JG_AS_MIDP_START + 0x06)

/** @} */

/**
 * @addtogroup GUI_PopupList
 * @{
 */

/**
 *   Component extended information definition.\
 *   This means the component was created as javax.microedition.lcdui.ChoiceGroup POPUP.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_CHOICEGROUP_POPUP            (JG_AS_MIDP_START + 0x07)

/** @} */

/**
 * @addtogroup GUI_CommandMenu
 * @{
 */

/**
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_COMMAND_MENU                 (JG_AS_MIDP_START + 0x08)

/** @} */

/**
 * @addtogroup GUI_TextBox
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.TextBox.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_TEXTBOX                      (JG_AS_MIDP_START + 0x09)

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.TextField.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_TEXTFIELD                    (JG_AS_MIDP_START + 0x0a)

/** @} */

/**
 * @addtogroup GUI_Ticker
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.Ticker.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_TICKER                       (JG_AS_MIDP_START + 0x0b)

/** @} */

/**
 * @addtogroup GUI_Gauge
 * @{
 */

/**
 * Component extended information definition.\
 * This means that the component was created as javax.microedition.lcdui.Gauge
 * in interactive mode.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_GAUGE_INTERACTIVE            (JG_AS_MIDP_START + 0x0c)

/**
 * Component extended information definition.\
 * This means that the component was created as javax.microedition.lcdui.Gauge
 * in non-interactive mode.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_GAUGE_NON_INTERACTIVE        (JG_AS_MIDP_START + 0x0d)

/** @} */

/**
 * @addtogroup GUI_DateField
 * @{
 */

/**
 *   Component extended information definition.\
 *   This means the component was created as javax.microedition.lcdui.DateField.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_DATEFIELD                    (JG_AS_MIDP_START + 0x0e)

/** @} */

/**
 * @addtogroup GUI_Label
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.Item Label.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_ITEM_LABEL                   (JG_AS_MIDP_START + 0x0f)

/** @} */

/**
 * @addtogroup GUI_Title
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.Displayable Title.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_DISPLAYABLE_TITLE            (JG_AS_MIDP_START + 0x10)

/**
 * Component extended information definition.\
 * This means the component was created as the title of MIDP Permission Dialog.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_PERMISSION_TITLE             (JG_AS_MIDP_START + 0x11)

/** @} */

/**
 * @addtogroup GUI_Button
 * @{
 */

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.StringItem BUTTON.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_STRINGITEM_BUTTON            (JG_AS_MIDP_START + 0x12)

/**
 * Component extended information definition.\
 * This means the component was created as javax.microedition.lcdui.ImageItem BUTTON.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_IMAGEITEM_BUTTON             (JG_AS_MIDP_START + 0x13)

/** @} */

/**
 * @addtogroup GUI_Alert
 * @{
 */

/*
 * Component extended information definition.\
 * This means the component was created as MIDP Permission Dialog.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_PERMISSION_DIALOG            (JG_AS_MIDP_START + 0x14)

/**
 *   Component extended information definition.\
 *   This means the component was created as <code>javax.microedition.lcdui.Alert</code>.
 * 
 * @see JgComGetExtraData
 */
#define JG_AS_MIDP_ALERT                        (JG_AS_MIDP_START + 0x15)

/** @} */




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_MIDP_H */

