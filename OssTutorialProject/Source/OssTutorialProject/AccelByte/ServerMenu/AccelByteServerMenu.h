// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "AccelByteServerMenu.generated.h"

class UTextBlock;
class UScrollBox;
class UButton;
class UAccelByteServerMenuPlayerEntry;
class AOssTutGameModeServerMenu;
class UOssTutorialProjectGameInstance;

/**
 * Custom Games Menu (P2P)
 * This code covers AccelByte sevices including:
 *
 * - Destroy custom games session
 * - Start custom games session
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteServerMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Start the game session.
	*/
	UFUNCTION()
	void OnClickStartServerMenuButton();

	/**
	* @brief Exit or Destroy the Server Menu Widget.
	*/
	UFUNCTION()
	void OnClickExitServerMenuButton();

protected:

	virtual void NativeConstruct() override;

	/**
	* @brief Text Box for Server Name.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_ServerName;
	
	/**
	* @brief Scroll Box for Players in Team A.
	*/
	UPROPERTY(meta = (BindWidget))
	UScrollBox* Sb_TeamA;

	/**
	* @brief Scroll Box for Players in Team B.
	*/
	UPROPERTY(meta = (BindWidget))
	UScrollBox* Sb_TeamB;

	/**
	* @brief Button for Ready to Play.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Ready;

	/**
	* @brief Button for Exit the Server Menu.
	*/
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Exit;

	/**
	* @brief Instantiate Game Mode.
	*/
	AOssTutGameModeServerMenu* ServerMenuGameMode;

	/**
	* @brief Exit or Destroy the Server Menu Widget.
	*/
	void DestroyCustomGamesSession();

	/**
	* @brief Start the custom game session.
	*/
	void StartCustomGamesSession();

private:
	/**
	* @brief Refresh Player Data.
	*/
	void RefreshPlayerList(FName SessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bIsSuccess);

	/**
	* @brief Manager to spawn player entry
	*/
	void PlayerEntryManager(const TArray< FUniqueNetIdRef >& PlayerIds);

	/**
	* @brief Called after Start session process is complete.
	*/
	void StartCustomGamesSessionComplete(FName SessionName, bool bIsSuccess);

	/**
	* @brief Called after Start session process is success.
	*/
	void StartCustomGamesSessionSuccess(FName SessionName);

	/**
	* @brief Called after Start session process is fail.
	*/
	void StartCustomGamesSessionFailed();

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
	* @brief Exit or Destroy the Server Menu Widget.
	*/
	IOnlineSessionPtr SessionInterface;

	/**
	* @brief Variable to Save The Session Name.
	*/
	FName CustomGameSessionName;

	/**
	* @brief Reference to Player Entry Class.
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteServerMenuPlayerEntry> PlayerEntryClass;

	/**
	* @brief Array containing list of player ids in current session.
	*/
	TArray<FUniqueNetIdRef> CurrentPlayerIds;
};
