# Global Configuration Parameters for RADVISION build system.

# This is example for MVISTA 
# The example is used for MVISTA running on PowerPC board and for 
# for MVista running on generic PC.
# We suppose that PPC is running MVista 3.1 while generic PC is used with
# 4.X version of MVista.

# Configuration Parameters ---------------------------------------------
# BUILD_TYE:= debug/release (build with debugging info or optimized)
BUILD_TYPE := debug

# Host Environment -----------------------------------------------------
# HOST_OS := osname (name of supported os)
HOST_OS := linux

# COMPILER_TOOL := toolname (name of supported compiler tool)
COMPILER_TOOL := gnu

# COMPILER_TOOL_VERSION := toolversion (name of supported compiler tool version)
COMPILER_TOOL_VERSION := 2.9
# ----------------------------------------------------------------------

# Target information ---------------------------------------------------
# TARGET_OS := osname (name of supported os)
TARGET_OS := linux

ifeq ($(VER), 5.0)
# TARGET_OS_VERSION := osversion (name of supported os version)
TARGET_OS_VERSION := MontaVista_5.0

#TARGET_CPU_FAMILY := family (family id used to identify compiler)
TARGET_CPU_FAMILY := pentium4

#TARGET_CPU_HEADERS := VALUE (value used to find and/or used by OS/compiler header files)
TARGET_CPU_HEADERS := pentium4

# TARGET_CPU_ID := id (cpu identifier passed to the compiler)
TARGET_CPU_ID := pentium4

#TARGET_CPU_ENDIAN := little/big (mode of CPU)
TARGET_CPU_ENDIAN := little

else 
ifeq ($(VER), 4.0)

#ifeq ($(VER), 4.0)
# TARGET_OS_VERSION := osversion (name of supported os version)
TARGET_OS_VERSION := MontaVista_4.0

#TARGET_CPU_FAMILY := family (family id used to identify compiler)
TARGET_CPU_FAMILY := 586

#TARGET_CPU_HEADERS := VALUE (value used to find and/or used by OS/compiler header files)
TARGET_CPU_HEADERS := 586

# TARGET_CPU_ID := id (cpu identifier passed to the compiler)
TARGET_CPU_ID := 586

#TARGET_CPU_ENDIAN := little/big (mode of CPU)
TARGET_CPU_ENDIAN := little

else
# TARGET_OS_VERSION := osversion (name of supported os version)
TARGET_OS_VERSION := MontaVista_3.1

#TARGET_CPU_FAMILY := family (family id used to identify compiler)
TARGET_CPU_FAMILY := ppc_7xx

#TARGET_CPU_HEADERS := VALUE (value used to find and/or used by OS/compiler header files)
TARGET_CPU_HEADERS := ppc_7xx

# TARGET_CPU_ID := id (cpu identifier passed to the compiler)
TARGET_CPU_ID := ppc_7xx

#TARGET_CPU_ENDIAN := little/big (mode of CPU)
TARGET_CPU_ENDIAN := big

endif
endif


#TARGET_CPU_BITS := 32/64 (bit model to use)
TARGET_CPU_BITS := 32
# ----------------------------------------------------------------------

# OpenSSL folders variables --------------------------------------------

# Defines the OpenSSL include folder, if it was not defined in environment
ifeq ($(OPENSSL_INC),)
OPENSSL_INC := /opt/montavista/pro/devkit/ppc/7xx/target/usr/local/ssl/openssl
endif

# Defines the OpenSSL libraries folder, if it was not defined in environment
ifeq ($(OPENSSL_LIB),)
OPENSSL_LIB := /opt/montavista/pro/devkit/ppc/7xx/target/usr/local/ssl/lib
endif
# ----------------------------------------------------------------------

# Additional information -----------------------------------------------
# Special compiler flags
CFLAGS :=

# Special linker flags
LDFLAGS :=
# ----------------------------------------------------------------------


# Install information --------------------------------------------------
# Destination root directory for install command (use '/', NOT '\" on Win32)
INSTALL_ROOT := /usr/local/rvcommon
# ----------------------------------------------------------------------
