#pragma once

#include "StubPluginPrivatePCH.h"
#include "StubPluginMenuCommands.h"

#include "StubPluginSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "StubPluginStyle.h"


#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "StubPlugin"
#define STUBLOC "StubPlugin"
#define STUBLOCTOOLTIP "StubPlugin_Tooltip"
#endif

class FStubPlugin : public IStubPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// adds button to toolbar
	void AddMyToolbarExtension(FToolBarBuilder& ToolbarBuilder);

	// Makes the menu for the above button
	TSharedRef<SWidget> GenerateToolbarMenuWidget();

	// Following are for extending the right click menu of selected actors
	virtual bool SupportsDynamicReloading() override;
	TSharedPtr<FExtender> Extender;
	static void ExtendMenu(class FMenuBuilder& MenuBuilder);
	static TSharedRef<FExtender> OnExtendLevelEditorMenu(const TSharedRef<FUICommandList> CommandList, TArray<AActor*> SelectedActors);


	// bind the button to an action
	TSharedPtr<FUICommandList> MyCommandBindings;
	void BindCommands();

	// add setttings to the preferences
	void RegisterCustomSettings();
	void UnregisterCustomSettings();
	bool HandleSaveSettings();



	// do stuff
	void TestButton();

	static void ExtendTestButton();

};

