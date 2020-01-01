
CC=aeon-elf-gcc
CFLAGS=-O2 -Wall -I../inc
SRCS = wchar.c atoi.c atof.c rand.c ctype_.c isspace.c qsort.c vsprintf.c vsnprintf.c sccl.c sscanf.c snprintf.c sprintf.c \
       strcat.c strcmp.c strcpy.c strlen.c strncat.c strncmp.c strncpy.c strchr.c strrchr.c strstr.c strtok.c strtok_r.c \
       memchr.c memcmp.c memcpy.c memmove.c memset.c strtoull_r.c strtoll_r.c strtoul.c strtol.c \
       mprec.c dtoa.c gdtoa-gethex.c gdtoa-hexnan.c strtod.c vfprintf.c vfscanf.c \
       setjmp.S utest.c

OBJS=$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o utest -v $(OBJS) #-nostdlib -lgcc -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<
