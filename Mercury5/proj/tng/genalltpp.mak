
include $(CONFIG_MAK)

all: $(ALLTPP:%=%.gentpp) $(ALLDUOTPP:%=%.gentppduo)
	echo "[ALLTPP]:"$(ALLTPP) "[ALLDUOTPP]:"$(ALLDUOTPP)

ifeq ($(RELEASE_PROCESS),0)
%.gentpp:
	$(MAKE_ONLY_TPP) TARGET=$* $(COMPILER_CMD) $(CT_CMD)
%.gentppduo:
	$(MAKE_ONLY_TPP) TARGET=$* $(COMPILER_CMD) $(CT_CMD) DUP_FLAG=1
endif

ifeq ($(RELEASE_PROCESS),1)
%.gentpp:
	$(REL_MAKE_ONLY_TPP) TARGET=$* $(COMPILER_CMD) $(CT_CMD)
%.gentppduo:
	$(REL_MAKE_ONLY_TPP) TARGET=$* $(COMPILER_CMD) $(CT_CMD) DUP_FLAG=1
endif



DFN: $(ALLTPP:%=%.gentdfn) $(ALLDUOTPP:%=%.gendfnduo)
	echo "[ALLTPP]:"$(ALLTPP) "[ALLDUOTPP]:"$(ALLDUOTPP)

%.gentdfn:
	$(MAKE_DFN) TARGET=$*   $(COMPILER_CMD) $(CT_CMD)
%.gendfnduo:
	$(MAKE_DFN) TARGET=$*   $(COMPILER_CMD) $(CT_CMD) DUP_FLAG=1



