
TARGET = e2p
.PHONY: e2p

ifeq "$(OSTYPE)" "Win32"
E2PCE_BIN=.\tng\ConvertE2pToText.exe
E2PCE_E2P_DIR=$(dir $(MAK)..\e2p\)
else
ifeq "$(OSTYPE)" "cygwin"
E2PCE_BIN=./tng/ConvertE2pToText.exe
E2PCE_E2P_DIR=$(dir $(MAK)../e2p/)
else
E2PCE_BIN=./tng/$(OSTYPE)/ConvertE2pToText
E2PCE_E2P_DIR=$(dir $(MAK)../e2p/)
endif
endif

E2P_BIN=./tng/E2PBin_NOR.py

E2P_LIST_TABLE=$(OUT)$(PRODUCT)_E2P_List_Table
E2P_LIST_TABLE_FMT=html

E2PCE_E2P_FILE_LIST_FILE=$(OUT)e2pce_e2p_file_list.log
E2PCE_STRUCT_FILE_LIST_FILE=$(OUT)e2pce_definition_file_list.log
E2PCE_DEF_VALUE_FILE_LIST_FILE=$(OUT)e2pce_default_value_file_list.log

E2PCE_E2P_FILE_LIST=$(shell cat $(E2PCE_E2P_FILE_LIST_FILE))
E2PCE_STRUCT_FILE_LIST=$(shell cat $(E2PCE_STRUCT_FILE_LIST_FILE))
E2PCE_DEF_VALUE_FILE_LIST=$(shell cat $(E2PCE_DEF_VALUE_FILE_LIST_FILE))

include $(CONFIG_MAK)
include $(TARGET_MAK)

list:
	$(foreach FILE,$(E2P_TO_DWL:%=$(OUT)%), $(shell echo "$(FILE)" >> $(E2PCE_E2P_FILE_LIST_FILE)))
	$(foreach FILE,$(GENE2P_E2P_FILE:%=$(OUT)%), $(shell echo "$(FILE)" >> $(E2PCE_E2P_FILE_LIST_FILE)))
	$(foreach FILE,$(VALUES_E2P_LIST:%=$(E2PCE_E2P_DIR)%), $(shell echo "$(FILE)" >> $(E2PCE_DEF_VALUE_FILE_LIST_FILE)))
	$(foreach FILE,$(STRUCT_HDR_LIST:%=$(OUT)%), $(shell echo "$(FILE)" >> $(E2PCE_STRUCT_FILE_LIST_FILE)))

final:
ifeq ($(SKIP_E2P_HTML),1)
	$(WARN) "=== ON DZ server, it skips generating E2P Item Table ... ==="
else
	$(WARN) "======== Generate E2P Item Table ... ========"
	$(INFO) $(E2P_LIST_TABLE).$(E2P_LIST_TABLE_FMT)
	$(E2PCE_BIN) -i $(E2PCE_E2P_FILE_LIST) -d $(E2PCE_STRUCT_FILE_LIST) $(OUT)e2p_stck.ho -v $(E2PCE_DEF_VALUE_FILE_LIST) -l $(OUT)e2p.h -s 2 -f html -o $(E2P_LIST_TABLE)
	python $(E2P_BIN) --e2p "$(E2PCE_E2P_FILE_LIST)" --out $(OUT)e2p.bin
endif
	rm -f $(E2PCE_E2P_FILE_LIST_FILE) $(E2PCE_STRUCT_FILE_LIST_FILE) $(E2PCE_DEF_VALUE_FILE_LIST_FILE)

init:
	rm -f $(E2PCE_E2P_FILE_LIST_FILE) $(E2PCE_STRUCT_FILE_LIST_FILE) $(E2PCE_DEF_VALUE_FILE_LIST_FILE)
