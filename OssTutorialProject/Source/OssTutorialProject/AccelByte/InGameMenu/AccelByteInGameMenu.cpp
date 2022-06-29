// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteInGameMenu.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemTypes.h"

#include "Components/Button.h"
#include "OssTutorialProject/OssTutorialProjectGameInstance.h"

void UAccelByteInGameMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_EndGame->OnClicked.AddUniqueDynamic(this, &UAccelByteInGameMenu::ClickEndSession);
	Btn_Cancel->OnClicked.AddUniqueDynamic(this, &UAccelByteInGameMenu::ClickCancelInGameMenu);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	CurrentGameSessionName = GameInstance->CustomSessionName;
}

void UAccelByteInGameMenu::EndGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnEndSessionCompleteDelegates.AddUObject(this, &UAccelByteInGameMenu::EndSessionComplete);

			SessionInterface->EndSession(NAME_GameSession);
			/*Todo: change this if you need it*/
			//SessionInterface->EndSession(CurrentGameSessionName);
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

void UAccelByteInGameMenu::DestroyCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	ULocalPlayer* const Player = GameInstance->GetFirstGamePlayer();

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UAccelByteInGameMenu::DestroyCustomGamesSessionComplete);

			SessionInterface->UnregisterPlayer(NAME_GameSession, *Player->GetPreferredUniqueNetId().GetUniqueNetId());
			SessionInterface->DestroySession(NAME_GameSession);
			/*Note: Uncomment this if you need to change the session name variable*/
			//SessionInterface->UnregisterPlayer(CurrentGameSessionName, *Player->GetPreferredUniqueNetId().GetUniqueNetId());
			//SessionInterface->DestroySession(CurrentGameSessionName);
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

void UAccelByteInGameMenu::ClickEndSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	SessionInterface = OnlineSub->GetSessionInterface();

	if (SessionInterface->GetNamedSession(NAME_GameSession)->bHosting)
	{
		EndGamesSession();
	}
	else
	{
		DestroyCustomGamesSession();
	}
}

void UAccelByteInGameMenu::ClickCancelInGameMenu()
{
	this->RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = false;
}

void UAccelByteInGameMenu::EndSessionComplete(FName SessionName, bool bIsSuccess)
{
	if (bIsSuccess)
	{
		EndSessionSuccess(SessionName);
	}
	else
	{
		EndSessionFailed();
	}
}

void UAccelByteInGameMenu::EndSessionSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("End Session success"));

	DestroyCustomGamesSession();
}

void UAccelByteInGameMenu::EndSessionFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("End Session failed"));
}

void UAccelByteInGameMenu::DestroyCustomGamesSessionComplete(FName SessionName, bool bIsSuccess)
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

void UAccelByteInGameMenu::DestroyCustomGamesSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Destroy Session success"));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UAccelByteInGameMenu::DestroyCustomGamesFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Destroy Session failed"));
}