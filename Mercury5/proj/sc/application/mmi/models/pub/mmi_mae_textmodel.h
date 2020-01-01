/**
 * @file    mmi_mae_textmodel.h
 * @brief   This file defines the interface of text-model.
 * 
 * @version $Id: mae_textmodel.h 38890 2009-08-29 16:22:38Z zinc.chen $
 */

#ifndef __MMI_MAE_TEXTMODEL_H__
#define __MMI_MAE_TEXTMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"
//#include "mmi_mae_common_def.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    u32 nTextLen; //length of pwText
    u32 nSelectionStart; //start of selection
    u32 nSelectionEnd; //end of selection
    u32 nUnderlineStart; //start of underline
    u32 nUnderlineEnd; //end of underline
    u32 nCursorPos; //Cursor position
    MAE_WChar *pwText; //text in model
} TextInfo;

// Event that the text model sends out
typedef struct
{
    ModelEvent_t MEvtBase;      ///< model event base structure
    TextInfo *pTextInfo;    ///< The pointer of text info of the text model, the model listener shouldn't free the pointer
} TextModelEvent_t;

#define TEXTMODELEVENT_Init(pe,c,dwp,pti) \
    do{(pe)->MEvtBase.nEvtCode = c; \
       (pe)->MEvtBase.nParam= dwp; \
       (pe)->pTextInfo = pti; \
    }while(0)

/*=============================================================*/
// interface
/*=============================================================*/
// ITextModel interface
#define INHERIT_ITextModel(IName) \
    INHERIT_IModel(IName); \
    MAE_Ret (*SetInitText) (IName *p, MAE_WChar *pwText, u32 nTextLen);\
    void (*SetSelection) (IName *p, u32 nSelectionStart, u32 nSelectionEnd);\
    u32 (*GetSelectText) (IName *p, MAE_WChar *pwText, u32 nTextLen);\
    MAE_Ret (*ReplaceSelectText) (IName *p, MAE_WChar *pwText, u32 nTextLen);\
    void (*SetUnderline) (IName *p, u32 nUnderlineStart ,u32 nUnderlineEnd );\
    u32 (*GetUnderlineText) (IName *p, MAE_WChar *pwText, u32 nTextLen);\
    void (*SetCursorPos) (IName *p, u32 nPos);\
    void (*GetTextInfo) (IName *p, TextInfo *pTextInfo)

