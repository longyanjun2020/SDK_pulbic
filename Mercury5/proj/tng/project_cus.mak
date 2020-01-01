TARGET = project_cus

.PHONY: project_cus

all: project_cus

PROJECT_CUS_FILE = project.CUS

include $(CONFIG_MAK)

project_cus:
	$(INSTALL) $(PATH_project_cus)/$(PROJECT_CUS_FILE) $(OUT)/$(PROJECT_CUS_FILE)
    