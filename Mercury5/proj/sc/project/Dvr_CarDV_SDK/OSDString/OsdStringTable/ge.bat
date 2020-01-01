@echo
@echo Three bitmap characters of KOREAN are not correct in Font_16_English.c.
@echo It needs copy those characters from Font_16_Korean.c to Font_16_English.c.
@echo Otherwise, the language menu page showing Korean item will be wrong!
@echo 

@echo Build a single FONT set for west Language except English
set WEST=/cWest.txt
set FONT_TARGET_FOLDER=..\Font\FontLarge
set STRINGS_POOL_TARGET_FOLDER=..\Font\FontLarge

@echo 1. English
set LANG=English
set SIZE=24
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_24_%LANG%.c

:SPANISH
@echo 2. Spanish
set LANG=Spanish
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c
REM Output WEST FONT set
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_West.c %FONT_TARGET_FOLDER%\Font_20_West.c

@echo 3. Russian
set LANG=Russian
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 4. Portuguese
set LANG=Portuguese
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

:SC
@echo 5. Simply Chinese
set LANG=SChinese
set SIZE=24
geFont /iStringTable_%LANG%.txt /fSimSun /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c

@echo 6. Traditional Chinese
set LANG=TChinese
set SIZE=24
geFont /iStringTable_%LANG%.txt /f²Ó©úÅé /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c

@echo 7. German
set LANG=German
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

:ITALIAN
@echo 8. Italian
set LANG=Italian
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 9. French
set LANG=French
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 10. Polish
set LANG=Polish
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 11. Romanian
set LANG=Romanian
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 12. Latvian
set LANG=Latvian
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 13. Slovak
set LANG=Slovak
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 14. Ukraninian
set LANG=Ukraninian
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

@echo 15. Japanese
set LANG=Japanese
set SIZE=24
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_24_%LANG%.c

@echo 16. Korean
set LANG=Korean
set SIZE=24
geFont /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_24_%LANG%.c

REM 17. CZECH
set LANG=Czech
set SIZE=19
geFont %WEST% /iStringTable_%LANG%.txt /fArial /s%SIZE% /o%STRINGS_POOL_TARGET_FOLDER%
move /Y %STRINGS_POOL_TARGET_FOLDER%\%LANG%OSDStringsPool.c %FONT_TARGET_FOLDER%\Large%LANG%OSDStringsPool.c
REM move /Y %STRINGS_POOL_TARGET_FOLDER%\Font_%SIZE%_%LANG%.c %FONT_TARGET_FOLDER%\Font_20_%LANG%.c

:END
pause
