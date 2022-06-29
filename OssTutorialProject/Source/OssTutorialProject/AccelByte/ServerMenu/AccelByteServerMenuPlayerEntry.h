// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccelByteServerMenuPlayerEntry.generated.h"

class UTextBlock;

/**
 * Player Entry Class. Used for representative available player in current session.
 */
UCLASS()
class OSSTUTORIALPROJECT_API UAccelByteServerMenuPlayerEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitPlayerData(const FUniqueNetId& PlayerIds);

protected:
	/**
	* @brief Text Box for Player Name.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_PlayersName;

	/**
	* @brief Text Box for Player Ready Status.
	*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tb_PlayerStatusReady;
private:

	FString PlayerNickname;
};
