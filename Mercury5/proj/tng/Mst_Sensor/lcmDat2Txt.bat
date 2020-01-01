@echo off
setlocal

if [%1]==[] (echo err: missing display table file & exit /b) else (set lcm_tab_file=%1)
if [%2]==[] (set lcm_tab_idx=0) else (set lcm_tab_idx=%2)

if not exist %lcm_tab_file% echo err: file not found - %lcm_tab_file% & exit /b

if %lcm_tab_idx%==0 (
    set lcm_label=primary
    set sect_id=120
) else if %lcm_tab_idx%==1 (
    set lcm_label=secondary
    set sect_id=121
) else (
    echo err: invalid index
    exit /b
)

echo $ Starting @ %date% %time%
echo $ -------------------------------------------
echo $ Sensor table file: %lcm_tab_file% (%lcm_label%)

echo $ Transfer DAT to TXT ...
if exist Mst.log del Mst.log
mst -dat2txt %lcm_tab_file% %sect_id% >> Mst.log

echo $ -------------------------------------------
echo $ Finish @ %date% %time%

endlocal
@echo on