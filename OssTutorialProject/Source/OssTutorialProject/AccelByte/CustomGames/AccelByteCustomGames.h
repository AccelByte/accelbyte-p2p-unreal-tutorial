// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.
#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"

#include "Blueprint/UserWidget.h"
#include "AccelByteCustomGames.generated.h"

class UButton;
class UScrollBox;
class UEditableTextBox;
class UAccelByteServerListEntry;
class AOssTutorialMenuHUD;

/**
 * Custom Games Setup (P2P)
 * This code covers AccelByte sevices including:
 *
 * - Create custom games session
 * - Find custom games session
 * - Log Out 
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteCustomGames : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	/**
	* @brief Scroll Box for Custom Games List Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UScrollBox* Sb_ServerList;

	/**
	* @brief Editable Text Box for Server Name inside CustomGames Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Etb_ServerName;

	/**
	* @brief Editable Text Box for Server Password inside CustomGames Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Etb_ServerPassword;

	/**
	* @brief Button for Create Server Session.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_CreateServer;

	/**
	* @brief Button for Refresh Available Server Session.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_RefreshList;

	/**
	* @brief Button for going back to Lobby Menu (Log out for now).
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_BackToLobby;

	/**
	* @brief Instantiate all casting to the tutorial menu HUD.
	*/
	UPROPERTY()
	AOssTutorialMenuHUD* TutorialMenuHUD;

	/**
	* @brief Create custom games session.
	*/
	void CreateCustomGamesSession();

	/**
	* @brief Find custom games session.
	*/
	void FindCustomGamesSession();

private:
	/**
	* @brief Create a New Session.
	*/
	UFUNCTION()
	void OnClickCreateSession();

	/**
	* @brief Refresh The Session List
	*/
	UFUNCTION()
	void RefreshSessionList();

	/**
	* @brief Closing the custom games menu widget.
	*/
	UFUNCTION()
	void CloseCustomGamesMenu();

	/**
	* @brief Called after create session process is complete.
	*/
	void CreateSessionComplete(FName SessionName, bool bIsSuccess);

	/**
	* @brief Called after create session process is success.
	*/
	void CreateSessionSuccess(FName SessionName);

	/**
	* @brief Called after create session process is fail.
	*/
	void CreateSessionFailed();

	/**
	* @brief Called after find session process is complete.
	*/
	void FindSessionComplete(bool bIsSuccess);

	/**
	* @brief Called after find session process is success.
	*/
	void FindSessionSuccess();

	/**
	* @brief Called after find session process is fail.
	*/
	void FindSessionFailed();

	/**
	* @brief Varibale Pointer for Online Session.
	*/
	IOnlineSessionPtr SessionInterface;

	/**
	* @brief Variable Pointer for Search Parameters and Results.
	*/
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/**
	* @brief Reference to Party Player Entry Class.
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteServerListEntry> CustomSessionEntryClass;

	/*
	* @brief Refresh Time Latency
	*/
	const float RefreshTime = 120.0f;

	/*
	* @brief Break To Refresh Latencies
	*/
	const bool bNeedRefresh = true;

	/*
	* @brief Timer Handle Delegate
	*/
	FTimerHandle MemberTimerHandle;
};
