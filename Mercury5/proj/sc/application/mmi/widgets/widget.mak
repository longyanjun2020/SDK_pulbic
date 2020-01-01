PATH_H = \
    $(PATH_app)/DesktopWidget/inc \
    $(PATH_app)/DesktopWidget/inc/priv \
    $(PATH_audio)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
	$(PATH_dynldr)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_gss)/pub \
    $(PATH_image_codec)/pub \
    $(PATH_mae)/pub \
    $(PATH_mae)/src \
    $(PATH_middleware)/drm_util/pub \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmicomn)/res \
    $(PATH_model)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_AppLauncher)/inc \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_mgl)/pub \
    $(PATH_widget)/inc \
    $(PATH_widget)/inc/priv \
    $(PATH_widget)/pub \
    $(PATH_widget)/res

MMI_PATH_H = 
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
	mae_view_pl.c \
	mae_viewtransition_pl.c \
	mae_abscontainerbase.c \
	mae_containerbase.c \
	mae_animation.c\
	mae_animation_math.c\
	mae_controllerbase.c \
	mae_decoratorbase.c \
	mae_dispcanvas.c \
	mae_glalbumslidewidget.c \
	mae_glboxlistwidget.c\
        mae_glphotoslidewidget.c\
	mae_glclotheffectwidget.c\
    mae_glcirclelistwidget.c\
    mae_glcoverflowwidget.c\
	mae_glflipeffectwidget.c\
	mae_glfotolistpagewidget.c\
	mae_glfotolistwidgetbase.c\
	mae_glmagnifywidget.c\
	mae_glmenuwidget.c\
	mae_glmultiidlepagewidget.c\
    mae_glmlpgwidget.c\
	mae_glrain.c\
	mae_glrotationmenuwidget.c\
	mae_gltransformwidget.c \
	mae_glwidget_common.c\
	mae_gridwidgetbase.c \
	mae_inputcontroller.c \
	mae_inputcontroller_chinese.c \
	mae_inputcontroller_encoding.c \
	mae_inputcontroller_handwriting.c \
	mae_inputcontroller_inputmenu.c \
	mae_inputcontroller_mark.c \
	mae_inputcontroller_mt_candidate.c \
	mae_inputcontroller_multitap.c \
	mae_inputcontroller_my.c \
	mae_inputcontroller_sg.c \
	mae_inputcontroller_numeric.c \
	mae_inputcontroller_smart.c \
	mae_inputcontroller_softkeyboard.c \
	mae_softkeyboard_highlightwidget.c\
	mae_inputcontroller_textmodel.c \
	mae_inputcontroller_viewonly.c \
	mae_inputcontroller_zi.c \
	mae_inputcontroller_format.c \
	mae_inputcontroller_type.c\
	mae_inputcontroller_dummy.c \
	mae_input_common.c \
	mae_viewportanim_android.c\
	mae_viewportanim_iphone.c\
    mae_viewportanim_boundonly.c\
	mae_wdgbackground.c \
	mae_widgetbase.c \
	mae_widgetborder.c \
	mae_widgetcell.c \
	mae_widget_common.c \
	mae_propcontainerbase.c\
	mmi_wdg_common_interface.c \
	mmi_wdg_screensaver_effect.c\
	mae_live_effect.c\
	mae_wallpaper_effect.c\
	mae_spectrumwidget.c\
	mae_spectrum_effect.c\
	mae_3deffect_common.c\
	mae_3deffect_earthrot.c\
	mae_3deffect_comet.c\
	mae_3deffect_droplet.c\
	mae_3deffect_snakeline.c\
	mae_3deffect_seashore.c\
	mae_3deffect_fallsnow.c\
	mae_3deffect_fish.c\
	mae_3deffect_fluttersnow.c\
	mae_3deffect_jumpgate.c\
	mae_3deffect_solarsystem.c\
    mae_3deffect_inwater.c\
    mae_3deffect_inwaterShoot.c\
	mae_3deffect_weather.c\
	mae_3deffect_grasstrace.c\
	mae_3deffect_farm.c\
        mae_3deffect_bird.c\
	mae_wallpaper_image.c\
    mmi_wdg_3dloader.c\
	mmi_wdg_animimage.c \
	mmi_wdg_abscontainer.c \
	mmi_wdg_animated_menu.c \
	mmi_wdg_animationcontainer.c\
	mmi_wdg_bitmap.c \
	mmi_wdg_basicbitmap.c\
	mmi_wdg_button.c \
	mmi_wdg_canvas.c \
	mmi_wdg_caret.c \
	mmi_wdg_commonpickitem.c \
	mmi_wdg_date.c \
	mmi_wdg_dateicon.c \
	mmi_wdg_doubleitem.c \
	mmi_wdg_dummy.c \
	mmi_wdg_drag.c \
	mmi_wdg_event.c \
	mmi_wdg_fadeout.c \
	mmi_wdg_fcdate.c \
	mmi_wdg_fctime.c \
	mmi_wdg_fliptext.c \
	mmi_wdg_formatinput.c \
	mmi_wdg_flipdclock.c \
	mmi_wdg_glowtext.c \
	mmi_wdg_gltimeindwidget.c \
	mmi_wdg_group.c \
	mmi_wdg_handwriting.c \
	mmi_wdg_ifone.c \
	mmi_wdg_image.c \
	mmi_wdg_overlayimage.c \
	mmi_wdg_image_text_image.c \
	mmi_wdg_image_doubleitem.c \
	mmi_wdg_imeassist.c \
	mmi_wdg_indicator.c \
	mmi_wdg_input.c \
	mmi_wdg_inputcandidate.c \
	mmi_wdg_inputhelper.c \
	mmi_wdg_inputgrid.c \
	mmi_wdg_ip.c \
	mmi_wdg_itf_dynamicmenu.c \
	mmi_wdg_itf_menu.c \
	mmi_wdg_itf_menu_cb.c \
	mmi_wdg_itf_menu_common.c \
	mmi_wdg_itf_menu_item.c \
	mmi_wdg_itf_staticmenu.c \
	mmi_wdg_list.c \
	mmi_wdg_menu.c \
	mmi_wdg_mflcontainer.c \
	mmi_wdg_multipagecontainer.c\
	mmi_wdg_optionmenu.c \
	mmi_wdg_osd.c \
	mmi_wdg_pick.c \
	mmi_wdg_popupselect.c \
	mmi_wdg_progress.c \
	mmi_wdg_propcirclecontainer.c\
	mmi_wdg_propcontainer.c \
	mmi_wdg_pulldown.c \
	mmi_wdg_rootcontainer.c \
	mmi_wdg_scroll_indicator.c \
	mmi_wdg_scrollbar.c \
	mmi_wdg_sheetcontainer.c \
	mmi_wdg_shortcutbar.c \
	mmi_wdg_slideswitch.c \
	mmi_wdg_snapshot.c \
	mmi_wdg_softkey.c \
	mmi_wdg_softkeyboard.c \
	mmi_wdg_statusbar.c \
	mmi_wdg_switchicon.c \
	mmi_wdg_switchiconitem.c \
	mmi_wdg_tab.c \
	mmi_wdg_text.c \
	mmi_wdg_textbubble.c \
	mmi_wdg_time.c \
	mmi_wdg_timerformat.c \
	mmi_wdg_title.c \
	mmi_wdg_transition.c \
	mmi_wdg_ringlist.c \
	mmi_wdg_viewercontainer.c \
	mmi_wdg_viewport.c \
	mmi_wdg_volume.c \
	mmi_wdg_wallpaper.c\
	mmi_wdg_ballslide.c\
  mmi_wdg_screeneffect_bezier.c \
  mmi_wdg_screeneffect_fire.c \
  mmi_wdg_screeneffect_firefly.c \
  mmi_wdg_screeneffect_meteor.c \
  mmi_wdg_screeneffect_ripple.c \
  mmi_wdg_screeneffect_snow.c \
  mmi_wdg_screeneffect_space.c \
  mmi_wdg_screeneffect_water.c \
        mmi_wdg_screeneffect.c \
  mmi_wdg_image_doubleitem_multifield.c \
  mmi_wdg_multitouchtest.c

