@echo off
setlocal

if [%1]==[] (echo err: missing mobile image file & exit /b) else (set mmi_img_file=%1)
if [%2]==[] (echo err: missing link info file    & exit /b) else (set mmi_lnk_file=%2)
if [%3]==[] (echo err: missing display table file & exit /b) else (set lcm_tab_file=%3)
if [%4]==[] (set lcm_tab_idx=0) else (set lcm_tab_idx=%4)

if not exist %mmi_img_file% echo err: file not found - %mmi_img_file% & exit /b
if not exist %mmi_lnk_file% echo err: file not found - %mmi_lnk_file% & exit /b
if not exist %lcm_tab_file% echo err: file not found - %lcm_tab_file% & exit /b

if %lcm_tab_idx%==0 (
    set lcm_label=primary
    set sect_id=122
) else if %lcm_tab_idx%==1 (
    set lcm_label=secondary
    set sect_id=123
) else (
    echo err: invalid index
    exit /b
)

echo $ Starting @ %date% %time%
echo $ -------------------------------------------
echo $ Mobile image file: %mmi_img_file%
echo $ Link information : %mmi_lnk_file%
echo $ Display table file: %lcm_tab_file% (%lcm_label%)
echo $

echo $ Parsing link information ...
set mtg_img_type=mainline
set mtg_img_symb=msmCfgRun_sa
for /f "usebackq tokens=1,2,4 delims= " %%G in (%mmi_lnk_file%) do if %%G==%mtg_img_symb% (set mtg_img_ofst=%%H) & (set mtg_img_size=%%I)
if %mtg_img_size% LEQ 20480 (set mtg_img_type=osduo)
set mtg_img_symb=msmDrvNormal_na
for /f "usebackq tokens=1,2,4 delims= " %%G in (%mmi_lnk_file%) do if %%G==%mtg_img_symb% (set mtg_img_ofst=%%H) & (set mtg_img_size=%%I)

echo $ Montage image symbol: %mtg_img_symb%
echo $ Montage image offset: %mtg_img_ofst%
echo $ Monatge image Size  : %mtg_img_size%
echo $

echo $ Updating lcm driver ...
if exist Mst.log del Mst.log
mst -x %mmi_img_file% %mtg_img_ofst% %mtg_img_size% %mtg_img_symb%.hif >> Mst.log
mst -r %mtg_img_symb%.hif %sect_id% >> Mst.log
mst -s %lcm_tab_file% %sect_id% %lcm_tab_file%.hif >> Mst.log
mst -i %mtg_img_symb%.hif -1 %lcm_tab_file%.hif >> Mst.log
mst -h %mmi_img_file% %mtg_img_ofst% %mtg_img_size% %mtg_img_symb%.hif >> Mst.log

echo $
echo $ Compressing updated mobile image ...
wzpacker.exe %mmi_img_file%
echo $ -------------------------------------------
echo $ Finish @ %date% %time%

endlocal
@echo on