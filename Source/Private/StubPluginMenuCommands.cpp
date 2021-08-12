#include "StubPluginPrivatePCH.h"
#include "StubPluginMenuCommands.h"

void FStubPluginCommands::RegisterCommands()
{
	UI_COMMAND(TestButton, "TestButton", "This button does not do anything", EUserInterfaceActionType::Button, FInputChord());
}

