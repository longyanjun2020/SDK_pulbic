	PROCESS		= lib
	PATH_C +=\
		$(PATH_tencentmcare)/src
	PATH_H +=\
		$(PATH_tencentmcare)/inc
	PATH_EXT_LIB +=\
		$(PATH_tencentmcare)/lib


C_OPTIONS += --diag_suppress 1,177,494,550,1295,223,111

#PORTING
REL_SRC_C_LIST += TencentMcare_app.c
REL_SRC_C_LIST += adaptVendor.c
