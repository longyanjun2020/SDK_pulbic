
TARGET=link

all: preprocess_scatter

include $(CONFIG_MAK)
include $(TARGET_MAK)

.PHONY: $(ALL_GROUP_SCATTER)

preprocess_scatter: $(ALL_GROUP_SCATTER)

$(SCATTER_SYS_LIB):
	$(foreach f,$(PRODUCT_SC_SYS) $(PRODUCT_LIB_SYS),echo MSTAR_LIB\(\"$f.lib\"\)>>$@;)
	
$(SCATTER_DRV_LIB):
	$(foreach f,$(PRODUCT_SC_DRV) $(PRODUCT_LIB_DRV),echo MSTAR_LIB\(\"$f.lib\"\)>>$@;)

$(SCATTER_MDL_LIB):
	$(foreach f,$(PRODUCT_SC_MDL) $(PRODUCT_LIB_MDL),echo MSTAR_LIB\(\"$f.lib\"\)>>$@;)

$(SCATTER_3RD_LIB):
	$(foreach f,$(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD),echo MSTAR_LIB\(\"$f.lib\"\)>>$@;)

$(SCATTER_3RDLIB_LIB):
	$(foreach f,$(LIBS_3RD),echo MSTAR_LIB\(\"$f\"\)>>$@;)

$(SCATTER_MMI_APP_LIB):
	$(foreach f,$(PRODUCT_SC_MMI_APP),echo MSTAR_LIB\(\"$f.lib\"\)>>$@;)