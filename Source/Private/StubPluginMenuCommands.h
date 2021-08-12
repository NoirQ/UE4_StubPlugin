#pragma once


class FStubPluginCommands : public TCommands<FStubPluginCommands>
{

public:
	FStubPluginCommands() : TCommands<FStubPluginCommands>
		(
			"StubPlugin",
			NSLOCTEXT("Contexts", "StubPlugin", "StubPlugin"),
			NAME_None, // "MainFrame" // @todo Fix this crash
			FEditorStyle::GetStyleSetName() // Icon Style Set
			)
	{}

	/** Toggle play */
	TSharedPtr< FUICommandInfo > TestButton;

	virtual void RegisterCommands() override;
};
