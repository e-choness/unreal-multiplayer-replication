// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class prototype : ModuleRules
{
	public prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "NavigationSystem", "AIModule", "PlayFab", "PlayFabCpp", "PlayFabCommon" });
	}
}
