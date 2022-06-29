// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "OssTutGameModeMainMenu.h"
#include "OssTutorialProject/HUD/OssTutorialMenuHUD.h"

AOssTutGameModeMainMenu::AOssTutGameModeMainMenu()
{
	HUDClass = AOssTutorialMenuHUD::StaticClass();
}