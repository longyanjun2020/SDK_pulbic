#ifndef _SMP_LIST_H
#define _SMP_LIST_H

#include "sgl_window.h"

/**
  \defgroup smp_list Simple List

  To work with simple list:
  - Create your data provider callbacks
  - Create the simple list
  - Set the list data provider with your callbacks
  - Add to the parent window
  - Response to the notify events

  \code
  int YourListGetTotal(VOID)
  {
  	...
  }

  VOID YourListGetRowData(int index, PSMPROWDATA pRowData)
  {
  	...
  }

  //create the list
  hList = SGL_CreateWindow(SMP_List_WndProc, ...);
  SMP_List_SetDataProvider(hList, YourListGetTotal, YourListGetRowData);
  SGL_AddChildWindow(hWnd, hList);

  //response to the notify messages
	case WM_COMMAND:
		WID id = LOWORD(wParam);
		WORD code = HIWORD(wParam);

		if(id == "the list id")
		{
			int index = (int)lParam; //the selected row index
			switch(code)
			{
			case SMP_LISTN_HILICHANGED:
				break;
			case SMP_LISTN_SELECTED:
				break;
			case SMP_LISTN_CLICKED:
				break;
			}
		}	  
  \endcode
  
  @ingroup controls
  @{
*/

	/**
	* \name Window Styles
	* @{
	*/

/**
 * \brief Indicates the list has no scrollbar.
 */
#define SMP_LISTS_NOSCRBAR			0x0001L

	/** @} */

	/**
	 * \name Window Notify Messages
	 * @{
	 */

/**
 * \brief Sent when high light index changed.
 *
 * \code
 *	case WM_COMMAND:
 *		WID id = LOWORD(wParam);
 *		WORD code = HIWORD(wParam);
 *
 *		if(id == "the list id" && code == SMP_LISTN_HILICHANGED)
 *		{
 *			int index = (int)lParam;
 * 			//handle the notify message
 *		}
 * \endcode
 *
 * \param index current high light index
 */
#define SMP_LISTN_HILICHANGED			0x0001

/**
 * \brief Sent when KEY SELECT up.
 *
 * \code
 *	case WM_COMMAND:
 *		WID id = LOWORD(wParam);
 *		WORD code = HIWORD(wParam);
 *
 *		if(id == "the list id" && code == SMP_LISTN_SELECTED)
 *		{
 *			int index = (int)lParam;
 * 			//handle the notify message
 *		}
 * \endcode
 *
 * \param index current high light index
 */
#define SMP_LISTN_SELECTED			0x0002

/**
 * \brief Sent when MOUSE up.
 *
 * \code
 *	case WM_COMMAND:
 *		WID id = LOWORD(wParam);
 *		WORD code = HIWORD(wParam);
 *
 *		if(id == "the list id" && code == SMP_LISTN_CLICKED)
 *		{
 *			int index = (int)lParam;
 * 			//handle the notify message
 *		}
 * \endcode
 *
 * \param index current high light index
 */
#define SMP_LISTN_CLICKED				0x0003

	/** @} */

/**
 * \brief Max supported collumns.  
 */
#define SMP_LIST_MAX_STR_COL		2

/**
 * \brief Row information.
 */
typedef struct SMP_RowData
{
	/** left margin */
	Uint16 margin;
	/** icon col width */
	Uint16 colWidth0;
	/** icon handle */
	HBITMAP hBmp;
	/** col information */
	struct{
		/** col string */
		PCWSTR str;
		/** col width */
		Uint16 width;
	}cols[SMP_LIST_MAX_STR_COL];	
}SMPROWDATA, *PSMPROWDATA;

enum
{
	SMP_LIST_TYPE_NORMAL=1,
	SMP_LIST_TYPE_SINGLE_SELECT,
	SMP_LIST_TYPE_MULTI_SELECT
};
typedef  u32  SMP_TYPE_E;

/**
 * \brief The function provide to list to get total row count.
 *
 * \return the total rows of the list
 */
typedef int (*SMP_List_GetTotal)(HWND hList);

