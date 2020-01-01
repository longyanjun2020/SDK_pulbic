# override TMP environment variable for VisualStudio intermediate files
TMP = ./Debug

.PHONY: mmi_enum

#################
# $(call run-bat-cmd, CMD.bat)
# run CMD.bat with different commands in according to different environment
#################
run-bat-cmd=$(if $(findstring $(OSTYPE),msys),cmd //c $(1),$(1))

mmi_enum: $(TMP)
	-@$(call run-bat-cmd,build.bat)
	-@cp $(TMP)/*.txt $(OUT)

$(TMP):
	mkdir $(TMP)
