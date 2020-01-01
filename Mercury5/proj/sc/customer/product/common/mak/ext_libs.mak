#===============================================================================
# ** Ext Libraries **
#===============================================================================

LINK += $(PRODUCT_SC_MDL:%=$(OUT)%.lib)\
        $(PRODUCT_SC_DRV:%=$(OUT)%.lib)\
        $(PRODUCT_SC_SYS:%=$(OUT)%.lib)\
        $(PRODUCT_SC_MMI:%=$(OUT)%.lib)\
        $(PRODUCT_SC_3RD:%=$(OUT)%.lib)\


#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_MDL:%=$(OUT)%.lib)) \
        $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_DRV:%=$(OUT)%.lib)) \
        $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_SYS:%=$(OUT)%.lib)) \
        $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_MMI:%=$(OUT)%.lib)) \
        $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_3RD:%=$(OUT)%.lib)) \


#EXT_LIBS +=

include $(PATH_3rd)/3rd_lib.mak
