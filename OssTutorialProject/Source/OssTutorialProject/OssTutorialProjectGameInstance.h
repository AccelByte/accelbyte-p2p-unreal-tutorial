// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OssTutorialProjectGameInstance.generated.h"

/**
 * When Game Instance spawned, Server will created
 * On server client.
 */
UCLASS()
class OSSTUTORIALPROJECT_API UOssTutorialProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	virtual void Init() override;

public:
	/**
	* @brief Used for keep the session name.
	*/
	void InitSessionName(FName SessionName);
	
	/**
	* @brief Variable containing currest session name.
	*/
	FName CustomSessionName;

private:
	/**
	* @brief Used for if Network Failure occur.
	*/
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
};
