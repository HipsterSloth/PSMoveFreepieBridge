@echo off
setlocal

::Select the path to the root PSMoveService dolder
set "psCommand="(new-object -COM 'Shell.Application')^
.BrowseForFolder(0,'Please select the root folder for PSMoveService (ex: c:\git-cboulay\PSMoveService).',0,0).self.path""
for /f "usebackq delims=" %%I in (`powershell %psCommand%`) do set "PSM_ROOT_PATH=%%I"
if NOT DEFINED PSM_ROOT_PATH (goto failure)

:: Find the distribution folder
For /D %%D in ("%PSM_ROOT_PATH%\dist") Do (
    set "DISTRIBUTION_FOLDER=%%~fD"
)
if NOT DEFINED DISTRIBUTION_FOLDER (
    echo "Failed to find the distribution folder for PSMoveService!"
    echo "Did you run BuildOfficialDistribution.bat?"
    goto failure
)

:: Set path variables
set "PSM_DEBUG_WIN32=%DISTRIBUTION_FOLDER%\Win32\Debug"
set "PSM_RELEASE_WIN32=%DISTRIBUTION_FOLDER%\Win32\Release"
set "PSM_DEBUG_X64=%DISTRIBUTION_FOLDER%\Win64\Debug"
set "PSM_RELEASE_X64=%DISTRIBUTION_FOLDER%\Win64\Release"
set "PSM_HEADERS=%PSM_RELEASE_X64%\include"

set "BRIDGE_DEBUG_WIN32=thirdparty\lib\x86\debug"
set "BRIDGE_RELEASE_WIN32=thirdparty\lib\x86\release"
set "BRIDGE_DEBUG_WIN64=thirdparty\lib\x64\debug"
set "BRIDGE_RELEASE_WIN64=thirdparty\lib\x64\release"
set "BRIDGE_HEADERS=thirdparty\headers\PSMoveService"

:: Copy over the header files
xcopy /y /r "%PSM_HEADERS%\ClientConstants.h" "%BRIDGE_HEADERS%" || goto failure
xcopy /y /r "%PSM_HEADERS%\ClientGeometry_CAPI.h" "%BRIDGE_HEADERS%" || goto failure
xcopy /y /r "%PSM_HEADERS%\PSMoveClient_CAPI.h" "%BRIDGE_HEADERS%" || goto failure
xcopy /y /r "%PSM_HEADERS%\PSMoveClient_export.h" "%BRIDGE_HEADERS%" || goto failure
xcopy /y /r "%PSM_HEADERS%\SharedConstants.h" "%BRIDGE_HEADERS%" || goto failure

:: Copy over the client DLLs
xcopy /y /r "%PSM_DEBUG_WIN32%\bin\PSMoveClient_CAPI.dll" "%BRIDGE_DEBUG_WIN32%" || goto failure
xcopy /y /r "%PSM_RELEASE_WIN32%\bin\PSMoveClient_CAPI.dll" "%BRIDGE_RELEASE_WIN32%" || goto failure
xcopy /y /r "%PSM_DEBUG_X64%\bin\PSMoveClient_CAPI.dll" "%BRIDGE_DEBUG_WIN64%" || goto failure
xcopy /y /r "%PSM_RELEASE_X64%\bin\PSMoveClient_CAPI.dll" "%BRIDGE_RELEASE_WIN64%" || goto failure

:: Copy over the client libs
xcopy /y /r "%PSM_DEBUG_WIN32%\lib\PSMoveClient_CAPI.lib" "%BRIDGE_DEBUG_WIN32%" || goto failure
xcopy /y /r "%PSM_RELEASE_WIN32%\lib\PSMoveClient_CAPI.lib" "%BRIDGE_RELEASE_WIN32%" || goto failure
xcopy /y /r "%PSM_DEBUG_X64%\lib\PSMoveClient_CAPI.lib" "%BRIDGE_DEBUG_WIN64%" || goto failure
xcopy /y /r "%PSM_RELEASE_X64%\lib\PSMoveClient_CAPI.lib" "%BRIDGE_RELEASE_WIN64%" || goto failure

echo "Successfully updated PSMoveService from: %DISTRIBUTION_FOLDER%"
pause
EXIT /B 0

:failure
echo "Failed to copy files from PSMoveService distribution"
pause
EXIT /B 1