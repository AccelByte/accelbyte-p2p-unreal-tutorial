@echo off

::Add CONDITION with "y" value for one time config
set CONDITION=n

echo You can also change the batch file to config the path manually
echo:

if %CONDITION% == y goto one_time_config
if %CONDITION% == n goto user_input_config

:one_time_config
::Remember to set ENGINEPATH
set ENGINEPATH=<YourEnginePath>

goto start

:user_input_config
echo Enter your Engine folder path. (Example: C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\Win64\UE4Editor.exe)
set /p ENGINEPATH=

:start

set UPROJECTPATH=%~dp0\OssTutorialProject\OssTutorialProject.uproject

echo Lauching Client 1...
start "Client 1" "%ENGINEPATH%" "%UPROJECTPATH%" MainMenu -game -log -ResX=1280 -ResY=720 -windowed -r.SetRes 1280x720w

echo Lauching Client 2...
start "Client 2" "%ENGINEPATH%" "%UPROJECTPATH%" MainMenu -game -log -ResX=1280 -ResY=720 -windowed -r.SetRes 1280x720w