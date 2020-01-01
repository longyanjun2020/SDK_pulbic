
#-------------------------------------------------------------------------------
# if turn on __DIAG_ERROR__, build system would treat warning as error,
# this is use to suppress the #174 warning
#-------------------------------------------------------------------------------
ifeq ($(COMPILER_VERSION),RVCTV22)
C_OBJS = cus_os_test.o
$(C_OBJS:%=$(OUT)%): C_OPTIONS+=--diag_suppress 174
endif

PATH_C +=\
    $(PATH_MsWrapper)/src

# path to C source files in "opxc" directories
PATH_C +=\
    $(PATH_MsWrapper)/opxc

PATH_H +=\
    $(PATH_MsWrapper)/inc\
    $(PATH_rtc)/pub

#------------------------------------------------------------------------------
#   List of source  files   of  the library or  executable to generate
#------------------------------------------------------------------------------

REL_SRC_C_LIST +=\
               cus_os.c \
               cus_os_flag.c\
               cus_os_mem.c\
               cus_os_msg.c\
               cus_os_sem.c\
               cus_os_timer.c\
               cus_os_util.c\
               opec_cus.c\
               cus_os_int.c

ifeq ($(COMPILER_VERSION),X86LINUXGCC)			   
REL_SRC_C_LIST += abi_headers_MsWrapper.c
endif


SRC_C_LIST =    \
