
#-------------------------------------------------------------------------------
# Common help info.
#-------------------------------------------------------------------------------
help:
	@echo -ne "\e[1m\e[34mMStar Semiconductor, Inc. Mobile build system\e[0m\n\
	Usage: \n\
	\e[1m\e[32mSPECIAL PARAMETERS (Can be applied to all build command!!)\e[0m\n\
	  e.g.  make speed XRG=1 NO_DEBUG=1 XRG_CUS=LangPack0000\n\
	  \tmake ibuild XRG_CUS=\"LangPack0000 LangPack0002\"\n\
	  \n\
	  XRG=1 : to skip XRG stage if mmi resource is already generated\n\
	          and not modified\n\
	  NO_DEBUG=1 : to turn off source level debug to speedup build process\n\
	              ( there are no mapping between c/cpp code and assembly code\n\
	               when using trace32 to debug )\n\
	  XRG_CUS=\"LangPack0000 LangPack0001 ...\" :\n\
	          specify the language pack you want to generate\n\
	          please reference to\n\
	          sc/customer/default/src/mmi/resource/Control_Files/CommonPortrait.xml\n\
	          to see which language packs are available\n\
	  GEN_PREPROCESS=1 : generate preprocessed C files on the fly of compilation\n\
	  GEN_ASSEMBLY=1 : generate assembly code on the fly of compilation\n\
	  NUM_THREAD=n : build with n threads\n\
	\n\
	\e[1m\e[32mCPMMON BUILD COMMAND\e[0m\n\
	  make clean_lib TARGET=<lib name>\t: clean only TARGET library\n\
	  make clean\t\t: delete out folder and MMI temp files\n\
	\n\
	\e[1m\e[32mDEP_CACHE COMMANDS\e[0m\n\
	  make makdep_cache_clean\t: clean dependency cache\n\n";
