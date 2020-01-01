#!/bin/sh

case `uname` in

  Linux*)
#   export SCRIPT_DIR=/software/tools/delivery/script ;;
    export SCRIPT_DIR=/software/int/adc/tools/script ;;

  *)
    export G1_VER=e00_011MFCMUX.g1
    export SCRIPT_DIR=$HOME/$G1_VER/script
esac

# aliases for SGT
alias use_ads='source $SCRIPT_DIR/ads.sh'
alias use_rvct='source $SCRIPT_DIR/rvct.sh'

case `uname` in
  Linux*)
    echo " Type use_ads  to load ADS  1.2 environment"
    echo " Type use_rvct to load RVCT 2.2 environment"
    echo " "
    echo " "
    ;;

  *)
    # Load compiler variable by default
    if [ ! -z $ARMROOT ]
    then
       if [ ! -z $ARMHOME ]
       then
          echo " Type use_ads  to load ADS  1.2 environment"
          echo " Type use_rvct to load RVCT 2.2 environment"
          echo " "
          echo " "
          echo " ==============================================="
          echo "  Set ADS 1.2 as default ARM Compiler path      "
          echo " ==============================================="
          echo " "
          echo " load ADS 1.2 compiler by default ..."
          echo " "
          use_ads
       else
          echo " Type use_rvct to load RVCT 2.2 environment"
          echo " "
          echo " "
          echo " ==============================================="
          echo "  Set RVCT 2.2 as default ARM Compiler path     "
          echo " ==============================================="
          echo " "
          echo " load RVCT 2.2 compiler by default ..."
          echo " "
          use_rvct
       fi
    else
       if [ ! -z $ARMHOME ]
       then
          echo " Type use_ads  to load ADS  1.2 environment"
          echo " "
          echo " "
          echo " ==============================================="
          echo "  Set ADS 1.2 as default ARM Compiler path      "
          echo " ==============================================="
          echo " "
          echo " load ADS 1.2 compiler by default ..."
          echo " "
          use_ads
       else
          echo " "
          echo " No ARM compiler detected !!!!!!!!!!"
          echo " "
       fi
    fi
    ;;

esac
