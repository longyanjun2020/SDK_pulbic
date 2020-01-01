# FAQ {#page_faq}

[TOC]


CGI and Configuration Space    {#faq_conf}
==============================================================================
Refer basic CGI concept @ref cgich1_intro.


How Can I Get Info from Camera? {#faq_conf1}
-----------------
Use @ref cgi_get "GET CGI"


How Can I Add a New Info in the Camera? {#faq_conf2}
----------------

These are standard procedure for add new configuration.

1. Add new configuration of in your project `conf file`:

   1.1 Your `conf file` should be in your project folder, the one with your `MCP file`. The file name would be `amn_project.ucos.conf`.

   1.2 Add your configuration in `amn_project.ucos.conf`. Typically you would append yours.

   ```
   #My comment
   Demo.MyStr="my string"
   Demo.MyInt=100
   ```

2. Run `Prelude_MCP.bat`. This file is with your `MCP file` too.

3. Rebuild the project and update your firmware as always.

4. Use typical CGI `get` and `set` to access your configuration.

   ```
   cgi-bin/Config.cgi?action=set&property=MyString&value=string2
   or
   http://192.72.1.1/cgi-bin/Config.cgi?action=get&property=MyString&value=string%202
   if the value "string 2" has spaces.
   ```

   And the result would be retrieved from

   ```
   cgi-bin/Config.cgi?action=get&property=MyString
   ```



How Can I Use a New Conf as Camera Setting? {#faq_conf3}
----------------
Here we take mute function as example. This function uses existing video operation method. Use new values "mute" and "unmute". Those CGIs changes the setting just like LCD GUI Menu with real key buttons pressing. It changes the menu value and will be applied in the next recording.

Now those features are broken down into the following steps.
1. **Design CGI**. The first thing is to design a new CGI.
   ````
   cgi-bin/Config.cgi?action=set&property=Video&value=mute/unmute
   ````
   If we try to test this command the following message should be gotten. Note that your code might include "mute" feature. Then you should try any other string for value to get the error message.
   ````
   701
   Illegal Parameter
   ````
   If the following message is shown, then it is likely that there is no such property in your configuration file, also known as NET CONF. A new line need in be added into your `amn_system.ucos.conf` like `MyProperty   ; RUNTIME`.
   ````
   703
   Unknown CGI-PARAM: Property
   ````
2. **Add CGI Handler**. Then allocate the CGI handler. In this function `Handle_VideoOperation()` will be used. Try to find or **add** your handler somewhere near `cgi_handler` or `get_Handler` if your using action set.

3. **Send UI Message in CGI Handler**. Process your value in that handler. Here "mute" and "unmute" will be added into `Handle_VideoOperation()`.  As you may see the existing code, it usually issues messages to UI modules. The UI Module have message routing and process the message in UI task. This action would avoid some racing condition or critical session issues since all UI operation will be executed in the same task sequentially. 
   If no `WIRELESS_CONNECT_MESSAGE` type suits your need, a new one must be added into the enumeration. Here `WIRELESS_SET_REC_MUTE` is added.

4. **Add UI Message**. Follow the message routing in UI message system and UI state machine. The handler would typically be in CGI state or Video/Camera State, but since UI module is highly customized on your own, plan which state should process the message. In this example, `UI_NET_CGICMD_STATE` will process the message `WIRELESS_SET_REC_MUTE` as a sub mode to any state that could receive CGI.

5. **UI Handler** .Follow SDK sample UI, could find some functions likes `STATE_NET_CGICMD_WIRELESS_SET_GSENSOR()` in `StateNetCGICmdFunc.c` or something likes it. Add your own function `STATE_NET_CGICMD_WIRELESS_SET_MUTE()` and don't forget to register it with `uiStateRegisterNetEventHandler()`.  The actual control for recording goes here.

6. **Continue Message Routing**. Now if you issue the CGI command to Camera. You could get
   ````
   0
   OK
   ````
   But in UART debugging message, it does not go into `STATE_NET_CGICMD_WIRELESS_SET_MUTE()`. 
   ````
   ##VERBOSE## prepare_response:70 'GET' '/cgi-bin/Config.cgi?action=set&property=Video&value=mute' 
   ncgi_op_feedback:Handle 2147479559(0x7FFFF007) RESULT 0
   --> COMMAND FINISH 0
   ##VERBOSE## handle_request:233 mini_dserver 2: COMPLETE
   ````
   Add message case in `KeyParser_NetCGICmdEvent()` and `KeyParser_NetStreamingEvent()`. 
   The new function should be up and running now.

7. **Feedback**. In step 2, Set CGI often **wait** UI task to feedback. It needs to report status to the client side. In some other cases, if the exiting flow does not feedback the status to CGI. Find something like `CGI_SET_STATUS()` and `CGI_FEEDBACK()`. If this step is missed, CGI handler in step 3 would wait until time-out, which is typically 6 seconds. In this case, the function still work but it blocks CGI for 6 seconds and probably blocks the next CGI in the client side. It is recommended that APP requests CGI sequentially.
