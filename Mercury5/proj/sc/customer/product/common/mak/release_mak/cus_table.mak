
STATIC_ID_TABLES = armMode.ini				\
										powerOnCause.ini  \
										MsmRegister.lst	

DYNAMIC_ID_TABLES =	exceptionType.ini	\
			TaskState.ini	\
			RemoteDefs.ini

TABLE_FILES=$(STATIC_ID_TABLES:%=$(TMPL)%) $(DYNAMIC_ID_TABLES:%=$(OUT)%)

