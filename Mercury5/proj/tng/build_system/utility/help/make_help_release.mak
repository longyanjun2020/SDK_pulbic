
#-------------------------------------------------------------------------------
# Help for customer
#-------------------------------------------------------------------------------
help:
	@echo -ne "\e[1m\e[32mRELEASE BUILD COMMAND\e[0m\n\
	  make release_build\t\t: build command\n\
	  make release_speed\t\t: w/o step info\n\
	  make release_speed_cus0\t: build w/o step info\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make release_ibuild\t\t: ibuild command\n\
	  make release_DZbuild\t\t: DZbuild command\n\
	  make release_fast\t\t: faster local build command\e[1m\e[36m(only LangPack0000)\e[0m\n\
	  make release_e2p\t\t: generate e2p files\n\
	  make release_log\t\t: show debug message\n\
	  make release_final\t\t: post build(link, e2p, tmt)\n\
	  make release_log\t\t: check build error log\n\
	  ./release_pmake.sh lib_1 lib_2..lib_n\t: only build target library\n\
	  make release_drv\t\t: only build driver libraries\n\
	  make release_sys\t\t: only build system libraries\n\
	  make release_mdl\t\t: only build mdl libraries\n\
	  make release_3rd\t\t: only build 3rd party libraries\n\
	  make release_mmi\t\t: only build MMI libraries\n\
	\n\
	\e[1m\e[32mMMI\e[0m\n\
	  make release_mmi\t\t: build MMI libraries\n\
	\t(app, core, common, widget, res) and link\n\
	  make release_mmi_app\t\t: build MMI app library and link\n\
	  make release_mmi_core\t\t: build MMI core library and link\n\
	  make release_mmi_common\t: build MMI common library and link\n\
	  make release_mmi_widget\t: build MMI widget ibrary and link\n\
	  make release_mmi_res\t\t: build MMI resource(XRG) and link\n\
	\n";
