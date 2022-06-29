// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

using UnrealBuildTool;
using System.Collections.Generic;

public class OssTutorialProjectTarget : TargetRules
{
	public OssTutorialProjectTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "OssTutorialProject", "AccelByteUe4Sdk", "OnlineSubsystemAccelByte", "AccelByteNetworkUtilities" });
	}
}
