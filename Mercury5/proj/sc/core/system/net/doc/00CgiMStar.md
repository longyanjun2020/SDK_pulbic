# CGI Specification

This document describes about @company CGI Specification. If this were a software document, it would be more like an overview and API specification. This is not a mobile phone development or porting guide, thus it would not include  source code examples.

First it introduces CGI specification and NET CONF file concept in the firmware. Later it introduces frequent used CGIs. This is also used as reference like an API document. In part 3, it lists some complex features that requires many steps and cooperation among firmware, UI layer, client and server.

This document does **NOT** cover detailed or precise parameters and some use case limitations. Those attributes varies a lot from project to project. Refer to your SDK source code consult your engineering contact window for customized use case. For instance: It won't include exact resolutions are able to be set for you project or which UI State is supported or allows to transit. 

[TOC]


CHAP 1  Introduction      {#cgich1_intro}
===============================================================================


HTTP Access Method                     {#cgich1_1}
--------------------------
The HTTP access method for most of the CGI APIs will be primarily by HTTP-GET, unless specified particularly for some cases with HTTP-POST.

For each CGI URL, we can define some access methods, which we call them `action`.
Some actions are specific to a particular CGI, for example, this will add a user `MyUser1` with password `MyPass1`

	/cgi-bin/User.cgi?action=add&user=MyUser1&pass=MyPass1

But we also define two common access methods for every CGI:
	get: to read  the value of a property or properties (by wildcards) from the Configuration Space
	set: to write the value of a property into the Configuration Space

We also define a generic Configuration Space CGI: Config.cgi, which can access the entire Configuration Space.

Therefore, for example, the below URLs have exactly the same effect:

	/cgi-bin/Config.cgi?action=get&property=User.Account.Totals
	/cgi-bin/User.cgi?action=get&property=Account.Totals

@if internal
User authority class                   {#cgich1_2}
--------------------------
Defined in this system with the below 3 classes:
1. ADMIN
   a. default with every properties permissible, except some special properties, such as 
      read-only properties like: Sys.Manual.GPIO.Input.Xxx, Product.Xxx
   b. Factory Default:
   username: admin
   password: admin

2. USER
   a. Default with every properties forbidden if not defined in the ACL.
   b. The system will ship with a Factory default, for permissible properties.
   c. The user ADMIN is allowed to add or delete some permissions
   d. Factory Default: 0 users with class USER

3. GUEST
   a. Default with every properties forbidden if not defined in the ACL.
   b. The Factory default will contain minimal permissible properties.
   c. The user ADMIN is allowed to add or delete some permissions
   d. There will always be a GUEST account, neither add nor delete allowable, but it can be disabled, and password protected.
   @endif



Concept of Configuration Space:        {#cgi_config_space}
-------------------------------------- 
Similar to MS-Windows' Registry, we define in our system the Configuration Space, which consists of:
1. **Property**: the name of the configuration item
2. **Value**: its value
3. **Hidden property**: we associate the ACL with the Configuration Space, to control which properties are permissible or forbidden from a particular user

Most of the properties are accessed by the actions:
	`get` or `set`

For some Enumeration properties, which has this generic format:

	Xxx.Yyy.Totals=3
	Xxx.Yyy.1.Attr1=...
	Xxx.Yyy.1.Attr2=...
	Xxx.Yyy.2.Attr1=...
	Xxx.Yyy.2.Attr2=...
	Xxx.Yyy.3.Attr1=...
	Xxx.Yyy.3.Attr2=...

@if internal
We define two special actions to add or delete the entries:
	`add` or `del`
@endif


@if internal
Concept of ACL                         {#cgich1_4}
--------------------
The ACL (Access Control List) for Configuration Space, has its own structure similar to the Configuration Space, thus can be implemented by the similar C subroutines to handle them both.

For example, 'Sys.Manual.GPIO.Input' is read-only for ADMIN user. This is specified in the ACL as:
	acl.Sys.Manual.GPIO.Input=ADMIN:get
Note, we don't need the access controls for class USER and GUEST, since they can't exceed ADMIN's authority.

Another example, for user account administrations:
	acl.User.Account=ADMIN:get/set/add/del USER: GUEST:
	acl.User.Account.%d=ADMIN:get/set USER:get/set GUEST:


Implementation Possibilities           {#cgich1_5}
--------------------------------
Here list some implementation possibilities:

Under Windows: leverage Registry

Under Linux:
1. Use a single file to keep all configurations. Ex.

       $ cat /etc/ipcam842x/system.conf
       Product.Video.Streams=3
       Product.Video.Format=H264,MJPEG
       Product.Video.TimeStamp=YES
       ...

2. Use distinct configuration files by parsing '.' into '/' and. Ex.

       $ cat /etc/ipcam842x/Product/Video.conf
       Streams=3
       Format=H264,MJPEG
       TimeStamp=YES
       ...

3. Use a single file but in Win INI format. Ex.

       $ cat /etc/ipcam842x/system.conf
       [Product.Video]
       Streams=3
       Format=H264,MJPEG
       TimeStamp=YES
       ...

4. Another example of using a single INI file. Ex.

       $ cat /etc/ipcam842x/system.conf
       [Product]
       Video.Streams=3
       Video.Format=H264,MJPEG
       Video.TimeStamp=YES
       ...
   @endif





CHAP 2  Web CGIs                       {#cgich2_web}
===============================================================================


URL format                             {#cgi_format}
-----------------
There are two formats for the URLs of the CGI commands:

	/cgi-bin/<command.cgi>  : the returned HTTP response will have "Content-Type: text/plain"

Every CGI support `get` and `set`, thus their definitions will only be specified in the section [Config.cgi](#config_cgi)


In response to the CGI commands, the HTTP Response Body text will consists of:

LINE 1 : Return Code in numerical text

     0 : successful
     other values : reason code for failure

LINE 2 : Return Code in text string

     0 -> OK
     701 -> illegal parameter format
     702 -> unknown action
     703 -> unknown property
     ...

LINE 3 : Optional additional reply text

     For get, it will consists of what are gotten !!!
     For set / add / del, it's empty

**Example Response of Successful SET**
```
    0
    OK
```
**Example Response of Successful GET**
```
0
OK
Camera.Menu.UIMode=VIDEO
```
**Example Response of Failed Command**
```
703
Unknown CGI-PARAM: Property
```


/cgi-bin/Config.cgi                    {#config_cgi}
-------------------------

This is a generic CGI for accessing the entire Configuration Space, where the access actions get / set / add / del are further confined by [ACL] (#cgich1_4) definitions. 

Command parameters: **Read the value(s)** from the specified property(s): `<ConfigProperty>`

	action=get
	property=<ConfigProperty>

@note 1. it is allowed to specify the wildcard pattern: `Xxx.Yyy.*` in the `<ConfigProperty>`
@note 2. no matter it is single get or wildcard get, the returned text will be NEWLINE "\n" separated lines:
```
            <ConfigProperty1>=<Value1>
            <ConfigProperty2>=<Value2>
            ...
```

Command parameters: **Write the value** into the specified property: `<ConfigProperty>`

	action=set
	property=<ConfigProperty>
	value=<Value>

@note 1. No wildcard for this command action.

Command parameters: Add an entry into the specified Enumeration Property

	action=add
	property=<ConfigProperty>
	attrs=<AttrList>

@warning It's not recommanded to use this command. Revise .conf files.
@note 1. The Enumeration properties has special format as described in the Section [Concept of Configuration Space](#cgi_config_space) \n
	    The DOT-Path of the `<ConfigProperty>` must be specified excluding the enumeration digit. \n
		For example, to add a new user, it will be given as: "User.Account"
@note 2. The `<AttrList>` is COMMA separated list of the pattern: `"attr1=value1,attr2=value2,..."` \n For example, to add a new user (MyName / MyPass) by this generic CGI, the HTTP request URL will be:

		/cgi-bin/Config.cgi?action=add&property=User.Account&attrs="Username%3DMyName,Password%3DMyPass"

Command parameters: Remove an entry from the specified Enumeration Property

	action=del
	property=<ConfigProperty>

@warning It's not recommanded to use this command. Revise .conf files.
@note 1. The Enumeration properties has special format as described in the Section [Concept of Configuration Space](#cgi_config_space) \n
	    The DOT-Path of the `<ConfigProperty>` must be specified including the enumeration digit. \n
		For example, to remove the 3rd user, it will be given as: `"User.Account.3"`.
@note 2. After this operation, the subsequent entries will be moved forward. In the previous examples, the original 4th user, will become `"User.Account.3"`


/cgi-bin/User.cgi                      {#cgi_user}
-------------------------

@deprecated User.cgi is still in the code base but not supported.

Allow the Client devices to perform user related activities on the Smart Camera device, such as login, adds a user, change password

Configuration Space Root:  `User.<ConfigProperty>`

command parameters: **Login** into the system.

	action=login
	user=<username>
	pass=<password>

@note 1.  The HTTP access method should choose HTTP-POST, so that the `<username> <password>` will be at least excluded from be manifested in the URL in the HTTP-Request line.
@note 2.  Possibly also by HTTP-AUTH ???

command parameters: **Adds a new user** into the system

	action=add
	user=<username>
	pass=<password>
	class=<class>

@note 1. The `<class>: [ ADMIN | USER ]`, default: `USER`

command parameters: **Deletes the specified user** from the system

	action=del
	user=<username>

command parameters: **Change the password** by the user himself

	action=mod
	user=<username>
	opass=<OriginalPassword>
	npass=<NewPassword>

command parameters: **Change the user info** by the administrator

	action=mod
	user=<username>
	pass=<password>
	class=<class>

@if internal
/cgi-bin/Sys.cgi                       {#sys_cgi}
-----------------------

@deprecated Sys.cgi is still in the code base but not supported.

Allow the Client devices to perform system-wise activities on the @company Smart Camera device, such as time, firmware, log, Machine, or GPIOs.

For the GPIO like entities in the system, we define a special action `switch`, which is essentially similar to `set`, but are specifically addressed to this configs properties: `Sys.Manual.<ConfigProperty>.` 
They can manually turn ON/OFF a OUTPUT function, such as recording, LED, Buzzer, GPIO Outputs, with additional parameter for Active Duration.
Or they can be manually queried for certain function's state, such as GPIO Sensor Input's state.

command parameters: switch ON or OFF of the specified properties: `Sys.Manual.<ConfigProperty>`

	action=switch
	property=<ConfigProperty>
	value=<value>
	duration=<ActiveDur>

@note 1.  the `<value>` can be: `[ ON | OFF ]`
@note 2.  if `<ActiveDur>` is missing, then 'Sys.Manual.ActiveDur' will be adopted.

command parameters: query the function's state of the specified properties: `Sys.Manual.<ConfigProperty>`

	action=sense
	property=<ConfigProperty>
	debounce=<DebounceAlgorithm>

@note 1.  For `<DebounceAlgorithm>`, currently only defines this one: SIMPLE
@note 2.  if `<DebounceAlgorithm>` is missing, then 'Sys.Manual.Debounce' will be adopted.
@endif


CHAP 3  Configuration File          {#cgi_ch3}
===============================================================================

@todo Add more description and new feature like `;RUNTIME`, Total=0
@todo Describe where .conf is and prelude_mcp.bat

To proper handle the string based configurations on an embedded system, an external PERL script will parsing the below configurations to generate the proper sources of C and H files.

For integer values type, each occupies 4 bytes. \n
For string values type, the maximum char array size will be determined by PERL by examing the aprostrphe delimiter: `"..."`

For example, for this one:

    Sys.Manual.GPIO.Input.1.Name="External Sensor at Kitchen Window                         "
Its trailing spaces will be trimmed, and the read back value will be:
	"External Sensor at Kitchen Window"
But maximum allowable string size for this item will be: 60  (aligned to 4 bytes boundary)

Special boolean values:\n
	ON, YES -> 1 \n
	OFF, NO -> 0

For Enumeration type, the maximum dimension must be declared explicitly !!

For example, the below config means: there are currently 2 user accounts defined, but maximum allowed accounts for the system are 4.

	User.Account.Totals=2
	User.Account.1.Username="admin            "
	User.Account.1.Password="admin            "
	User.Account.1.Class="ADMIN "
	User.Account.2.Username="handsomeboy            "
	User.Account.2.Password="1234    "
	User.Account.2.Class="USER  "
	User.Account.3.Username="                       "
	User.Account.3.Password="        "
	User.Account.3.Class="USER  "
	User.Account.4.Username="                       "
	User.Account.4.Password="        "
	User.Account.4.Class="USER  "

