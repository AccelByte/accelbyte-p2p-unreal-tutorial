// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "OssTutorialServerMenuHUD.h"

#include "OssTutorialProject/AccelByte/ServerMenu/AccelByteServerMenu.h"

void AOssTutorialServerMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();

	ServerMenu = CreateWidget<UAccelByteServerMenu>(PlayerController, ServerMenuClass.Get());

	OpenServerMenu();
}

void AOssTutorialServerMenuHUD::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	CloseServerMenu();
}

void AOssTutorialServerMenuHUD::OpenServerMenu()
{
	ServerMenu->AddToViewport();
}

void AOssTutorialServerMenuHUD::CloseServerMenu()
{
	ServerMenu->RemoveFromViewport();
}