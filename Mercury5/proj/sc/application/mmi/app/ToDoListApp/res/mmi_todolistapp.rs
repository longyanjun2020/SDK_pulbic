ApBegin(RS,CLSID_TODOLISTAPP)

    WndBegin(TODOLIST_WND_TODOLIST)
        WdgBegin(CLSID_VTMMENU,ToDoListVtmMenu)
            VtmCreateMenuRC({IMG_NULL_ID, TXT_LTL_N_TODO_LIST, WDG_MENU_TYPE_NORMAL, WDG_MENU_ITEM_TYPE_IMAGETEXT_IMAGE, WDG_MENU_CHECK_STYLE_NONE, 0, 0, 0})
       WdgEnd(CLSID_VTMMENU,ToDoListVtmMenu)
    WndEnd(TODOLIST_WND_TODOLIST)

    WndBegin(TODOLIST_WND_TODOLISTOPTION)
        WdgBegin(CLSID_VTMOPTIONMENU,ToDoListOptionVtm)
            VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,7})
                        VtmCreateOptionMenuDataRC(7,{
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_VIEW}		 ,TXT_OIL1_N_VIEW},
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_EDIT}		 ,TXT_OIL1_N_EDIT},
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_ADD}		 ,TXT_OIL1_N_ADD},
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_DELETE}	 ,TXT_OIL1_N_DELETE},
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_DELETEALL} ,TXT_OIL1_N_DELETE_ALL},
            										{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_SORTBY}    ,TXT_OIL1_N_TODOLISTAPP_SORT_BY},
                                                    {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_SEND}      ,TXT_OIL1_N_SEND}})
        WdgEnd(CLSID_VTMOPTIONMENU,ToDoListOptionVtm)
    WndEnd(TODOLIST_WND_TODOLISTOPTION)
    
    WndBegin(TODOLIST_WND_ADDTASK)
        WndSetAllSoftkeyRC({SK_SAVE, SK_OK, SK_CANCEL})
        WndSetTitleRC({IMG_NULL_ID,TXT_LTL_N_TODOLISTAPP_ADD_TASK})
        WdgBegin(CLSID_DOUBLE_TEXT_WIDGET,ContentDoubleTextWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},DOUBLEITEM_STYLE_DOUBLE_TEXT})
#ifdef __APP_MMI_TODOLIST_VTODO__  //vtodo flow
			WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_SUBJECT,TXT_NULL_ID})
#else
			WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_CONTENT,TXT_NULL_ID})
#endif

        WdgEnd(CLSID_DOUBLE_TEXT_WIDGET,ContentDoubleTextWidget)

        WdgBegin(CLSID_LINE2INFOPICK_TEXTWIDGET,PriorityTextPickWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},COMMONPICK_STYLE_LINE2INFOPICK_TEXTWIDGET})
            WdgCommonPickSetDataByIDRC(3, {0,{IMG_NULL_ID,TXT_LIL_N_PRIORITY}},{{IMG_NULL_ID,TXT_LTL_N_TODOLISTAPP_HIGH},{IMG_NULL_ID,TXT_LIL_N_NORMAL},{IMG_NULL_ID,TXT_LIL_N_TODOLISTAPP_LOW}})
        WdgEnd(CLSID_LINE2INFOPICK_TEXTWIDGET,PriorityTextPickWidget)
        WdgBegin(CLSID_LINE2INFOPICK_TEXTWIDGET,StatusTextPickWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},COMMONPICK_STYLE_LINE2INFOPICK_TEXTWIDGET})
            WdgCommonPickSetDataByIDRC(2, {0,{IMG_NULL_ID,TXT_LIL_N_STATUS}},{{IMG_NULL_ID,TXT_LIL_N_UNCHECKED},{IMG_NULL_ID,TXT_LIL_N_CHECKED}})
        WdgEnd(CLSID_LINE2INFOPICK_TEXTWIDGET,StatusTextPickWidget)
#ifdef  __APP_MMI_TODOLIST_VTODO__        
        WdgBegin(CLSID_DOUBLE_TEXT_WIDGET,LocationDoubleTextWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},DOUBLEITEM_STYLE_DOUBLE_TEXT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_LOCATION,TXT_NULL_ID})
        WdgEnd(CLSID_DOUBLE_TEXT_WIDGET,LocationDoubleTextWidget)
        WdgBegin(CLSID_DOUBLE_TEXT_WIDGET,DescriptionDoubleTextWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},DOUBLEITEM_STYLE_DOUBLE_TEXT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_DESCRIPTION,TXT_NULL_ID})
        WdgEnd(CLSID_DOUBLE_TEXT_WIDGET,DescriptionDoubleTextWidget)
#endif
        WdgBegin(CLSID_LINE2INFOPICK_TEXTWIDGET,ReminderTextPickWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},COMMONPICK_STYLE_LINE2INFOPICK_TEXTWIDGET})
            WdgCommonPickSetDataByIDRC(2, {0,{IMG_NULL_ID,TXT_LIL_N_REMINDER}},{{IMG_NULL_ID,TXT_LIL_N_OFF},{IMG_NULL_ID,TXT_LIL_N_ON} })
        WdgEnd(CLSID_LINE2INFOPICK_TEXTWIDGET,ReminderTextPickWidget)
        WdgBegin(CLSID_TEXT_DATE_WIDGET,DateTextDateWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},DOUBLEITEM_STYLE_TEXT_DATE})
            WdgDoubleItemTextDateSetDataByIDRC({TXT_LIL_N_DATE,{0,0,0,0,0,0,0,0}})
        WdgEnd(CLSID_TEXT_DATE_WIDGET,DateTextDateWidget)
        WdgBegin(CLSID_TEXT_TIME_WIDGET,TimeTextTimeWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{0,0},DOUBLEITEM_STYLE_TEXT_TIME})
            WdgDoubleItemTextDateSetDataByIDRC({TXT_LIL_N_TIME,{0,0,0,0,0,0,0,0}})
        WdgEnd(CLSID_TEXT_TIME_WIDGET,TimeTextTimeWidget)
    WndEnd(TODOLIST_WND_ADDTASK)

    WndBegin(TODOLIST_WND_EDITCONTENT)
    	WdgBegin(CLSID_VTMMENU,InputWdg)
