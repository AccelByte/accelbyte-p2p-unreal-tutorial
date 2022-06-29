// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystemUtils.h"
#include "AccelByteServerListEntry.generated.h"

class UTextBlock;
class UButton;
class AOssTutorialMenuHUD;
class UAccelByteServerPassword;

/**
 * Server Entry Class. Used for representative available session in Custom Games List.
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteServerListEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Init Data Game Session.
	*/
	void InitData(const FOnlineSessionSearchResult& SearchResult);

protected:
	virtual void NativeConstruct() override;

	/**
	* @brief Text for the name of custom games.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_ServerName;

	/**
	* @brief Text for the game mode of custom games.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_ServerGameMode;

	/**
	* @brief Text for the capacity of custom games.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_ServerCapacity;

	/**
	* @brief Button for join custom games session.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_JoinServer;

	/**
	* @brief Instantiate all casting to the tutorial menu HUD.
	*/
	UPROPERTY()
	AOssTutorialMenuHUD* TutorialMenuHUD;

private:
	/**
	* @brief Join a Session.
	*/
	UFUNCTION()
	void OnClickJoinButton();

	UAccelByteServerPassword* ServerPassword;

	/**
	* @brief Varibale Pointer for Online Session.
	*/
	IOnlineSessionPtr SessionInterface;

	/**
	* @brief Variable to Save Search Result Data.
	*/
	FOnlineSessionSearchResult SessionData;

	/**
	* @brief Variable to Save The Session Name .
	*/
	FName CustomGameSessionName;

	/**
	* @brief Variable to Save The Server Address.
	*/
	FString ServerAddress;
};
