MD rom

setlocal
if [%1]==[] (set java_solution=__JAVA_OAKMONT__)else (set java_solution=%1)

if %java_solution%==NO_PREINSTALL_DATA (
PapayaPik.exe -config PapayaPik_NoPreinstall.cfg
)else if %java_solution%==__JAVA_OAKMONT_JAP0__ (
PapayaPik.exe -config PapayaPik_JAP0.cfg
) else if  %java_solution%==__JAVA_OAKMONT__ (
PapayaPik.exe -config PapayaPik.cfg 
) else if  %java_solution%==__JAVA_OAKMONT_JAP2__ (
PapayaPik.exe -config PapayaPik_JAP2.cfg 
) else (
PapayaPik.exe -config PapayaPik.cfg
)

DirRomizer.exe rom
move kjava_sys_data_content.c ../
move kjava_sys_data_content.h ../../../inc
RD /s/q rom
