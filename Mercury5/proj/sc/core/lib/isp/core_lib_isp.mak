#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# c file list
SRC_C_LIST = \
    isp_if.c\
	
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
	$(PATH_core_lib_isp)/inc\
 
#	$(PATH_ex20)/ex21/ex22\
#	$(PATH_ex23)/ex24/ex25/ex26/ex27\
#	$(PATH_ex28)/ex29/ex30/ex31

# c/cpp source code for this library 
PATH_C =\
	$(PATH_core_lib_isp)/src\

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

