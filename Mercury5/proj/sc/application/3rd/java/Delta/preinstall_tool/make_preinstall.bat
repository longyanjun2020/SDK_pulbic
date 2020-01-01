@echo off


IF EXIST c:\NemoMP ECHO c:\NemoMP exists and will be remove!!!
IF EXIST c:\NemoMP rmdir /S /Q c:\NemoMP 
IF NOT EXIST c:\NemoMP ECHO c:\NemoMP create!
IF NOT EXIST c:\NemoMP mkdir c:\NemoMP
copy security.policy  c:\NemoMP
copy systemProperties.jar  c:\NemoMP\systemProperties.zip
copy suitesDetail.utf  c:\NemoMP
copy suitesDetail_bak.utf  c:\NemoMP
copy suitesList.utf  c:\NemoMP
copy suitesList_bak.utf  c:\NemoMP
copy jam.keystore  c:\NemoMP
copy j2me.keystore  c:\NemoMP
copy java.properties  c:\NemoMP
j9_installer2005.exe -jamService -installJar KQQ3_Common.jar
j9_installer2005.exe -jamService -install UCWEB6-60-999-70-08070218.jad UCWEB6-60-999-70-08070218.jar
j9_installer2005.exe -jamService -install opera-mini-4.2.13400-cn-local.jad opera-mini-4.2.13400-cn-local.jar
installPacker 3 c:\NemoMP
REM copy Java_preinstall_out.bin ..\..\..\..\..\..\customer\default\src\mmi\resource\xmmi_ta\system\global_Res\java
@echo Done!!
