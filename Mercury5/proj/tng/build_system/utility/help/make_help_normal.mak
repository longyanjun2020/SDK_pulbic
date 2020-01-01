
#-------------------------------------------------------------------------------
# Help for internal user
#-------------------------------------------------------------------------------
help:
	@echo -ne "\e[1m\e[32mNORMAL BUILD COMMAND\e[0m\n\
	  make\t\t\t: normal build command\n\
	  make speed\t\t: build w/o step info\n\
	  make speed_cus0\t: build w/o showing compilation info\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make DZbuild\t\t: for dropzone, faster than speed\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make fast\t\t: faster local build command,\n\tfor RD use\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make ibuild\t\t: distributed build\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make dz_normal\t: build dz file\n\
	  make dz_redownload\t: build dz file(excluding z_factory.e2p)\n\
	  make log\t\t: show debug message of the build process\n\
	  ./pmake lib_1 lib_2..lib_n\t: only build target library\n\
	  make final\t\t: post build(link, e2p, tmt etc.)\n\
	  make final_fast\t: make final faster version\n\
	\tskip e2p table generating and checking\n\
	  make final_fast2\t: make final even faster version\n\
	\tskip e2p table generating, checking and exec gen_msg_id.pl\n\
	  make e2p\t\t: generate e2p files\n\
	  make e2p_fast\t\t: make e2p faster version\n\
	\tskip e2p table generating and checking\n\
	\n\
	\e[1m\e[32mBUILD LIBRARY SET ONLY\e[0m\n\
	  make libs_drv\t\t: only build drv libraries\n\
	  make libs_sys\t\t: only build sys libraries\n\
	  make libs_mdl\t\t: only build mdl libraries\n\
	  make libs_3rd\t\t: only build 3rd party libraries\n\
	  make libs_mmi\t\t: only build MMI libraries\n\
	\n\
	\e[1m\e[32mMMI\e[0m\n\
	  make mmi\t\t\t: build MMI libraries\n\
	\t(app, core, common, widget, res) and link\n\
	  make mmi_app\t\t\t: build MMI app library and link\n\
	  make mmi_core\t\t\t: build MMI core library and link\n\
	  make mmi_common\t\t: build MMI common library and link\n\
	  make mmi_widget\t\t: build MMI widget ibrary and link\n\
	  make mmi_res\t\t\t: build MMI resource(XRG) and link\n\
	  make mmi_cus\t\t\t: call XRG to generate MMI resource\n\
	  make mmi_cus0\t\t\t: Generate 1 language package\n\
	\n\
	\e[1m\e[32mCOMMANDS for MSC/MSZ build\e[0m\n\
	  make quick\t\t\t: normal build command(auto-detect QUICK)\n\
	  make quick_fast\t\t: normal build command(auto-detect QUICK)\n\
	  make quick_ap\t\t\t: quick mode skipping prepared libraries\n\
	  make quick_ap_fast\t\t: fast quick command\n\
	  make ibuild_mst\t\t: distributed build\n\
	  make ibuild_msz\t\t: incredibuild for MST.\n\
	  make final QUICK=MSC/MST/MSZ\t: post build(link, e2p, tmt)\n\
	  make clean\t\t\t: clean target build image\n\
	  ./pmake lib_1 lib_2..lib_n\t: only build target lib\n\
	\n";
