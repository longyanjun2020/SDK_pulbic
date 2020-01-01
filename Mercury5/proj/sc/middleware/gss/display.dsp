# Microsoft Developer Studio Project File - Name="display" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=display - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "display.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "display.mak" CFG="display - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "display - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "display - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "display - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\itf" /I ".\inc" /I "..\..\system\sys\itf_open" /I "..\..\system\fc\com" /I "..\..\system\sys\itf" /I "..\..\system\sys\inc" /I "..\..\system\trc\itf" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_MSIM_" /YX /FD /c
# ADD BASE RSC /l 0x404 /d "NDEBUG"
# ADD RSC /l 0x404 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "display - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\system\sys\inc" /I "..\..\system\trc\itf" /I ".\itf" /I ".\inc" /I "..\..\system\sys\itf_open" /I "..\..\system\fc\com" /I "..\..\system\sys\itf" /I "..\..\system\trc\itf_open" /I "..\..\system\rtk\arm\itf_open" /I "..\..\telecom\sim\itf" /I "..\..\system\e2p\itf_open" /I "..\..\system\rtk\arm\inc" /I "..\..\system\fc\itf" /I "..\..\system\io\itf" /I "..\..\system\io\itf_open" /I "..\..\platform\atlas\inc" /I "..\..\system\rtk\arm\itf" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_DEBUG" /D "__DUAL_LCD__" /D "__QVGA_18BITS__" /D "__TARGET__" /YX /FD /GZ /c
# ADD BASE RSC /l 0x404 /d "_DEBUG"
# ADD RSC /l 0x404 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "display - Win32 Release"
# Name "display - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\BitBlt.c
# End Source File
# Begin Source File

SOURCE=.\src\BltPattern.c
# End Source File
# Begin Source File

SOURCE=.\src\DispBasicGrap.c
# End Source File
# Begin Source File

SOURCE=.\src\DispInit.c
# End Source File
# Begin Source File

SOURCE=.\src\DispLine.c
# End Source File
# Begin Source File

SOURCE=.\src\DispPowerMgr.c
# End Source File
# Begin Source File

SOURCE=.\src\DispSurfMgr.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_2dgp_drv.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_2dgp_itf.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_cisi_drv.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_cisi_itf.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_ctrl.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_display.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_jpg_drv.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_jpg_itf.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_lcdc_drv.c
# End Source File
# Begin Source File

SOURCE=.\src\gss_lcdc_itf.c
# End Source File
# Begin Source File

SOURCE=.\src\lcdx_lcdc_dual.c
# End Source File
# Begin Source File

SOURCE=.\src\lcdx_lcdc_main.c
# End Source File
# Begin Source File

SOURCE=.\src\PanelInfo.c
# End Source File
# Begin Source File

SOURCE=.\src\PanelInfoHW.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\inc\bitblt.h
# End Source File
# Begin Source File

SOURCE=.\inc\bltpattern.h
# End Source File
# Begin Source File

SOURCE=.\inc\dispbasicgrap.h
# End Source File
# Begin Source File

SOURCE=.\inc\dispfunctable.h
# End Source File
# Begin Source File

SOURCE=.\inc\displine.h
# End Source File
# Begin Source File

SOURCE=.\inc\disppowermgr.h
# End Source File
# Begin Source File

SOURCE=.\inc\dispsurfmgr.h
# End Source File
# Begin Source File

SOURCE=.\inc\functypes.h
# End Source File
# Begin Source File

SOURCE=.\itf\graphdevice.h
# End Source File
# Begin Source File

SOURCE=.\inc\gss_2dgp_drv.h
# End Source File
# Begin Source File

SOURCE=.\inc\gss_cisi_drv.h
# End Source File
# Begin Source File

SOURCE=.\inc\gss_jpg_drv.h
# End Source File
# Begin Source File

SOURCE=.\inc\gss_lcdc_drv.h
# End Source File
# Begin Source File

SOURCE=.\itf\msgdidef.h
# End Source File
# Begin Source File

SOURCE=.\inc\panelinfo.h
# End Source File
# Begin Source File

SOURCE=.\inc\panelinfohw.h
# End Source File
# Begin Source File

SOURCE=.\inc\rm_lcd.h
# End Source File
# End Group
# End Target
# End Project
