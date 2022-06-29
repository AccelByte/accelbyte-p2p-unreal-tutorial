// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "AccelByteInGameMenu.generated.h"

class UButton;

/**
 * In Games Menu (P2P)
 * This code covers AccelByte sevices including:
 *
 * - Destroy custom games session
 * - End custom games session
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteInGameMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	/**
	* @brief Scroll Box for Custom Games List Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_EndGame;

	/**
	* @brief Editable Text Box for Server Name inside CustomGames Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Cancel;

	/**
	* @brief Varibale Pointer for Online Session.
	*/
	IOnlineSessionPtr SessionInterface;

	/**
	* @brief Create custom games session.
	*/
	void EndGamesSession();

	/**
	* @brief Exit or Destroy the Server Menu Widget.
	*/
	void DestroyCustomGamesSession();

private:
	/**
	* @brief End current running session.
	*/
	UFUNCTION()
	void ClickEndSession();

	/**
	* @brief Close current in game menu pop up.
	*/
	UFUNCTION()
	void ClickCancelInGameMenu();

	/**
	* @brief Called after create session process is complete.
	*/
	void EndSessionComplete(FName SessionName, bool bIsSuccess);

	/**
	* @brief Called after create session process is success.
	*/
	void EndSessionSuccess(FName SessionName);

	/**
	* @brief Called after create session process is fail.
	*/
	void EndSessionFailed();

	/**
	* @brief Called after Destroy session process is complete.
	*/
	void DestroyCustomGamesSessionComplete(FName SessionName, bool bIsSuccess);

	/**
	* @brief Called after Destroy session process is success.
	*/
	void DestroyCustomGamesSuccess(FName SessionName);

	/**
	* @brief Called after Destroy session process is fail.
	*/
	void DestroyCustomGamesFailed();

	/**
	* @brief Variable to save the current session name.
	*/
	FName CurrentGameSessionName;
};
