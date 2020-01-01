#ifndef __MMI_COMMON_THEME_COLOR_RS__
#define __MMI_COMMON_THEME_COLOR_RS__

#define RS_THEME_COLOR 0

#endif /*__MMI_COMMON_THEME_COLOR_RS__*/

//// mapping to ThemeColor[THEME_COLOR_NUMBER] in mmi_common_thm_color.h
ApBegin(RS,CLSID_RSTHEMES)
    WndBegin(RS_THEME_COLOR)
        RSCustomize(u32, ThemeColor[THEME_COLOR_NUMBER], { 
        												DEF_THM_COMMON_DEFAULT_BG,	       											
														DEF_THM_COMMON_COLOR_LIST_TITLE_TEXT,
														DEF_THM_COMMON_COLOR_LIST_TITLE_TEXT_OUTLINE,
														DEF_THM_COMMON_COLOR_LIST_TITLE_NUMBER_TEXT,
														DEF_THM_COMMON_COLOR_SOFTKEY_TEXT,
														DEF_THM_COMMON_COLOR_SOFTKEY_OUTLINE,
														DEF_THM_COMMON_COLOR_TAB_TEXT,
														DEF_THM_COMMON_COLOR_TAB_HIGHLIGHT_TEXT,
														DEF_THM_COMMON_COLOR_LIST_TEXT,
														DEF_THM_COMMON_COLOR_LIST_HIGHLIGHT_TEXT,    
														DEF_THM_COMMON_COLOR_LIST_INFO_TEXT,
														DEF_THM_INPUT_COLOR_BORDER,
														DEF_THM_INPUT_COLOR_ACTIVE_BG,
														DEF_THM_INPUT_COLOR_ACTIVE_TEXT,
														DEF_THM_INPUT_COLOR_HIGHLIGHT_BG,
														DEF_THM_INPUT_COLOR_HIGHLIGHT_TEXT,
														DEF_THM_INPUT_COLOR_CURSOR,
														DEF_THM_NOTICE_COLOR_TEXT,
														DEF_THM_DISABLE_COLOR_TEXT,
														DEF_THM_IDLE_COLOR_OPERATOR_NAME_TEXT,		
														DEF_THM_IDLE_COLOR_OPERATOR_NAME_TEXT_OUTLINE,
														DEF_THM_IDLE_COLOR_DATE_TEXT,
														DEF_THM_IDLE_COLOR_DATE_TEXT_OUTLINE,
														DEF_THM_IDLE_COLOR_TIME1_TEXT,
														DEF_THM_IDLE_COLOR_TIME1_TEXT_OUTLINE,
														DEF_THM_IDLE_COLOR_TIME2_TEXT,
														DEF_THM_IDLE_COLOR_TIME2_TEXT_OUTLINE,
														DEF_THM_BJX_FOCUS_COLOR_BG,
														DEF_THM_BJX_COLOR_BG,
														DEF_THM_COMMON_COLOR_OUTLINE1,				
														DEF_THM_COMMON_COLOR_OUTLINE2,
														                                                        
														                                                        
														DEF_THM_COMMON_COLOR_LIST_TITLE_BG,
														DEF_THM_COMMON_COLOR_LIST_INFO_BG,
														DEF_THM_COMMON_COLOR_SYSTEM_BG,
														DEF_THM_COMMON_COLOR_LIST_SEL_1,
														DEF_THM_COMMON_COLOR_LIST_SEL_2,
														DEF_THM_COMMON_COLOR_OPTION_BG_5,
														DEF_THM_COMMON_COLOR_OPTION_BG_3,
														DEF_THM_NOTICE_COLOR_BG,
														DEF_THM_NOTICE_COLOR_PROGRESS_BG,			
														DEF_THM_NOTICE_COLOR_PROGRESS,
													
													
													
														//BUTTON WIDGET
														DEF_THM_WDG_BUTTON_PRESS_TEXT,
														DEF_THM_WDG_BUTTON_PRESS_OUTLINE_TEXT,
														DEF_THM_WDG_BUTTON_UNPRESS_TEXT,
														DEF_THM_WDG_BUTTON_UNPRESS_OUTLINE_TEXT,
													
														//TEXT WIDGET
														DEF_THM_WDG_TEXT_TEXT,
														DEF_THM_WDG_TEXT_OUTLINE_TEXT,
														DEF_THM_WDG_TEXT_HIGHLIGHT_TEXT,
														DEF_THM_WDG_TEXT_HIGHLIGHT_OUTLINE_TEXT,
														DEF_THM_WDG_TEXT_HIGHLIGHT_BG,				
														DEF_THM_WDG_TEXT_FCS_ITEM_BG,
													
														//INPUT CANDIDATE WIDGET
														DEF_THM_WDG_INPUTCANDIDATE_SPELLING_FONT,
														DEF_THM_WDG_INPUTCANDIDATE_SPELLING_HIGHLIGHT,
														DEF_THM_WDG_INPUTCANDIDATE_SPELLING_FOCUSED_BG,
														DEF_THM_WDG_INPUTCANDIDATE_SPELLING_NOT_FOCUSED_BG,
														DEF_THM_WDG_INPUTCANDIDATE_CANDIDATE_FONT,
														DEF_THM_WDG_INPUTCANDIDATE_CANDIDATE_HIGHLIGHT,

														DEF_THM_WDG_INPUTCANDIDATE_COMPONENT_FONT,
														DEF_THM_WDG_INPUTCANDIDATE_COMPONENT_HIGHLIGHT,
														DEF_THM_WDG_INPUTCANDIDATE_COMPONENT_FOCUSED_BG,	

														DEF_THM_WDG_INPUTCANDIDATE_HANDWRITING_CANDIDATE_FONT,
														DEF_THM_WDG_INPUTCANDIDATE_SELECTNO,
													
														//INPUT WIDGET																											
														DEF_THM_WDG_INPUT_TEXT,
														DEF_THM_WDG_INPUT_BG,
														DEF_THM_WDG_INPUT_HIGHLIGHT_TEXT,
														DEF_THM_WDG_INPUT_HIGHLIGHT_BG,
														DEF_THM_WDG_INPUT_UNDERLINE,
														DEF_THM_WDG_INPUT_CURSOR,
														DEF_THM_WDG_INPUT_BORDER,
														DEF_THM_WDG_INPUT_INACTIVE_TEXT,			
														DEF_THM_WDG_INPUT_MSGEDITOR_UNDERLINE,
														DEF_THM_WDG_INPUT_DROP_DOWN_LIST_BORDER,														
													
														//PROGRESS WIDGET
														DEF_THM_WDG_PROGRESS_FG_BORDER,
														DEF_THM_WDG_PROGRESS_FG_FILL,
														DEF_THM_WDG_PROGRESS_BG_BORDER,
														DEF_THM_WDG_PROGRESS_BG_FILL,
													
														//MENU WIDGET
														DEF_THM_WDG_MENU_EMPTY_TEXT,
														DEF_THM_WDG_MENU_ITEM_TEXT,						
														DEF_THM_WDG_MENU_HIGHLIGHT_ITEM_TEXT,
														DEF_THM_WDG_MENU_BORDER,					
													
														//SOFTKEY WIDGET
														DEF_THM_WDG_SOFTKEY_OUTLINE_TEXT,
													
														//TITLE WIDGET
														DEF_THM_WDG_TITLE_BG,

														
														//TAB WIDGET
														DEF_THM_COMMON_COLOR_TAB_BG,
														DEF_THM_COMMON_COLOR_TAB_INACT,
														DEF_THM_COMMON_COLOR_TAB_ACT,
													
														//MAIN MENU APP
														DEF_THM_MAINMENUAPP_TEXT,													
														DEF_THM_MAINMENUAPP_TEXT_OUTLINE,
													
														//DIALER APP
														DEF_THM_DIALERAPP_BG,	
														DEF_THM_DIALERAPP_TEXT,		
														
														//PULL DOWN WIDGET
														DEF_THM_WDG_PULLDOWN_TEXT,					
														DEF_THM_WDG_PULLDOWN_UNFOCUS_BG,
														DEF_THM_WDG_PULLDOWN_HIGHLIGHT_TEXT,
														DEF_THM_WDG_PULLDOWN_FOCUS_BG,	
														DEF_THM_WDG_PULLDOWN_DROPLIST_BORDER,
														
														//MFL WIDGET
														DEF_THM_WDG_MFL_BORDER_COLOR,
														
														//LINE2INFOPICK WIDGET
														DEF_THM_WDG_L2INFOPICK_BG,
														DEF_THM_WDG_L2INFOPICK_HIGHLIGHT_BG,

														//SKB WIDGET,
														DEF_THM_WDG_SKB_HIGHTLIGHT_TEXT,
														DEF_THM_WDG_SKB_UNPRESSED_TEXT,
														DEF_THM_WDG_SKB_PRESSED_TEXT,				
														DEF_THM_WDG_SKB_INVALID_KRY_TEXT,

														//DATE ICON
														DEF_THM_WDG_DATEICON_MONTH_TEXT, 	
														DEF_THM_WDG_DATEICON_MONTH_OUTLINE,
														DEF_THM_WDG_DATEICON_DAY_TEXT,		
														DEF_THM_WDG_DATEICON_DAY_OUTLINE,	
														DEF_THM_WDG_DATEICON_TIME_TEXT,		
														DEF_THM_WDG_DATEICON_TIME_OUTLINE,

														//HAND WRITING 
														DEF_THM_WDG_HANDWRITING_DRAW_COLOR,
														
														//BMI APP
														DEF_THM_BMIAPP_VALUE_BG,
														
														//CALENDAR APP
														DEF_THM_CALENDARAPP_WEEKDAY_TEXT,			
														DEF_THM_CALENDARAPP_DAY_HIGHLIGHT_TEXT,
														
														//BT APP
														DEF_THM_BTAPP_DOWNITEM_HIGHLIGHT_TEXT,
														
														//MESSAGE EDITOR APP_MMS
														DEF_THM_MSGEDITORAPP_MMS_ADDTEXT_BG,
														DEF_THM_MSGEDITORAPP_MMS_NO_CONTENT_TEXT

        						} )               						
    WndEnd(RS_THEME_COLOR)    
ApEnd(RS,CLSID_RSTHEMES)

