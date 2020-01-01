#ifndef _SMP_TOOLBAR_H
#define _SMP_TOOLBAR_H

#include "sgl_window.h"

/**
  \defgroup smp_toolbar Simple Toolbar

  Simple toolbar will transfer the notify message to the key events:
  - Left -- softkey left up
  - Mid -- softkey select up
  - Right -- softkey right up

  To work with the simple toolbar:
  - Create the simple toolbar
  - Set the toolbar strings
  - Response to the softkey left/select/right

  \code
  	//create the toolbar
  	hToolbar = SGL_CreateWindow(SMP_Toolbar_WndProc, ...);
  	SMP_Toolbar_SetStrings(hToolbar, ...);
  	SGL_AddChildWindow(hWnd, hToolbar);

  	//response 
  	case WM_KEYUP:
  		if(MR_KEY_SOFTLEFT == wParam)
  		{
  			//left
  		}else if(MR_KEY_SELECT == wParam){
  			//mid
  		}else if(MR_KEY_SOFTRIGHT == wParam){
  			//right
  		}
  \endcode

  @ingroup controls
  @{
*/

/**
 * \brief Max support toolbar items.
 */
#define SMP_TOOLBAR_ITEMCOUNT		3

/**
 * \brief Left location of the  simple toolbar.
 */
#define SMP_TOOLBARLOC_LEFT		0

/**
 * \brief Mid location of the  simple toolbar.
 */
#define SMP_TOOLBARLOC_MID		1

/**
 * \brief Right location of the  simple toolbar.
 */
#define SMP_TOOLBARLOC_RIGHT		2

	/**
	 * \name Window Member Functions
	 * @{
	 */

/**
 * \brief Set toolbar strings.
 *
 * \param hWnd the toolbar handle
 * \param left the left string
 * \param mid the middle string
 * \param right the right string
 * \param redraw redraw the toolbar
 */
VOID SMP_Toolbar_SetStrings(HWND hWnd, char* left, char* mid, char* right, BOOL redraw);

/**
 * \brief Get the toolbar item id.
 * 
 * \param hWnd the toolbar window handle
 * \param location which item
 * \return the item id
 */
DWORD SMP_Toolbar_GetString(HWND hWnd, int location);

	/** @} */

	/**
	 * \name Window Procedure
	 * @{
	 */

/**
 * \brief The simple toolbar window procedure.
 *
 * \param hWnd the window handle
 * \param Msg the window message
 * \param wParam the first parameter
 * \param lParam the second parameter
 * \return the result of message process 
 */
LRESULT SMP_Toolbar_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	/** @} */

/** @} end of smp_toolbar */

#endif /* _SMP_TOOLBAR_H */

