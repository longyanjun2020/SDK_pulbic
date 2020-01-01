
TARGET=csn

all: csn

include $(TOP)config.mak
# include csn parameters
include $(TARGET_MAK)

TMP_CSN=$(PATH_csnout)

export PATH:=$(PATH):../../../../$(BIN)/bin

ifeq ("$(OSTYPE)","linux")
export CSN1PATH="../../../../$(BIN)/bin/../"
endif

CSN_FLAGS=-c $(CSN_DEFINES:%=-D%) -I. -b -o

# target files
CSN_TGTS = $(CSN_SRCS:%.csn=%.c)

# main rule
csn: $(TMP_CSN) $(CSN_DEPS:%=$(TMP_CSN)%) $(CSN_TGTS:%=$(TMP_CSN)%) convert2unix

$(CSN_R1:%=$(TMP_CSN)%): CSN_FLAGS+=-r1

$(CSN_R2:%=$(TMP_CSN)%): CSN_FLAGS+=-r2

$(CSN_R5:%=$(TMP_CSN)%): CSN_FLAGS+=-r5

$(CSN_M:%=$(TMP_CSN)%): CSN_FLAGS+=-m

$(TMP_CSN)%.c: $(TMP_CSN)%.csn
	$(INFO) $@
	cd $(TMP_CSN) && ycsn $(CSN_FLAGS) $(<F)

convert2unix:
ifeq ($(OSTYPE),$(findstring $(OSTYPE),cygwin msys))
	cd $(TMP_CSN) && dos2unix *.c
	cd $(TMP_CSN) && dos2unix *.h
endif

$(TMP_CSN):
	$(MKDIR) $@

vpath %.csn $(PATH_CSN)

$(TMP_CSN)%.csn: %.csn
	$(INFO) $@
	$(INSTALL) $< $@
