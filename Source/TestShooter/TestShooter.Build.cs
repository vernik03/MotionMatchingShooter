// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestShooter : ModuleRules
{
	public TestShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NetCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.Add("TestShooter/");

        PublicDependencyModuleNames.AddRange(new string[] {
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks"
        });
    }
}
