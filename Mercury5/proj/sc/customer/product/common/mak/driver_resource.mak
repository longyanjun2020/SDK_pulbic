
#
#	Important :	This software is protected by Copyright and the information
#	            contained herein is confidential. Distribution, reproduction
#	            as well as exploitation and transmission of its	contents is
#	            not allowed except if expressly permitted. Infringments
#	            result in damage claims.
#
#	            Copyright (c) 2009 MStar

# ****************************************************************************

###FIRST_SENSOR_CUS_SRC is optional, assign at most "one single" file for First sensor cus
CC = gcc

FIRST_SENSOR_CUS_SRC=\

FIRST_SENSOR_CUS = $(FIRST_SENSOR_CUS_SRC:.dat="")

SENSOR_CUS_LIST 	= $(SENSOR_CUS_SRC:.dat="")

LCD_CUS_LIST 	= $(LCD_CUS_SRC:.dat="")

DISPTBL_CUS_LIST = $(DISP_CUS_SRC:.dat="")


PATH_sensor      = $(PATH_customer_product_sensor)
PATH_lcd_res     = $(PATH_customer_product_lcd)
PATH_disptbl     = $(PATH_customer_product_disptbl)

PATH_CUS +=\
	$(PATH_sensor)

DOWNLOAD_CHECKER = Download_Checker.exe
FLASH_TYPE =\


###file name of lcd, display and sensor table cus files
LCD_CUS_FILE = LT_LcdPack.cus
DISPTBL_CUS_FILE = DT_DispTblPack.cus
SENSOR_CUS_FILE = ST_SensorPack.cus
FIRST_SENSOR_CUS_PREFIX = ST_First_


