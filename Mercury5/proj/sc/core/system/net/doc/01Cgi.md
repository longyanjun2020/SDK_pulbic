Smart Camera CGI {#smart_camera_cgi}
===============================
@version 1.4

Basic Format:

	http://<CAMERA_IP>/cgi-bin/Config.cgi?action=<ACT>&property=<PROP>[&value=<VALUE>]
	<ACT>:	set|get|dir|del
	<PROP>:	reference A1. for set|get
	<VALUE>:depend on <PROP>
@note `http://<CAMERA_IP>/` will be omitted in the rest of this document since they are all the same.

Example: `http://192.72.1.1/cgi-bin/Config.cgi?action=get&property=Camera.Preview.MJPEG.h`
	
Response:

	HTTP/1.1 200 OK\r\n
	CONTENT-LENGTH: <size of byte>\r\n
	CONTENT-TYPE: text/plain\r\n
	.....
	0\n
	OK\n (or FAIL\n)
	.....

Refer CGI Format for more [detailed explainations](@ref cgi_format)
    
[TOC]
1. CGI set URL format
2. CGI get URL format
3. CGI dir (get file list) URL format
4. CGI Delete file URL format
5. CGI Delete group file URL format
6. CGI Video record/stop URL format
7. CGI Video capture URL format
8. CGI find me URL format
9. File Streaming over HTML5
10. Query Video recording status
11. Get Date/Time and MJPEG streaming info
12. Set Date/Time
13. Get/Set Settings 
14. Reset network
15. Get UI State
16. Set UI State
17. Get JPEG thumbnail of .JPG or .MOV
18. Upload firmware and burn the firmware

A1. All available properties list

1. set                                 {#cgi_set}
=====================

	cgi-bin/Config.cgi?action=set&property=<PROP>&value=<VALUE>[&property=<PROP>&value=<VALUE>]

example A:
    
	http://192.168.0.177/cgi-bin/Config.cgi?action=set&property=Camera.Preview.MJPEG.bitrate&value=4000000
        0\n
        OK\n


example B:

	http://192.168.0.177/cgi-bin/Config.cgi?action=set&property=Camera.Preview.MJPEG.w&value=320&property=Camera.Preview.MJPEG.h&value=184
        0\n
        OK\n
        0\n
        OK\n


2. get                                 {#cgi_get}
=====================

	cgi-bin/Config.cgi?action=get&property=<PROP>[&property=<PROP>]

example A:

	http://192.168.0.177/cgi-bin/Config.cgi?action=get&property=Camera.Preview.MJPEG.w&property=Camera.Preview.MJPEG.h
        0\n
        OK\n
        Camera.Preview.MJPEG.h=184\n
        Camera.Preview.MJPEG.w=320\n

example B:

    http://192.168.0.177/cgi-bin/Config.cgi?action=get&property=Camera.Preview.MJPEG.*
        0\n
        OK\n
        Camera.Preview.MJPEG.TimeStamp=ACTIVE\n
        Camera.Preview.MJPEG.TimeStamp.day=1\n
        Camera.Preview.MJPEG.TimeStamp.hour=0\n
        Camera.Preview.MJPEG.TimeStamp.minute=6\n
        Camera.Preview.MJPEG.TimeStamp.month=1\n
        Camera.Preview.MJPEG.TimeStamp.second=24\n
        Camera.Preview.MJPEG.TimeStamp.year=2013\n
        Camera.Preview.MJPEG.WarningMSG=ACTIVE\n
        Camera.Preview.MJPEG.bitrate=3300000\n
        Camera.Preview.MJPEG.fps=30\n
        Camera.Preview.MJPEG.h=184\n
        Camera.Preview.MJPEG.status=Standby\n
        Camera.Preview.MJPEG.w=320\n

3. dir (Get file list)                 {#cgi_dir}
=====================================
@param action= <b> `dir`|`reardir` </b> List front(default) or rear camera files.
@param property= Name of DCF data base to be listed. @b `Multi` might also be used for customizable list. Note that this options requires FW changes.
@param count= Number of files returned per CGI request. This should not be a super large number. Typically 15~20 is recommended.
@param from= Start from 0. 
@param format= <b> `all|mov|avi|jpeg` </b> is available for file extension filtering.
@param new= since CGI 1.2  List new files, which are created from the listed. No value after `=`.
@param backward= since CGI 1.2  List in backward order of the file list. No value after `=`. Note that this options requires FW compiler options setting. When this option is used, only `from=0` for the first time. And no `from=` for continuous listing.

List all of files in SD:

    cgi-bin/Config.cgi?action=dir&property=DCIM&format=[all|mov|avi|jpeg]&count=[<number items>]{&from=<from>}

<!-- @if ACTION_CAM -->
List all of first file of group in SD.

    cgi-bin/Config.cgi?action=dir&property=DCIM&format=[all|mov|avi|jpeg]&group=all&count=[<number items>]{&from=<from>}
<!-- @endif -->

## How to List All Files ##
Pseudo Code
````perl
    @from = 0
    @count = 16
    do {
        http://192.72.1.1/cgi-bin/Config.cgi?action=dir&property=Normal&format=all&count=@count&from=@from
        @from += amount; //amount is the number returned files from XML response
    } while (amount == @count);
````
or
````pl
    @count = 16
	http://192.72.1.1/cgi-bin/Config.cgi?action=dir&property=Normal&format=all&count=@count&from=0
	while (amount == @count) {
		http://192.72.1.1/cgi-bin/Config.cgi?action=dir&property=Normal&format=all&count=@count
		//no `from=0` here
    }
````
@note \@from and \@count cannot not be 1.

Example list:
````
http://192.72.1.1/cgi-bin/Config.cgi?&action=dir&property=Video&count=3&format=all&from=0
````
````xml

<?xml version="1.0" encoding="UTF-8" ?>
<Video>
<file>
        <name>/SD/Normal/F/FILE160102-000031F.MOV</name>
        <format size="1920x1080" fps="30" time="59.9">MOV</format>
        <size>91758592</size>
        <attr>RW</attr>
        <time>2016-01-02 00:00:31</time>
</file>
<file>
        <name>/SD/Normal/F/FILE161004-010100F.MOV</name>
        <format size="1920x1080" fps="30" time="3.3">MOV</format>
        <size>5283840</size>
        <attr>RW</attr>
        <time>2016-10-04 01:01:00</time>
</file>
<file>
        <name>/SD/Normal/F/FILE161004-010102F.MOV</name>
        <format size="1920x1080" fps="30" time="60.0">MOV</format>
        <size>92061696</size>
        <attr>RW</attr>
        <time>2016-10-04 01:01:02</time>
</file>
<amount>3</amount>
</Video>
````

This example list the following 3 more files.
````
http://192.72.1.1/cgi-bin/Config.cgi?&action=dir&property=Video&count=3&format=all
````
````xml

<?xml version="1.0" encoding="UTF-8" ?>
<Video>
<file>
        <name>/SD/Normal/F/FILE161004-010103F.MOV</name>
        <format size="1920x1080" fps="30" time="3.1">MOV</format>
        <size>4968448</size>
        <attr>RW</attr>
        <time>2016-10-04 01:01:03</time>
</file>
<file>
        <name>/SD/Normal/F/FILE161004-010159F.MOV</name>
        <format size="1920x1080" fps="30" time="5.5">MOV</format>
        <size>8556544</size>
        <attr>RW</attr>
        <time>2016-10-04 01:01:59</time>
</file>
<file>
        <name>/SD/Normal/F/FILE161027-000000F.MOV</name>
        <format size="1920x1080" fps="30" time="1.7">MOV</format>
        <size>2715648</size>
        <attr>RW</attr>
        <time>2016-10-27 00:00:00</time>
</file>
<amount>3</amount>
</Video>
````

@if ACTION_CAM
### Group Parameters 
group information is in `<group>`. There are mode, key, id, total and no attributes.
    - **mode**: The file is created in which mode, it can be CAMERA, BURST or TIMELAPSE. Refer @ref Handle_UIMode
    - **key**:  the DIR key for DCF in Camera FW.
    - **id**:   Group id. Minimum is 1. When key changed, the id will be counted from 1.\n
                If a unique ID of the group is wanted, both `key` and `id` needs to be combined.
    - **total**:How many files in the group, Minimum is 1
    - **no**:   File number in the group, Minimum is 1

@note Group info feature depends on DCF system. Double check with DCF implementation of your project.

Example list of Group:

This example shows that there are 2 groups of Image files. The first group has 1 file and the second
group has 7 files, it total of 8 files. The second group is typically captured in burst shot feature.
```xml
    http://192.168.0.177/cgi-bin/Config.cgi?action=dir&property=DCIM&format=all&count=12&from=0
        <DCIM>
            <file>
                <name>/DCIM/100_NOML/PICT0013.MOV</name>
                <format>MOV</format>
                <size>416056150</size>
                <attr>RW</attr>
                <time>2014-09-23 11:25:58</time>
                <group mode="VIDEO" key="100" id="5" total="1" no="1"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0014.JPG</name>
                <format>jpeg</format>
                <size>2161345</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="1"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0015.JPG</name>
                <format>jpeg</format>
                <size>2164741</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="2"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0016.JPG</name>
                <format>jpeg</format>
                <size>2236862</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="3"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0017.JPG</name>
                <format>jpeg</format>
                <size>2254183</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="4"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0018.JPG</name>
                <format>jpeg</format>
                <size>2371329</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="5"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0019.JPG</name>
                <format>jpeg</format>
                <size>2335775</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="6"/>
            </file>
            <file>
                <name>/DCIM/100_NOML/PICT0020.JPG</name>
                <format>jpeg</format>
                <size>2335800</size>
                <attr>RW</attr>
                <time>2014-09-24 16:36:02</time>
                <group mode="TIMELAPSE" key="100" id="6" total="7" no="7"/>
            </file>
            <amount>8</amount>
        </DCIM>
```
@endif

## Other File Lists ##

@note This section describes some variations for dir command. Depending on project compiler options and customized features, these may or may not be applied. 

### List Files in Rear Camera Folder
This is for Car DV with rear camera enabled project. Use `action=reardir` rather than `action=dir`

    cgi-bin/Config.cgi?action=reardir&property=DCIM&format=[all|mov|avi|jpeg]&count=[<number items>]{&from=<from>}

### List Customized File Combination
This requires customized media data base. Try to find DCFDT_DBM_MULTI_FOLDER_PATH or MIMF_CUSTOMIZED_SORT_TYPE in your project source code. Use `property=Multi` in your HTTP requests. Note that `Multi` is also defined in the code and might be customized for your need. Try to find DCFDT_DBM_MULTI_FOLDER_PATH in your `cfg` directory.

    cgi-bin/Config.cgi?action=dir&property=Multi&format=[all|mov|avi|jpeg]&count=[<number items>]{&from=<from>}


4. del (Delete file)                   {#cgi_del}
=============================

	cgi-bin/Config.cgi?action=del&property=<DCIM FILE PATH>
	cgi-bin/Config.cgi?action=del&property=*.*
	cgi-bin/Config.cgi?action=del&property=*.JPG
	cgi-bin/Config.cgi?action=del&property=*.MP4

`<DCIM FILE PATH>` format:

    DCIM$ddd__DSC$MOV_hhhh.MOV
    ddd:  100 ~ 999
    hhhh: 0001 ~ 9999
example:

	cgi-bin/Config.cgi?action=del&property=DCIM$100__DSC$MOV_1163.AVI

5. del,group (Delete group files)      {#cgi_del_group}
===================================
@if ACTION_CAM

	cgi-bin/Config.cgi?action=del&property=key&value=<dir_key>&property=group&value=<group_id>
example:\n
    there is a file as
```xml
        <file>
            <name>/DCIM/100_NOML/PICT0013.MOV</name>
            <format>MOV</format>
            <size>416056150</size>
            <attr>RW</attr>
            <time>2014-09-23 11:25:58</time>
            <group mode="VIDEO" key="100" id="5" total="1" no="1"/>
        </file>
```
Use

	cgi-bin/Config.cgi?action=del&property=key&value=100&property=group&value=5
@else
	This command is not available for Car DV SDK.
@endif


6. record (Record/Stop)                {#cgi_record}
===================================
This refers to starting/stopping recording in VIDEO mode, and capture an image in CAMERA mode.

	cgi-bin/Config.cgi?action=set&property=Video&value=record
   
7. capture (Capture Video Image)       {#cgi_capture}
===============================
This refers to captureing image in VIDEO mode.

	cgi-bin/Config.cgi?action=set&property=Video&value=capture
   
8. findme (Find Device)                {#cgi_findme}
=========================
Tell @company Smart Camera to notify human user where it is. This is used to make sure which camera current client APP connects to.

	cgi-bin/Config.cgi?action=set&property=Net&value=findme
   
9. play (File Streaming over HTML5)    {#cgi_play}
============================
@todo Double check it this CGI is preferrable rather than using `http://<CAMERA_IP>/<DCIM FILE PATH>`

	cgi-bin/Config.cgi?action=play&property=<DCIM FILE PATH>
		<DCIM FILE PATH> format:
			DCIM$ddd__DSC$MOV_hhhh.MOV
			ddd:  100 ~ 999
			hhhh: 0001 ~ 9999
example:

	cgi-bin/Config.cgi?action=play&property=DCIM/100__DSC/MOV_0001.MOV

10. Query Video recording status       {#cgi_record_status}
===============================
```
	cgi-bin/Config.cgi?action=get&property=Camera.Preview.MJPEG.status.record
```
Response:
```
    0
    OK
    Camera.Preview.MJPEG.status.record=Recording
```
or 
```
    0
    OK
    Camera.Preview.MJPEG.status.record=Standby
```

11. Get Date/Time and MJPEG streaming info {#cgi_date_time}
==========================================

	cgi-bin/Config.cgi?action=get&property=Camera.Preview.MJPEG.*
    
Response:
```
    0
    OK
    Camera.Preview.MJPEG.TimeStamp=ACTIVE
    Camera.Preview.MJPEG.TimeStamp.day=1
    Camera.Preview.MJPEG.TimeStamp.hour=0
    Camera.Preview.MJPEG.TimeStamp.minute=6
    Camera.Preview.MJPEG.TimeStamp.month=1
    Camera.Preview.MJPEG.TimeStamp.second=24
    Camera.Preview.MJPEG.TimeStamp.year=2013
    Camera.Preview.MJPEG.WarningMSG=ACTIVE
    Camera.Preview.MJPEG.bitrate=3300000
    Camera.Preview.MJPEG.fps=30
    Camera.Preview.MJPEG.h=184
    Camera.Preview.MJPEG.status=Standby
    Camera.Preview.MJPEG.w=320
```

12. Set Date/Time                      {#cgi_set_date_time}
===============================
	cgi-bin/Config.cgi?action=set&property=TimeSettings&value=yyyy$MM$dd$HH$mm$ss
Response:

    0
    OK
    
Example:

	cgi-bin/Config.cgi?action=set&property=TimeSettings&value=2014$05$26$12$30$00
		
13. Example Get/Set Settings           {#cgi_ex_settings}
===============================
These are settings could be get or set
    - Video resolution
	- Capture resolution
	- MTD
	- AWB
	- Flicker
	- EV
	- FW version

@note These are examples only. Many of them are customizable for your project. Check your `.conf` file and SDK of your project.

**Get settings**

    cgi-bin/Config.cgi?action=get&property=Camera.Menu.*	
    Response:
        0
        OK
        Camera.Menu.AWB=AUTO
        Camera.Menu.EV=EV0
        Camera.Menu.FWversion=3042
        Camera.Menu.Flicker=50Hz
        Camera.Menu.ImageRes=8MP
        Camera.Menu.IsStreaming=NO
        Camera.Menu.MTD=UNKNOWN
        Camera.Menu.UIMode=VIDEO
        Camera.Menu.VideoRes=1080P60
**Set White balance**

    cgi-bin/Config.cgi?action=set&property=AWB&value=[AUTO|CLOUDY|DAYLIGHT|FLUORESC|UNDERWATER]

**Set Video resolution**\n
Refer @ref CGI_MENU_VIDEO_RES in @ref AHC_Wireless.c for the latest available resolution in your code.

    cgi-bin/Config.cgi?action=set&property=VideoRes&value=[4K15|2.7K30|1080P60|1080P50|720P120|720P100]

@copybrief CGI_MENU_VIDEO_RES
@snippet AHC_Wireless.c CGI for CGI_MENU_VIDEO_RES

**Set Image resolution**

    cgi-bin/Config.cgi?action=set&property=ImageRes&value=[8MP|6MPW|6MP]

**Set Flicker**

    cgi-bin/Config.cgi?action=set&property=Flicker&value=[50Hz|60Hz]

**Set EV**

    cgi-bin/Config.cgi?action=set&property=EV&value=[EVN200|EVN167|EVN133|EVN100|EVN067|EVN033|EV0|EVP033|EVP067|EVP100|EVP133|EVP167|EVP200]
		
14. Reset network                      {#cgi_net_reset}
=================================
@note This command also stores the modified network setting into SIF so that it could be used later.
      An example usage would be set SSID of Smart Camera SSID as AP.


	cgi-bin/Config.cgi?action=set&property=Net&value=reset

Response:

    0
    OK
			
15. Get UI States                      {#cgi_get_ui}
==========================================================
@note These are examples only. Many of them are customizable for your project. Check your `.conf` file and SDK of your project.
@note The values in `()` are possbile values could be used. Those values are also depends on SDK implementation in your project and it's open to be customized. Refer your code for the detail.

Possible modes or attributes for UI module to be accessed:
-  Mode (VIDEO, CAMERA, BURST, TIMELAPSE, SETTING)
-  AWB  (AUTO, DAYLIGHT, CLOUDY, FLUORESC, UNDERWATER)
-  EV   (EVN200,EVN167,EVN133,EVN100,EVN067,EVN033,EV0,EVP033,EVP067,EVP100,EVP133,EVP167,EVP200)
-  Flicker (50Hz,60Hz)
-  HDR  (OFF,ON)
-  Videores (4K15,2.7K30,1080P60,1080P50,720P120,720P100)
-  Imageres (8MP,6MPW,6M)
-  LoopingVideo (OFF,5MIN,10MIN)
-  PhotoBurst (3_1SEC,5_1SEC,10_1SEC)
-  Timelapse (2SEC,5SEC,10SEC,30SEC,60SEC)
-  Upsidedown (Normal,Upsidedown)
-  SpotMeter (OFF,ON)
-  StatusLights (OFF,ON)
-  SoundIndicator (OFF,ON)
-  Q-SHOT (OFF,ON)
-  PowerSaving (OFF,1MIN,2MIN,5MIN)

@par Use Wildcard to Get All Camera Menu Settings
```
	cgi-bin/Config.cgi?action=get&property=Camera.Menu.*
```
Response:
```
    0
    OK
    Camera.Menu.AWB=AUTO
    Camera.Menu.EV=EV0
    Camera.Menu.FWversion=3198
    Camera.Menu.Flicker=60Hz
    Camera.Menu.HDR=ON
    Camera.Menu.ImageRes=8MP
    Camera.Menu.IsStreaming=NO
    Camera.Menu.LoopingVideo=10MIN
    Camera.Menu.MTD=HIGH
    Camera.Menu.PhotoBurst=3_1SEC
    Camera.Menu.PowerSaving=OFF
    Camera.Menu.Q-SHOT=OFF
    Camera.Menu.SoundIndicator=ON
    Camera.Menu.SpotMeter=OFF
    Camera.Menu.StatusLights=ON
    Camera.Menu.Timelapse=2SEC
    Camera.Menu.UIMode=VIDEO
    Camera.Menu.UpsideDown=Normal
    Camera.Menu.VideoRes=1080P30
```

16. Set UI States                      {#cgi_set_ui}
==========================================================
@note These are examples only. Many of them are customizable for your project. Check your `.conf` file and SDK of your project.
@note The values in `()` are possbile values could be used. Those values are also depends on SDK implementation in your project and it's open to be customized. Refer your code for the detail.


-  UIMode (VIDEO, CAMERA, BURST, TIMELAPSE, SETTING) Refer @ref CGI_MENU_UI_STATE
@snippet AHC_Wireless.c CGI for CGI_MENU_UI_STATE
-  AWB  (AUTO, DAYLIGHT, CLOUDY, FLUORESC, UNDERWATER)
-  EV   (EVN200,EVN167,EVN133,EVN100,EVN067,EVN033,EV0,EVP033,EVP067,EVP100,EVP133,EVP167,EVP200)
-  Flicker (50Hz,60Hz)
-  HDR  (OFF,ON)
-  Videores (4K15,2.7K30,1080P60,1080P50,720P120,720P100) Refer @ref CGI_MENU_VIDEO_RES
@snippet AHC_Wireless.c CGI for CGI_MENU_VIDEO_RES
-  Imageres (8MP,6MPW,6M)
-  LoopingVideo (OFF,5MIN,10MIN)
-  PhotoBurst (3_1SEC,5_1SEC,10_1SEC)
-  Timelapse (2SEC,5SEC,10SEC,30SEC,60SEC)
-  Upsidedown (Normal,Upsidedown)
-  SpotMeter (OFF,ON)
-  StatusLights (OFF,ON)
-  SoundIndicator (OFF,ON)
-  Q-SHOT (OFF,ON)
-  PowerSaving (OFF,1MIN,2MIN,5MIN)

**examples**

	cgi-bin/Config.cgi?action=set&property=UIMode&value=CAMERA
	cgi-bin/Config.cgi?action=set&property=Videores&value=1080P60
	cgi-bin/Config.cgi?action=set&property=Imageres&value=8MP
	cgi-bin/Config.cgi?action=set&property=AWB&value=AUTO
	cgi-bin/Config.cgi?action=set&property=EV&value=EV0
	cgi-bin/Config.cgi?action=set&property=HDR&value=OFF
	cgi-bin/Config.cgi?action=set&property=SoundIndicator&value=OFF
	cgi-bin/Config.cgi?action=set&property=StatusLights&value=ON
	cgi-bin/Config.cgi?action=set&property=LoopingVideo&value=ON
	cgi-bin/Config.cgi?action=set&property=Upsidedown&value=NO
	cgi-bin/Config.cgi?action=set&property=Timelapse&value=2SEC
	cgi-bin/Config.cgi?action=set&property=Flicker&value=60Hz
	cgi-bin/Config.cgi?action=set&property=PowerSaving&value=2MIN
	cgi-bin/Config.cgi?action=set&property=SpotMeter&value=ON
	cgi-bin/Config.cgi?action=set&property=PhotoBurst&value=3_1SEC
	cgi-bin/Config.cgi?action=set&property=Q-SHOT&value=OFF


**Success Response**

    0
    OK
    
**Error Response**

    709
    ?

17. Get JPEG thumbnail of .JPG or .MOV {#cgi_thumb}
=================================

	/thumb/<JPEG FILE NAME>
    
It maps to `SD:/<JPEG FILE NAME>` \n
Example:

	/thumb/DCIM/100__DSC/PICT0001.JPG  (map to SD:/DCIM/100__DSC/PICT0001.JPG)
	/thumb/DCIM/100__DSC/PICT0002.MOV  (map to SD:/DCIM/100__DSC/PICT0002.MOV)


18. Upload and Burn the Firmware {#cgi_18_ref}
=================================
Refer a [Seperated page](@ref CGI18) for the detailed description.

