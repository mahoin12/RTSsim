// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTSsim : ModuleRules
{
	public RTSsim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
			"InputCore", "HeadMountedDisplay", "NavigationSystem",
			"AIModule", "GameplayTasks" });
	}
}
