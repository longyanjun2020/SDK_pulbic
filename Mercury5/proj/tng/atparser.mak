
TARGET=atparser


all: parser

include $(TOP)config.mak
# include csn parameters

# target files
LEX_FILE = ati.l 
YACC_FILE = ati.y 
BISON_SIMPLE=$(OUT)/bison.simple
export BISON_SIMPLE
LEX_FILE_TGTS=$(LEX_FILE:%=$(OUT)%)
YACC_FILE_TGTS=$(YACC_FILE:%=$(OUT)%)

# main rule
parser: $(OUT) $(LEX_FILE_TGTS) $(YACC_FILE_TGTS) awkscripts yacc_skel $(OUT)ati_mandatory_lex.c $(OUT)ati_mandatory_yacc.c $(OUT)ati_yacc.h

$(OUT)ati_mandatory_lex.c: $(LEX_FILE_TGTS)
	$(INFO) $@
	$(TDEBUG) $(LEX) $(LEX_OPT) -o $@ $< 
	awk -f $(OUT)lex.awk $@ > $@".tmp"
	$(TDEBUG) mv $@".tmp" $@
	mv $@ $(PATH_ati)/inc_to_del

$(OUT)ati_mandatory_yacc.c: $(YACC_FILE_TGTS) 
	$(INFO) $@
	$(TDEBUG) $(YACC) $(YACC_OPT) -o $@ $< 
	awk -f $(OUT)yacc.awk $@ > $@".tmp"
	$(TDEBUG) mv $@".tmp" $@
	mv $@ $(PATH_ati)/inc_to_del
	
$(OUT)ati_yacc.h: $(YACC_FILE_TGTS)
	mv $(OUT)ati_mandatory_yacc.h $@

vpath %.l $(PATH_ati)/parser
vpath %.y $(PATH_ati)/parser
vpath %.simple $(PATH_ati)/parser
vpath %.awk $(PATH_ati)/parser

$(OUT)%.l: %.l
	$(INFO) $@
	$(INSTALL) $< $@

$(OUT)%.y: %.y
	$(INFO) $@
	$(INSTALL) $< $@

yacc_skel: $(OUT)bison.simple
$(OUT)%.simple: %.simple
	$(INFO) $@
	$(INSTALL) $< $@

awkscripts :$(OUT)lex.awk $(OUT)yacc.awk 

$(OUT)%.awk: %.awk
	$(INSTALL) $< $@


$(OUT):
	$(MKDIR) $@
	
