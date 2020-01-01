

/**
 * @file
 * Agent Porting Layer
 *
 * Basic support functions that are needed by agent.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_agent Interface
 * - NCCPort_brwagent_regAuthGetFunc()
 * - NCCPort_brwagent_regDialNumberFunc()
 * - NCCPort_brwagent_regSendDtmfFunc()
 * - NCCPort_brwagent_regAddToPhonebookFunc()
 * - NCCPort_brwagent_regSendWtaiNotifyFunc()
 * - NCCPort_brwagent_regSaveDataDialogFunc()
 * - NCCPort_brwagent_regSaveDataFileFunc()
 * - NCCPort_brwagent_clearScreen()
 * - NCCPort_brwagent_isEmpty()
 * - NCCPort_brwagent_setAddressEdit()
 * - NCCPort_brwagent_getCharWidthAttr()
 * - NCCPort_brwagent_getFontWidth()
 * - NCCPort_brwagent_getFontWidthAttr()
 * - NCCPort_brwagent_getFontHeight()
 * - NCCPort_brwagent_authGetFunc()
 * - NCCPort_brwagent_hangup()
 * - NCCPort_brwagent_dialNumber()
 * - NCCPort_brwagent_addPhonebook()
 * - NCCPort_brwagent_makeDtmf()
 * - NCCPort_brwagent_sendWtaiNotify()
 * - NCCPort_brwagent_saveFileDialog()
 * - NCCPort_brwagent_saveDataDialog()
 * - NCCPort_brwagent_saveDataFile()
 * - NCCPort_brwagent_getTextAreaHeight()
 * - NCCPort_brwagent_getRadioBoxHeight()
 * - NCCPort_brwagent_getRadioBoxWidth()
 * - NCCPort_brwagent_getCheckBoxHeight()
 * - NCCPort_brwagent_getCheckBoxWidth()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_AGENT_H__
#define __NCCPORT_BROWSER_AGENT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t(* brwagentAuthGetFunc)(int8_t *info, int8_t **username, int8_t **passwd);
typedef int32_t(* brwagentDialNumberFunc)(int8_t *number);
typedef int32_t(* brwagentPlayStreamingFunc)(int8_t *pURL, bool isRtsp, int8_t *pReAccessURL);
typedef int32_t(* brwagentSendDtmfFunc)(int8_t *dtmf);
typedef int32_t(* brwagentAddToPhonebookFunc)(int8_t *name, int8_t *number);
typedef int32_t(* brwagentSendWtaiNotify)(int32_t cause);
typedef int32_t(* brwagentSaveDataDialogFunc)(int8_t *from, int8_t *contentType, int8_t *name, int32_t ContentLength, bool isOMADownload);
typedef int32_t(* brwagentSaveDataFileFunc)(uint8_t *buf, int32_t sumlen,int32_t saveDataErrorFlag, bool isOMADownload);
typedef int32_t(* brwagentShowOMADDInfoFunc)(int8_t *pName, int8_t *pType, int8_t *pSize, int8_t *pVendor, int8_t *pUri, int8_t *pDescription);
typedef void(*brwagentNotifyOMADDStatus)(int32_t status);
typedef int32_t(* brwagentGetExtension)(const u8* pMime);
typedef int32_t(* brwagentCheckSpaceAvailable)(int32_t fileSize, int32_t bufferFactor);

/**
 * Register the authentication function.
 */
void NCCPort_brwagent_regAuthGetFunc(brwagentAuthGetFunc func);

/**
 * Register the dial number function.
 */
void NCCPort_brwagent_regDialNumberFunc(brwagentDialNumberFunc func);

/**
 * Register the send dtmf function.
 */
void NCCPort_brwagent_regSendDtmfFunc(brwagentSendDtmfFunc func);

/**
 * Register the send wtai notify function.
 */
void NCCPort_brwagent_regSendWtaiNotifyFunc(brwagentSendWtaiNotify func);

/**
 * Register the add to phone book function.
 */
void NCCPort_brwagent_regAddToPhonebookFunc(brwagentAddToPhonebookFunc func);

/**
 * Register the save data dialog function.
 */
void NCCPort_brwagent_regSaveDataDialogFunc(brwagentSaveDataDialogFunc func);

/**
 * Register the save data file function.
 */
void NCCPort_brwagent_regSaveDataFileFunc(brwagentSaveDataFileFunc func);

/**
 * Register the play streaming function.
 */
void NCCPort_brwagent_regPlayStreamingFunc(brwagentPlayStreamingFunc func);

