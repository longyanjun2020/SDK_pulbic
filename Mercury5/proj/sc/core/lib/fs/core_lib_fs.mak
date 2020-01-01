#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# c file list
SRC_C_LIST += \
	api_dev.c\
	api_dir.c\
	api_in.c\
	api_misc.c\
	api_out.c\
	FS_AddSpaceHex.c\
	FS_AssignCache.c\
	FS_Attrib.c\
	FS_CopyFile.c\
	FS_Core.c\
	FS_ErrorNo2Text.c\
	FS_ErrorOut.c\
	FS_Format.c\
	FS_GetFilePos.c\
	FS_GetFileSize.c\
	FS_GetNumFiles.c\
	FS_GetNumOpenFiles.c\
	FS_Init.c\
	FS_Log.c\
	FS_Move.c\
	FS_OS_Interface.c\
	FS_Read.c\
	FS_Rename.c\
	FS_SetEndOfFile.c\
	FS_SetFilePos.c\
	FS_Time.c\
	FS_Truncate.c\
	FS_Unmount.c\
	FS_Verify.c\
	FS_Volume.c\
	FS_Warn.c\
	FS_Write.c\
	FS__ECC256.c\
	FS__CLIB_atoi.c\
	FS__CLIB_memcmp.c\
	FS__CLIB_memcpy.c\
	FS__CLIB_memset.c\
	FS__CLIB_strchr.c\
	FS__CLIB_strcmp.c\
	FS__CLIB_strcpy.c\
	FS__CLIB_strlen.c\
	FS__CLIB_strncmp.c\
	FS__CLIB_strncpy.c\
	FS__CLIB_toupper.c\
	FAT_API.c\
	FAT_CheckDisk.c\
	fat_dir.c\
	FAT_DirEntry.c\
	FAT_DiskInfo.c\
	FAT_Format.c\
	fat_in.c\
	fat_ioct.c\
	fat_misc.c\
	FAT_Move.c\
	fat_open.c\
	fat_out.c\
	FAT_Rename.c\
	FAT_SetEndOfFile.c\
	FAT_VolumeLabel.c\
	lfn.c\
	CacheAll.c\
	CacheMan.c\
	CacheRW.c\
	CacheRWQuota.c\
	lb_misc.c\
	fs_x_no_os.c\
	fs_x_ucos_ii.c\
	fs_x_rtk.c\
	#r_misc.c\
	#sd_misc.c\
	#sm_misc.c\
		
# cpp file list
#SRC_CPP_LIST = \
#	C4.cpp\
#	C5.cpp\
#	C6.cpp

# asm file list
#SRC_ASM_LIST =\
#	A1.asm\
#	A2.asm

# header file folder for this library 
PATH_H +=\
	$(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
 	$(PATH_sys)/pub\
	$(PATH_MsWrapper)/pub\
 	
#	$(PATH_ex20)/ex21/ex22\
#	$(PATH_ex23)/ex24/ex25/ex26/ex27\
#	$(PATH_ex28)/ex29/ex30/ex31

# c/cpp source code for this library 
PATH_C +=\
	$(PATH_core_lib_fs)/src/API\
	$(PATH_core_lib_fs)/src/CLIB\
	$(PATH_core_lib_fs)/src/FSL/fat\
	$(PATH_core_lib_fs)/src/FSL/fat/LFN\
	$(PATH_core_lib_fs)/src/LBL\
	$(PATH_core_lib_fs)/src/OS\

	#$(PATH_core_lib_fs)/src/DEVICE/ram\
	#$(PATH_core_lib_fs)/src/DEVICE/sd\
	#$(PATH_core_lib_fs)/src/DEVICE/sm\

# $(PATH_ex1)/ex2/ex3\
# $(PATH_ex4)/ex5/ex6/ex7/ex8\
# $(PATH_ex9)/ex10/ex11/ex12

# assembler source code for this library 
#PATH_ASM =\
# $(PATH_ex31)/ex32/ex33\
# $(PATH_ex34)/ex35/ex36/ex37/ex38\
# $(PATH_ex39)/ex40/ex41/ex42

# mark C_OPTIONS if there is no cpp files would be compiled
#C_OPTIONS += \
#	--cpp

