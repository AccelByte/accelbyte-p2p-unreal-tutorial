// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteAuth.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "OssTutorialProject/HUD/OssTutorialMenuHUD.h"
#include "OnlineSubsystemAccelByte/Public/OnlineSubsystemAccelByteDefines.h"

void UAccelByteAuth::NativeConstruct()
{
	Super::NativeConstruct();

	TutorialMenuHUD = Cast<AOssTutorialMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Btn_Login->OnClicked.AddUniqueDynamic(this, &UAccelByteAuth::OnClickLoginButton);
}

void UAccelByteAuth::AccelByteOssLogin()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		const IOnlineIdentityPtr IdentityInterface = OnlineSub->GetIdentityInterface();

		if (IdentityInterface.IsValid())
		{
			FOnlineAccountCredentials AccountCredentials;

			AccountCredentials.Type = "AccelByte";
			AccountCredentials.Id = Etb_Username->GetText().ToString();
			AccountCredentials.Token = Etb_Password->GetText().ToString();

			//Login
			IdentityInterface->Login(PlayerNum, AccountCredentials);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Identity Interface is Invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Online Subsystem is Invalid"));
	}
}

void UAccelByteAuth::AccelByteOssLogout()
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	if (OnlineSub)
	{
		const IOnlineIdentityPtr IdentityInterface = OnlineSub->GetIdentityInterface();

		if (IdentityInterface.IsValid())
		{
			//Log out
			IdentityInterface->Logout(PlayerNum);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Identity Interface is Invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Online Subsystem is Invalid"));
	}
}

void UAccelByteAuth::OnClickLoginButton()
{
	//Login Delegate
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	if (!OnlineSub->GetIdentityInterface()->OnLoginCompleteDelegates->IsBoundToObject(this))
	{
		OnlineSub->GetIdentityInterface()->OnLoginCompleteDelegates->AddUObject(this, &UAccelByteAuth::LoginComplete);
	}
	AccelByteOssLogin();
}

void UAccelByteAuth::OnClickLogoutButton()
{
	//Logout Delegate
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);
	if (!OnlineSub->GetIdentityInterface()->OnLogoutCompleteDelegates->IsBoundToObject(this))
	{
		OnlineSub->GetIdentityInterface()->OnLogoutCompleteDelegates->AddUObject(this, &UAccelByteAuth::LogoutComplete);
	}
	AccelByteOssLogout();
}

void UAccelByteAuth::LoginComplete(int32 PlayerNumber, bool bIsSuccess, const FUniqueNetId& UserId, const FString& ErrorMessage)
{
	if (bIsSuccess)
	{
		LoginSuccess(bIsSuccess);
	}
	else
	{
		LoginFailed(ErrorMessage);
	}
}

void UAccelByteAuth::LoginSuccess(bool bIsSuccess)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Login with Username via AB OSS is Success"));

	TutorialMenuHUD->OnLoginRequest.Broadcast(bIsSuccess);
}

void UAccelByteAuth::LoginFailed(const FString& ErrorMessage)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Login with Username via AB OSS is Failed, Message: %s"), *ErrorMessage));
}

void UAccelByteAuth::LogoutComplete(int32 PlayerNumber, bool bIsSuccess)
{
	if (bIsSuccess)
	{
		LogoutSuccess(bIsSuccess);
	}
	else
	{
		LogoutFailed();
	}
}

void UAccelByteAuth::LogoutSuccess(bool bIsSuccess)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Logout via AB OSS is Success"));

	if (TutorialMenuHUD == nullptr)
	{
		TutorialMenuHUD = Cast<AOssTutorialMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	}

	TutorialMenuHUD->OnLogoutRequest.Broadcast(bIsSuccess);
}

void UAccelByteAuth::LogoutFailed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Logout via AB OSS is Failed"));
}