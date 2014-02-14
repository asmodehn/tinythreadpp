@echo off
setlocal

set BUILD_DIR="build"
set SRC_DIR="%~dp0"
set BUILD_TYPE=Release
set ENABLE_TESTS=ON

@echo on

set ORI_DIR=%CD%

REM this can fail if directory already exist
mkdir %BUILD_DIR%
cd %BUILD_DIR%

echo "Running in %CD% :"
cmake %SRC_DIR%

@echo off

echo|set /p=Detecting VS 10.0 install in 
setlocal ENABLEEXTENSIONS
REM set KEY_NAME=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\10.0
set KEY_NAME=HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\VisualStudio\10.0
set VALUE_NAME=InstallDir
FOR /F "tokens=2*" %%A IN ('REG.exe query "%KEY_NAME%" /v "%VALUE_NAME%"') DO (set pInstallDir=%%B)
echo %pInstallDir%

@echo on

echo Initializing VS environment
call "%pInstallDir%\..\..\VC\vcvarsall.bat"

echo Building project
devenv TinyThread++.sln /Build %BUILD_TYPE%

ctest

cd %ORI_DIR%
endlocal
