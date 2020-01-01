#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

A_OBJS = setjmp.o


PATH_H +=\
  $(PATH_libc)/inc

PATH_C +=\
  $(PATH_libc)/src


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  wchar.c \
  atoi.c \
  atof.c \
  rand.c \
  ctype_.c \
  dtoa.c \
  div.c \
  gdtoa-gethex.c \
  gdtoa-hexnan.c \
  isspace.c \
  memchr.c \
  memcmp.c \
  memcpy.c \
  memmove.c \
  memset.c \
  mprec.c \
  qsort.c \
  sccl.c \
  sscanf.c \
  snprintf.c \
  sprintf.c \
  strcat.c \
  strcmp.c \
  strcpy.c \
  strlen.c \
  strncat.c \
  strncmp.c \
  strncpy.c \
  strchr.c \
  strrchr.c \
  strstr.c \
  strtod.c \
  strtok.c \
  strtok_r.c \
  strtoul.c \
  strtol.c \
  strspn.c \
  vfprintf.c \
  vsprintf.c \
  vsnprintf.c \
  vfscanf.c \
  strtoull_r.c \
  strtoll_r.c
  
SRC_ASM_LIST =\
  setjmp.S
  