DEFINE_INTERFACE( ITextModel );
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_QueryInterface(pITextModel,id,pp,pOwner)      GET_FUNCTBL((pITextModel),ITextModel)->QueryInterface(pITextModel,id,pp,pOwner)
#define ITEXTMODEL_SendNotify(pITextModel,pMdlEvt)        GET_FUNCTBL((pITextModel),ITextModel)->SendNotify(pITextModel,pMdlEvt)
#define ITEXTMODEL_AddMdlListener(pITextModel,pMdlLsn)    GET_FUNCTBL((pITextModel),ITextModel)->AddMdlListener(pITextModel,pMdlLsn)
//#define ITEXTMODEL_CancelMdlListener(pITextModel,pMdlLsn) GET_FUNCTBL((pITextModel),ITextModel)->CancelMdlListener(pITextModel,pMdlLsn)
// use MDLLISTENER_CANCEL() instead //
#else
__INLINE MAERet_t ITEXTMODEL_QueryInterface( ITextModel *pITextModel, MAEIId_t id, void **pp, IBase *pOwner )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->QueryInterface( pITextModel , id , pp , pOwner );
}
__INLINE void ITEXTMODEL_SendNotify( ITextModel *pITextModel, ModelEvent_t *pMdlEvt )
{
    GET_FUNCTBL( ( pITextModel ) , ITextModel )->SendNotify( pITextModel , pMdlEvt );
}
__INLINE MAE_Ret ITEXTMODEL_AddMdlListener( ITextModel *pITextModel, ModelListener_t *pMdlLsn )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->AddMdlListener( pITextModel , pMdlLsn );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_AddEvtListener(pITextModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pITextModel),ITextModel)->AddEvtListener(pITextModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ITEXTMODEL_AddEvtListener( ITextModel *pITextModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->AddEvtListener( pITextModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_CancelEvtListener(pITextModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pITextModel),ITextModel)->CancelEvtListener(pITextModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ITEXTMODEL_CancelEvtListener( ITextModel *pITextModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->CancelEvtListener( pITextModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_CancelEvtAllListener(pITextModel,nEvtCode) \
    GET_FUNCTBL((pITextModel),ITextModel)->CancelEvtListener(pITextModel,nEvtCode)
#else
__INLINE MAE_Ret ITEXTMODEL_CancelEvtAllListener( ITextModel *pITextModel, ModelEvtCode_t nEvtCode )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->CancelEvtAllListener( pITextModel , nEvtCode );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_SetInitText:
 * <PRE> 
 *       This function set the initial text for the text model.
 *       (1) free the original text, if the text model have set the text before.
 *       (2) allocate the memory for the new text, and copy the pwText
 *       (3) reset the cursor position as 0
 *       (4) reset the selection Start, End as 0
 *       (5) reset the underline Start, End as 0
 *       (6) Sent the EVT_TEXTMDL_TEXTCHANGE event notify
 * </PRE>          
 * @par Prototype:
 *           MAE_Ret ITEXTMODEL_SetInitText(ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen);
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] pwText       Pointer to the text that is to initiate the current the text model.
 *                            Pass NULL with nLen set to 0 (zero) to delete the text stored in the current model.
 * @param[in] nLen:        The length of the text, in characters, passed in 'pwText'.
 *   
 * @retval MAE_RET_SUCCESS   - The text model was successfully initiated.
 * @retval MAE_RET_OUT_OF_MEMORY - The text model was unable to allocate enough memory to accommodate the initial text.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_SetInitText(pITextModel,pwText,nLen) GET_FUNCTBL((pITextModel),ITextModel)->SetInitText(pITextModel,pwText,nLen)
#else
__INLINE MAE_Ret ITEXTMODEL_SetInitText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->SetInitText( pITextModel , pwText , nLen );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_SetSelection:
 * <PRE>
 *       This function sets the current selection start and end position for the selection range stored in the text model.
 *       (1)Sent the EVT_TEXTMDL_SELECT event notify
 * </PRE>          
 * @par Prototype:
 *           void ITEXTMODEL_SetSelection(ITextModel *pITextModel, u32 nStart, u32 nEnd)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] nStart       The start position of the text selection.
 * @param[in] nEnd         The end position of the text selection.
 *                         (if the nStart/nEnd larger then the length of the whole text in text model, ITEXTMODEL_SetSelection will set the nStart/nEnd
 *                         position equal to the length of the whole text in text model.)
 * 
 * @retval None
 * 
 * @note
 * 
 * <PRE>
 *       Both nStart and nEnd are zero based.
 * 
 *       To illustrate, if 'nStart' is set to 7 and 'nEnd' is set to 9,
 *       the selection will displayed as shown below:  the selection text will be "is"
 *                                                                                             
 *       0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *       ---------------------------------------------------------------------------
 *       | S | n | o | o | p | y |   { i | s }   | s | o |   | c | u | t | e |
 *       ---------------------------------------------------------------------------
 *                                 start    end
 * </PRE>
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_SetSelection(pITextModel,nStart,nEnd) GET_FUNCTBL((pITextModel),ITextModel)->SetSelection(pITextModel,nStart,nEnd)        


#define ITEXTMODEL_GetSelectText(pITextModel,pwText,nLen) GET_FUNCTBL((pITextModel),ITextModel)->GetSelectText(pITextModel,pwText,nLen)    
#else
__INLINE void ITEXTMODEL_SetSelection( ITextModel *pITextModel, u32 nStart, u32 nEnd )
{
    GET_FUNCTBL( ( pITextModel ) , ITextModel )->SetSelection( pITextModel , nStart , nEnd );
}
__INLINE u32 ITEXTMODEL_GetSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->GetSelectText( pITextModel , pwText , nLen );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
 * @par ITEXTMODEL_ReplaceSelectText:
 * <PRE>
 *       This function replaces the current selection text in the text model with a new block of text. 
 *       The selection is a range of the text that saved in the TextInfo by the text model.
 *       Depending on the text selection range and the new text, ITEXTMODEL_ReplaceSel() can be used to replace, insert, append, or delete text
 *       at any position within the stored text.
 *       (1)Sent the EVT_TEXTMDL_TEXTCHANGE event notify
 * </PRE>
 * @par Prototype:
 *           MAE_Ret TextModel_ReplaceSelectText(ITextModel *pITextModel, MAE_WChar *pwText, u32 nTextLen)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] pwText       The pointer to an MAE_WChar buffer for replacing the selection text. 
 * @param[in] nLen         The string length of pwText, (in MAE_WChar *). (not include the zero teriminator)  
 * 
 * @retval MAE_RET_SUCCESS   - The selection text was successfully replaced.
 * @retval MAE_RET_OUT_OF_MEMORY   - The text model was unable to allocate enough memory to accommodate the replacement of the selection text.
 * 
 * @note
 *
 * <PRE>
 *       (1) This selection text replacement will update the underline range, and cursor position automatically. 
 * 
 *            ~ Underline covered Selection => replace selection will still be underlin"
 *            -----------------------------------------------------------------------------
 *            Ex: Replace the "Snoopy" to "Kitty", if the "Snoopy" is underline, after replacement the "Kitty" will still underline
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { S | n | o | o | p | y }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^                       ^           
 *                SS,US                   SE,UE           
 *                
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { K | i | t | t | y }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^                   ^              
 *                SS,US             SE, UE
 * 
 * 
 * 
 *            ~ Underline is the subset of Selection => Underline region will be removed~
 *            -----------------------------------------------------------------------------
 *            Ex: Replace the "Snoopy" to "Kitty", if the underline string is "oopy", after replacement the underline region will be removed
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { S | n [ o | o | p | y ]}  | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^       ^               ^
 *                SS       US             UE,SE
 *                    
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { K | i | t | t | y }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^                   ^
 *                SS                  SE, US, UE
 * 
 * 
 *            ~ Selection overlaps Underline => the overlapped underline will be removed~
 *            -----------------------------------------------------------------------------------
 *            Ex: Replace the "Snoopy" to "Kitty", if the underline string is "oopy is", after replacement the underline string will be " is"
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { S | n [ o | o | p | y }   | i | s ]   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^       ^               ^           ^
 *                SS       US             SE           UE
 *                    
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { K | i | t | t | y }[  | i | s ]   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                 ^                   ^           ^   
 *                SS                  SE, US,      UE
 *                    
 *                
 *            ~ Cursor on the boundary of the Selection"
 *            ------------------------------------------
 *            Ex: Replace the "so" to "very", if the cursor position is equal to the original Selection Start/End,
 *                after replacement the new cursor position will be equal to the new Selection Start/End  
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   { s | o }!  | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                                                         ^       ^  
 *                                                         SS     SE,Cursor
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9
 *                 -------------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   { v | e | r | y }!  | c | u | t | e |
 *                 -------------------------------------------------------------------------------
 *                                                         ^               ^  
 *                                                         SS             SE,Cursor
 * 
 * 
 * 
 *            ~ Cursor is in the Selection Region"
 *            ------------------------------------------
 *            Ex: Replace the "so" to "very", if the cursor position is just after the "s", after the replacement, the new cursor position 
 *                will be equal to the new Selection End  
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   { s ! o }  | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                                                         ^   ^   ^  
 *                                                         SS  C   SE
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9
 *                 -------------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   { v | e | r | y }!  | c | u | t | e |
 *                 -------------------------------------------------------------------------------
 *                                                         ^               ^  
 *                                                         SS             SE,Cursor
 * 
 *           
 *       (2) To illustrate the REPLACE, INSERT, APPEND, DELETE, the text selection should be set as follow: 
 * 
 *            ~To replace text~
 *            ---------------------
 *            Call ITEXTMODEL_SetSelection() to set the range of selection text
 *            Then call ITEXTMODEL_ReplaceSelectText() to replace the selection text as the new block of text.
 * 
 *            Ex:
 *                 ITEXTMODEL_SetInitText(pITextModel, L"Snoopy is so cute", 17);
 *                 ITEXTMODEL_SetSelection(pITextModel, 0, 6);
 *                 ITEXTMODEL_ReplaceSelectText(pITextModel,L"Kitty",5);
 *                     
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { S | n | o | o | p | y }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                                                   
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 { K | i | t | t | y }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 * 
 *            ~To insert text~
 *            -------------------
 *            Call ITEXTMODEL_SetSelection() to set the start/end as the position where the new block of text will be inserted in
 *            Then call ITEXTMODEL_ReplaceSelectText() to replace the selection text as the new block of text.
 * 
 *            Ex:
 *                 ITEXTMODEL_SetInitText(pITextModel, L"Snoopy is so cute", 17);
 *                 ITEXTMODEL_SetSelection(pITextModel, 6, 6);
 *                 ITEXTMODEL_ReplaceSelectText(pITextModel,L"!",1);
 *                     
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y {}  | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 * 
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y { ! }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                                         ^   ^
 *                                       start end
 * 
 * 
 *            ~To append text~
 *            ---------------------
 *            Call ITEXTMODEL_SetSelection() to set the start/end as the position where the new block of text will be append to
 *            Then call ITEXTMODEL_ReplaceSelectText() to replace the selection text as the new block of text.
 * 
 *            Ex:
 *                 ITEXTMODEL_SetInitText(pITextModel, L"Snoopy is so cute", 17);
 *                 ITEXTMODEL_SetSelection(pITextModel, 17, 17);
 *                 ITEXTMODEL_ReplaceSelectText(pITextModel,L"!",1);
 *                     
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   | s | o |   | c | u | t | e {}
 *                 ---------------------------------------------------------------------------
 * 
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y |   | i | s |   | s | o |   | c | u | t | e { ! }
 *                 ---------------------------------------------------------------------------
 *                                                                                     ^   ^
 *                                                                                  start end
 *  
 *            ~To delete text~
 *            ---------------------
 *            Call ITEXTMODEL_SetSelection() to set the region of selection text which will be removed.
 *            Then call ITEXTMODEL_ReplaceSelectText() to replace the selection text as a NULL text.
 * 
 *            Ex:
 *                 ITEXTMODEL_SetInitText(pITextModel, L"Snoopy! is so cute", 18);
 *                 ITEXTMODEL_SetSelection(pITextModel, 6, 7);
 *                 ITEXTMODEL_ReplaceSelectText(pITextModel,L"",0);
 *                     
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y { ! }   | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 *                                         ^   ^
 *                                       start end
 * 
 *                 =>After replace
 * 
 *                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   
 *                 ---------------------------------------------------------------------------
 *                 | S | n | o | o | p | y {}  | i | s |   | s | o |   | c | u | t | e |
 *                 ---------------------------------------------------------------------------
 * </PRE>
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_ReplaceSelectText(pITextModel,pwText,nLen) GET_FUNCTBL((pITextModel),ITextModel)->ReplaceSelectText(pITextModel,pwText,nLen)
#else
__INLINE MAE_Ret ITEXTMODEL_ReplaceSelectText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->ReplaceSelectText( pITextModel , pwText , nLen );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_SetUnderline:
 * <PRE>
 *       This function sets the current underline start and end position for the underline range stored in the text model.
 *       (1)Sent the EVT_TEXTMDL_UNDERLINE event notify
 * </PRE>          
 * @par Prototype:
 *           void ITEXTMODEL_SetUnderline(ITextModel *pITextModel, u32 nStart, u32 nEnd)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] nStart       The start position of the underline text.
 * @param[in] nEnd         The end position of the underlilne text.
 *                         (if the nStart/nEnd larger then the length of the whole text in text model, ITEXTMODEL_SetUnderline will set the nStart/nEnd
 *                         position equal to the length of the whole text in text model.)
 * 
 * @retval None
 * 
 * @note
 *
 * <PRE> 
 *       Both nStart and nEnd are zero based.
 * 
 *       To illustrate, if 'nStart' is set to 7 and 'nEnd' is set to 9,
 *       the underline will displayed as shown below:  the underline text will be "is"
 *                                                                                             
 *       0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *       ---------------------------------------------------------------------------
 *       | S | n | o | o | p | y |   [ i | s ]   | s | o |   | c | u | t | e |
 *       ---------------------------------------------------------------------------
 *                                 start    end
 * </PRE>
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_SetUnderline(pITextModel,nStart,nEnd) GET_FUNCTBL((pITextModel),ITextModel)->SetUnderline(pITextModel,nStart,nEnd)        
#else
__INLINE void ITEXTMODEL_SetUnderline( ITextModel *pITextModel, u32 nStart, u32 nEnd )
{
    GET_FUNCTBL( ( pITextModel ) , ITextModel )->SetUnderline( pITextModel , nStart , nEnd );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_GetUnderlineText:
 * <PRE>
 *       This function retrieves the current underline text in the text model. 
 *       (1) Copy the underline text to the pwText
 *       (2) if the length of underline text larger then the nLen-1  (1 means the zero teriminator)
 *            => This function only copy the (nLen-1) characters
 *           otherwise, This function will copy the whole underline text
 *       (3) Set the teriminate character as NULL
 *       (4) return the copy string length of step (2) 
 * </PRE>          
 * @par Prototype:
 *           u32 ITEXTMODEL_GetUnderlineText (ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] pwText       The pointer to an MAE_WChar buffer into which ITEXTMODEL_GetUnderlineText will copy the selection text. 
 * @param[in] nLen         The pwText buffer lenght, (in MAE_WChar *). 
 *                         This function will reserved 1 character for zero teriminator.
 *                         So the maximun length of retrieved underline text will be nLen-1.
 * 
 * @retval The actually retrieved string length. (<= nLen-1)
 * 
 * @note
 *
 * <PRE>  
 *       ITEXTMODEL_GetUnderlineText will copy into pwText, at most, (nLen -1) characters.
 *       So, to retrieve the entire underline text, nLen must be the length of the underline text plus 1 (1 for the terminating NULL character).
 *       User could get the entire underline text lenght through the ITEXTMODEL_GetTextInfo API
 *           
 *       To illustrate, if nLen >= 3, the retrieved pwText will be the string "is"
 *                                                                                             
 *       0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *       ---------------------------------------------------------------------------
 *       | S | n | o | o | p | y |   [ i | s ]   | s | o |   | c | u | t | e |
 *       ---------------------------------------------------------------------------
 *                                 start    end
 * </PRE>
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_GetUnderlineText(pITextModel,pwText,nLen) GET_FUNCTBL((pITextModel),ITextModel)->GetUnderlineText(pITextModel,pwText,nLen)    
#else
__INLINE u32 ITEXTMODEL_GetUnderlineText( ITextModel *pITextModel, MAE_WChar *pwText, u32 nLen )
{
    return GET_FUNCTBL( ( pITextModel ) , ITextModel )->GetUnderlineText( pITextModel , pwText , nLen );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_SetCursorPos:
 * <PRE>
 *       This function sets the current currsor position stored in the text model.
 *       (1)Sent the EVT_TEXTMDL_CURSOR event notify
 * </PRE>          
 * @par Prototype:
 *           void TEXTMODEL_SetCursorPos(ITextModel *pITextModel, u32 nPos)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] nPos         The cursor position. (if the nPos larger then the length of the whole text in text model, 
 *                         ITEXTMODEL_SetCursorPos will set the cursor position equal to the length of the whole text in text model.)
 * @retval None
 * 
 * @note
 *
 * <PRE> 
 *       nPos are zero based.
 *       To illustrate, if 'nPos' is 6, the Cursor will displayed just after the "y" as shown below
 *                                                                                             
 *       0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
 *       ---------------------------------------------------------------------------
 *       | S | n | o | o | p | y |   [ i | s ]   | s | o |   | c | u | t | e |
 *       ---------------------------------------------------------------------------
 *                                 start    end
 * </PRE>
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_SetCursorPos(pITextModel,nPos) GET_FUNCTBL((pITextModel),ITextModel)->SetCursorPos(pITextModel,nPos)        
#else
__INLINE void ITEXTMODEL_SetCursorPos( ITextModel *pITextModel, u32 nPos )
{
    GET_FUNCTBL( ( pITextModel ) , ITextModel )->SetCursorPos( pITextModel , nPos );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * @par ITEXTMODEL_GetTextInfo:
 * <PRE>
 *       This function retrieves information about the text stored in the text model, 
 *       including the current selection range, current underline range, current cursosr position, a pointer of the stored text, and the string length of the stored text. 
 * </PRE>   
 * @par Prototype:
 *           void ITEXTMODEL_GetTextInfo(ITextModel *pITextModel, TextInfo *pTextInfo)
 * 
 * @param[in] pITextModel  Pointer to the ITextModel interface object.
 * @param[in] pTextInfo    Pointer to a TextInfo data structure, which contains the length of the text, selection range, underline range, cursor position, and the pointer of stored text.
 * @par TextInfo:
 * <PRE>
 *    typedef struct
 *    {
 *      u32 nTextLen; //length of pwText
 *      u32 nSelectionStart; //start of selection
 *      u32 nSelectionEnd; //end of selection
 *      u32 nUnderlineStart; //start of underline
 *      u32 nUnderlineEnd; //end of underline
 *      u32 nCursorPos; //Cursor position
 *      MAE_WChar *pwText; //text in model
 *    }TextInfo; 
 * </PRE>
 * @retval None
 * 
 * @note
 *           pTextInfo is the pointer of the textInfo data structure, user should prepare usable memory for textInfo before calling the ITEXTMODEL_GetTextInfo.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ITEXTMODEL_GetTextInfo(pITextModel,pTextInfo) GET_FUNCTBL((pITextModel),ITextModel)->GetTextInfo(pITextModel,pTextInfo)  
#else
__INLINE void ITEXTMODEL_GetTextInfo( ITextModel *pITextModel, TextInfo *pTextInfo )
{
    GET_FUNCTBL( ( pITextModel ) , ITextModel )->GetTextInfo( pITextModel , pTextInfo );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/*=============================================================*/
// functions
/*=============================================================*/


#endif //__MMI_MAE_TEXTMODEL_H__
/*=============================================================*/
// end of file
