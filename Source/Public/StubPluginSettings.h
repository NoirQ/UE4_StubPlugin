// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StubPluginSettings.generated.h"

/**
 *  Use this class to add an item to the preferences
 */
UCLASS(Config = Editor, defaultconfig)
class STUBPLUGIN_API UStubPluginSettings : public UObject
{
	GENERATED_BODY()
public: 
	UStubPluginSettings(const FObjectInitializer& ObjectInitalizer);

	/*UPROPERTY(EditAnywhere, config, Category = Custom)
	bool testBoolean;

	UPROPERTY(EditAnywhere, config, Category = Custom, meta = (EditCondition = testBoolean))
	FString testString;*/

	
};
