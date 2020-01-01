# Upload and Burn the Firmware           {#page_cgi18}
[TOC]

# 18. Upload and Burn the Firmware #     {#CGI18}

## Prerequists ##                        {#CGI18_Pre}
This section describes how the things need to be prepared before using Firmware Update feature. However, due to these are all included in SDK, all these could be skipped and follow the steps in the next section directly. Come back here if something goes wrong.

### Code Modules ###
`FWupload_cgi.c` is included and built in your project. This module handles FWUPDATE related CGI commands.

`StateNetFwUpdateMod.c` is included and built in your project. This module provides an extra UI state that dedicates the camera for firmware updating.

`Netapp.c` is always included. `Handle_UIMode()` sets the UI mode into dedicated `UI_NET_FWUPDATE_STATE` mode. Make sure the message and handled. Now it is probably in `AHC_Wireless.c` which located in UI directory. Each project could have its own related UI. For example, project 1 turn off LED after burning is finished and project 2 beeps twice with a buzzer.


## CGI Steps ##                        {#CGI18_Steps}

### Step 1: Check firmware version

```
    cgi-bin/Config.cgi?action=get&property=Camera.Menu.Fwversion
    response:0
             OK
             Camera.Memu.FWversion=253
```
  This step verify current firmware version so that the client side APP could ignore the rest steps if the device FW is newer.


### Step 2: Make Camera into Update Firmware mode

````
    cgi-bin/Config.cgi?action=set&property=UIMode&value=UPDATEFW
    response: 0
              OK
````
  If camera is recording or capturing in Timelapse, the response will be ` 709\r\n???\r\n `
  If FWUpload feature is not implemented in current firmware, it also responses ` 709\r\n???\r\n `

### Step 3: Upload firmware

```
  curl --form "fileupload=@.\SD_CarDV.bin" http://192.72.1.1/cgi-bin/FWupload.cgi
     POST /cgi-bin/FWupload.cgi HTTP/1.1\r\n
     User-Agent: curl/7.38.0\r\n
     Host: 192.72.1.1\r\n
     Accept: */*\r\n
     Content-Length:8388850 
     Content-Type: multipart/form-data; boundary=------------------59b6c38ead18\r\n
     \r\n
     ------------------59b6c38ead18\r\n
     Content-Disposition: form-data; name="fileupload"; filename="SD_CarDV.bin"\r\n
     Content-Type: application/octet-stream\r\n\r\n
           <......FIRMWARE......>
     \r\n------------------59b6c38ead18\r\n
```

  Alternative:
````
     curl -F "fileupload=@.\SD_CarDV.bin;filename=MyFw.bin" http://192.72.1.1/cgi-bin/FWupload.cgi
     -F means --form
````
  Filename could be assigned for your project.


### Step 4: Start to flash

```
    cgi-bin/FWupload.cgi?action=flash
    response: 0
              OK
```

  If any error, the following would be replied.
```
    <html><body><h1>503 Service Unavailable</h1></body></html>
```
  The firmware is not there. Or the device state is not ready for FWUpload, such as recording, or time-lapse capturing.
  If the unlock file, such as "CanUploadFw.ini", is not there, there would be no error directly reply to this command.

### Step 5: Flash Finished

  UDP broadcast (IP: 255.255.255.255, Port 49142)

```
    fwflash=done\nCHKSUM=1240\n
           0x66+0x77+0x66+0x6c+0x61+0x73+0x68+0x3d+0x64+0x6f+0x6e+0x65+0x0a = 1240 (decimal)
              f    w    f    l    a    s    h    =    d    o    n    e   \n
```
  In case the FW bin file is corrupt (format error or MD5 issue), the broadcast will be
```
    fwflash=failed\nCHKSUM=1431\n
```

### Step 6: Power OFF

If flash successfully, or failed to show ERROR and wait user clicks a key to exist FWUpdate state.
For now, this step could only be done by human.

## Example Windows Scripts             {#CGI18_examples}

Google `Windows curl download` for a windows command line executable. Add it into your PATH environment variables.

```bat
@echo off
@REM Usage 1: SdUpdate.bat  - Upload Sd_CarDV.bin for SD card FW burning
@REM Usage 2: SdUpdate.bat <MY_FILE> - Upload <MY_FILE> to SD:\<MY_FILE>
@REM Usage 3: SdUpdate.bat <MY_FILE> <DEV_FILE> - Upload <MY_FILE> to SD:\DEV_FILE>
IF "%IP%"=="" (
	echo "undefined IP. Use SET IP=<DEVICE IP> to config"
	goto EOF
)
IF "%1"=="" (
	set file_name=.\Sd_CarDV.bin
) ELSE (
	set file_name=%1
)

@echo on
curl "http://%IP%/cgi-bin/Config.cgi?action=set&property=UIMode&value=UPDATEFW"
@echo off

IF "%2"=="" (
@echo Uploading %file_name%
	@echo on
	curl -F "fileupload=@%file_name%" "http://%IP%/cgi-bin/FWupload.cgi"
	@echo off
) ELSE (
	@echo on
	curl -F "fileupload=@%file_name%;filename=%2" "http://%IP%/cgi-bin/FWupload.cgi"
	@echo off
)

@echo on
curl "http://%IP%/cgi-bin/FWupload.cgi?action=flash"
@echo off

:EOF
```
