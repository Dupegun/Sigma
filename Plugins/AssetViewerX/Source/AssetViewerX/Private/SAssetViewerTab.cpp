
#include "SAssetViewerTab.h"
#include "SAssetViewerTemplateEditor.h"

void SAssetViewerTab::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(5)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Asset Viewer X"))
				.Justification(ETextJustify::Center)
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.Padding(10)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					// Template editor widget
					SAssignNew(TemplateEditor, SAssetViewerTemplateEditor)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			.Padding(5)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					SNew(SButton)
					.Text(FText::FromString("Save Templates"))
					.OnClicked_Lambda([this]()
					{
						// if (UAssetViewerTemplateManager* Manager = GetTemplateManager())
						// {
						// 	Manager->SaveTemplatesToConfig();
						// 	return FReply::Handled();
						// }
						// return FReply::Unhandled();
						return FReply::Handled();
					})
				]
			]
		]
	];
}