ifeq ($(filter __IME_MMI_CSTAR__, $(PP_OPT_COMMON)), __IME_MMI_CSTAR__)
SRC_C_LIST += kmx_ime.c
SRC_C_LIST += kmx_ime_config.c
SRC_C_LIST += kmx_inputcontroller.c
SRC_C_LIST += kmx_softkeyboardwidget.c
SRC_C_LIST += kmx_layout_helper.c
SRC_C_LIST += mae_inputcontroller_kmx.c
SRC_C_LIST += mstar_ime_profiling.c
SRC_C_LIST += cs_ime.c
SRC_C_LIST += cs_ime_adapter.c
SRC_C_LIST += kmxime_api.c
SRC_C_LIST += kmxime_callback.c
SRC_C_LIST += kmxime_keypad.c
endif

ifeq ($(filter __MMI_SCRIPT_EASY_EDITOR__, $(PP_OPT_COMMON)), __MMI_SCRIPT_EASY_EDITOR__)
SRC_C_LIST += kmx_wdg_input.c
endif

#delete original {MMI_}PATH_H

PATH_C +=\
	$(PATH_widget)/src

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc
endif

ifeq ($(filter __FEATURE_PGL__ ,$(PP_OPT_COMMON)),__FEATURE_PGL__)
MMI_PATH_H += \
    $(PATH_pgl)/mChipmunk/inc \
    $(PATH_pgl)/pub
endif

ifeq ($(filter __IME_MMI_MY__ ,$(PP_OPT_COMMON)),__IME_MMI_MY__)
MMI_PATH_H += $(PATH_ime)/my/inc
endif
ifeq ($(filter __IME_MMI_SG__ ,$(PP_OPT_COMMON)),__IME_MMI_SG__)
MMI_PATH_H += $(PATH_ime)/sg/inc 
endif
ifeq ($(filter __IME_MMI_CSTAR__, $(PP_OPT_COMMON)), __IME_MMI_CSTAR__)
MMI_PATH_H += \
	$(PATH_widget)/kmx
PATH_C +=\
	$(PATH_widget)/kmx
endif
ifeq ($(filter __MMI_SCRIPT_EASY_EDITOR__, $(PP_OPT_COMMON)), __MMI_SCRIPT_EASY_EDITOR__)
MMI_PATH_H += \
	$(PATH_mae)/inc/kmx\
	$(PATH_widget)/kmx
PATH_C +=\
	$(PATH_widget)/kmx
endif
#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_widget.c
