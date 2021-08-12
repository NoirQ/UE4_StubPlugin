// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class StubPlugin : ModuleRules
	{
		public StubPlugin(ReadOnlyTargetRules Target) : base (Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/StubPlugin/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
                    "Engine",
                    "LevelEditor",
                    "CoreUObject",
                    "UMG",
                    "EditorStyle",
                    "Projects",
                    "DesktopPlatform",
                    "Sockets",
                    "Networking",
                    "UnrealEd",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Slate",
                    "SlateCore",
                    "DesktopPlatform",
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
                    
				}
				);
		}
	}
}