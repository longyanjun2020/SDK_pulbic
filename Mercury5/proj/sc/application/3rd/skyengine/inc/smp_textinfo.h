#ifndef _SMP_TEXTINFO_H
#define _SMP_TEXTINFO_H

#include "sgl_window.h"

/**
  \defgroup smp_textinfo Simple TextInfo

  To work with the textinfo window:
  - Create the textinfo window
  - Set the textinfo content

  \code
  	hTextInfo = SGL_CreateWindow(SMP_TextInfo_WndProc, ...);
  	SMP_TextInfo_SetContent(hTextInfo, ...);
  	SGL_AddChildWindow(hWnd, hTextInfo);
  \endcode
  
  @ingroup controls
  @{
*/

/**
 * \brief Max supported lines.
 */
#define SMP_TEXTINFO_LINECOUNT	50

	/**
	* \name Window Styles
	* @{
	*/

/**
 * \brief Indicate the window does not have a scrollbar.
 */
#define SMP_TEXTINFOS_NOSCRBAR		0x0001L

	/** @} */

	/**
	 * \name Window Member Functions
	 * @{
	 */

/**
 * \brief Set the content of the text info.
 *
 * \param hWnd the text info window handle
 * \param pContent the content
 */
VOID SMP_TextInfo_SetContent(HWND hWnd, PCWSTR pContent);

/**
 * \brief Relayout the content.
 *
 * \param hWnd the textinfo window handle
 */
VOID SMP_TextInfo_Refresh(HWND hWnd);

	/** @} */

	/**
	 * \name Window Procedure
	 * @{
	 */

/**
 * \brief The textinfo window procedure.
 *
 * \param hWnd the window handle
 * \param Msg the window message
 * \param wParam the first parameter
 * \param lParam the second parameter
 * \return the result of message process 
 */
LRESULT SMP_TextInfo_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	/** @} */

/** @} end of smp_textinfo */

#endif /* _SMP_TEXTINFO_H */
