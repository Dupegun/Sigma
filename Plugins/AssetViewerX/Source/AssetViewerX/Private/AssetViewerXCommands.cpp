// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetViewerXCommands.h"

#define LOCTEXT_NAMESPACE "FAssetViewerXModule"

void FAssetViewerXCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AssetViewerX", "Bring up AssetViewerX window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
