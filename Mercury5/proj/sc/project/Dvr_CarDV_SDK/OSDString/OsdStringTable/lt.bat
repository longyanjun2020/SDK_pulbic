REM
REM Three bitmap characters of KOREAN are not correct in Font_16_English.c.
REM It needs copy those characters from Font_16_Korean.c to Font_16_English.c.
REM Otherwise, the language menu page showing Korean item will be wrong!
REM 

set FONT_TARGET_FOLDER=..\Font
set STRINGS_POOL_TARGET_FOLDER=..\OSDStringsPool

REM 1. ENGLISH
set LANG=English
set SIZE=18
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

:SPANISH
REM 2. SPANISH
set LANG=Spanish
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%

REM 3. RUSSIAN
set LANG=Russian
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 4. PORTUGUESE
set LANG=Portuguese
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 7. GERMAN
set LANG=German
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 8. ITALIAN
set LANG=Italian
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 9. POLISH
set LANG=Polish
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 10. FRENCH
set LANG=French
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 11. LATVIAN
set LANG=Latvian
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 12. ROMANIAN
set LANG=ROMANIAN
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y ..\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 13. SLOVAK
set LANG=SLOVAK
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 14. UKRANINIAN
set LANG=Ukraninian
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 17. CZECH
set LANG=Czech
set SIZE=16
geFont /cWest.txt /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_West.c %FONT_TARGET_FOLDER%\Font_16_West.c

:SC
REM 5. SIMPLE CHINESE
set LANG=SChinese
set SIZE=18
geFont /iStringTable_%LANG%.txt /fSimSun /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 6. TRADITIONAL CHINESE
set LANG=TChinese
set SIZE=18
geFont /iStringTable_%LANG%.txt /f²Ó©úÅé /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

REM 15. JAPANESE
set LANG=Japanese
set SIZE=18
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

:KOREAN
REM 16. KOREAN
set LANG=Korean
set SIZE=18
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_16_%LANG%.c

:END

pause
