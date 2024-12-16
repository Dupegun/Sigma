
#include "SAssetViewerTemplateEditor.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SScrollBox.h"

void SAssetViewerTemplateEditor::Construct(const FArguments& InArgs)
{
    RefreshTemplates();

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(5)
        [
            SNew(STextBlock)
            .Text(FText::FromString("Templates"))
        ]
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(5)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .FillWidth(1.0f)
            .Padding(5)
            [
                SNew(SEditableTextBox)
                .HintText(FText::FromString("Enter Template Name"))
                .OnTextCommitted(this, &SAssetViewerTemplateEditor::OnTemplateNameCommitted)
                .SelectAllTextWhenFocused(true)
                .SelectAllTextOnCommit(true)
                .RevertTextOnEscape(true)
            ]
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(5)
            [
                SNew(SButton)
                .Text(FText::FromString("Add Template"))
                .OnClicked(this, &SAssetViewerTemplateEditor::OnAddTemplateClicked)
            ]
        ]
        + SVerticalBox::Slot()
        .FillHeight(1.0f)
        .Padding(5)
        [
            SNew(SScrollBox)
            + SScrollBox::Slot()
            [
                GenerateTemplates()
            ]
        ]
    ];
}

TSharedRef<SWidget> SAssetViewerTemplateEditor::GenerateTemplates()
{
    return SNew(SVerticalBox)
    + SVerticalBox::Slot()
    .AutoHeight()
    .Padding(5)
    [
        SNew(STextBlock)
        .Text(FText::FromString("Existing Templates"))
    ]
    + SVerticalBox::Slot()
    .AutoHeight()
    .Padding(5)
    [
        SNew(SScrollBox)
        .Orientation(Orient_Vertical)
        + SScrollBox::Slot()
        [
            // Iterate through the template list to display each template
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(5)
            [
                SNew(STextBlock)
                .Text(FText::FromString("Template 1 (Example)"))
            ]
        ]
    ];
}

void SAssetViewerTemplateEditor::RefreshTemplates()
{
}

FReply SAssetViewerTemplateEditor::OnAddTemplateClicked()
{
    return FReply::Handled();
}

void SAssetViewerTemplateEditor::OnTemplateNameCommitted(const FText& InText, ETextCommit::Type InCommitType)
{
}
