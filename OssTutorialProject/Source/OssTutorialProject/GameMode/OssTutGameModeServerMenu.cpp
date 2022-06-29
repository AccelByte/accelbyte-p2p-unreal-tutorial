// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "OssTutGameModeServerMenu.h"

void AOssTutGameModeServerMenu::TravelToGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("To the game map"));

	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		check(World);
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");
	}
	else
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->ClientTravel("/Game/Maps/ThirdPersonExampleMap", ETravelType::TRAVEL_Absolute);
	}
}