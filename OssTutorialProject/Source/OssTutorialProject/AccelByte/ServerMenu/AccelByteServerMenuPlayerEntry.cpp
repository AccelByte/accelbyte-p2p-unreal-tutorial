// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteServerMenuPlayerEntry.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemAccelByteDefines.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSubsystemTypes.h"

#include "Components/TextBlock.h"

void UAccelByteServerMenuPlayerEntry::InitPlayerData(const FUniqueNetId& PlayerIds)
{
	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(ACCELBYTE_SUBSYSTEM);

	PlayerNickname = OnlineSub->GetIdentityInterface()->GetPlayerNickname(PlayerIds);

	if (PlayerNickname.IsEmpty())
	{
		Tb_PlayersName->SetText(FText::FromString(PlayerIds.ToString()));
	}
	else
	{
		/*Note: work around since GetPlayerNickname only returning the name of local player*/
		//Tb_PlayersName->SetText(FText::FromString(PlayerNickname));
		Tb_PlayersName->SetText(FText::FromString(PlayerIds.ToString().Mid(10,20)));
	}
}