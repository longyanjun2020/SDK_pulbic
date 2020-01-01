@echo off
setlocal

if [%1]==[] (echo err: missing sensor table file & exit /b) else (set sen_tab_file=%1)
if [%2]==[] (set sen_tab_idx=0) else (set sen_tab_idx=%2)

if not exist %sen_tab_file% echo err: file not found - %sen_tab_file% & exit /b

if %sen_tab_idx%==0 (
    set sen_label=primary
    set sect_id=124
) else if %sen_tab_idx%==1 (
    set sen_label=secondary
    set sect_id=125
) else (
    echo err: invalid index
    exit /b
)

echo $ Starting @ %date% %time%
echo $ -------------------------------------------
echo $ Display table file: %sen_tab_file% (%sen_label%)

echo $ Transfer DAT to TXT ...
if exist Mst.log del Mst.log
mst -dat2txt %sen_tab_file% %sect_id% >> Mst.log

echo $ -------------------------------------------
echo $ Finish @ %date% %time%

endlocal
@echo on