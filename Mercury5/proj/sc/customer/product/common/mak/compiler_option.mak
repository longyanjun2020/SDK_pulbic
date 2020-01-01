
#===============================================================================
#    v2751_t12 -> Options (Used for make_lib .... -d COMPILER=v2751_12)
#===============================================================================
ifeq ($(COMPILER_VERSION),ADSV12)

  # b : remove warning : Warning: C2485W: ANSI C forbids bit field type
  #     In strict ANSI C, the only types allowed for a bit field are int, signed int and unsigned int.
  #     in order to avoid big-little endian problem we suppress the warning

  C_WARNING_OPTIONS +=b+adefgiklmopvx

  CC=$(PLTM_CC)

  C_OPTIONS   +=            \
    -apcs //noswst//interwork \
    -Ono_data_reorder       \
    -Ecz                    \
    -cpu 5TEJ               \
    -g                      \
    -fpu softvfp            \
    -W$(C_WARNING_OPTIONS)  \
    -O2

ifeq "$(DISABLE_FEEDBACK)" "1"
  C_OPTIONS += \
	--no_autoinline
endif

ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)

  ASM_OPTIONS +=                                   \
    -PD "__DSP_39MHZ__ SETL {FALSE}"               \
    -PD "__ABNORMAL_RST_DETECT__ SETL {FALSE}"     \
    -PD "__RTK_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
    -PD "__HW_WATCHDOG_FIQ__ SETL {TRUE}" \
    -PD "__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
    -PD "__SEPARATE_INTERRUPT_API__ SETL {TRUE}" \
    -apcs //noswst//interwork                        \
    -cpu 5TEJ                                      \
    -g                                             \
    -fpu softvfp

ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_DIAGNOSE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    -PD "__RTK_DIAGNOSE_ENHANCE__ SETL {TRUE}"
endif

else

  ASM_OPTIONS +=                                   \
    -PD "__DSP_39MHZ__ SETL {FALSE}"               \
    -PD "__ABNORMAL_RST_DETECT__ SETL {FALSE}"     \
    -apcs //noswst//interwork                        \
    -cpu 5TEJ                                      \
    -g                                             \
    -fpu softvfp

