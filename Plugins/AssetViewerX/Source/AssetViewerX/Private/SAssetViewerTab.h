#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SAssetViewerTemplateEditor;

class SAssetViewerTab : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAssetViewerTab) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<SAssetViewerTemplateEditor> TemplateEditor;
};
