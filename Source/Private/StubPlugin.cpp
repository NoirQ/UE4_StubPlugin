// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "StubPluginPrivatePCH.h"
#include "StubPlugin.h"
#include "StubPluginMenuCommands.h"

#include "StubPluginSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "StubPluginStyle.h"
#include "Editor.h"


IMPLEMENT_MODULE(FStubPlugin, StubPlugin)


void FStubPlugin::StartupModule()
{
#if WITH_EDITOR
	FStubPluginStyle::Initialize();
	FStubPluginCommands::Register();
	BindCommands();
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	TSharedPtr<FExtender> MyExtender = MakeShareable(new FExtender);
	MyExtender->AddToolBarExtension("Content", EExtensionHook::After, NULL, FToolBarExtensionDelegate::CreateRaw(this, &FStubPlugin::AddMyToolbarExtension));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MyExtender);

	RegisterCustomSettings();

	FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors LevelEditorMenuExtenderDelegate;
	LevelEditorMenuExtenderDelegate = FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateStatic(&FStubPlugin::OnExtendLevelEditorMenu);
	auto& MenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	MenuExtenders.Add(LevelEditorMenuExtenderDelegate);
#endif
}

void FStubPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FStubPluginCommands::Unregister();
	FStubPluginStyle::Shutdown();
	if (UObjectInitialized())
	{
		UnregisterCustomSettings();
	}
}

bool FStubPlugin::SupportsDynamicReloading()
{
	return true;
}

void FStubPlugin::ExtendMenu(class FMenuBuilder& MenuBuilder)
{
	FUIAction Action_Test(FExecuteAction::CreateStatic(&FStubPlugin::ExtendTestButton));
	MenuBuilder.BeginSection("Test", LOCTEXT("Actor Menu", "Test"));
	{
		MenuBuilder.AddMenuEntry
		(
			LOCTEXT(STUBLOC, "Actor Button"),
			LOCTEXT(STUBLOCTOOLTIP, "Test Button on an actor"),
			FSlateIcon(),
			Action_Test,
			NAME_None,
			EUserInterfaceActionType::Button
		);
	}
	MenuBuilder.EndSection();
}

TSharedRef<FExtender> FStubPlugin::OnExtendLevelEditorMenu(const TSharedRef<FUICommandList> CommandList, TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender> Extender(new FExtender());
	Extender->AddMenuExtension(
		"ActorSelectVisibilityLevels",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&FStubPlugin::ExtendMenu)
	);
	return Extender;
}

void FStubPlugin::AddMyToolbarExtension(FToolBarBuilder& ToolbarBuilder)
{
	FSlateIcon MyIcon = FSlateIcon(FStubPluginStyle::Get()->GetStyleSetName(), "StubPluginStyle.Icon");
	ToolbarBuilder.BeginSection(TEXT(STUBLOC));
	{
		ToolbarBuilder.AddComboButton(
			FUIAction(),
			FOnGetContent::CreateRaw(this,&FStubPlugin::GenerateToolbarMenuWidget),
			LOCTEXT(STUBLOC, STUBLOC),
			LOCTEXT(STUBLOCTOOLTIP, STUBLOC),
			FSlateIcon(FStubPluginStyle::Get()->GetStyleSetName(), "StubPluginStyle.Icon"),
			false);
			
	}
	ToolbarBuilder.EndSection();

}

TSharedRef<SWidget> FStubPlugin::GenerateToolbarMenuWidget()
{
	FMenuBuilder MenuBuilder(true, MyCommandBindings);

	MenuBuilder.BeginSection(STUBLOC, LOCTEXT("Stub", STUBLOC));
	{
		MenuBuilder.AddMenuEntry(FStubPluginCommands::Get().TestButton);
	}
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}



void FStubPlugin::BindCommands()
{
	MyCommandBindings = MakeShareable(new FUICommandList);
		
	FUICommandList& ActionList = *MyCommandBindings;
	const FStubPluginCommands& Commands = FStubPluginCommands::Get();

	MyCommandBindings->MapAction(
		Commands.TestButton,
		FExecuteAction::CreateRaw(this, &FStubPlugin::TestButton),
		EUIActionRepeatMode::RepeatEnabled);
}


void FStubPlugin::RegisterCustomSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", STUBLOC, LOCTEXT("RuntimeGeneralSettingsName", "Stub Plugin"), LOCTEXT("RuntimeGeneralSettingsDescription", "My config"), GetMutableDefault<UStubPluginSettings>());

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FStubPlugin::HandleSaveSettings);
		}
	}
}

void FStubPlugin::UnregisterCustomSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", STUBLOC);
	}
}

bool FStubPlugin::HandleSaveSettings()
{
	UStubPluginSettings* Settings = GetMutableDefault<UStubPluginSettings>();

	//Todo: Validation
	Settings->SaveConfig();

	return true;
}


// the bits that actuall do stuff:

void FStubPlugin::TestButton()
{
	UE_LOG(LogTemp, Warning, TEXT("This button works!"));
}

void FStubPlugin::ExtendTestButton()
{
	UE_LOG(LogTemp, Warning, TEXT("This static button works!"));
}
