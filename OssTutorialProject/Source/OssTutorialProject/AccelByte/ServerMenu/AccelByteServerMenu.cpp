// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteServerMenu.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemTypes.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "../ServerMenu/AccelByteServerMenuPlayerEntry.h"
#include "OssTutorialProject/OssTutorialProjectGameInstance.h"
#include "OssTutorialProject/GameMode/OssTutGameModeServerMenu.h"

void UAccelByteServerMenu::OnClickExitServerMenuButton()
{
	DestroyCustomGamesSession();
}

void UAccelByteServerMenu::OnClickStartServerMenuButton()
{
	if (CurrentPlayerIds.Num() >= 2)
	{
		StartCustomGamesSession();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Can't start session when alone"));
	}
}

void UAccelByteServerMenu::NativeConstruct()
{
	Super::NativeConstruct();

	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	SessionInterface = OnlineSub->GetSessionInterface();

	SessionInterface->OnRegisterPlayersCompleteDelegates.AddUObject(this, &UAccelByteServerMenu::RefreshPlayerList);
	SessionInterface->OnUnregisterPlayersCompleteDelegates.AddUObject(this, &UAccelByteServerMenu::RefreshPlayerList);

	if (GetOwningPlayer()->HasAuthority())
	{
		Btn_Ready->OnClicked.AddUniqueDynamic(this, &UAccelByteServerMenu::OnClickStartServerMenuButton);
	}
	else
	{
		Btn_Ready->SetVisibility(ESlateVisibility::Collapsed);
	}

	Btn_Exit->OnClicked.AddUniqueDynamic(this, &UAccelByteServerMenu::OnClickExitServerMenuButton);

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	CustomGameSessionName = GameInstance->CustomSessionName;

	Tb_ServerName->SetText(FText::FromName(CustomGameSessionName));
}

void UAccelByteServerMenu::DestroyCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	ULocalPlayer* const Player = GameInstance->GetFirstGamePlayer();

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UAccelByteServerMenu::DestroyCustomGamesSessionComplete);

			SessionInterface->UnregisterPlayer(NAME_GameSession, *Player->GetPreferredUniqueNetId().GetUniqueNetId());
			SessionInterface->DestroySession(NAME_GameSession);
			/*Note: Uncomment this if you need to change the session name variable*/
			//SessionInterface->UnregisterPlayer(CustomGameSessionName, *Player->GetPreferredUniqueNetId().GetUniqueNetId());
			//SessionInterface->DestroySession(CustomGameSessionName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session Failed; Session Interface is invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session Failed; Subsystem Invalid"));
	}
}

void UAccelByteServerMenu::StartCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnStartSessionCompleteDelegates.AddUObject(this, &UAccelByteServerMenu::StartCustomGamesSessionComplete);

			SessionInterface->StartSession(NAME_GameSession);
			/*Note: Uncomment this if you need to change the session name variable*/
			//SessionInterface->StartSession(CustomGameSessionName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session Failed; Session Interface is invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session Failed; Subsystem Invalid"));
	}
}

void UAccelByteServerMenu::RefreshPlayerList(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bIsSuccess)
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	SessionInterface = OnlineSub->GetSessionInterface();

	FNamedOnlineSession* ThisSessionInfo = SessionInterface->GetNamedSession(SessionName);

	CurrentPlayerIds = ThisSessionInfo->RegisteredPlayers;

	PlayerEntryManager(CurrentPlayerIds);
}

void UAccelByteServerMenu::PlayerEntryManager(const TArray<FUniqueNetIdRef>& PlayerIds)
{
	Sb_TeamA->ClearChildren();
	Sb_TeamB->ClearChildren();

	for (int i = 0; i < PlayerIds.Num(); i++)
	{
		const TWeakObjectPtr<UAccelByteServerMenuPlayerEntry> CustomSessionEntry = MakeWeakObjectPtr<UAccelByteServerMenuPlayerEntry>(CreateWidget<UAccelByteServerMenuPlayerEntry>(this, PlayerEntryClass.Get()));

		if (i % 2 == 0)
		{
			CustomSessionEntry->InitPlayerData(PlayerIds[i].Get());

			Sb_TeamA->AddChild(CustomSessionEntry.Get());
		}
		else
		{
			CustomSessionEntry->InitPlayerData(PlayerIds[i].Get());

			Sb_TeamB->AddChild(CustomSessionEntry.Get());
		}
	}
}

void UAccelByteServerMenu::StartCustomGamesSessionComplete(FName SessionName, bool bIsSuccess)
{
	if (bIsSuccess)
	{
		StartCustomGamesSessionSuccess(SessionName);
	}
	else
	{
		StartCustomGamesSessionFailed();
	}
}

void UAccelByteServerMenu::StartCustomGamesSessionSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Start Session success"));

	//travel to the game mape using server menu game mode
	UWorld* world = GetWorld();
	AOssTutGameModeServerMenu* GameModeServerMenu = Cast<AOssTutGameModeServerMenu>(world->GetAuthGameMode());

	GameModeServerMenu->TravelToGame();
}

void UAccelByteServerMenu::StartCustomGamesSessionFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Start Session failed"));
}

void UAccelByteServerMenu::DestroyCustomGamesSessionComplete(FName SessionName, bool bIsSuccess)
{
	if (bIsSuccess)
	{
		DestroyCustomGamesSuccess(SessionName);
	}
	else
	{
		DestroyCustomGamesFailed();
	}
	SessionInterface->ClearOnDestroySessionCompleteDelegates(this);
}

void UAccelByteServerMenu::DestroyCustomGamesSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Destroy Session success"));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UAccelByteServerMenu::DestroyCustomGamesFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session failed"));
}