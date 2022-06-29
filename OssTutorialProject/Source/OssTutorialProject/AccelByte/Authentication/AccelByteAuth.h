// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccelByteAuth.generated.h"

class UEditableTextBox;
class UButton;
class AOssTutorialMenuHUD;
class UCanvasPanel;

/**
 * Authentication Games Setup 
 * This code covers AccelByte sevices including:
 *
 * - Login using AccelByte Account using OSS
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteAuth : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Logout a session using AccelByte OSS.
	* Executed automatically on component construction
	*/
	UFUNCTION()
	void OnClickLogoutButton();
	
protected:
	
	virtual void NativeConstruct() override;

	/**
	* @brief Log In Menu Canvas Panel inside MainMenu Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CP_LoginMenu;
	
	/**
	* @brief Editable Text Box for Username inside MainMenu Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Etb_Username;
	
	/**
	* @brief Editable Text Box for Password inside MainMenu Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Etb_Password;
	
	/**
	* @brief Take Button Log In inside MainMenu Widget.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Login;
	
	/**
	 * @brief Instantiate all casting to the main menu HUD
	 */
	AOssTutorialMenuHUD* TutorialMenuHUD;

	/**
	* @brief Logging in with AccelByte OSS
	*/
	void AccelByteOssLogin();

	/**
	* @brief Logging out with AccelByte OSS
	*/
	void AccelByteOssLogout();

	/**
	* @brief The number of user in local client.
	*/
	const int PlayerNum = 0;

private:
	/**
	* @brief Log an account in using AccelByte OSS.
	*/
	UFUNCTION()
	void OnClickLoginButton();

	/**
	* @brief Called after Log In process is complete.
	*/
	void LoginComplete(int32 PlayerNumber, bool bIsSuccess, const FUniqueNetId& UserId, const FString& ErrorMessage);

	/**
	* @brief Function behavior when Log In process is succeeded.
	*/
	void LoginSuccess(bool bIsSuccess);

	/**
	* @brief Function behavior when Log In process is failed.
	*/
	void LoginFailed(const FString& ErrorMessage);

	/**
	* @brief Called after Log Out process is complete.
	*/
	void LogoutComplete(int32 PlayerNumber, bool bIsSuccess);

	/**
	* @brief Function behavior when Log Out process is succeeded.
	*/
	void LogoutSuccess(bool bIsSuccess);

	/**
	* @brief Function behavior when Log Out process is succeeded.
	*/
	void LogoutFailed();
};
