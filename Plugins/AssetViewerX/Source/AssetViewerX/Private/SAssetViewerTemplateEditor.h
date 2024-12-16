#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SAssetViewerTemplateEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAssetViewerTemplateEditor) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> GenerateTemplates();
	void RefreshTemplates();
	FReply OnAddTemplateClicked();
	void OnTemplateNameCommitted(const FText& InText, ETextCommit::Type InCommitType);
	void OnSaveTemplateClicked();

	TArray<TSharedPtr<FString>> Templates;
};
