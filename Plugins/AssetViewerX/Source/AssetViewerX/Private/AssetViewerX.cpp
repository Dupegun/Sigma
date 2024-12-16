// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetViewerX.h"
#include "AssetViewerXStyle.h"
#include "AssetViewerXCommands.h"
#include "LevelEditor.h"
#include "SAssetViewerTab.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName AssetViewerXTabName("AssetViewerX");

#define LOCTEXT_NAMESPACE "FAssetViewerXModule"

void FAssetViewerXModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssetViewerXStyle::Initialize();
	FAssetViewerXStyle::ReloadTextures();

	FAssetViewerXCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetViewerXCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAssetViewerXModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetViewerXModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AssetViewerXTabName, FOnSpawnTab::CreateRaw(this, &FAssetViewerXModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAssetViewerXTabTitle", "AssetViewerX"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAssetViewerXModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetViewerXStyle::Shutdown();

	FAssetViewerXCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AssetViewerXTabName);
}

TSharedRef<SDockTab> FAssetViewerXModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SAssetViewerTab)
		];
}

void FAssetViewerXModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AssetViewerXTabName);
}

void FAssetViewerXModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAssetViewerXCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AssetsToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAssetViewerXCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetViewerXModule, AssetViewerX)