// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteServerPassword.h"
#include "OssTutorialProject/AccelByte/ServerMenu/AccelByteServerMenu.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "OssTutorialProject/OssTutorialProjectGameInstance.h"
#include "OssTutorialProject/HUD/OssTutorialMenuHUD.h"

void UAccelByteServerPassword::InitData(const FOnlineSessionSearchResult& SearchResult)
{
	SessionData = SearchResult;
	CustomGameSessionName = FName(SearchResult.Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString());
}

void UAccelByteServerPassword::NativeConstruct()
{
	Super::NativeConstruct();

	TutorialMenuHUD = Cast<AOssTutorialMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Btn_CancelJoinServer->OnClicked.AddUniqueDynamic(this, &UAccelByteServerPassword::ClickCancelConfirmButton);

	Btn_JoinServer->OnClicked.AddUniqueDynamic(this, &UAccelByteServerPassword::ClickConfirmPasswordButton);
}

void UAccelByteServerPassword::JoinCustomGamesSession()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Joining a Session"));

			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UAccelByteServerPassword::JoinSessionComplete);

			SessionInterface->JoinSession(0, NAME_GameSession, SessionData);
			/*Note: Uncomment this if you need to change the session name variable*/
			//SessionInterface->JoinSession(0, CustomGameSessionName, SessionData);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Join Session Failed; Session Interface is invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Join Session Failed; Subsystem Invalid"));
	}
}

void UAccelByteServerPassword::ClickConfirmPasswordButton()
{
	const FString InputedPassword = Etb_InputServerPassword->GetText().ToString();

	const FString ActualPassword = SessionData.Session.SessionSettings.Settings.FindRef("SESSION_PASSWORD").Data.ToString();

	if (InputedPassword == ActualPassword)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Password is correct"));

		JoinCustomGamesSession();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Password is not same, Try again"));
	}
}

void UAccelByteServerPassword::ClickCancelConfirmButton()
{
	this->RemoveFromViewport();
}

void UAccelByteServerPassword::JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	switch (Result)
	{
	case EOnJoinSessionCompleteResult::Success:
		JoinSessionSuccess(SessionName);
		break;
	default:
		JoinSessionFailed();
		break;
	}
	SessionInterface->ClearOnJoinSessionCompleteDelegates(this);
}

void UAccelByteServerPassword::JoinSessionSuccess(FName SessionName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Joining session success, session name %s"), *SessionName.ToString()));

	if (!SessionInterface->GetResolvedConnectString(SessionName, ServerAddress))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Joining session failed; Couldn't get connect string"));
		return;
	}

	auto GameInstance = Cast<UOssTutorialProjectGameInstance>(GetGameInstance());
	GameInstance->InitSessionName(SessionName);
	/*Note: Uncomment this if you need to change the session name variable*/
	//GameInstance->InitSessionName(CustomGameSessionName);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
}

void UAccelByteServerPassword::JoinSessionFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Joining session failed"));
}
