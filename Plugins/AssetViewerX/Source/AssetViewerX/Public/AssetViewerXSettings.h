// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AssetViewerXSettings.generated.h"

UENUM()
enum class EAssetViewerXEntryType : uint8
{
	Property,
	Category,
};

USTRUCT()
struct FAssetViewerXEntry
{
	GENERATED_BODY()

	//Property or category name
	UPROPERTY(EditAnywhere)
	FName Name;
	
	UPROPERTY(EditAnywhere)
	EAssetViewerXEntryType Type = EAssetViewerXEntryType::Property;
};

USTRUCT()
struct FAssetViewerXElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UObject> Object;
	
	UPROPERTY(EditAnywhere)
	TArray<FAssetViewerXEntry> Entries;
};

USTRUCT()
struct FAssetViewerXTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName TemplateName;
	
	UPROPERTY(EditAnywhere)
	TArray<FAssetViewerXElement> Elements;
};

USTRUCT()
struct FAssetViewerXTemplateList
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FAssetViewerXTemplate> Templates;
};

UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName = "AssetViewerX", ToolTip="Configure AssetViewerX here"))
class ASSETVIEWERX_API UAssetViewerXSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category="Templates")
	FAssetViewerXTemplateList TemplateList;

	UPROPERTY(EditAnywhere, Category="TEST")
	FAssetViewerXTemplateList TestTemplateList;

	UPROPERTY(EditAnywhere, Category="TEST")
	FAssetViewerXTemplate TestTemplate;
	
	UPROPERTY(EditAnywhere, Category="TEST")
	FAssetViewerXElement TestElement;
	
	UPROPERTY(EditAnywhere, Category="TEST")
	FAssetViewerXEntry TestElementEntry;
};
