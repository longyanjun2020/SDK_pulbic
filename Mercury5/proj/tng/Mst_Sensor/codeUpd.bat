@echo off
setlocal

if [%1]==[] (echo err: missing mobile image file & exit /b) else (set mmi_img_file=%1)
if [%2]==[] (echo err: missing link info file    & exit /b) else (set mmi_lnk_file=%2)
if [%3]==[] (echo err: missing init_montage image file & exit /b) else (set init_img_file=%3)
if [%4]==[] (set run_img_file=N/A) else (set run_img_file=%4)

if not exist %mmi_img_file% echo err: file not found - %mmi_img_file% & exit /b
if not exist %mmi_lnk_file% echo err: file not found - %mmi_lnk_file% & exit /b
if not exist %init_img_file% echo err: file not found - %init_img_file% & exit /b
echo $ Starting @ %date% %time%
echo $ -------------------------------------------
echo $ Mobile image file: %mmi_img_file%
echo $ Link information : %mmi_lnk_file%
echo $ Init_montage file: %init_img_file%
echo $ Run_montage file:  %run_img_file%
echo $

echo $ Parsing link information ...

set init_img_symb=msmDrvNormal_na
for /f "usebackq tokens=1,2,4 delims= " %%G in (%mmi_lnk_file%) do if %%G==%init_img_symb% (set init_img_ofst=%%H) & (set init_img_size=%%I)

echo $ init_montage image symbol: %init_img_symb%
echo $ init_montage image offset: %init_img_ofst%
echo $ init_montage image Size  : %init_img_size%
echo $

set run_img_symb=msmCfgRun_sa
for /f "usebackq tokens=1,2,4 delims= " %%J in (%mmi_lnk_file%) do if %%J==%run_img_symb% (set run_img_ofst=%%K) & (set run_img_size=%%L)

echo $ run_montage image symbol: %run_img_symb%
echo $ run_montage image offset: %run_img_ofst%
echo $ run_montage image Size  : %run_img_size%
echo $

echo $ Updating init_montage image ...
if exist Mst.log del Mst.log
mst -h %mmi_img_file% %init_img_ofst% %init_img_size% %init_img_file% >> Mst.log

if not %run_img_file%==N/A (
    echo $ Updating run_montage image ...
    mst -h %mmi_img_file% %run_img_ofst% %run_img_size% %run_img_file% >> Mst.log
)

echo $
echo $ Compressing updated mobile image ...
wzpacker.exe %mmi_img_file%
echo $ -------------------------------------------
echo $ Finish @ %date% %time%

endlocal
@echo on