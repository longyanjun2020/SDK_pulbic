
TMPL=$(PATH_common)tmpl/

TMT_DEFAULT=$(PATH_common)tmpl/default.wks
TMT_TEMPLATE=$(OUT)default.wks

TMPL_FILES=DiagnoseTips.ini\
		MokaWatches.ini


OUT_FILES=e2p.h\
		backtraces.axf\
		symbols\
		remtrace.csv


SOURCE_TREE_FILES = $(PATH_sys)/itf_open/vm_ftr.ho
TMT_FILES=$(TMPL_FILES:%=$(TMPL)%) $(OUT_FILES:%=$(OUT)%) $(SOURCE_TREE_FILES)
