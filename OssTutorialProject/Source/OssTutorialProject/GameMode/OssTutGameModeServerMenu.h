// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineSubsystemUtils.h"
#include "OssTutGameModeServerMenu.generated.h"

class UAccelByteServerMenu;

/**
 * Server Menu Game Mode.
 */
UCLASS()
class OSSTUTORIALPROJECT_API AOssTutGameModeServerMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**
	* @brief Used to travel to game map after the session start is success.
	*/
	UFUNCTION()
	void TravelToGame();

};
