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
	C1.c\
	C2.c\
	C3.c

# cpp file list
SRC_CPP_LIST = \
	C4.cpp\
	C5.cpp\
	C6.cpp

# asm file list
SRC_ASM_LIST =\
	A1.asm\
	A2.asm

# header file folder for this library 
PATH_H +=\
	$(PATH_ex20)/ex21/ex22\
	$(PATH_ex23)/ex24/ex25/ex26/ex27\
	$(PATH_ex28)/ex29/ex30/ex31

# c/cpp source code for this library 
PATH_C =\
 $(PATH_ex1)/ex2/ex3\
 $(PATH_ex4)/ex5/ex6/ex7/ex8\
 $(PATH_ex9)/ex10/ex11/ex12

# the header file included by assembler source code for this library 
PATH_I =\
 $(PATH_ex43)/ex44/ex45\
 $(PATH_ex46)/ex47
 
# assembler source code for this library 
PATH_ASM =\
 $(PATH_ex31)/ex32/ex33\
 $(PATH_ex34)/ex35/ex36/ex37/ex38\
 $(PATH_ex39)/ex40/ex41/ex42

 

# For reducing build time and disk sapce, please do not commit $(moduel).mak with ¡§GEN_PREPROCESS=1¡¨/¡¨ GEN_ASSEMBLY=1¡¨ to P4

# generate preprocess file (e.g. A.c --> A.o.pp)
#GEN_PREPROCESS = 1

# generate preprocess file (e.g. A.c --> A.o.asm)
#GEN_ASSEMBLY=1


#-------------------------------------------------------------------------------
# Ignored by mak parser
#
# Additional configuration to avoid release process delete following description
#-------------------------------------------------------------------------------


# following statement could only be perform in RVCT22 
ifeq ($(COMPILER_VERSION),RVCTV22)

# keep this statement if you got SRC_CPP_LIST to compile
$(SRC_CPP_LIST:%.cpp=$(OUT)%.o): C_OPTIONS += --cpp
$(REL_SRC_CPP_LIST:%.cpp=$(OUT)%.o): C_OPTIONS += --cpp

# the list specified the files to be compiled to arm mode
ARM_OBJS=$(SRC_C_LIST)	
# keep this statement if ARM_OBJS is not null
$(ARM_OBJS:%.c=$(OUT)%.o) $(ARM_OBJS:%.cpp=$(OUT)%.o) $(ARM_OBJS:%.asm=$(OUT)%.o):C_OPTIONS += --arm

# the list specified the files to be compiled to arm mode
O3OBJS=$(SRC_C_LIST)	
# keep this statement if O3OBJS is not null
$(O3OBJS:%.c=$(OUT)%.o) $(O3OBJS:%.cpp=$(OUT)%.o) $(O3OBJS:%.asm=$(OUT)%.o):C_OPTIONS += -O3 -Otime

# suppress the warning to whole module
C_OPTIONS+=--diag_suppress tag[,tag...]

# suppress the warning to specified file
$(OUT)$(file_name).o: C_OPTIONS+= --diag_suppress tag[,tag,...]
endif

