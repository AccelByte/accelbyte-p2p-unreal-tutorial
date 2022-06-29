// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystemUtils.h"
#include "AccelByteServerPassword.generated.h"

class UButton;
class UEditableTextBox;
class AOssTutorialMenuHUD;

/**
 *
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteServerPassword : public UUserWidget
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
	* @brief Button for Closing Password Menu.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_CancelJoinServer;

	/**
	* @brief Button for Confirm Password Menu.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_JoinServer;

	/**
	* @brief Editable Text Box for Input Server Password inside Password Menu Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Etb_InputServerPassword;

	/**
	* @brief Join to custom games session.
	*/
	void JoinCustomGamesSession();

	/**
	* @brief Instantiate all casting to the tutorial menu HUD.
	*/
	UPROPERTY()
	AOssTutorialMenuHUD* TutorialMenuHUD;
private:
	/**
	* @brief Join a Session By Confirming the Password First.
	*/
	UFUNCTION()
	void ClickConfirmPasswordButton();

	/**
	* @brief Join a Session.
	*/
	UFUNCTION()
	void ClickCancelConfirmButton();

	/**
	* @brief Called after join session process is complete.
	*/
	void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/**
	* @brief Called after join session process is success.
	*/
	void JoinSessionSuccess(FName SessionName);

	/**
	* @brief Called after join session process is fail.
	*/
	void JoinSessionFailed();

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
