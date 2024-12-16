// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "AssetViewerXStyle.h"

class FAssetViewerXCommands : public TCommands<FAssetViewerXCommands>
{
public:

	FAssetViewerXCommands()
		: TCommands<FAssetViewerXCommands>(TEXT("AssetViewerX"), NSLOCTEXT("Contexts", "AssetViewerX", "AssetViewerX Plugin"), NAME_None, FAssetViewerXStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};