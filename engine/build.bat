@echo off
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VSINSTALLDIR=%%i\"
)
if not defined VSINSTALLDIR (
    echo ERROR: Visual Studio Build Tools installation not found.
    exit /b 1
)
call "%VSINSTALLDIR%Common7\Tools\VsDevCmd.bat" -arch=x64
rmdir /s /q "build"
cmake --preset release -S .
if errorlevel 1 exit /b %errorlevel%
cmake --build --preset release
exit /b %errorlevel%