/**
 * Remove nodes from view windows for next draw.
 * \param none
 */
void NCCPort_brwagent_clearScreen(void);

/**
 * Whether to clear history.
 * \return <ul>
 *         <li>TRUE :clear
 *         <li>FALSE :not clear
 *         </ul>
 */
int32_t NCCPort_brwagent_isEmpty(void);

/**
 * What size is short of memory.
 * \return size of memory
 */
int32_t NCCPort_brwagent_shortOfMemSize(void);

/**
 * Remain memory when loading a new page.
 * \return size of memory
 */
int32_t NCCPort_brwagent_minMemSizeWhenNew(void);

/**
 * Set need remain min memory size when loading a new page.
 * \param none
 */
void NCCPort_brwagent_setMinMemSizeWhenNew(int32_t memSize);

/**
 * Get need remain min memory size when loading a new page.
 * \return size of memory
 */
int32_t NCCPort_brwagent_getMinMemSizeWhenNew(void);

/**
 * Set text of address edit box.
 * \param  url Text of the url.
 */
void NCCPort_brwagent_setAddressEdit(int8_t * url);

/**
 * Query character width font size, font family, font attributes and its code in utf8.
 * \param fontsize Font size.
 * \param ch unicode character
 * \param attr Attributes of font, such as bold, italic etc.
 *       <li>bit 0(0x01): bold</li>
 *       <li>bit 1(0x02): italicized</li>
 *       <li>bit 2(0x04): underline</li>
 *       <li>bit 3(0x08): strikethrough</li>
 *       <li>bit 4(0x10): subscript</li>
 *       <li>bit 5(0x20): superscript</li>
 * \param fontName Font family.
 * \return font width in pixel.
 */
int32_t NCCPort_brwagent_getCharWidthAttr(int32_t fontsize, uint16_t ch, int32_t attr, const char* fontName);

/**
 * Query character width using system default font.
 * \param ch unicode character
 * \return font width in pixel.
 */
int32_t NCCPort_brwagent_getCharDefaultWidth(uint16_t ch);

/**
 * Query the width of specified font and character.
 * \param fontsize Font size.
 * \param ch The character.
 * \return Return the width.
 */
int32_t NCCPort_brwagent_getFontWidth(int32_t fontsize,int8_t ch);

/**
 * Query the width of specified font and character.
 * \param fontsize Font size.
 * \param ch The character.
 * \param attr The character attribute.
 * \return Return the width.
 * \attention Unused function.
 */
int32_t NCCPort_brwagent_getFontWidthAttr(int32_t fontsize, int8_t c, int32_t attr);

/**
 * Query max line height of specified font
 * \param fontsize Font size
 * \return Max line height
 */
int32_t NCCPort_brwagent_getFontHeight(int32_t fontsize);

/**
 * Release font attribute memory
 */
int32_t NCCPort_brwagent_releaseFontAttr(void);

/**
 * Query TextArea height by rows.
 * \param rows Total rows.
 * \return Height of TextArea.
 */
int32_t NCCPort_brwagent_getTextAreaHeight(int32_t rows);

/**
 * Query RadioBox height.
 * \return the height of radiobox of current plat.
 */
int32_t NCCPort_brwagent_getRadioBoxHeight(void);

/**
 * Query RadioBox height.
 * \return the height of radiobox of current plat.
 */
int32_t NCCPort_brwagent_getRadioBoxWidth(void);

/**
 * Query CheckBox height.
 * \return the height of Checkbox of current plat.
 */
int32_t NCCPort_brwagent_getCheckBoxHeight(void);

/**
 * Query CheckBox height.
 * \return the height of Checkbox of current plat.
 */
int32_t NCCPort_brwagent_getCheckBoxWidth(void);

/**
 * Get username and password of basic http validate.
 * \param ream Info of validate
 * \param user Username
 * \param pass Password
 * \return <ul>
 *         <li> TRUE :gotten
 *         <li> FALSE :cancel
 *         </ul>
 */
int32_t NCCPort_brwagent_authGetFunc(int8_t * ream,int8_t **user,int8_t ** pass);

/** WTAI functions,need realized by useragent */

/**
 * Hang up telephone.
 * Suppose to realize a prompt of success or failed. If not support this function,
 * please realize a empty API.
 * \return <ul>
 *          <li>0:success;</li>
 *          <li>-108: failed;</li>
 *          <li>-200: invalid;</li>
 *          <li>-1: unknown error.</li>
 *        </ul>
 */
int32_t NCCPort_brwagent_hangup(void);

