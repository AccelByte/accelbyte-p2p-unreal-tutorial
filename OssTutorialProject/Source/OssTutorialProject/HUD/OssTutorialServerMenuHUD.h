// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OssTutorialServerMenuHUD.generated.h"

class UAccelByteServerMenu;

/**
 * Menu Widget Controller. All Server Menu UI Widget functionality controlled here.
 */
UCLASS()
class OSSTUTORIALPROJECT_API AOssTutorialServerMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	/**
	* @brief Getter for Server Menu widget
	*/
	UAccelByteServerMenu* GetServerMenu() const { return ServerMenu; }

protected:
	/**
	* @brief Called at the beginning of start game
	*/
	virtual void BeginPlay() override;
	
	/**
	* @brief Called at the beginning of end game or level
	*/
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

private:
	/**
	* @brief Shows Server Menu on screen
	*/
	void OpenServerMenu();

	/**
	* @brief Remove Server Menu on screen
	*/
	void CloseServerMenu();

	/**
	* @brief Server Menu widget class
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAccelByteServerMenu> ServerMenuClass;

	/**
	* @brief Server Menu widget pointer
	*/
	UPROPERTY()
	UAccelByteServerMenu* ServerMenu;
};
