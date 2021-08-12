#include "StubPluginPrivatePCH.h"
#include "StubPluginStyle.h"
#include "SlateStyle.h"
#include "IPluginManager.h"


#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FStubPluginStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )


FString FStubPluginStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("StubPlugin"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FStubPluginStyle::StyleSet = NULL;
TSharedPtr< class ISlateStyle > FStubPluginStyle::Get() { return StyleSet; }

void FStubPluginStyle::Initialize()
{
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("StubPluginStyle"));
	StyleSet->SetContentRoot(FPaths::GetProjectFilePath() / TEXT("Content"));
	StyleSet->SetCoreContentRoot(FPaths::GetProjectFilePath() / TEXT("Content"));

	// Plugins Manager
	{
		StyleSet->Set("StubPluginStyle.Icon", new IMAGE_BRUSH("Icon40", Icon40x40));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FStubPluginStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}