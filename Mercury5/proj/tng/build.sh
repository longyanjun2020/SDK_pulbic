#!/bin/bash

sync

echo generate customer settings by profile
cd tng
if ["$OSTYPE" == "msys"]
    .//CodeReleaseMaker.exe //C CONFIG //F ..//sc//customer//default//profile//CustomerSettings.xml //O ..//sc//customer//default//profile//CustomerSettings.dat
then
    ./CodeReleaseMaker.exe /C CONFIG /F ../sc/customer/default/profile/CustomerSettings.xml /O ../sc/customer/default/profile/CustomerSettings.dat
fi
cd -

echo make release_build
make release_build 2>&1 1>&make_release_build.log

./buildM2Sensor.sh

echo finish
