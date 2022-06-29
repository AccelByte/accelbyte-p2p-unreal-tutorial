@echo off

:: Check the plugins folder
if not exist .\OssTutorialProject\Plugins goto submodule_folder_missing

:: Check the submodule
if exist .\OssTutorialProject\Plugins\AccelByte\AccelByteNetwork\AccelByteNetworkUtilities.uplugin goto submodule_exist
if exist .\OssTutorialProject\Plugins\AccelByte\AccelByteOSS\OnlineSubsystemAccelByte.uplugin goto submodule_exist
if exist .\OssTutorialProject\Plugins\AccelByte\AccelByteUe4Sdk\AccelByteUe4Sdk.uplugin goto submodule_exist 

:: Initiliaze submodule for AccelByte OSS, SDK, and Networking
echo Initiliaze AccelByte OSS, SDK, and Networking submodule . . .
echo:
call git submodule update --init
echo:

if not exist .\OssTutorialProject\Plugins\AccelByte\AccelByteNetwork\AccelByteNetworkUtilities.uplugin goto error
if not exist .\OssTutorialProject\Plugins\AccelByte\AccelByteOSS\OnlineSubsystemAccelByte.uplugin goto error
if not exist .\OssTutorialProject\Plugins\AccelByte\AccelByteUe4Sdk\AccelByteUe4Sdk.uplugin goto error
echo Initialize submodule is successful
goto end

:: Add Plugin if the folder is missing
:submodule_folder_missing
echo Add AccelByte OSS, SDK, and Networking submodule . . .
echo:
call git submodule add --force https://github.com/AccelByte/accelbyte-unreal-oss OssTutorialProject/Plugins/AccelByte/AccelByteOSS
call git submodule add --force https://github.com/AccelByte/accelbyte-unreal-network-utilities OssTutorialProject/Plugins/AccelByte/AccelByteNetwork
call git submodule add --force https://github.com/accelbyte/accelbyte-unreal-sdk-plugin OssTutorialProject/Plugins/AccelByte/AccelByteUe4Sdk
echo:

:: Error handler
:error
echo Initialize submodule is failed
goto end

:: Submodule is already exist
:submodule_exist
echo Submodule is already exist. Trying to update submodule into latest . . .
call git submodule update --remote
goto end

:: End
:end
echo:


