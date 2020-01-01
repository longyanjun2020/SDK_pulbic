#
# gen all lib list
#

include $(CONFIG_MAK)

all: module_mak_list_preprocess $(PRODUCT_ALL:%=%.checking_list)

module_mak_list_preprocess:
	-$(CLEAN) $(LIST_MODULE_MAK)
	@echo 'ALL_MODULE_MAK = \' > $(LIST_MODULE_MAK)

%.checking_list:
	@echo '  $(PATH_$(basename $@))/$(basename $@)$(FLAVOR_$(basename $@)).mak\' >> $(LIST_MODULE_MAK)
