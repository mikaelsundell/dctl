@echo off
set "target_dir=C:\ProgramData\Blackmagic Design\DaVinci Resolve\Support\LUT\DCTL"
if not exist "%target_dir%" (
    echo Target directory %target_dir% does not exist. Creating the directory.
    mkdir "%target_dir%"
)
set "current_dir=%cd%"

:: copy .h, .dctl, and .cube files
for %%f in ("%current_dir%\*.h" "%current_dir%\*.dctl" "%current_dir%\*.cube") do (
    if exist "%%f" (
        copy "%%f" "%target_dir%"
        echo Copied %%f to %target_dir%
    )
)

echo installation complete.
pause
