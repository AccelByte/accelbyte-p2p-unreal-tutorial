// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

using UnrealBuildTool;
using System.Collections.Generic;

public class OssTutorialProjectEditorTarget : TargetRules
{
	public OssTutorialProjectEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "OssTutorialProject", "AccelByteUe4Sdk", "OnlineSubsystemAccelByte", "AccelByteNetworkUtilities" });
	}
}
