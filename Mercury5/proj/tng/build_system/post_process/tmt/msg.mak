
TARGET=msg

.PHONY: msg .phony

all: msg

include $(CONFIG_MAK)

TMT=$(BUILD)$(PRODUCT)/tmt/
TMT_MSG=$(TMT)$(PRODUCT).msg
## ALL_HEADER_FILE_OUT must sync. with $:setpp_out $pp_out in get_msg_id.pl
ALL_HEADER_FILE_OUT=$(OUT)all_msg.h
ALL_HEADER_FILE=$(OUT)sys_sys_message.h
PRE_INCLUDE_FILE_1=msgofs.hc
PRE_INCLUDE_FILE_2=cus_msg.hc
PRE_INCLUDE_FILE_3=
PRE_INCLUDE_FILE_4=
PRE_INCLUDE_FILE_5=


msg: $(TMT_MSG)

$(TMT_MSG): .phony
ifeq ($(filter AEONGCC RVCTV22, $(COMPILER_VERSION)), )
	@echo "NO" > $@
else # ifeq ($(filter AEONGCC RVCTV22, $(COMPILER_VERSION)), )

# 1. preprocess command line
#   1.1.1 add speical include file to $(ALL_HEADER_FILE)
	@echo "#include \"$(PRE_INCLUDE_FILE_1)\""					>  $(ALL_HEADER_FILE)
	@echo "#include \"$(PRE_INCLUDE_FILE_2)\""					>> $(ALL_HEADER_FILE)
#	@echo "#include \"$(PRE_INCLUDE_FILE_3)\""					>> $(ALL_HEADER_FILE)
#	@echo "#include \"$(PRE_INCLUDE_FILE_4)\""					>> $(ALL_HEADER_FILE)
#	@echo "#include \"$(PRE_INCLUDE_FILE_5)\""					>> $(ALL_HEADER_FILE)
	@echo ""													>> $(ALL_HEADER_FILE)
	@echo "#ifndef VM_MSG_DEF"									>> $(ALL_HEADER_FILE)
	@echo "#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,"	>> $(ALL_HEADER_FILE)
	@echo "#endif"												>> $(ALL_HEADER_FILE)
	@echo ""													>> $(ALL_HEADER_FILE)
	@echo "enum{"												>> $(ALL_HEADER_FILE)
	@echo "MESSAGE_ID_START,"									>> $(ALL_HEADER_FILE)
	@echo ""													>> $(ALL_HEADER_FILE)
#   1.1.2 cat all *_message_define__.hi.MSG to $(ALL_HEADER_FILE)
#     add '-' before cat since there is possibly no _message_define__.hi.MSG in out folder
	-@cat $(DIR_MSG)*_message_define__.hi						>> $(ALL_HEADER_FILE)
	@echo ""													>> $(ALL_HEADER_FILE)
	@echo "}; // end of enum"									>> $(ALL_HEADER_FILE)
#   1.1.3 preprocess $(ALL_HEADER_FILE)
	$(PLTM_CC) ${CFLAGS} ${IFLAGS} -E $(ALL_HEADER_FILE) -o $(ALL_HEADER_FILE_OUT)

# 2. generate msg id with the preprocess file. It can add -v2 for debugging
	$(TNG)get_msg_id.pl -i$(OUT) -o$@

endif # ifeq ($(filter AEONGCC RVCTV22, $(COMPILER_VERSION)), )
