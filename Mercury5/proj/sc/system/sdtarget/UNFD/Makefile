UNFD_ROOT	= .

CROSS_COMPILE	?= arm
CC		:= $(CROSS_COMPILE)cc
AR		:= $(CROSS_COMPILE)ar

CFLAGS		+= -I../include -I$(UNFD_ROOT)/inc -I$(UNFD_ROOT)/inc/sys -I$(UNFD_ROOT)/pub
CFLAGS		+= --diag_suppress 111

SRC		+= src/drvNAND_hal.c
SRC		+= src/drvNAND_rom.c
SRC		+= src/drvNAND_utl.c
SRC		+= src/drvNAND_platform.c


OBJS		:= $(patsubst %.c,%.o,$(SRC))

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

unfd.a: $(OBJS)
	$(AR) r $@ $(OBJS)

all: unfd.a


clean:
	rm $(OBJS) unfd.a
