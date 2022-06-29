// Copyright (c) 2022 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

using UnrealBuildTool;

public class OssTutorialProject : ModuleRules
{
	public OssTutorialProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AccelByteUe4Sdk", "AccelByteNetworkUtilities", "OnlineSubsystemAccelByte",  "UMG", "Slate", "SlateCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities", "OnlineSubsystem", "OnlineSubsystemSteam", "Steamworks", "http", "WebBrowserWidget" });
	}
}
