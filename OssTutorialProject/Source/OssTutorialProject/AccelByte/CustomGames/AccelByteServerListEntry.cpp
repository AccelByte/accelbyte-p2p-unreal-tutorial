// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteServerListEntry.h"
#include "AccelByteCustomGames.h"
#include "OssTutorialProject/AccelByte/ServerMenu/AccelByteServerMenu.h"
#include "AccelByteServerPassword.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OssTutorialProject/HUD/OssTutorialMenuHUD.h"

void UAccelByteServerListEntry::InitData(const FOnlineSessionSearchResult& SearchResult)
{
	//Server Name
	CustomGameSessionName = FName(SearchResult.Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString());
	Tb_ServerName->SetText(FText::FromName(CustomGameSessionName));

	//Game Mode
	FString Mode;
	SearchResult.Session.SessionSettings.Get(SETTING_GAMEMODE, Mode);
	Tb_ServerGameMode->SetText(FText::FromString(Mode));

	//Current Capacity
	int32 MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
	int32 CurrentPlayers = MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
	FString Capacity = FString::Printf(TEXT("%d/%d"), CurrentPlayers, MaxPlayers);
	Tb_ServerCapacity->SetText(FText::FromString(Capacity));

	if (CurrentPlayers == MaxPlayers)
	{
		Btn_JoinServer->SetIsEnabled(false);
	}

	SessionData = SearchResult;
}

void UAccelByteServerListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	TutorialMenuHUD = Cast<AOssTutorialMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Btn_JoinServer->OnClicked.AddUniqueDynamic(this, &UAccelByteServerListEntry::OnClickJoinButton);
}

void UAccelByteServerListEntry::OnClickJoinButton()
{
	TutorialMenuHUD->OnInitSessionPassword.Broadcast(SessionData);
}