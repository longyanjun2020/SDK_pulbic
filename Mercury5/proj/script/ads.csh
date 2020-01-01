#!/bin/csh

set OS_TYPE=`uname -o`

switch ($OS_TYPE)

  case GNU/Linux:
       ############################################
       # ADS 1.2 (Build 848) Environment Settings #
       ############################################
       echo " "
       echo "  Set License for ADS 1.2 (Build 848) Linux environment ..."
       echo " "
    
       setenv      LM_LICENSE_FILE /tools/asic-bb/licenses/licenses_arm.dat
       echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"

       echo " "
       echo "  Loading ADS 1.2 (Build 848) for Linux environment with use_ads ..."
       echo " "

       # ADS home directory:
       setenv ARMHOME /tools/asic-bb/arm/ads/1.2b848
       setenv ARMLIB $ARMHOME/common/lib
       setenv ARMINC $ARMHOME/common/include
       setenv ARMSD_DRIVER_DIR $ARMHOME/linux/bin
       setenv ARMDLL $ARMHOME/linux/bin
       setenv ARMCONF $ARMHOME/linux/bin
       setenv WUHOME $ARMHOME/windu
       setenv HHHOME $ARMHOME/windu/bin.linux_i32/hyperhelp
   
       if ( $?LD_LIBRARY_PATH == 0 )
       then
            setenv LD_LIBRARY_PATH /usr/dt/lib
       else
            setenv LD_LIBRARY_PATH /usr/dt/lib:${LD_LIBRARY_PATH}
       endif
       
       if ( ${LD_LIBRARY_PATH} !~ */usr/openwin/lib* )
       then
            setenv LD_LIBRARY_PATH /usr/openwin/lib:${LD_LIBRARY_PATH}
       endif
       
       setenv LD_LIBRARY_PATH ${ARMHOME}/windu/lib.linux_i32:${LD_LIBRARY_PATH}
       
       setenv LD_LIBRARY_PATH ${ARMHOME}/linux/bin:${LD_LIBRARY_PATH}
       
       setenv LD_LIBRARY_PATH /usr/lib:${LD_LIBRARY_PATH}
       set path=($ARMHOME/linux/bin $WUHOME/bin.linux_i32 $WUHOME/lib.linux_i32 $path)
   
       echo "      ARMHOME exported for ADS 1.2 (build 848) !"
       echo "      ARMHOME  = $ARMHOME"
       echo " "
       echo "  ADS 1.2 (build 848) environment loaded."
       echo " "
       breaksw

  case Cygwin:
       ############################################
       # ADS 1.2 (Build 848) Environment Settings #
       ############################################

       # Update ARMHOME if RVCT compiler already used
       if ( $?$BCKUP_ARMHOME_ADS != 0 )
       then
            setenv ARMHOME $BCKUP_ARMHOME_ADS
       endif
   
       echo " "
       echo "  Set License for ADS 1.2 (Build 848) Cygwin environment ..."
       echo " "
       setenv      LM_LICENSE_FILE $ARMHOME\\Licenses\\license.dat
       echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"
   
       echo " "
       echo "  Loading ADS 1.2 (Build 848) for Cygwin environment with use_ads ..."
       echo " "
   
       # ADS home directory:
       # Use current ADS 'ARMHOME'          environment variable set on windows
       # Use current ADS 'ARMLIB'           environment variable set on windows
       # Use current ADS 'ARMINC'           environment variable set on windows
   
       # Reconfigure ADS 'ARMDLL'           environment variable set on windows
       setenv ARMDLL $ARMHOME\\Bin
   
       # Configure   ADS 'ARMSD_DRIVER_DIR' environment variable 
       setenv ARMSD_DRIVER_DIR 
   
       # Reconfigure ADS 'ARMCONF'          environnment variable set on windows
       setenv ARMCONF $ARMHOME\\Bin
   
       setenv WUHOME 
       setenv HHHOME
    
       echo "      ARMHOME exported for ADS 1.2 (build 848) !"
       echo "      ARMHOME path => $ARMHOME"
       echo " "
       echo "  ADS 1.2 (build 848) environment loaded."
       echo " "
       breaksw

endsw
