// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OssTutorialMenuHUD.generated.h"

class UAccelByteAuth;
class UAccelByteCustomGames;
class UAccelByteServerPassword;

DECLARE_EVENT_OneParam(AOssTutorialMenuHUD, FOnTutLoginCompletedEvent, bool)
DECLARE_EVENT_OneParam(AOssTutorialMenuHUD, FOnTutLogoutCompletedEvent, bool)
DECLARE_EVENT_OneParam(AOssTutorialMenuHUD, FOnInitSessionPassword, const FOnlineSessionSearchResult&)

/**
 * Menu Widget Controller. All Menu UI Widget functionality controlled here.
 */
UCLASS()
class OSSTUTORIALPROJECT_API AOssTutorialMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	/**
	* @brief Getter for Login Menu widget
	*/
	UAccelByteAuth* GetLoginMenu() const { return LoginMenu; }

	/**
	* @brief Getter for Custom Games Menu widget
	*/
	UAccelByteCustomGames* GetCustomGamesMenu() const { return CustomGamesMenu; }

	/**
	* @brief Getter for Server Password Menu widget
	*/
	UAccelByteServerPassword* GetServerPasswordMenu() const { return ServerPasswordMenu; }

	/**
	* @brief Broadcast delegate after Login is Success
	*/
	FOnTutLoginCompletedEvent OnLoginRequest;

	/**
	* @brief Broadcast delegate after Logout is Success
	*/
	FOnTutLogoutCompletedEvent OnLogoutRequest;

	/**
	* @brief Broadcast delegate to input session password
	*/
	FOnInitSessionPassword OnInitSessionPassword;

protected:
	/**
	* @brief Called at the beginning of start game
	*/
	virtual void BeginPlay() override;

	/**
	* @brief Called at the beginning of end game or level
	*/
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

	/**
	* @brief Login Menu widget class
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteAuth> LoginMenuClass;
		
	/**
	* @brief Custom Games Menu widget class
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteCustomGames> CustomGamesMenuClass;
	
	/**
	* @brief Server Password Menu widget class
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteServerPassword> ServerPasswordMenuClass;

private:
	/**
	* @brief Called after Log In process is complete.
	*/
	void OnLoginSuccess(bool bIsSuccess);

	/**
	* @brief Called after Log Out process is complete.
	*/
	void OnLogoutSuccess(bool bIsSuccess);
	
	/**
	* @brief Called after Log Out process is complete.
	*/
	void OnInitDataSessionPassword(const FOnlineSessionSearchResult& SessionData);

	/**
	* @brief Login Menu widget pointer
	*/
	UPROPERTY()
	UAccelByteAuth* LoginMenu;
	
	/**
	* @brief Custom Games Menu widget pointer
	*/
	UAccelByteCustomGames* CustomGamesMenu;

	/**
	* @brief Server Password Menu widget pointer
	*/
	UPROPERTY()
	UAccelByteServerPassword* ServerPasswordMenu;

	/**
	* @brief Shows Login Menu on screen
	*/
	void OpenLoginMenu();

	/**
	* @brief Shows Custom Games Menu on screen
	*/
	void OpenCustomGamesMenu();

	/**
	* @brief Shows Server Password Menu on screen
	*/
	void OpenServerPasswordMenu();

	/**
	* @brief Destroys Custom Login Menu Widget
	*/
	void CloseLoginMenu();
		
	/**
	* @brief Destroys Custom Games Menu Widget
	*/
	void CloseCustomGamesMenu();

	/**
	* @brief Destroys Server Password Menu Widget
	*/
	void CloseServerPasswordMenu();
};
