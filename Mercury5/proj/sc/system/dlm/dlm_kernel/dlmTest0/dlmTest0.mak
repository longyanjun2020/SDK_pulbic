
SRC_C_LIST = \
	dlmTest0.c\

DLM_COMPILER = ARM
DLM_LINKER = ABSTRACT

#
# Option_Selection = SRV/DRV/MDL/SYS/3RD/ (NULL)
# If UT_GROUP is defined, dlm_file would be generated in out/dlm/Dlm_UT/$(UT_GROUP) folder
# for unit test only...
#
UT_GROUP=

#
# multiple source code path is allowed !
#
PATH_SC_dlmTest0=$(PATH_dlm_kernel)/dlmTest0/src
