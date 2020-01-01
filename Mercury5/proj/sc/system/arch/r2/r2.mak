#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
	
# if build 8830X then include R2
PATH_H +=\
  $(PATH_r2)/inc\
  $(PATH_r2)/pub
	
# path to C header files
PATH_H +=\
  $(PATH_system)/mswrapper/pub
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	   r2_core.c\
	   r2_pthread.c\
	   r2_irq.c\
	   r2_traps.c