/**
 * \brief The function provide to list to get row data.
 *
 * \param index the row index
 * \param[out] pRowData the row data
 */
typedef VOID (*SMP_List_GetRowData)(HWND hList, int index, PSMPROWDATA pRowData);

/**
 * \brief The draw row function.
 *
 * \param index the row index
 * \param r the r rectangle
 * \param pRowData the row data
 * \param hilight the high light row index
 * \param flush if flush to the screen
 */
typedef VOID (*SMP_List_DrawRow)(HWND hList,int index, PRECT r, PSMPROWDATA pRowData, int hilight, BOOL flush);

	/**
	 * \name Window Member Functions
	 * @{
	 */

/**
 * \brief Set user data provide callbacks.
 *
 * \param hList the list window handle
 * \param fnGetTotal the function to get total row count
 * \param fnGetRowData the function to get row data by index that from 0
 */
VOID SMP_List_SetDataProvider(HWND hList, SMP_List_GetTotal fnGetTotal, SMP_List_GetRowData fnGetRowData);

/**
 * \brief Set a user specific drawing function.
 *
 * \param hList the List window handle
 * \param fnDrawRow the new draw row function
 */
VOID SMP_List_SetDrawRowCallback(HWND hList, SMP_List_DrawRow fnDrawRow);

/**
 * \brief The default draw row function.
 *
 * \param index the index of the list item
 * \param r the list item draw rect
 * \param pRowData the row data
 * \param hilight current hilight list item index
 * \param flush if flush to screen
 */
VOID SMP_List_DefaultDrawRowCallback(HWND hList,int index, PRECT r, PSMPROWDATA pRowData, int hilight, BOOL flush);

/**
 * \brief High light a row by index.
 *
 * \param hList the List window
 * \param index the row index
 */
VOID SMP_List_HilightByIndex(HWND hList, int index);

/**
 * \brief Get current high light row index.
 *
 * \param hList the List window handle
 * \return the row index
 */
int SMP_List_GetHilightIndex(HWND hList);

/**
 * \brief Get the current page start item index and page size.
 *
 * \param hList the list window handle
 * \param[out] pagestart the current page start list item
 * \param[out] pagesize the list page size
 */
VOID SMP_List_GetPageInfo(HWND hList, int* pagestart, int* pagesize);

/**
 * \brief Page up the list.
 *
 * \param hList the list window handle
 */
VOID SMP_List_PageUp(HWND hList);

/**
 * \brief Page down the list. 
 *
 * \param hList the list window handle
 */
VOID SMP_List_PageDown(HWND hList);

/**
 * \brief Line up the list.
 *
 * \param hList the list window handle
 */
VOID SMP_List_LineUp(HWND hList);

/**
 * \brief Line down the list.
 *
 * \param hList the list window handle
 */
VOID SMP_List_LineDown(HWND hList);

/**
 * \brief Notify list that total list items changed.
 *
 * \param hList the list window handle
 */
VOID SMP_List_Refresh(HWND hList);

/**
 * \brief Reset the list.
 * 
 * \param hList the list window handle
 */
VOID SMP_List_Reset(HWND hList);

	/** @} */

	/**
	 * \name Window Procedure
	 * @{
	 */

/**
 * \brief The simple list window procedure.
 *
 * \param hList the window handle
 * \param Msg the window message
 * \param wParam the first parameter
 * \param lParam the second parameter
 * \return the result of message process 
 */
LRESULT SMP_List_WndProc(HWND hList, UINT Msg, WPARAM wParam, LPARAM lParam);

	/** @} */
	
/**
 * \brief set hilight.
 *
 * \param hList the list window handle.
 * \param index is the hilight.
 */

VOID SMP_List_SetHilight(HWND hList, int index);


void SMP_List_SetListType(HWND hList, int listtype);


void SMP_List_SetIniSelItem(HWND hList,char *sel, int32 total, int32 signal_sel);


void SMP_List_SetSelItem(HWND hList,int32 signal_sel);

	/** @} */
	
/** @} end of smp_list */

#endif /* _SMP_LIST_H */