/**
 * Dial.
 * Suppose to realize a prompt of success or failed. If not support this function, please realize a empty API.
 * \param number tel number.
 * \return <ul>
 *          <li>0: success;
 *          <li>-105: the number you called is busy.
 *          <li>-106: no network
 *          <li>-107: no response.
 *          <li>-200: invalid.
 *          <li>-1: unknown error.
 *       </ul>
 */
int32_t NCCPort_brwagent_dialNumber(int8_t * number);

/**
 * Add Phone book.
 * Suppose to realize a prompt of success or failed. If not support this function, please realize a empty API.
 * \param name name.
 * \param number tel number.
 * \return <ul>
 *          <li>0: success;
 *          <li>-100: name invalid or too long;
 *          <li>-102: num invalid or too long;
 *          <li>-103: write failed.
 *          <li>-104: full of phone book.
 *          <li>-200: invalid.
 *          <li>-1: unknown error.
 *       </ul>
 */
int32_t NCCPort_brwagent_addPhonebook(int8_t * name, int8_t * number);

/**
 * Generate phonetic data.
 * Suppose to realize a prompt of success or failed. If not support this function, please realize a empty API.
 * \param dtmf data string.
 * \return <ul>
 *          <li>0:    success;
 *          <li>-108: failed.
 *          <li>-200: invalid.
 *          <li>-1: unknown error.
 *       </ul>
 */
int32_t NCCPort_brwagent_makeDtmf(int8_t * dtmf);

/**
* send WTAI notify to MMI level
* \return <ul>
*          <li>0:  success;
*          <li>-1: unknown error.
*       </ul>
*/
int32_t NCCPort_brwagent_sendWtaiNotify(int32_t cause);

/**
* dial to gprs
* \return <ul>
*          <li>0:    success;
*          <li>-1: unknown error.
*       </ul>
*/
int32_t NCCPort_brwagent_dialGprs(void);
/**
 * Dialog for save page to local file.
 * \return <ul>
 *      <li>TRUE: can save
 *      <li>FALSE:can not save
 *      </ul>
 */
int32_t NCCPort_brwagent_saveFileDialog(void);

/**
 * Dialog for save download file.
 * Dialog will pop up when a download file is not a img of a page,
 * and user will chose whether to save or not, where to save and the name to save.
 * \param   path            Url of the download file
 * \param   contentType     Contenttype of the download file
 * \param   length          Length of the download file
 * \return <ul>
 *      <li>TRUE: can save
 *      <li>FALSE:can not save
 *      </ul>
 */
int32_t NCCPort_brwagent_saveDataDialog(
                              int8_t * path,
                              int8_t * contentType,
                              int8_t * contentName,
                              int32_t ContentLength,
                              bool isOMADownload
                              );

/**
 * Save download file.
 * \param   buf Data pointer of the download file
 * \param   length Length of the download file
 * \return <ul>
 *      <li>TRUE: can save
 *      <li>FALSE:can not save
 *      </ul>
 */
int32_t NCCPort_brwagent_saveDataFile(int8_t * buf,int32_t sumlen, int32_t saveDataErrorFlag, bool isOMADownload);

void NCCPort_brwagent_regShowOMADDInfoFunc(brwagentShowOMADDInfoFunc func);

void NCCPort_brwagent_regNotifyOMADDStatusFunc(brwagentNotifyOMADDStatus func);

void NCCPort_brwagent_regGetExtension(brwagentGetExtension func);

void NCCPort_brwagent_regCheckSpaceAvailable(brwagentCheckSpaceAvailable func);
/**
 * Generate the display infomation for DD
 */
int32_t NCCPort_brwagent_showOMADDInfo(int8_t *pName, int8_t *pType,
    int8_t *pSize, int8_t *pVendor, int8_t *pUri, int8_t *pDescription);

void NCCPort_brwagent_notifyOMADDStatus(int32_t status);

int8_t* NCCPort_brwagent_getExtension(int8_t *pMime);

int32_t NCCPort_brwagent_checkSpaceAvailable(int32_t fSize, int32_t bufferFactor);

/**
 * Play streaming.
 * Suppose to realize a prompt of success or failed. If not support this function, please realize a empty API.
 * \param pURL streaming location.
 * \param isRtsp streaming type. TRUE: RTSP, FALSE: HTTP
 * \param pReAccessURL last browsing page URL.
 * \return void
 */
int32_t NCCPort_brwagent_playStreaming(int8_t * pURL, bool isRtsp, int8_t * pReAccessURL);

#ifdef __cplusplus
}
#endif

#endif/* __NCCPORT_BROWSER_AGENT_H__ */

