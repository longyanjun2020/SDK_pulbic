# Features {#page_feature}

[TOC]

Integrated with Reference APP   {#app_feature}
===============================================================================

Standalone Net Features {#standalone_feature}
===============================================================================

**Standalone Net Features** here means that these features are for network integration but have not been included with Reference APP. It may or may not be integrated into Reference APP in the future.

One-Click-Sharing and Emergency File Downloading {#one_click_sharing}
--------------------------

**Current Status:**
- `20160524_MergeTUTKAnd264Wifi` Only for CGI interface. UI layer and real function is not ready. 
- `20160601_OneClickShare_DiffResol` CGI, and real function is ready. Downloading callbacks is not ready.

@msc One-Click-Sharing Message Flow
	arcgradient = 8;
    C [label="Client, typically means APP"], S [label="Server, typically means Camera"], UI[label="UI Module"];
    |||;
	C->S [label="CGI triggering", ID="1", URL="@ref cgi_one_click_triggering"];
	S->C [label="broadcast: file name", ID="2", URL="@ref cgi_one_click_broadcasting"];
	--- [label="Different sets of CGIs"];
	C->S [label="(Optional) Get DIR list", ID="3", URL="@ref cgi_one_click_dir"];
	---;
	C->S [label="Download the file", ID="4", URL="@ref cgi_one_click_download"];
	S->UI [label="Callback in firmware", ID="5", URL="@ref cgi_one_click_callback"];
@endmsc


### 1. CGI triggering ###                                  {#cgi_one_click_triggering}

   ```{.url}
   cgi-bin/Config.cgi?action=set&perperty=Video&value=rec_short
   cgi-bin/Config.cgi?action=set&perperty=Video&value=rec_emer
   ```
   Note that the External button or on-device button or customized algorithm or peripheral may also triggers this feature.\n
   *Alternative Verification:* web browser or `curl.exe`\n

### 2. Broadcast ###                  {#cgi_one_click_broadcasting}
   Find the broadcast term: `shortFn` or `emerFn` for the file name.
   Refer section Broadcast for more info.\n
   *Alternative Verification:* `Wireshark` or `nc.exe (netcat.exe)`.

### 3. (Optional) Get DIR list ###    {#cgi_one_click_dir}
   Before download the file. An alternative way is use DIR CGI to get the list for certain file list for specified folder.
   With this method, some project could download the files in the background to synchronize important files, such as emergency files.\n
   *Alternative Verification:* `Wireshark` or `nc.exe (netcat.exe)`.

### 4. Download the file ###   {#cgi_one_click_download}
   When APP get the broadcast message. Start download the file.\n
   *Alternative Verification:* web browser (Recommended) or `curl.exe`.

### 5. Callback in the Firmware ###   {#cgi_one_click_callback}
   When start downloading the file, an icon might be shown on the panel.
   When stop downloading the file, the icon would be hidden. It could also remove the file name for @ref cgi_one_click_broadcasting "step 2" for further broadcasting.\n
   *Alternative Verification:* None.