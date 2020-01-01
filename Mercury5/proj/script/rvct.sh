#!/bin/sh

case `uname` in

  Linux*)
    ############################################
    # RVCT2.2 [Build 616] Environment Settings #
    ############################################
    echo " "
    echo "  Set License for RVCT 2.2 (build 616) Linux environment ..."
    echo " "
    export      LM_LICENSE_FILE=/tools/asic-bb/licenses/licenses_arm.dat
    echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"

    echo " "
    echo "  Loading RVCT 2.2 (Build 616) for Linux environment with use_rvct ..."
    echo " "

    # ADS home directory:
    export ARMHOME=/software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Programs/2.2/503/linux-pentium
    export ARMLIB=/software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Data/2.2/503/lib
    export ARMINC=/software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Data/2.2/503//include/unix
    export ARMSD_DRIVER_DIR=$ARMHOME 
    export ARMDLL=$ARMHOME 
    export ARMCONF=$ARMHOME

    echo "      ARMHOME exported for RVCT 2.2 (build 616) !"
    echo "      ARMHOME path => $ARMHOME"
    echo " "
    echo "  RVCT 2.2 (build 616) environment loaded."
    echo " " ;;

  *)
    ############################################
    # RVCT2.2 [Build 616] Environment Settings #
    ############################################
    echo " "
    echo "  Set License for RVCT 2.2 (build 616) Cygwin environment ..."
    echo " "
    export      LM_LICENSE_FILE=$ARMROOT\\Licenses\\license.dat
    echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"

    echo " "
    echo "  Loading RVCT 2.2 (Build 616) for Cygwin environment with use_rvct ..."
    echo " "

    # RVCT home directory:
    # Reconfigure current 'ARMHOME'  environment variable set on windows for RVCT compiler 
    if [ -z $BCKUP_ARMHOME_ADS ]
    then
         export BCKUP_ARMHOME_ADS=$ARMHOME
    fi
    export ARMHOME=$RVCT22BIN

    # Reconfigure current 'ARMLIB'   environment variable set on windows for RVCT compiler 
    export ARMLIB=$RVCT22LIB

    # Reconfigure current 'ARMINC'   environment variable set on windows for RVCT compiler 
    export ARMINC=$RVCT22INC

    # Set current 'ARMSD_DRIVER_DIR' environment variable set on windows for RVCT compiler 
    export ARMSD_DRIVER_DIR=

    # Reconfigure current 'ARMDLL'   environment variable set on windows for RVCT compiler 
    export ARMDLL=$ARMHOME

    # Reconfigure current 'ARMCONF'  environment variable set on windows for RVCT compiler 
    export ARMCONF=$ARMHOME

    echo "      ARMROOT exported for RVCT 2.2 (build 616) !"
    echo "      ARMROOT path => $ARMROOT"
    echo " "
    echo "  RVCT 2.2 (build 616) environment loaded."
    echo " " ;;

esac
