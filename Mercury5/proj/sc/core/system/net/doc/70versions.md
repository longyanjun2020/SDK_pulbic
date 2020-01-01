# CGI Versions {#page_cgi_ver}

@copydoc NCGI_VERSION \n
Refer @ref NCGI_VERSION for confirm the string in the firmware.

The first word in column **Command** is `action=` in CGI URI. The second word is `property=`. The optional third word is `value=`\n For example, `set Video record/capture` means `/cgi-bin/Config.cgi?action=set&property=Video&value=record`.\n
**Obsolete** is still usable but is not recommended to be used. It is typically not included in the latest Reference APP. Consult us before you use it.\n
**Removed** sometimes remains usable for historical issues. It should not be used in new product.

<!-- Remember to keep a blank line in the end of this document for the rest of auto generated part to append -->
<!--@addtogroup cgi_ver_matrix  CGI Version Matrix-->
<!-- @weakgroup cgi_ver_matrix CGI Version Matrix -->
| Command  | Since  | Obsolete  | Removed | Remarks |
| -------- | ------ | --------- | ------- | ------- |
| set UIMode  | 1.0 | | | Unusable for now if CR_CGI_SET_UI_MODE is not on. |
| set\n get Camera.Menu.UIMode  | set 1.2\n get 1.0 | | | Unusable for now if CR_CGI_SET_UI_MODE is not on. |
| set DefMode  | 1.0 | 1.1 | 1.2 | Set default UI State |
| get Camera.Menu.DefMode  | 1.0 | 1.1 | 1.2 | Set default UI State |
| set Video record/capture   | 1.0 | | | Main video operation. |
| set Video rec_emer/rec_short   | 1.2 | | | Main video operation. |
| set WiFi     | 1.0 | | | Turn off WiFi module. |
| set Videores | 1.0 | 1.2 | | Set video recording resolution: `value=` resolution string |
| set\n get Camera.Menu.VideoRes | set 1.2\n get 1.0 | | | Set video recording resolution: `value=` resolution string |
| set Imageres  | 1.0 | 1.2 | | Set Image capturing resolution: `value=` resolution string.\n Typically used for UI Camera State. |
| set\n get Camera.Menu.ImageRes  | set 1.2\n get 1.0 | | | Image resolution for capturing: `value=` resolution string.\n Typically used for UI Camera State. |
| set DeFlickerfMode  | 1.0 | 1.2 | | Set Anti-Flicker mode. |
| set\n get Camera.Menu.Flicker  | set 1.2\n get 1.0 | | | Set Anti-Flicker mode. |
| set AWB  | 1.0 | 1.2 | | Set Auto White Balance mode. |
| set\n get Camera.Menu.AWB  | set 1.2\n get 1.0 | | | Set Auto White Balance mode. |
| set TimeSettings  | 1.0 | | | Set Real-Time-Clock (RTC) time.\n `value=Year$Month$Day$Hour$Minute$Second` |
| set Net    | 1.0 | | | Reset network function and find the camera.\n Note that it would store network settings into Flash.|
| set Camera.Preview.MJPEG.[x]    | 1.0 | | | Set MJPEG live preview parameters. Such as width and height.|
| set EV    | 1.0 | 1.2 | | Set Camera Exposure Value.|
| set\n get Camera.Menu.EV    | set 1.2\n get 1.0 | | | Set Camera Exposure Value.|
| set MTD    | 1.1 | | | Set MoTion Detection Mode.\n Typically for parking mode, with level or off.|
| set\n get Camera.Menu.MTD    | set 1.2\n get 1.0 | | | Set MoTion Detection Mode.\n Typically for parking mode, with level or off.|
| set PhotoBurst    | 1.0 | 1.2 | | Set Photo Burst Mode interval.|
| set\n get Camera.Menu.PhotoBurst | set 1.2\n get 1.0 | | | Set Photo Burst Mode interval.|
| set Timelapse    | 1.0 | 1.2 | | Set Timelapse Shot interval.|
| set\n get Camera.Menu.Timelapse | set 1.2\n get 1.0 | | | Set Timelapse Shot interval.|
| set UpsideDown    | 1.0 | 1.2 | | Set Orientation of Camera Image Sensor.|
| set\n get Camera.Menu.UpsideDown | set 1.2\n get 1.0  | | | Set Orientation of Camera Image Sensor.|
| set SpotMeter    | 1.0 | 1.2 | | Set Camera Spot Meter mode.|
| set\n get Camera.Menu.SpotMeter | set 1.2\n get 1.0 | | | Set Camera Spot Meter mode.|
| set LoopingVideo    | 1.0 | 1.2 | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
| set\n get Camera.Menu.LoopingVideo | set 1.2\n get 1.0 | | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
| set\n get Camera.Menu.VideoClipTime | set 1.2\n get 1.0 | | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
| set HDR    | 1.0 | 1.2 | | Set HDR mode. Typically on or off. |
| set\n get Camera.Menu.HDR | set 1.2\n get 1.0 | | | Set HDR mode. Typically on or off.|
| set Q-SHOT    | 1.0 | 1.2 | | Set Q shot mode.|
| set\n get Camera.Menu.Q-SHOT | set 1.2\n get 1.0 | | | Set Q shot mode.|
| set StatusLights    | 1.0 | 1.2 | | Set status LED. It's typically for customized LED controlling.|
| set\n get Camera.Menu.StatusLights | set 1.2\n get 1.0 | | | Set status LED. It's typically for customized LED controlling.|
| set SoundIndicator    | 1.0 | 1.2 | | Controls status beeper or speaker. It's typically a customized feature.|
| set\n get Camera.Menu.SoundIndicator | set 1.2\n get 1.0 | | | Controls status beeper or speaker. It's typically a customized feature.|
| set PowerSaving    | 1.0 | 1.2 | | Set power saving timer.|
| set\n get Camera.Menu.PowerSaving | set 1.2\n get 1.0 | | | Set power saving timer.|
| set TVSystem    | 1.0 | 1.2 | | Set TV system as NTSC or PAL.|
| set\n get Camera.Menu.TVSystem | set 1.2\n get 1.0 | | | Set TV system as NTSC or PAL.|
| set TimeFormat    | 1.0 | | | Set Time format, such as YMD or DMY.|
| set LCDPowerSave    | 1.0 | | | Set LCD power saving timer.|
| set\n get Camera.Menu.LCDPower | set 1.2\n get 1.0 | | | Set LCD power saving timer.|
| set GSensor    | 1.0 | | | Set G-sensor sensitivity.|
| set\n get Camera.Menu.GSensor | set 1.2\n get 1.0 | | | Set G-sensor sensitivity.|
| set PowerOffDelay | 1.0 | 1.2 | | Set power off delay time |
| set\n get Camera.Menu.PowerOffDelay | set 1.2\n get 1.0 | | | Set power off delay time |
| set SD0 | 1.0 | 1.1 | | `value=format` to format SD card to Camera preferred format. |
| get Camera.Menu.SD0 | 1.0 | 1.1 | | `value=format` to format SD card to Camera preferred format. |
| set Playback | 1.1 | | | Enter/Leave UI_NET_PLAYBACK_STATE.\n APP also sends heart beat periodically to notify Camera that it's still alive.\n **Plan to use UIMode for entering and leaving.** |
