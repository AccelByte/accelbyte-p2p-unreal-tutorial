// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OssTutGameControllerServerMenu.generated.h"

/**
 * Server Menu Controller Class.
 */
UCLASS()
class OSSTUTORIALPROJECT_API AOssTutGameControllerServerMenu : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
};
