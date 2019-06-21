@echo off
cd /d %~dp0

set gpparg=-mwindows -DDX_GCC_COMPILE -DDX_NON_INLINE_ASM -LDxLib -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt

if "%1" == "" goto MAIN

set filename=%1
goto GPP

:MAIN
set filename=main

:GPP
if NOT EXIST %filename%.cpp goto NOTFOUNDFILE

g++ -o %filename%.exe %filename%.cpp %gpparg%
IF errorlevel 1 exit /B
%filename%.exe
REM del %filename%.exe
exit /B

:NOTFOUNDFILE
echo not found %filename%
exit /B