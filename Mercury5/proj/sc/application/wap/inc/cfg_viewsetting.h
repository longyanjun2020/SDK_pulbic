
/**
 * @file
 * View setting interfaces.
 */

#ifndef __CFG_VIEWSETTING_H__
#define __CFG_VIEWSETTING_H__

#include <cfg_internal.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Get font mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Font mode
 */
E_FONT_MODE cfg_getFontMode(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Set font mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   fontMode        Font mode which will be set.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setFontMode(T_BROWSERCONFIG *pBrowserConfig, E_FONT_MODE fontMode);

/**
 * Get language mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Language mode
 */
E_LANG_MODE cfg_getLangMode(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Set max image in one page
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   nMaxImgInPage   Max image in one page
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setMaxImgInPage(T_BROWSERCONFIG *pBrowserConfig, int32_t nMaxImgInPage);

/**
 * Get max image in one page
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  The number of max image in one page
 */
int32_t cfg_getMaxImgInPage(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Set language mode
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   langMode        Language mode which will be set.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setLangMode(T_BROWSERCONFIG *pBrowserConfig, E_LANG_MODE langMode);



/**
 * Get max number of character encodings supported by browser.
 *
 * \return  Maximum of character encodings.
 */
int32_t cfg_getEncodingTotalNum(void);

/*
 * Get handle of original charset encoding.
 * \return  pointer of array to charset encoding string.
 */
const int8_t **cfg_getOriginalEncodingHandle(void);

/**
 * Get handle of browser codepage setting
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  pointer to pointer to codepage string.
 */
int8_t **cfg_getCodepageHandle(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get current codepage index.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Index of current codepage string.
 */
int32_t cfg_getCurCodepage(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Set current codepage index.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \parm    index           Index for current selected codepage in codepage array.
 * \return  Index of current codepage string.
 */
int32_t cfg_setCurCodepage(T_BROWSERCONFIG *pBrowserConfig, int32_t index);

/**
 * Get handle of screen Resolution setting.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  Address of resolution array.
 *
 *\attention    one 32bit display a screen resolution
 */
int32_t *cfg_getScreenResolutionList(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get current resolutin index of screen Resolution setting.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  current resolution index.
 */
int32_t cfg_getCurScreenResolution(T_BROWSERCONFIG *pBrowserConfig);

/**
 * Get current resolutin index of screen Resolution setting.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   index           Index of screen resolution array.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_setCurScreenResolution(T_BROWSERCONFIG *pBrowserConfig, int32_t index);

/**
 * Get current advance options.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
int32_t cfg_getAdvanceOption(T_BROWSERCONFIG *pBrowserConfig, E_ADVANCE_OPTION advanceOpton);

/**
 * Set new advance options.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   advanceOpton    New advance options.
 * \return  <ul>
 *              <li> TRUE   if sucessful.
 *              <li> FALSE  if failed.
 *          </ul>
 */
void cfg_setAdvanceOption(T_BROWSERCONFIG *pBrowserConfig, E_ADVANCE_OPTION advanceOpton);

/**
 * Unset certain advance option.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 * \param   advanceOpton    Advance option which will be unset.
 */
void cfg_unsetAdvanceOption(T_BROWSERCONFIG *pBrowserConfig, E_ADVANCE_OPTION advanceOpton);

/**
 * Revert to default advance options.
 * \param   pBrowserConfig  Pointer to Browser running config structure.
 */
void cfg_resetAdvanceOption(T_BROWSERCONFIG *pBrowserConfig);

#ifdef __cplusplus
}
#endif

#endif /* __CFG_VIEWSETTING_H__ */