endif

  ifeq ($(filter __RTK_STACK_DIAGNOSE__ ,$(PP_OPT_COMMON)),__RTK_STACK_DIAGNOSE__)
  ASM_OPTIONS +=                                   \
    --PD "__RTK_STACK_DIAGNOSE__ SETL {TRUE}"
  endif

  ifeq ($(filter __RTK_PROFILE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_PROFILE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --PD "__RTK_PROFILE_ENHANCE__ SETL {TRUE}"
  endif

  ifeq ($(filter __EMI_PAD_PWD__ ,$(PP_OPT_COMMON)),__EMI_PAD_PWD__)
  ASM_OPTIONS +=                                   \
    -PD "__EMI_PAD_PWD__ SETL {TRUE}"
  endif

    ifneq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
    ASM_OPTIONS += -PD "__NOR_BOOT__ SETL {TRUE}"
    endif
  ifeq ($(COMPILER),ADSV12_arm)

    # C run-time support adaptation for NGOS (NexGenOS, which supports NGIP and NGPPP)
    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_ADS        \
      NG_CODE_ARM

  endif

  ifeq ($(COMPILER),ADSV12_thumb)

    # C run-time support adaptation for NGOS (NexGenOS, which supports NGIP and NGPPP)
    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_ADS        \
      NG_CODE_THUMB

    CC=$(PLTM_THUMB_CC)

ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)

    ASM_OPTIONS +=  \
      -PD "__THUMB__ SETL {TRUE}" \
      -PD "__LOGIC_ANALYSER__ SETL {FALSE}"\
      -PD "__SOFTWARE_WATCHDOG__ SETL {TRUE}"\
      -PD "__RTK_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
      -PD "__HW_WATCHDOG_FIQ__ SETL {TRUE}" \
      -PD "__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
      -PD "__SEPARATE_INTERRUPT_API__ SETL {TRUE}"

ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_DIAGNOSE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    -PD "__RTK_DIAGNOSE_ENHANCE__ SETL {TRUE}"
endif

else

        ASM_OPTIONS +=  \
          -PD "__THUMB__ SETL {TRUE}" \
          --pd "__LOGIC_ANALYSER__ SETL {FALSE}"\

endif

  ifeq ($(filter __RTK_STACK_DIAGNOSE__ ,$(PP_OPT_COMMON)),__RTK_STACK_DIAGNOSE__)
  ASM_OPTIONS +=                                   \
    --PD "__RTK_STACK_DIAGNOSE__ SETL {TRUE}"
  endif

  ifeq ($(filter __RTK_PROFILE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_PROFILE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --PD "__RTK_PROFILE_ENHANCE__ SETL {TRUE}"
  endif

    ifeq ($(filter __EMI_PAD_PWD__ ,$(PP_OPT_COMMON)),__EMI_PAD_PWD__)
    ASM_OPTIONS +=                                   \
      -PD "__EMI_PAD_PWD__ SETL {TRUE}"
    endif

     ifneq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
     ASM_OPTIONS += -PD "__NOR_BOOT__ SETL {TRUE}"
     endif

  endif

endif  #($(COMPILER_VERSION),ADSV12)

ifeq ($(COMPILER_VERSION),RVCTV22)
  # 1     : last line of file ends without a new line
  # 161   : unrecognized #pragma
  # 1294  : Old-style function <function>
  # 1295  : Deprecated declaration <xxxx> - give arg types
  # 1296  : extended constant initialiser used
  # 2084  : support for --apcs /adsabi is deprecated

  WARNING_OPTIONS = --diag_suppress 1,161,1294,1295,1296,2084

  CC=$(PLTM_CC)


  C_OPTIONS   +=                \
    --apcs //noswst//interwork    \
    --cpu 5TEJ                  \
    --fpu softvfp               \
    --no_debug_macros           \
    --loose_implicit_cast       \
    --min_array_alignment=4     \
    -O2 --c90                   \
#    $(WARNING_OPTIONS)

ifneq (FALSE, $(strip $(SOURCE_LEVEL_DEBUG)))
ifneq (1, $(strip $(NO_DEBUG)))
  C_OPTIONS += --debug
endif
endif

ifeq "$(DISABLE_FEEDBACK)" "1"
  C_OPTIONS += \
	--no_autoinline
endif

ifeq "$(OSTYPE)" "Win32"
  C_OPTIONS+=  \
    -D__VER_INFO_CUS__=\"$(VERSION_CUS)\" \
    -DSYS_PHY_RAM_SIZE_SETTING=\"$(SYS_PHY_RAM_SIZE_SETTING)\" \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=\"$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING)\" \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=\"$(DRV_EMBEDED_SPI_FLASH_SIZE)\"

  ifeq ($(call FILE_EXISTED, $(COMMON)version.mak), TRUE)
  C_OPTIONS   +=                \
    -D__VER_INFO__=\"$(VERSION)\"
  endif
else
  C_OPTIONS   +=                \
    -D__VER_INFO_CUS__="$(VERSION_CUS)"  \
    -DSYS_PHY_RAM_SIZE_SETTING=$(SYS_PHY_RAM_SIZE_SETTING)  \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING) \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=$(DRV_EMBEDED_SPI_FLASH_SIZE)

  ifeq ($(call FILE_EXISTED, $(COMMON)version.mak), TRUE)
  C_OPTIONS+=  \
    -D__VER_INFO__="$(VERSION)"
  endif
endif

ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)

  ASM_OPTIONS +=                                    \
    --pd "__DSP_39MHZ__  SETL {FALSE}"              \
    --pd "__ABNORMAL_RST_DETECT__  SETL {FALSE}"    \
    --pd "__RTK_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}"     \
    --pd "__HW_WATCHDOG_FIQ__ SETL {TRUE}" \
    --pd "__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
    --pd "__SEPARATE_INTERRUPT_API__ SETL {TRUE}" \
    --apcs //noswst//interwork                        \
    --cpu 5TEJ                                      \
    --fpu softvfp

ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_DIAGNOSE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_DIAGNOSE_ENHANCE__ SETL {TRUE}"
endif

else

    ASM_OPTIONS +=                                    \
      --pd "__DSP_39MHZ__  SETL {FALSE}"              \
      --pd "__ABNORMAL_RST_DETECT__  SETL {FALSE}"    \
      --apcs //noswst//interwork                        \
      --cpu 5TEJ                                      \
      --fpu softvfp                                      \
      --debug

endif

ifneq (FALSE, $(strip $(SOURCE_LEVEL_DEBUG)))
ifneq (1, $(strip $(NO_DEBUG)))
  ASM_OPTIONS += --debug
endif
endif

  ifeq ($(filter __RTK_STACK_DIAGNOSE__ ,$(PP_OPT_COMMON)),__RTK_STACK_DIAGNOSE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_STACK_DIAGNOSE__ SETL {TRUE}"
  endif

  ifeq ($(filter __RTK_PROFILE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_PROFILE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_PROFILE_ENHANCE__ SETL {TRUE}"
  endif

  ifeq ($(filter __EMI_PAD_PWD__ ,$(PP_OPT_COMMON)),__EMI_PAD_PWD__)
  ASM_OPTIONS +=                                   \
    --pd "__EMI_PAD_PWD__ SETL {TRUE}"
  endif

    ifneq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
    ASM_OPTIONS += --pd "__NOR_BOOT__ SETL {TRUE}"
    endif

  ifeq ($(COMPILER),RVCTV22_arm)

    # C run-time support adaptation for NGOS (NexGenOS, which supports NGIP and NGPPP)
    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_RVCT       \
      NG_CODE_ARM

  endif

  ifeq ($(COMPILER),RVCTV22_thumb)

    # C run-time support adaptation for NGOS (NexGenOS, which supports NGIP and NGPPP)
    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_RVCT       \
      NG_CODE_THUMB

    C_OPTIONS   +=  \
      --thumb

ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)

    ASM_OPTIONS +=  \
      --pd "__THUMB__ SETL {TRUE}" \
      --pd "__LOGIC_ANALYSER__ SETL {FALSE}"\
      --pd "__SOFTWARE_WATCHDOG__ SETL {TRUE}"\
      --pd "__RTK_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}"     \
      --pd "__HW_WATCHDOG_FIQ__ SETL {TRUE}" \
      --pd "__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__ SETL {TRUE}" \
      --pd "__SEPARATE_INTERRUPT_API__ SETL {TRUE}"

ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_DIAGNOSE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_DIAGNOSE_ENHANCE__ SETL {TRUE}"
endif

else

        ASM_OPTIONS +=  \
          --pd "__I_SW__ SETL {TRUE}" \
          --pd "__THUMB__ SETL {TRUE}" \
          --pd "__ARM_POWER_OFF__ SETL {TRUE}"\
          --pd "__LOGIC_ANALYSER__ SETL {FALSE}"\

endif

  ifeq ($(filter __RTK_STACK_DIAGNOSE__ ,$(PP_OPT_COMMON)),__RTK_STACK_DIAGNOSE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_STACK_DIAGNOSE__ SETL {TRUE}"
  endif

  ifeq ($(filter __RTK_PROFILE_ENHANCE__ ,$(PP_OPT_COMMON)),__RTK_PROFILE_ENHANCE__)
  ASM_OPTIONS +=                                   \
    --pd "__RTK_PROFILE_ENHANCE__ SETL {TRUE}"
  endif

    ifeq ($(filter __EMI_PAD_PWD__ ,$(PP_OPT_COMMON)),__EMI_PAD_PWD__)
    ASM_OPTIONS +=                                   \
      --pd "__EMI_PAD_PWD__ SETL {TRUE}"
    endif

    ifneq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
    ASM_OPTIONS += --pd "__NOR_BOOT__ SETL {TRUE}"
    endif

  ifeq ($(filter __AUTO_CPU_SPEED__ ,$(PP_OPT_COMMON)),__AUTO_CPU_SPEED__)
  ASM_OPTIONS += \
    --pd "__AUTO_CPU_SPEED__ SETL {TRUE}"
  endif
  endif

endif  #($(COMPILER_VERSION),RVCTV22)

ifeq ($(COMPILER_VERSION),AEONGCC)

CC = $(PLTM_CC)

CXX_OPTIONS += \
    -fno-threadsafe-statics\
    -fno-implicit-templates\
    -fno-rtti\
    -fno-exceptions

C_OPTIONS += \
    -Wall\
    -ggdb\
    -O2\
    -Os\
    -malign32\
    -mhard-float1\
    -fomit-frame-pointer\
    -EL\
    -fno-strict-aliasing\
    -ffunction-sections\
    -fdata-sections\
    -fshort-wchar\
    -march=aeonR2\
    -mredzone-size=4\
    -mstruct-size-boundary=1\
    -mlong-calls\
    -fno-zero-initialized-in-bss

C_OPTIONS += \
    -D__VER_INFO__="$(VERSION)" \
    -D__VER_INFO_MMP__="$(M2_VER)" \
    -D__VER_INFO_CUS__="$(VERSION_CUS)" \
    -D__CUST_ID__="$(CUST_ID)" \
    -D__PRODUCT_ID__="$(PRODUCT_ID)" \
    -D__LAN_ID__="$(LAN_ID)" \
    -D__SW_MAJ_VER__="$(SW_MAJ_VER)" \
    -D__SW_MIN_VER__="$(SW_MIN_VER)"  \
    -DSYS_PHY_RAM_SIZE_SETTING=$(SYS_PHY_RAM_SIZE_SETTING)  \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING) \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=$(DRV_EMBEDED_SPI_FLASH_SIZE)

ifeq ($(filter __G1_GDB_RSP__, $(PP_OPT_COMMON)), __G1_GDB_RSP__)
C_OPTIONS += \
	-D__G1_GDB_RSP__
endif

ifeq ($(filter __DALVIK__, $(PP_OPT_COMMON)), __DALVIK__)
ASM_OPTIONS += -D__DALVIK__
endif

ifeq ($(filter __CONFIG_ALLOW_UNALIGNED_MEM_ACCESS__, $(PP_OPT_COMMON)), __CONFIG_ALLOW_UNALIGNED_MEM_ACCESS__)
ASM_OPTIONS += -D__CONFIG_ALLOW_UNALIGNED_MEM_ACCESS__
endif

ifeq ($(filter __USER_LEVEL_PTHREAD__, $(PP_OPT_COMMON)), __USER_LEVEL_PTHREAD__)
ASM_OPTIONS += -D__USER_LEVEL_PTHREAD__
endif

ifeq ($(filter __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__)
ASM_OPTIONS += -D__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
endif

ASM_OPTIONS += -c -D__ASSEMBLY__ $(C_OPTIONS)

endif  #($(COMPILER_VERSION),AEONGCC)

ifeq ($(COMPILER_VERSION),MIPSGCC)

    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_RVCT       \
      NG_CODE_THUMB

CC = $(PLTM_CC)

C_OPTIONS += \
    -Wall\
    -Wno-packed\
    -Wcast-align\
    -ggdb\
    -Os\
    -fsee\
    -G0\
    -fomit-frame-pointer\
    -EL\
    -ffunction-sections\
    -fdata-sections\
    -fshort-wchar\
    -fshort-enums\
    -fira-algorithm=priority\
    -mmicromips -Wl,--relax


C_OPTIONS += \
    -D__VER_INFO__="$(VERSION)" \
    -D__VER_INFO_MMP__="$(M2_VER)" \
    -D__VER_INFO_CUS__="$(VERSION_CUS)" \
    -D__CUST_ID__="$(CUST_ID)" \
    -D__PRODUCT_ID__="$(PRODUCT_ID)" \
    -D__LAN_ID__="$(LAN_ID)" \
    -D__SW_MAJ_VER__="$(SW_MAJ_VER)" \
    -D__SW_MIN_VER__="$(SW_MIN_VER)"  \
    -DSYS_PHY_RAM_SIZE_SETTING=$(SYS_PHY_RAM_SIZE_SETTING)  \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING) \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=$(DRV_EMBEDED_SPI_FLASH_SIZE)


ASM_OPTIONS += -c -D__ASSEMBLY__ $(C_OPTIONS)

endif  #($(COMPILER_VERSION),MIPSGCC)

ifeq ($(COMPILER_VERSION),X86LINUXGCC)

    PP_OPT_COMMON +=     \
      __NEW_BACK_TRACE__ \
      NG_COMP_RVCT       \
      NG_CODE_THUMB

CC = $(PLTM_CC)

C_OPTIONS += \
	-fshort-wchar \
	-Uunix -U__unix -U__unix__ -Ulinux -U__linux -U__linux__ -U__gnu_linux__ \

# build-in option for makedepend
MKDEP_FLAGS = \
	-D__i686__ -D__GNUC__=4 -D__cplusplus


C_OPTIONS += \
    -D__VER_INFO__="$(VERSION)" \
    -D__VER_INFO_MMP__="$(M2_VER)" \
    -D__VER_INFO_CUS__="$(VERSION_CUS)" \
    -D__CUST_ID__="$(CUST_ID)" \
    -D__PRODUCT_ID__="$(PRODUCT_ID)" \
    -D__LAN_ID__="$(LAN_ID)" \
    -D__SW_MAJ_VER__="$(SW_MAJ_VER)" \
    -D__SW_MIN_VER__="$(SW_MIN_VER)"  \
    -DSYS_PHY_RAM_SIZE_SETTING=$(SYS_PHY_RAM_SIZE_SETTING)  \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING) \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=$(DRV_EMBEDED_SPI_FLASH_SIZE)

ASM_OPTIONS += -c -D__ASSEMBLY__ $(C_OPTIONS)

endif  #($(COMPILER_VERSION),X86LINUXGCC)



ifeq ($(COMPILER_VERSION),ARMGCC)

CC = $(PLTM_CC)

# albert.liao modified 2017/11/01
ifeq ($(COMPILER_EXECUTABLE),arm-linux-gnueabihf-gcc)
#C_OPTIONS += -Uunix -U__unix -U__unix__ -Ulinux -U__linux -U__linux__ -U__gnu_linux__
endif

C_OPTIONS += \
    -Wall\
    -Wno-packed\
    -ggdb\
    -O2\
    -Os\
    -fomit-frame-pointer\
    -ffunction-sections\
    -fdata-sections\
	-march=armv7-a\
	-falign-functions=1\
	-falign-jumps=1\
	-falign-labels=1\
	-falign-loops=1\
	-mfpu=vfp3\
	-gdwarf-2\
#	-g\
#	-fno-inline\
	-gstrict-dwarf

#    -Wcast-align\
#	-Wshadow\
#	-Wwrite-strings\
#	-Wundef\
#	-Wstrict-prototypes\
#	-Wunused\
#	-Wunused-parameter\
#	-Wunused-function\
#	-Wunused-value\
#	-Wdeclaration-after-statement\
#	-Wold-style-definition\
#	-fno-builtin-strlen\
#	-finline-limit=0\
#	-fomit-frame-pointer\
#	-ffunction-sections\
#	-fdata-sections\
#	-fno-guess-branch-probability\
#	-funsigned-char\
#	-static-libgcc\
#   -nostdlib\
#    -fshort-wchar\

C_OPTIONS += \
    -D__VER_INFO__="$(VERSION)" \
    -D__VER_INFO_MMP__="$(M2_VER)" \
    -D__VER_INFO_CUS__="$(VERSION_CUS)" \
    -D__CUST_ID__="$(CUST_ID)" \
    -D__PRODUCT_ID__="$(PRODUCT_ID)" \
    -D__LAN_ID__="$(LAN_ID)" \
    -D__SW_MAJ_VER__="$(SW_MAJ_VER)" \
    -D__SW_MIN_VER__="$(SW_MIN_VER)"  \
    -DSYS_PHY_RAM_SIZE_SETTING=$(SYS_PHY_RAM_SIZE_SETTING)  \
    -DMAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING=$(MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING) \
    -DDRV_EMBEDED_SPI_FLASH_SIZE=$(DRV_EMBEDED_SPI_FLASH_SIZE) \
    -D__ARM_NEON__\

MKDEP_FLAGS = \
	-D__arm__ -D__arm
#    -D__cplusplus

C_OPTIONS += $(MKDEP_FLAGS)

ifeq ($(filter __HW_WATCHDOG_FIQ__, $(PP_OPT_COMMON)), __HW_WATCHDOG_FIQ__)
ASM_OPTIONS += -D__HW_WATCHDOG_FIQ__
endif

ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
ASM_OPTIONS += -D__RTK_DIAGNOSE_ENHANCE__
endif
ifeq ($(filter __MMU_STACK_PROTECTION__, $(PP_OPT_COMMON)), __MMU_STACK_PROTECTION__)
ASM_OPTIONS += -D__MMU_STACK_PROTECTION__
endif
ifeq ($(filter __RTK_STACK_DIAGNOSE__, $(PP_OPT_COMMON)), __RTK_STACK_DIAGNOSE__)
ASM_OPTIONS += -D__RTK_STACK_DIAGNOSE__
endif
ifeq ($(filter __SEPARATE_INTERRUPT_API__, $(PP_OPT_COMMON)), __SEPARATE_INTERRUPT_API__)
ASM_OPTIONS += -D__SEPARATE_INTERRUPT_API__
endif
ifeq ($(filter __SEPARATE_INTERRUPT_API_PROFILE__, $(PP_OPT_COMMON)), __SEPARATE_INTERRUPT_API_PROFILE__)
ASM_OPTIONS += -D__SEPARATE_INTERRUPT_API_PROFILE__
endif
ifeq ($(filter __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__)
ASM_OPTIONS += -D__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
endif
ifeq ($(filter __RTK_PROFILE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_PROFILE_ENHANCE__)
ASM_OPTIONS += -D__RTK_PROFILE_ENHANCE__
endif
ifeq ($(filter __REAL_TIME_PROBLEM_DIAGNOSE__, $(PP_OPT_COMMON)), __REAL_TIME_PROBLEM_DIAGNOSE__)
ASM_OPTIONS += -D__REAL_TIME_PROBLEM_DIAGNOSE__
endif
ifeq ($(filter __INTERRUPT_INTEGRITY_PROTECT__, $(PP_OPT_COMMON)), __INTERRUPT_INTEGRITY_PROTECT__)
ASM_OPTIONS += -D__INTERRUPT_INTEGRITY_PROTECT__
endif
ifeq ($(filter __SOFTWARE_WATCHDOG_PROFILE__, $(PP_OPT_COMMON)), __SOFTWARE_WATCHDOG_PROFILE__)
ASM_OPTIONS += -D__SOFTWARE_WATCHDOG_PROFILE__
endif
ifeq ($(filter __SOFTWARE_WATCHDOG__, $(PP_OPT_COMMON)), __SOFTWARE_WATCHDOG__)
ASM_OPTIONS += -D__SOFTWARE_WATCHDOG__
endif
ifeq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
ASM_OPTIONS += -D__I_SW__
endif
ifeq ($(filter __ISW_NORBOOT__, $(PP_OPT_COMMON)), __ISW_NORBOOT__)
ASM_OPTIONS += -D__ISW_NORBOOT__
endif
ifeq ($(filter __NOR_BOOT__, $(PP_OPT_COMMON)), __NOR_BOOT__)
ASM_OPTIONS += -D__NOR_BOOT__
endif
ifeq ($(filter __BRANCH_To_ZERO__, $(PP_OPT_COMMON)), __BRANCH_To_ZERO__)
ASM_OPTIONS += -D__BRANCH_To_ZERO__
endif
ASM_OPTIONS += -c -D__ASSEMBLY__ $(C_OPTIONS)

endif  #($(COMPILER_VERSION),ARMGCC)


#-------------------------------------------------------------------------------
# ** ASIC / FPGA / SIMU mode handling **
#-------------------------------------------------------------------------------
ifeq ($(filter __MAK_ARM__ ,$(PP_OPT_COMMON)),__MAK_ARM__)
ifneq ($(COMPILER_VERSION),ARMGCC)
ifeq ($(filter __FPGA__,$(PP_OPT_COMMON)),__FPGA__)
CONFIG_FPGA=y
export CONFIG_FPGA
ASM_OPTIONS += \
	--pd "__FPGA__ SETL {TRUE}" \
	--pd "__TARGET__ SETL {TRUE}"
else
ifeq ($(filter __TARGET__,$(PP_OPT_COMMON)),__TARGET__)
CONFIG_ASIC=y
export CONFIG_ASIC
ASM_OPTIONS += \
	--pd "__FPGA__ SETL {FALSE}" \
	--pd "__TARGET__ SETL {TRUE}"
else
CONFIG_SIMU=y
export CONFIG_SIMU
ASM_OPTIONS += \
	--pd "__FPGA__ SETL {FALSE}" \
	--pd "__TARGET__ SETL {FALSE}"
endif
endif
endif
endif

