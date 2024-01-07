// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class eos : ModuleRules
{
	public eos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"OnlineServicesInterface",
			"CoreOnline",
			"OnlineSubsystem",
			"OnlineSubsystemEOS",
			"OnlineSubsystemUtils"
		});
	}
}
