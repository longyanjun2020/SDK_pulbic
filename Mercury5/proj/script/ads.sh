#!/bin/sh

case `uname` in

  Linux*)
    ############################################
    # ADS 1.2 (Build 848) Environment Settings #
    ############################################
    echo " "
    echo "  Set License for ADS 1.2 (Build 848) Linux environment ..."
    echo " "
    export      LM_LICENSE_FILE=/tools/asic-bb/licenses/licenses_arm.dat
    echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"

    echo " "
    echo "  Loading ADS 1.2 (Build 848) for Linux environment with use_ads ..."
    echo " "

    # ADS home directory:
    export ARMHOME=/tools/asic-bb/arm/ads/1.2b848
    export ARMLIB=$ARMHOME/common/lib
    export ARMINC=$ARMHOME/common/include
    export ARMSD_DRIVER_DIR=$ARMHOME/linux/bin
    export ARMDLL=$ARMHOME/linux/bin
    export ARMCONF=$ARMHOME/linux/bin

    echo "      ARMHOME exported for ADS 1.2 (build 848) !"
    echo "      ARMHOME  = $ARMHOME"
    echo " "
    echo "  ADS 1.2 (build 848) environment loaded."
    echo " " ;;

  *)
    ############################################
    # ADS 1.2 (Build 848) Environment Settings #
    ############################################

    # Update ARMHOME if RVCT compiler already used
    if [ ! -z $BCKUP_ARMHOME_ADS ]
    then
         export ARMHOME=$BCKUP_ARMHOME_ADS
    fi

    echo " "
    echo "  Set License for ADS 1.2 (Build 848) Cygwin environment ..."
    echo " "
    export      LM_LICENSE_FILE=$ARMHOME\\Licenses\\license.dat
    echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"

    echo " "
    echo "  Loading ADS 1.2 (Build 848) for Cygwin environment with use_ads ..."
    echo " "

    # ADS home directory:

    # Use current ADS 'ARMHOME'          environment variable set on windows
    # Use current ADS 'ARMLIB'           environment variable set on windows
    # Use current ADS 'ARMINC'           environment variable set on windows

    # Reconfigure ADS 'ARMDLL'           environment variable set on windows
    export ARMDLL=$ARMHOME\\Bin

    # Configure   ADS 'ARMSD_DRIVER_DIR' environment variable 
    export ARMSD_DRIVER_DIR= 

    # Reconfigure ADS 'ARMCONF'          environnment variable set on windows
    export ARMCONF=$ARMHOME\\Bin
    
    echo "      ARMHOME exported for ADS 1.2 (build 848) !"
    echo "      ARMHOME path => $ARMHOME"
    echo " "
    echo "  ADS 1.2 (build 848) environment loaded."
    echo " " ;;

esac
