/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_macro.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "MenuCommon.h"
#if (VIRTUAL_KEY_BOARD)
#include "MenuTouchButton.h"
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/ 

PSMENUSTRUCT pCurrentMenu = NULL;

#if (VIRTUAL_KEY_BOARD)
#define KEYBOARD_BUFFER_LENGTH  (128)
#define KEYBOARD_TYPE           (4)

SKEY m_sKey[] = {{'Q', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                 {'W', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                 {'E', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'R', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'T', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'Y', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'U', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'I', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'O', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'P', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 /************************/
                 {'A', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'S', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'D', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'F', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'G', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'H', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'J', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'K', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'L', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 /************************/
                 {KEYBOARD_KEY_CTR, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'Z', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'X', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'C', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'V', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'B', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'N', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {'M', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {KEYBOARD_KEY_DEL, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                 /************************/
                 {KEYBOARD_KEY_CHG, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {' ', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                 {KEYBOARD_KEY_ENT, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}
                 };
                             
SKEY m_sKey_Ctr[] = {{'q', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                     {'w', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                     {'e', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'r', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'t', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'y', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'u', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'i', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'o', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'p', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     /************************/
                     {'a', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'s', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'d', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'f', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'g', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'h', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'j', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'k', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'l', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     /************************/
                     {KEYBOARD_KEY_CTR, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'z', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'x', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'c', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'v', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'b', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'n', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {'m', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {KEYBOARD_KEY_DEL, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                     /************************/
                     {KEYBOARD_KEY_CHG, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {' ', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                     {KEYBOARD_KEY_ENT, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}
                     }; 
         
SKEY m_sKey2[] = {  {'1', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                    {'2', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                    {'3', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'4', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'5', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'6', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'7', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'8', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'9', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'0', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    /************************/
                    {'-', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'/', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {':', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {';', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'(', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {')', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'$', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'&', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'@', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'"', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    /************************/
                    {KEYBOARD_KEY_CTR, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'.', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {',', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'?', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'!', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {'\'', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {KEYBOARD_KEY_DEL, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                    /************************/
                    {KEYBOARD_KEY_CHG, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {' ', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                    {KEYBOARD_KEY_ENT, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}};


SKEY m_sKey2_Ctr[] = {  {'[', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                        {']', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                        {'{', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'}', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'#', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'%', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'^', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'*', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'+', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'=', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        /************************/
                        {'_', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'\\', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'|', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'~', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'<', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'>', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'$', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'&', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'@', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'"', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        /************************/
                        {KEYBOARD_KEY_CTR, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'.', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {',', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'?', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'!', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {'\'', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {KEYBOARD_KEY_DEL, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}, 
                        /************************/
                        {KEYBOARD_KEY_CHG, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {' ', {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
                        {KEYBOARD_KEY_ENT, {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0}};
                    
SKEYBOARD m_sKeyBoard[] = {  {60, 10, 28, 40, 2, 2, 10, &m_sKeyBoard[1]},
                             {102, 30, 28, 40, 2, 2, 9, &m_sKeyBoard[2]},
                             {144, 10, 28, 40, 2, 2, 9, &m_sKeyBoard[3]},
                             {186, 10, 28, 40, 2, 2, 3, NULL}
                             };
                             
SKEYBOARD m_sKeyBoard2[] = { {60, 10, 28, 40, 2, 2, 10, &m_sKeyBoard2[1]},
                             {102, 10, 28, 40, 2, 2, 10, &m_sKeyBoard2[2]},
                             {144, 10, 35, 40, 4, 2, 7, &m_sKeyBoard2[3]}, 
                             {186, 10, 28, 40, 2, 2, 6, NULL}
                             };


UINT32 m_sKeySpaceIndex = 0;
SKEYSPACE m_sKeySpace[KEYBOARD_TYPE];

UINT32 m_KeyBoardBufferIndex = 0;
INT8 m_KeyBoardBuffer[KEYBOARD_BUFFER_LENGTH] = "Text Me";

#endif

/*===========================================================================
 * Function body
 *===========================================================================*/ 

PSMENUSTRUCT GetCurrentMenu(void)
{
    return pCurrentMenu;
}

void SetCurrentMenu(PSMENUSTRUCT pMenu)
{
    AHC_DBG_MSG(1, FG_YELLOW("# Menu ID[%d] Name[%s]\r\n"), pMenu->iMenuId, (char*)OSD_GetEnglishStringViaID(pMenu->uiStringId));
    pCurrentMenu = pMenu;
}

void ResetCurrentMenu(void)
{
    pCurrentMenu = NULL;
}

int RemoveMenuItem(SMENUSTRUCT *plist, SMENUITEM *pItem)
{
    int		i, j;
    int		ri;
    
    ri = -1;
    
    for (i = 0, j = 0; i < plist->iNumOfItems; i++) 
    {
        if (plist->pItemsList[i] != pItem) {
            plist->pItemsList[j++] = plist->pItemsList[i];
        } else {
            ri = i;
        }
    }
    
    plist->iNumOfItems = j;
    return ri;
}

AHC_BOOL IsCurrentTopMenu(PSMENUSTRUCT pMenu)
{
    INT32	CurMenuId;

    CurMenuId = pMenu->iMenuId;
    
    if( CurMenuId == MENUID_TOP_MENU )
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL IsCurrentUSBMenu(PSMENUSTRUCT pMenu)
{
    INT32	CurMenuId;

    CurMenuId = pMenu->iMenuId;
    
    if( CurMenuId == MENUID_USB_MODE_SELECT )
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL IsCurrentMainMenu(PSMENUSTRUCT pMenu)
{
    INT32	CurMenuId;

    CurMenuId = pMenu->iMenuId;
    
    if( CurMenuId == MENUID_MAIN_MENU_MANUAL 	||
        CurMenuId == MENUID_MAIN_MENU_VIDEO 	||
        CurMenuId == MENUID_MAIN_MENU_STILL 	||
        CurMenuId == MENUID_MAIN_MENU_PLAYBACK 	||
        CurMenuId == MENUID_MAIN_MENU_EDIT 		||
        CurMenuId == MENUID_MAIN_MENU_MEDIA 	||
        CurMenuId == MENUID_MAIN_MENU_GENERAL 	||
        CurMenuId == MENUID_MAIN_LANGUAGE_SET	||
        CurMenuId == MENUID_MAIN_MENU_EXIT )
        
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL IsCurMultiLayerMenu(PSMENUSTRUCT pMenu)
{
    INT32	CurMenuId;

    CurMenuId = pMenu->iMenuId;
    
    if(	CurMenuId == MENUID_SUB_MENU_DELETE_ALL				||
        CurMenuId == MENUID_SUB_MENU_DELETE_ALL_VIDEO  		||
        CurMenuId == MENUID_SUB_MENU_DELETE_ALL_IMAGE  		||
        CurMenuId == MENUID_SUB_MENU_PROTECT_ALL	 		||
        CurMenuId == MENUID_SUB_MENU_PROTECT_ALL_VIDEO 		||
        CurMenuId == MENUID_SUB_MENU_PROTECT_ALL_IMAGE 		||
        CurMenuId == MENUID_SUB_MENU_UNPROTECT_ALL			||
        CurMenuId == MENUID_SUB_MENU_UNPROTECT_ALL_VIDEO	||
        CurMenuId == MENUID_SUB_MENU_UNPROTECT_ALL_IMAGE )
        
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL IsTopSubMenuLinked(PSMENUSTRUCT pMenu)
{
#if (TOP_MENU_PAGE_EN)

    PSMENUSTRUCT	pParentMenu = pMenu->pParentMenu;

    if(IsCurrentMainMenu(pMenu))
        return AHC_FALSE;

    if( pParentMenu != NULL &&
        pParentMenu->iMenuId == MENUID_TOP_MENU)
        return AHC_TRUE;
    else
        return AHC_FALSE;
#else
    return AHC_FALSE;
#endif		
}

int OffsetItemNumber_Menu(int iCur, int iMin, int iMax, int iOffset, AHC_BOOL bWrap )
{
    int      iRange, iResult,iMul;
    AHC_BOOL bSign;

    iRange  = iMax - iMin + 1;
    iCur    = FIT_IN_RANGE(iCur, iMin, iMax) - iMin;

    // Offset is positive or negative
    bSign = ( iOffset < 0 )? (AHC_TRUE):(AHC_FALSE);

    if( bWrap )
    {
        // Align up
        iMul = (bSign)?(-iOffset):(iOffset);
        iMul = ALIGN_UP( iMul, iRange );

        // Calculate the position
        if((iOffset > 0) && (( iCur >= ((iRange - 1)/iOffset)*iOffset) && ( iCur <= ((iRange - 1)/iOffset)*iOffset + 2 )))
        {
            iCur = 0;
        }
        else if((iCur + iOffset ) < 0)
        {
            iCur = (iRange - 1)/iOffset*iOffset;
        }
        else
        {
            iCur = (( iCur + iOffset)/iOffset)*iOffset;
        }
        iResult = iCur + iMin;
    }
    else
    {
        // Non Wrap
        iResult = FIT_IN_RANGE( iCur+iMin+iOffset, iMin, iMax );
    }

    return iResult;
}

int OffsetItemNumber(int iCur, int iMin, int iMax, int iOffset, AHC_BOOL bWrap )
{
    int      iRange, iResult,iMul;
    AHC_BOOL bSign;

    iRange  = iMax - iMin + 1;
    iCur    = FIT_IN_RANGE(iCur, iMin, iMax) - iMin;

    // Offset is positive or negative
    bSign = ( iOffset < 0 )? (AHC_TRUE):(AHC_FALSE);

    if( bWrap )
    {
        // Align up
        iMul = (bSign)?(-iOffset):(iOffset);
        iMul = ALIGN_UP( iMul, iRange );
      
        // Calculate the position
        iCur = (iCur+iMul+iOffset) % iRange;
        
        iResult = iCur + iMin;
    }
    else
    {
        // Non Wrap
        iResult = FIT_IN_RANGE( iCur+iMin+iOffset, iMin, iMax );
    }
    
    return iResult;
}

#if (VIRTUAL_KEY_BOARD)
void KEYBOARD_INIT(void)
{
    UINT32 i, uiMaxLength;

    KEYBOARD_ResetWord();
    
    m_sKeySpaceIndex = 0;

    //**************************************************************
    // Index 0
    m_sKeySpace[0].sKeyBoard = m_sKeyBoard;
    m_sKeySpace[0].sKey = NULL;
    m_sKeySpace[0].psNextSpace = NULL;
    m_sKeySpace[0].psPrevSpace = NULL;
    
    uiMaxLength = sizeof(m_sKey)/sizeof(SKEY);
    
    for(i = 0; i < uiMaxLength; i++)
    {
        KEYBOARD_AddKey(&(m_sKeySpace[0].sKey), &m_sKey[i]);
    }
    
    KEYBOARD_AdjustPosition(m_sKeySpace[0].sKeyBoard, m_sKeySpace[0].sKey);

    //**************************************************************
    // Index 1
    m_sKeySpace[1].sKeyBoard = m_sKeyBoard;
    m_sKeySpace[1].sKey = NULL;
    m_sKeySpace[1].psNextSpace = NULL;
    m_sKeySpace[1].psPrevSpace = NULL;
    
    uiMaxLength = sizeof(m_sKey_Ctr)/sizeof(SKEY);
    
    for(i = 0; i < uiMaxLength; i++){
        KEYBOARD_AddKey(&(m_sKeySpace[1].sKey), &m_sKey_Ctr[i]);
    }

    KEYBOARD_AdjustPosition(m_sKeySpace[1].sKeyBoard, m_sKeySpace[1].sKey);

    //**************************************************************
    // Index 2
    m_sKeySpace[2].sKeyBoard = m_sKeyBoard2;
    m_sKeySpace[2].sKey = NULL;
    m_sKeySpace[2].psPrevSpace = NULL;
    m_sKeySpace[2].psNextSpace = NULL;

    uiMaxLength = sizeof(m_sKey2)/sizeof(SKEY);
    
    for(i = 0; i < uiMaxLength; i++){
        KEYBOARD_AddKey(&(m_sKeySpace[2].sKey), &m_sKey2[i]);
    }

    KEYBOARD_AdjustPosition(m_sKeySpace[2].sKeyBoard, m_sKeySpace[2].sKey);
    //**************************************************************
    // Index 3
    m_sKeySpace[3].sKeyBoard = m_sKeyBoard2;
    m_sKeySpace[3].sKey = NULL;
    m_sKeySpace[3].psPrevSpace = NULL;
    m_sKeySpace[3].psNextSpace = NULL;

    uiMaxLength = sizeof(m_sKey2_Ctr)/sizeof(SKEY);
    
    for(i = 0; i < uiMaxLength; i++){
        KEYBOARD_AddKey(&(m_sKeySpace[3].sKey), &m_sKey2_Ctr[i]);
    }

    KEYBOARD_AdjustPosition(m_sKeySpace[3].sKeyBoard, m_sKeySpace[3].sKey);
}


AHC_BOOL KEYBOARD_AddKey(PSKEY* psKeyHead, PSKEY psKey)
{
    if(*psKeyHead == NULL){

        *psKeyHead = psKey;
        psKey->psPrevKey = NULL;
        psKey->psNextKey = NULL;
        
    }else{
        AHC_BOOL bFind = AHC_FALSE;
        PSKEY psTempKey = *psKeyHead;
        
        while( psTempKey != NULL){
            if(psTempKey->psNextKey == NULL){
                bFind = AHC_TRUE;
                break;
            }
            psTempKey = psTempKey->psNextKey;
        }
        
        if(bFind == AHC_TRUE){
            psTempKey->psNextKey = psKey;
            psKey->psPrevKey = psTempKey;
            psKey->psNextKey = NULL;

        }else{
            return AHC_FALSE;
        }
    
    }

    return AHC_TRUE;
}

PSKEY KEYBOARD_GetKeyHead(void)
{
    return m_sKeySpace[m_sKeySpaceIndex].sKey;
}

AHC_BOOL KEYBOARD_DelKey(PSKEY pKey)
{
    return AHC_TRUE;
}

AHC_BOOL KEYBOARD_AdjustPosition(PSKEYBOARD psKeySpace, PSKEY psKey)
{
    UINT32 uiTop;
    UINT32 uiLeft;
    UINT32 uiWidth;
    UINT32 uiHeight;
    PSKEYBOARD psTempSpace = NULL;
    PSKEY psTempKey   = NULL;
    
    psTempSpace = psKeySpace;
    psTempKey = psKey;
    
    while(psTempSpace != NULL){
        
        UINT32 uiKey = psTempSpace->uiKeyNumber;

        uiTop    = psTempSpace->uiTop;
        uiLeft   = psTempSpace->uiLeft;
        uiHeight = psTempSpace->uiKeyHeight;
        
        while(uiKey != 0){

            if(psTempKey == NULL)
                break;
            
            #if 0    
            printc("%x \n", psTempKey->uiASCIICode);
            printc("%x \n", 'CTR');
            printc("%x \n", 'DEL');
            printc("%x \n", 'CHG');
            printc("%x \n", 'ENT');
            printc("%x \n", ' ');
            #endif
            
            switch(psTempKey->uiASCIICode){
            
            
            case KEYBOARD_KEY_CTR:
                #if 0
                printc("CTR \n");
                #endif
                uiWidth  = 30;
                break;
            case KEYBOARD_KEY_DEL:
                #if 0
                printc("DEL \n");
                #endif
                uiWidth  = 60;
                break;
            case KEYBOARD_KEY_CHG:
                #if 0
                printc("CHG \n");
                #endif
                uiWidth  = 50;
                break;
            case KEYBOARD_KEY_ENT:
                #if 0
                printc("ENT \n");
                #endif
                uiWidth  = 70;
                break;
            case ' ':
                #if 0
                printc("SPACE \n");
                #endif
                uiWidth  = 180;
                break;
            default:
                #if 0
                printc("Default \n");
                #endif
                uiWidth  = psTempSpace->uiKeyWidth;
                break;
            }
            
            // UI    
            psTempKey->rcUIRegion.uiTop    = uiTop;
            psTempKey->rcUIRegion.uiLeft   = uiLeft;
            psTempKey->rcUIRegion.uiWidth  = uiWidth;
            psTempKey->rcUIRegion.uiHeight = uiHeight;
            // Touch
            psTempKey->rcTouchRegion.uiTop    = uiTop;
            psTempKey->rcTouchRegion.uiLeft   = uiLeft;
            psTempKey->rcTouchRegion.uiWidth  = uiWidth;
            psTempKey->rcTouchRegion.uiHeight = uiHeight;

            //offset
            uiLeft += (uiWidth + psTempSpace->uiHorizontalGap);

            psTempKey = psTempKey->psNextKey;
            uiKey--;
        }
        
        psTempSpace = psTempSpace->psNextRow;
    }
    
    
    
    return AHC_TRUE;
}


AHC_BOOL KEYBOARD_CheckTouchButton(PSKEY* psKey, PPOINT pPoint)
{
    POINT   pt = *pPoint;
    PSKEY psTempKey = NULL;
    
    psTempKey = *psKey;
    
    while(psTempKey != NULL)
    {
        if( IS_POINT_IN_RECT( pt, psTempKey->rcTouchRegion ) )
        {
            *psKey = psTempKey;
            {
            INT8 ch[2];
            
            memset(ch, 0, 2);
            
            ch[0] = (*psKey)->uiASCIICode;
            //printc("KEY : %s , %d \n", &ch, (*psKey)->uiASCIICode);
            
            }
            return AHC_TRUE;
        }
        
        psTempKey = psTempKey->psNextKey;
    }
    
    
    /**	@brief	can not get one touch button. */
    
    return AHC_FALSE;
}

UINT32 KEYBOARD_EventHandler(PSKEY psKey)
{
    UINT32 uiEvent = KEYBOARD_EVENT_NONE;
    
    switch(psKey->uiASCIICode){
    
    
    case KEYBOARD_KEY_CTR:
        #if 1
        printc("CTR \n");
        #endif
        if(m_sKeySpaceIndex == 0){
            m_sKeySpaceIndex = 1;
        }else if(m_sKeySpaceIndex == 1){
            m_sKeySpaceIndex = 0;
        }else if(m_sKeySpaceIndex == 2){
            m_sKeySpaceIndex = 3;
        }else if(m_sKeySpaceIndex == 3){
            m_sKeySpaceIndex = 2;
        }
        uiEvent = KEYBOARD_EVENT_CTR;
        break;
    case KEYBOARD_KEY_DEL:
        #if 1
        printc("DEL \n");
        #endif
        KEYBOARD_DelWord(1);
        break;
    case KEYBOARD_KEY_CHG:
        #if 1
        printc("CHG \n");
        #endif
        if((m_sKeySpaceIndex == 2)||(m_sKeySpaceIndex == 3)){
            m_sKeySpaceIndex = 0;
        }else if((m_sKeySpaceIndex == 0)||(m_sKeySpaceIndex == 1)){
            m_sKeySpaceIndex = 2;
        }
        uiEvent = KEYBOARD_EVENT_CHG;
        break;
    case KEYBOARD_KEY_ENT:
        #if 1
        printc("ENT \n");
        #endif
        uiEvent = KEYBOARD_EVENT_ENTER;
        break;
    case ' ':
    default:
        #if 1
        printc("Default \n");
        #endif
        {
        INT8 TempStr[4];
        
        memset(TempStr, 0, 4);
        
        TempStr[0] = psKey->uiASCIICode;
        
        printc("press char %s\n", TempStr);
        KEYBOARD_IpnputWord((INT8*)TempStr, 1);
        }

        break;
    }
    
    return uiEvent;
}

void KEYBOARD_ResetWord(void)
{
    m_KeyBoardBufferIndex = 0;
    memset(m_KeyBoardBuffer, 0, KEYBOARD_BUFFER_LENGTH);

}

AHC_BOOL KEYBOARD_IpnputWord(INT8* pchWord, UINT32 uiWordLength)
{
    UINT32 uiTotalLength;
    
    uiTotalLength = m_KeyBoardBufferIndex + uiWordLength;
    
    if(uiTotalLength >= (KEYBOARD_BUFFER_LENGTH - 1)){
        return AHC_FALSE;
    }else{
        memcpy(&m_KeyBoardBuffer[m_KeyBoardBufferIndex], pchWord, uiWordLength);
        m_KeyBoardBufferIndex += uiWordLength;
    }
    
    return AHC_TRUE;
}

INT8* KEYBOARD_GetWord(void)
{
    return m_KeyBoardBuffer;
}

UINT32 KEYBOARD_GetWordLength(void)
{
    return m_KeyBoardBufferIndex;
}

AHC_BOOL KEYBOARD_DelWord(UINT32 uiWordLength)
{
   
    if(m_KeyBoardBufferIndex < uiWordLength){
        return AHC_FALSE;
    }else{
        memset(&m_KeyBoardBuffer[m_KeyBoardBufferIndex - uiWordLength], 0, uiWordLength);
        m_KeyBoardBufferIndex -= uiWordLength;
    }

    return AHC_TRUE;
}

#if VIRTUAL_KEY_BOARD_FOR_CAR_ID
extern char Driverid[10];

void KEYBOARD_CarNo(void)
{
    if(sizeof(Driverid) > KEYBOARD_GetWordLength())
        memcpy(Driverid, KEYBOARD_GetWord(), KEYBOARD_GetWordLength());
    else
        memcpy(Driverid, KEYBOARD_GetWord(), strlen(Driverid) - 1);
    
    Driverid[strlen(Driverid) - 1] = 0;	
}
#endif

#if VIRTUAL_KEY_BOARD_FOR_WIFI
#include "inc/amn_sysobjs.h"
unsigned char ucWifiAPParamModified = 0;
unsigned char ucWifiSTAParamModified = 0;
unsigned char ucwifiStassid[6][64] = {0};
unsigned char ucwifiStapswd[6][64] = {0};

#if MENU_WIFI_AP_SSID_EN
void KEYBOARD_WifiAPSSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;
    
    cfg = amn_config_get(0, "Net.WIFI_AP.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    
    err = amn_config_set(0/*CONFIG_SPACE_TYPE_CURRENT*/, "Net.WIFI_AP.SSID", KEYBOARD_GetWord());
    
    cfg = amn_config_get(0, "Net.WIFI_AP.SSID");
    
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiAPParamModified = 1;
    }	
    else
    {
        ucWifiAPParamModified = 0;
    }	
}
#endif

#if MENU_WIFI_AP_PSWD_EN
//Warning: passphrase must be between 8 and 64 characters
// 1.show warning or 2.Auto Increment to 8 bit; 
void KEYBOARD_WifiAPPSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;
    
    cfg = amn_config_get(0, "Net.WIFI_AP.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    
    err = amn_config_set(0/*CONFIG_SPACE_TYPE_CURRENT*/, "Net.WIFI_AP.CryptoKey", KEYBOARD_GetWord());
    
    cfg = amn_config_get(0, "Net.WIFI_AP.CryptoKey");

    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiAPParamModified = 1;
    }	
    else
    {
        ucWifiAPParamModified = 0;
    }
}	
#endif

#if MENU_WIFI_STATION2_SSID_EN
void KEYBOARD_WifiSTA2SSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.2.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.2.SSID", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.2.SSID");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 2;
        //MEMSET0(ucwifiStassid[ucWifiSTAParamModified]);
        STRCPY(ucwifiStassid[ucWifiSTAParamModified], cfg->v.strVal);
        printc("wifi sta pswd 2 %s\n", ucwifiStassid[ucWifiSTAParamModified]);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION2_PSWD_EN
void KEYBOARD_WifiSTA2PSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.2.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.2.CryptoKey", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.2.CryptoKey");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 2;
        //MEMSET0(ucwifiStapswd[ucWifiSTAParamModified]);
        STRCPY(ucwifiStapswd[ucWifiSTAParamModified], cfg->v.strVal);
        printc("wifi sta pswd 2 %s\n", ucwifiStapswd[ucWifiSTAParamModified]);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION3_SSID_EN
void KEYBOARD_WifiSTA3SSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.3.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.3.SSID", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.3.SSID");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 3;
        //MEMSET0(ucwifiStassid[ucWifiSTAParamModified]);
        STRCPY(ucwifiStassid[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION3_PSWD_EN
void KEYBOARD_WifiSTA3PSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.3.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.3.CryptoKey", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.3.CryptoKey");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 3;
        //MEMSET0(ucwifiStapswd[ucWifiSTAParamModified]);
        STRCPY(ucwifiStapswd[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION4_SSID_EN
void KEYBOARD_WifiSTA4SSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.4.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.4.SSID", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.4.SSID");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 4;
        //MEMSET0(ucwifiStassid[ucWifiSTAParamModified]);
        STRCPY(ucwifiStassid[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION4_PSWD_EN
void KEYBOARD_WifiSTA4PSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.4.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.4.CryptoKey", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.4.CryptoKey");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 4;
        //MEMSET0(ucwifiStapswd[ucWifiSTAParamModified]);
        STRCPY(ucwifiStapswd[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION5_SSID_EN
void KEYBOARD_WifiSTA5SSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.5.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.5.SSID", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.5.SSID");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 5;
        //MEMSET0(ucwifiStassid[ucWifiSTAParamModified]);
        STRCPY(ucwifiStassid[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION5_PSWD_EN
void KEYBOARD_WifiSTA5PSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.5.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.5.CryptoKey", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.5.CryptoKey");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 5;
        //MEMSET0(ucwifiStapswd[ucWifiSTAParamModified]);
        STRCPY(ucwifiStapswd[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION6_SSID_EN
void KEYBOARD_WifiSTA6SSID(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.6.SSID");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.6.SSID", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.6.SSID");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 6;
        //MEMSET0(ucwifiStassid[ucWifiSTAParamModified]);
        STRCPY(ucwifiStassid[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif

#if MENU_WIFI_STATION6_PSWD_EN
void KEYBOARD_WifiSTA6PSWD(void)
{
    int err = 100;
    char WifiApSsid[32];
    struct amn_cfgspace_value_t		*cfg;

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.6.CryptoKey");
    memcpy(WifiApSsid, cfg->v.strVal, strlen(cfg->v.strVal));
    err = amn_config_set(0, "Net.WIFI_STA.AP.6.CryptoKey", KEYBOARD_GetWord());

    cfg = amn_config_get(0, "Net.WIFI_STA.AP.6.CryptoKey");
    if(strcmp((char *)WifiApSsid, cfg->v.strVal))
    {
        ucWifiSTAParamModified = 6;
        //MEMSET0(ucwifiStapswd[ucWifiSTAParamModified]);
        STRCPY(ucwifiStapswd[ucWifiSTAParamModified], cfg->v.strVal);
    }
    else
    {
        ucWifiSTAParamModified = 0;
    }
}
#endif
#endif

#if VIRTUAL_KEY_BOARD_BY_KEY
unsigned char KEYBOARD_GetKeyMount(void)
{
    unsigned char i = 0; 

    PSKEY psKey = (PSKEY)KEYBOARD_GetKeyHead();
    
    while(psKey != NULL)
    {
        i++;
        psKey = psKey->psNextKey;
    }

    return i;	
}
#endif

#endif


