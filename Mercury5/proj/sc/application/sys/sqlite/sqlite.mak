#------------------------------------------------------------------------------
#   List of source  files   of  the library or  executable to generate
#------------------------------------------------------------------------------

C_OBJS1 = sqlite3.o

ifeq ($(COMPILER_VERSION),RVCTV22)
$(C_OBJS1:%=$(OUT)%): CFLAGS += -W
endif

SRC_C_LIST = \
	sqlite_UT.c\
	sqlite3.c

PATH_H = \
	$(PATH_sqlite)/inc \
	$(PATH_sqlite)/pub \
	$(PATH_sqlite)/src \
	$(PATH_mmicomn)/inc \
	$(PATH_build) \
	$(PATH_widget)/inc\
	$(PATH_widget)/pub\
	$(PATH_mae)/porting/inc \
	$(PATH_mae)/src \
	$(PATH_mae)/inc \
	$(PATH_mae)/pub \
	$(PATH_mae)/src/models \
	$(PATH_mae)/src/fonts \
	$(PATH_mae)/src/resource \
	$(PATH_mae)/extras/util \
	$(PATH_esl)/itf \
	$(PATH_srv)/inc \
	$(PATH_srv)/pub \
	$(PATH_srv)/CodecSrv/inc/priv \
	$(PATH_customer_define_folder)/pub \
	$(PATH_FileMgr)\
	$(PATH_truetype)/freetype2/inc \
	$(PATH_hopper)/pub \
	$(PATH_FileMgr)/pub \
	$(PATH_mae)/extras/datamgr \
	$(PATH_vfs)/pub \
	$(PATH_MsWrapper)/pub \
        $(PATH_fc)/pub \
        $(PATH_rtk)/pub \
        $(PATH_sys)/pub \
        $(PATH_time)/pub \
        $(PATH_timer)/pub \
        $(PATH_ucs2)/pub \
        $(PATH_rtc)/pub
	
PATH_C =\
	$(PATH_sqlite)/src

#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_sqlite.c
