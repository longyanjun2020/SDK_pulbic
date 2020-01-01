# Makefile used to generate definition files (.dfn)
# from "VK" software components makefiles

include $(CONFIG_MAK)

# include SC makefile
include $(PATH_dlm_entry_inc)dlm_entry.lst

.PHONY: dlm_entry_mak clean_dlm_pre

all: gen_dlm_stub dlm_entry_mak

gen_dlm_stub: $(PATH_dlm_entry_src) $(DLM_ENTRY_LST:%=$(PATH_dlm_entry_src)stub_%.c)

$(PATH_dlm_entry_src):
	$(MKDIR) $@

$(PATH_dlm_entry_src)stub_%.c: $(PATH_dlm_entry_inc)%.def $(PATH_dlm_entry_pub)%.h
	$(INFO) "creating stub file:" $@
	$(STUBGEN) -id $< -ih $(PATH_dlm_entry_pub)$(notdir $(patsubst %.def,%.h,$<)) -oc $@


dlm_entry_mak: $(PATH_dlm_entry)/dlm_entry.mak

$(PATH_dlm_entry)/dlm_entry.mak: $(PATH_dlm_entry_inc)dlm_entry.lst $(COMMON_OPTIONS_MAK) $(OPTIONS_CUS_MAK)
	$(INFO) "creating make file:" $@ "  from: " $<
	dos2unix $(PATH_dlm_entry_inc)dlm_entry.lst
	$(TNG)dlm_pre.pl $@ $(PATH_dlm_entry_src)stub_dlm_dummy.c $(DLM_ENTRY_LST)
	dos2unix $@

clean_dlm_pre:
	-$(CLEAN)  $(PATH_dlm_entry)/dlm_entry.mak
	-$(CLEAN)  $(DLM_ENTRY_LST:%=$(PATH_dlm_entry_src)stub_%.c)