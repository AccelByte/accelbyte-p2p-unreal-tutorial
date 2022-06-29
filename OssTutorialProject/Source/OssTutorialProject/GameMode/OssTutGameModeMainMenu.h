// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "OssTutGameModeMainMenu.generated.h"

class AOssTutorialMenuHUD;

/**
 * Main Menu Games Mode
 */
UCLASS()
class OSSTUTORIALPROJECT_API AOssTutGameModeMainMenu : public AGameMode
{
	GENERATED_BODY()

protected:

	class AOssTutorialMenuHUD* TutorialMenuHUD;

	AOssTutGameModeMainMenu();
	
};
