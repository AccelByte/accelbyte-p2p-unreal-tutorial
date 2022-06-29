// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteCustomGames.h"
#include "AccelByteServerListEntry.h"
#include "../Authentication/AccelByteAuth.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemTypes.h"

#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "OssTutorialProject/HUD/OssTutorialMenuHUD.h"
#include "OssTutorialProject/OssTutorialProjectGameInstance.h"

void UAccelByteCustomGames::NativeConstruct()
{
	Super::NativeConstruct();

	TutorialMenuHUD = Cast<AOssTutorialMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Btn_CreateServer->OnClicked.AddUniqueDynamic(this, &UAccelByteCustomGames::OnClickCreateSession);
	Btn_RefreshList->OnClicked.AddUniqueDynamic(this, &UAccelByteCustomGames::RefreshSessionList);
	Btn_BackToLobby->OnClicked.AddUniqueDynamic(this, &UAccelByteCustomGames::CloseCustomGamesMenu);

	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UAccelByteCustomGames::RefreshSessionList, RefreshTime, bNeedRefresh);

	RefreshSessionList();
}

void UAccelByteCustomGames::CreateCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;

			SessionSettings.NumPublicConnections = 2;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = false;
			SessionSettings.bAllowJoinInProgress = false;

			SessionSettings.Set(SETTING_GAMEMODE, FString(TEXT("1v1")), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionSettings.Set(SETTING_MAPNAME, FString(TEXT("ServerMenu")), EOnlineDataAdvertisementType::ViaOnlineService);

			SessionSettings.Set(SETTING_ACCELBYTE_ICE_ENABLED, true);

			SessionSettings.Set(FName("SESSION_NAME"), Etb_ServerName->GetText().ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionSettings.Set(FName("SESSION_PASSWORD"), Etb_ServerPassword->GetText().ToString(), EOnlineDataAdvertisementType::DontAdvertise);

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UAccelByteCustomGames::CreateSessionComplete);

			SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
			/*Note: Uncomment this if you need to change the session name variable*/
			//SessionInterface->CreateSession(0, FName(Etb_ServerName->GetText().ToString()), SessionSettings);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Create Session Failed; Session Interface is invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Create Session Failed; Subsystem Invalid"));
	}
}

void UAccelByteCustomGames::FindCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			if (SessionSearch.IsValid())
			{
				SessionSearch->MaxSearchResults = 100;
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
				SessionSearch->QuerySettings.Set(SETTING_SEARCH_TYPE, FString(SETTING_SEARCH_TYPE_PEER_TO_PEER_RELAY), EOnlineComparisonOp::Equals);

				SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UAccelByteCustomGames::FindSessionComplete);

				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Looking for Session Failed; FOnlineSessionSearch is invalid"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Looking for Session Failed; Session Interface is invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Looking for Session Failed; Subsystem Invalid"));
	}
}

void UAccelByteCustomGames::OnClickCreateSession()
{
	CreateCustomGamesSession();
}

void UAccelByteCustomGames::RefreshSessionList()
{
	Sb_ServerList->ClearChildren();

	FindCustomGamesSession();
}

void UAccelByteCustomGames::CloseCustomGamesMenu()
{
	TutorialMenuHUD->GetLoginMenu()->OnClickLogoutButton();
}

void UAccelByteCustomGames::CreateSessionComplete(FName SessionName, bool bIsSuccess)
{
	if (bIsSuccess)
	{
		CreateSessionSuccess(SessionName);
	}
	else
	{
		CreateSessionFailed();
	}
	SessionInterface->ClearOnCreateSessionCompleteDelegates(this);
}

void UAccelByteCustomGames::CreateSessionSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Creating Session Success, Session Name: %s"), *SessionName.ToString()));

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	GameInstance->InitSessionName(SessionName);
	/*Note: Uncomment this if you need to change the session name variable*/
	//GameInstance->InitSessionName(FName(Etb_ServerName->GetText().ToString()));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ClientTravel("/Game/Maps/ServerMenu?listen", ETravelType::TRAVEL_Absolute);
}

void UAccelByteCustomGames::CreateSessionFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Creating Session Failed"));
}

void UAccelByteCustomGames::FindSessionComplete(bool bIsSuccess)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Finish Looking for sessions"));

	if (bIsSuccess)
	{
		FindSessionSuccess();
	}
	else
	{
		FindSessionFailed();
	}
	SessionInterface->ClearOnFindSessionsCompleteDelegates(this);
}

void UAccelByteCustomGames::FindSessionSuccess()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Successfully found game sessions"));

	if (SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			const TWeakObjectPtr<UAccelByteServerListEntry> CustomSessionEntry = MakeWeakObjectPtr<UAccelByteServerListEntry>(CreateWidget<UAccelByteServerListEntry>(this, CustomSessionEntryClass.Get()));

			CustomSessionEntry->InitData(SearchResult);

			Sb_ServerList->AddChild(CustomSessionEntry.Get());
		}
	}
}

void UAccelByteCustomGames::FindSessionFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Failed to find game sessions"));
}