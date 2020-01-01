del /s /f /q .\testload\*.*
md .\testload\
copy .\*.bin .\testload
copy .\*.e2p .\testload
copy .\*.CUS .\testload
copy .\*.cus .\testload
copy .\*.wpb .\testload
copy .\*.fat .\testload
copy .\*.ini .\testload
copy .\*.prm .\testload
copy .\*.wt .\testload
copy .\*.pat .\testload
copy .\*.img .\testload
copy .\*.axf .\testload
copy .\*.prt .\testload
copy .\link.info .\testload
copy .\*.nni .\testload
copy .\*.pni .\testload
copy .\*.bst .\testload
copy .\*.ldr .\testload
copy .\setting.miu .\testload
copy .\*.nro .\testload
copy .\*.nrw .\testload
copy .\*.dll .\testload
copy .\*.val .\testload
copy .\*.bt.map .\testload
copy .\NvramMerge.exe .\testload
copy .\nvram.i .\testload
copy .\list_*.mak .\testload

md .\testload\fat
xcopy .\fat .\testload\fat /s

md .\testload\hfat
xcopy .\hfat .\testload\hfat /s

md .\testload\tmt\
copy ..\tmt\*.* .\testload\tmt\*.*