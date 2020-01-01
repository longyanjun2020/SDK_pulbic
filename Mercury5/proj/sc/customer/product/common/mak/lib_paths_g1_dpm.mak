ifeq ($(DPM),eml_main)
PRODUCT_SC += eml_main
PATH_eml_main = $(PATH_middleware)eml_main
PATH_C +=\
    $(PATH_eml_main)/src/Mapper\
    $(PATH_eml_main)/src
PATH_H += $(PATH_eml_main)/inc
endif