#ifdef __APP_MMI_TODOLIST_VTODO__
		    VtmCreateInputRC({IMG_NULL_ID,TXT_LIL_N_SUBJECT,0,FALSE})
#else
            VtmCreateInputRC({IMG_NULL_ID,TXT_LIL_N_CONTENT,0,FALSE})
#endif
        WdgEnd(CLSID_VTMMENU,InputWdg)											
    WndEnd(TODOLIST_WND_EDITCONTENT)
    
    WndBegin( TODOLIST_WND_PICKPRIORITY)
		WdgBegin(CLSID_VTMPOPUPSELECT,PriorityMenuWdg)
            VtmCreatePopUpSelectRC({NULL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_RADIO,3,0,0})
            VtmCreatePopUpSelectDataRC(3,{
            								{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_HIGH, TXT_LTL_N_TODOLISTAPP_HIGH},
                                      		{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_NORMAL, TXT_LIL_N_NORMAL},
                                      		{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_LOW, TXT_LIL_N_TODOLISTAPP_LOW}})
        WdgEnd(CLSID_VTMPOPUPSELECT,PriorityMenuWdg)
    WndEnd( TODOLIST_WND_PICKPRIORITY)
    
    WndBegin(TODOLIST_WND_VIEWTASK)
           WdgBegin(CLSID_TEXTWIDGET,TextWdg)
            	VtmCreateInputRC({IMG_NULL_ID,TXT_LTL_N_VIEW_TASK,0,TRUE})
           WdgEnd(CLSID_TEXTWIDGET,TextWdg)        
    WndEnd(TODOLIST_WND_VIEWTASK)
    
    WndBegin(TODOLIST_WND_VIEWTASKOPTION)
			WdgBegin(CLSID_VTMOPTIONMENU,ViewOptionVtm)
            VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,3})
            VtmCreateOptionMenuDataRC(3, {
                                      {MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_TODOLIST_VIEWTASK_EDIT, TXT_LIL_N_EDIT},
                                      {MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_TODOLIST_VIEWTASK_DELETE, TXT_OIL1_N_DELETE},
                                      {MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_TODOLIST_VIEWTASK_CHECK, TXT_LIL_N_CHECKED}})
        WdgEnd(CLSID_VTMOPTIONMENU,ViewOptionVtm)
	WndEnd(TODOLIST_WND_VIEWTASKOPTION)
	
    WndBegin( TODOLIST_WND_SORTBY)
		WdgBegin(CLSID_VTMPOPUPSELECT,SortByMenuWdg)
            VtmCreatePopUpSelectRC({NULL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_RADIO,3,0,0})
            VtmCreatePopUpSelectDataRC(3,{
            								{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_STATUS, TXT_LIL_N_STATUS},
                                      		{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_PRIORITY, TXT_LIL_N_PRIORITY},
                                      		{MENUMODEL_ITEM_VISABLE, {SK_OK_TEXT,SK_OK,SK_CANCEL}, MNU_TODOLIST_DUEDATE, TXT_LTL_N_DUEDATE}})
        WdgEnd(CLSID_VTMPOPUPSELECT,SortByMenuWdg)        
    WndEnd(TODOLIST_WND_SORTBY)
    
    WndBegin(TODOLIST_WND_EDITTASK)
        WdgBegin(CLSID_VTMMENU,EditTaskVtm)
            VtmCreateMenuRC({IMG_NULL_ID,TXT_LTL_N_EDIT_TASK,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_TEXT,WDG_MENU_CHECK_STYLE_NONE,0,0,0})
        WdgEnd(CLSID_VTMMENU,EditTaskVtm)
    WndEnd(TODOLIST_WND_EDITTASK)
    
    WndBegin(TODOLIST_WND_SEND)
		WdgBegin(CLSID_VTMMENU,SendMenuWdg)
            VtmCreateMenuRC({IMG_NULL_ID,TXT_LTL_N_SEND,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,CHECK_RADIO_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(1, {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_CHECK, SK_CANCEL}, MNU_TODOLIST_SMS, TXT_LIL_N_SMS}})
        WdgEnd(CLSID_VTMMENU,SendMenuWdg)
    WndEnd(TODOLIST_WND_SEND)
    
    WndBegin(TODOLIST_WND_EDITCONTENTOPTION)
	    WdgBegin(CLSID_VTMOPTIONMENU,EditContentOptionVtm)
		    VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,2})
		    VtmCreateOptionMenuDataRC(2,{	
		    								{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_SET},TXT_OIL1_N_OK},
										    {{MENUMODEL_ITEM_VISABLE|MENUMODEL_ITEM_HAS_CHILD,{SK_SELECT,SK_OK,SK_CANCEL},MNU_TODOLIST_INPUTMENU},TXT_OIL1_N_INPUT_MENU}})
	    WdgEnd(CLSID_VTMOPTIONMENU,EditContentOptionVtm)
	WndEnd(TODOLIST_WND_EDITCONTENTOPTION)
ApEnd(RS,CLSID_TODOLISTAPP)

