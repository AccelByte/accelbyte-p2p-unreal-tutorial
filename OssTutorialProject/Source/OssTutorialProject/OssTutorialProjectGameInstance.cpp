// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "OssTutorialProjectGameInstance.h"
#include "AccelByte/ServerMenu/AccelByteServerMenu.h"
#include "Kismet/GameplayStatics.h"

void UOssTutorialProjectGameInstance::Init()
{
	Super::Init();

	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UOssTutorialProjectGameInstance::OnNetworkFailure);
	}
}

void UOssTutorialProjectGameInstance::InitSessionName(FName SessionName)
{
	CustomSessionName = SessionName;
}

void UOssTutorialProjectGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Netwrok Failure, Message: %s"), *ErrorString));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}