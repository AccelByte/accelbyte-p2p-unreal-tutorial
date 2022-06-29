// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "OssTutorialMenuHUD.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

#include "OssTutorialProject/AccelByte/Authentication/AccelByteAuth.h"
#include "OssTutorialProject/AccelByte/CustomGames/AccelByteCustomGames.h"
#include "OssTutorialProject/AccelByte/CustomGames/AccelByteServerPassword.h"
#include "OnlineSubsystemAccelByte/Public/OnlineSubsystemAccelByteDefines.h"

void AOssTutorialMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();

	check(LoginMenuClass);
	check(CustomGamesMenuClass);
	check(ServerPasswordMenuClass);

	LoginMenu = CreateWidget<UAccelByteAuth>(PlayerController, LoginMenuClass.Get());
	CustomGamesMenu = CreateWidget<UAccelByteCustomGames>(PlayerController, CustomGamesMenuClass.Get());
	ServerPasswordMenu = CreateWidget<UAccelByteServerPassword>(PlayerController, ServerPasswordMenuClass.Get());

	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	const IOnlineIdentityPtr IdentityInterface = OnlineSub->GetIdentityInterface();

	OnLoginRequest.AddUObject(this, &AOssTutorialMenuHUD::OnLoginSuccess);
	OnLogoutRequest.AddUObject(this, &AOssTutorialMenuHUD::OnLogoutSuccess);
	OnInitSessionPassword.AddUObject(this, &AOssTutorialMenuHUD::OnInitDataSessionPassword);

	if (IdentityInterface->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		OpenCustomGamesMenu();
	}
	else
	{
		OpenLoginMenu();
	}
}

void AOssTutorialMenuHUD::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	CloseLoginMenu();
	CloseCustomGamesMenu();
	CloseServerPasswordMenu();
}

void AOssTutorialMenuHUD::OnLoginSuccess(bool bIsSuccess)
{
	if (bIsSuccess)
	{
		OpenCustomGamesMenu();
		CloseLoginMenu();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD:OnLoginSuccess is failed"));
	}
}

void AOssTutorialMenuHUD::OnLogoutSuccess(bool bIsSuccess)
{
	if (bIsSuccess)
	{
		OpenLoginMenu();
		CloseCustomGamesMenu();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD:OnLogoutSuccess is failed"));
	}
}

void AOssTutorialMenuHUD::OnInitDataSessionPassword(const FOnlineSessionSearchResult& SessionData)
{
	ServerPasswordMenu->InitData(SessionData);
	OpenServerPasswordMenu();
}

void AOssTutorialMenuHUD::OpenLoginMenu()
{
	LoginMenu->AddToViewport();
}

void AOssTutorialMenuHUD::OpenCustomGamesMenu()
{
	CustomGamesMenu->AddToViewport();
}

void AOssTutorialMenuHUD::OpenServerPasswordMenu()
{
	ServerPasswordMenu->AddToViewport();
}

void AOssTutorialMenuHUD::CloseLoginMenu()
{
	LoginMenu->RemoveFromViewport();
}

void AOssTutorialMenuHUD::CloseCustomGamesMenu()
{
	CustomGamesMenu->RemoveFromViewport();
}

void AOssTutorialMenuHUD::CloseServerPasswordMenu()
{
	ServerPasswordMenu->RemoveFromViewport();
}