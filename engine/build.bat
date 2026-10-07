@echo off
set BUILD_TYPE=release
if not [%1]==[] (
    set BUILD_TYPE=%1
)
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VSINSTALLDIR=%%i\"
)
if not defined VSINSTALLDIR (
    echo ERROR: Visual Studio Build Tools installation not found.
    exit /b 1
)
call "%VSINSTALLDIR%Common7\Tools\VsDevCmd.bat" -arch=x64
cmake --preset %BUILD_TYPE% -S .
if errorlevel 1 exit /b %errorlevel%
cmake --build --preset %BUILD_TYPE%
exit /b %errorlevel%
