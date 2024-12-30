#include "AssetViewerXTemplateListCustomization.h"

#include "AssetViewerXSettings.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "PropertyCustomizationHelpers.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "AssetViewerXTemplateCustomization"

TSharedRef<IPropertyTypeCustomization> FAssetViewerXTemplateListCustomization::MakeInstance()
{
    return MakeShared<FAssetViewerXTemplateListCustomization>();
}

void FAssetViewerXTemplateListCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    StructPropertyHandle = PropertyHandle;
    TemplatesHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXTemplateList, Templates))->AsArray();

    RefreshCachedData();

    HeaderRow
    .NameContent()
    [
        PropertyHandle->CreatePropertyNameWidget()
    ]
    .ValueContent()
    .MinDesiredWidth(300.0f)
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(0, 0, 5, 0)
            [
                SNew(SButton)
                .Text(LOCTEXT("AddTemplate", "Add Template"))
                .OnClicked(FOnClicked::CreateLambda([this]()
                {
                    OnAddTemplate();
                    return FReply::Handled();
                }))
            ]
        ]
    ];
}

void FAssetViewerXTemplateListCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    uint32 NumTemplates;
    TemplatesHandle->GetNumElements(NumTemplates);

    for (uint32 TemplateIndex = 0; TemplateIndex < NumTemplates; ++TemplateIndex)
    {
        // FAssetViewerXTemplate
        TSharedPtr<IPropertyHandle> TemplateHandle = TemplatesHandle->GetElement(TemplateIndex);
        TSharedPtr<IPropertyHandle> TemplateNameHandle = TemplateHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXTemplate, TemplateName));
        TSharedPtr<IPropertyHandle> ElementsHandle = TemplateHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXTemplate, Elements));
        
        // Customize the row for each template
        IDetailPropertyRow& Row = ChildBuilder.AddProperty(TemplateHandle.ToSharedRef());
        Row.CustomWidget(true)
        .NameContent()
        [
            TemplateNameHandle->CreatePropertyValueWidget()
        ]
        .ValueContent()
        [
            CreateTemplateWidget(TemplateIndex)
        ];
    }
}

TSharedRef<SWidget> FAssetViewerXTemplateListCustomization::CreateTemplateWidget(int32 TemplateIndex)
{
    TSharedPtr<IPropertyHandle> TemplateHandle = TemplatesHandle->GetElement(TemplateIndex);
    TSharedPtr<IPropertyHandle> ElementsHandle = TemplateHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXTemplate, Elements));

    return SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(0, 2)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(0, 0, 5, 0)
            [
                ElementsHandle->CreatePropertyValueWidget()
            ]
            + SHorizontalBox::Slot()
            .AutoWidth()
            [
                SNew(SButton)
                .Text(LOCTEXT("RemoveTemplate", "Remove Template"))
                .OnClicked(FOnClicked::CreateLambda([this, TemplateIndex]()
                {
                    OnRemoveTemplate(TemplateIndex);
                    return FReply::Handled();
                }))
            ]
        ];
}

void FAssetViewerXTemplateListCustomization::OnAddTemplate()
{
    FScopedTransaction Transaction(LOCTEXT("AddTemplate", "Add Template"));
    StructPropertyHandle->NotifyPreChange();

    uint32 NumTemplates;
    TemplatesHandle->GetNumElements(NumTemplates);
    
    TemplatesHandle->AddItem();

    StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
    RefreshCachedData();
}

void FAssetViewerXTemplateListCustomization::OnRemoveTemplate(int32 TemplateIndex)
{
    FScopedTransaction Transaction(LOCTEXT("RemoveTemplate", "Remove Template"));
    StructPropertyHandle->NotifyPreChange();

    TemplatesHandle->DeleteItem(TemplateIndex);

    StructPropertyHandle->NotifyPostChange(EPropertyChangeType::ValueSet);
    RefreshCachedData();
}

void FAssetViewerXTemplateListCustomization::RefreshCachedData()
{
    CachedTemplates.Empty();

    uint32 NumTemplates;
    TemplatesHandle->GetNumElements(NumTemplates);

    for (uint32 i = 0; i < NumTemplates; ++i)
    {
        TSharedPtr<FAssetViewerXTemplate> Template = MakeShared<FAssetViewerXTemplate>();
        CachedTemplates.Add(Template);
    }
}

TSharedRef<IPropertyTypeCustomization> FAssetViewerXTemplateCustomization::MakeInstance()
{
    return MakeShared<FAssetViewerXTemplateCustomization>();
}

void FAssetViewerXTemplateCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    HeaderRow
    .NameContent()
    [
        PropertyHandle->CreatePropertyNameWidget()
    ]
    .ValueContent()
    [
        PropertyHandle->CreatePropertyValueWidget()
    ];
}

void FAssetViewerXTemplateCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    TSharedPtr<IPropertyHandle> ElementsHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXTemplate, Elements));
    
    TSharedRef<FAssetViewerXElementArrayBuilder> ArrayBuilder = MakeShared<FAssetViewerXElementArrayBuilder>(
        ElementsHandle.ToSharedRef(),
        ChildBuilder
    );

    ChildBuilder.AddCustomBuilder(ArrayBuilder);
}

// Element Customization Implementation
TSharedRef<IPropertyTypeCustomization> FAssetViewerXElementCustomization::MakeInstance()
{
    return MakeShared<FAssetViewerXElementCustomization>();
}

void FAssetViewerXElementCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    TSharedPtr<IPropertyHandle> ObjectHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXElement, Object));
    TSharedPtr<IPropertyHandle> EntriesHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXElement, Entries));

    ThisPropertyHandle = PropertyHandle.ToSharedPtr();
    PropertyUtilities = CustomizationUtils.GetPropertyUtilities();
    
    HeaderRow
    .NameContent()
    [
        ObjectHandle->CreatePropertyValueWidget()
    ]
    .ValueContent()
    [
        EntriesHandle->CreatePropertyValueWidget()
    ];

    EntriesHandle->SetOnPropertyValueChanged(
        FSimpleDelegate::CreateSP(this, &FAssetViewerXElementCustomization::OnEntriesChanged));
}

void FAssetViewerXElementCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    TSharedPtr<IPropertyHandle> EntriesHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXElement, Entries));
    
    TSharedRef<FAssetViewerXEntriesArrayBuilder> ArrayBuilder = MakeShared<FAssetViewerXEntriesArrayBuilder>(
        EntriesHandle.ToSharedRef(),
        ChildBuilder
    );

    ChildBuilder.AddCustomBuilder(ArrayBuilder);
    
    // TSharedPtr<IPropertyHandle> EntriesHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXElement, Entries));
    //
    // uint32 NumEntries;
    // EntriesHandle->GetNumChildren(NumEntries);
    //
    // for (uint32 i = 0; i < NumEntries; ++i)
    // {
    //     TSharedPtr<IPropertyHandle> EntryHandle = EntriesHandle->GetChildHandle(i);
    //     TSharedPtr<IPropertyHandle> NameHandle = EntryHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXEntry, Name));
    //     TSharedPtr<IPropertyHandle> TypeHandle = EntryHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXEntry, Type));
    //     
    //     FDetailWidgetRow& Row = ChildBuilder.AddCustomRow(FText::FromString(FString::Printf(TEXT("Entry (%d)"), i)));
    //     Row.NameContent()
    //     [
    //         TypeHandle->CreatePropertyValueWidget()
    //     ]
    //     .ValueContent()
    //     [
    //         NameHandle->CreatePropertyValueWidget()
    //     ];
    // }
}

void FAssetViewerXElementCustomization::OnEntriesChanged()
{
    if (PropertyUtilities)
    {
        PropertyUtilities->RequestRefresh();
    }
}

FAssetViewerXElementArrayBuilder::FAssetViewerXElementArrayBuilder(TSharedRef<IPropertyHandle> InArrayPropertyHandle, IDetailChildrenBuilder& InChildBuilder)
    : FDetailArrayBuilder(InArrayPropertyHandle, false, true), // No drag/drop, allow buttons
      ArrayPropertyHandle(InArrayPropertyHandle->AsArray()),
      ChildBuilder(InChildBuilder)
{
    OnGenerateArrayElementWidget(FOnGenerateArrayElementWidget::CreateLambda(
        [this](TSharedRef<IPropertyHandle> ElementHandle, int32 Index, IDetailChildrenBuilder& Builder)
        {
            //TODO ?
        }));
}

void FAssetViewerXElementArrayBuilder::GenerateHeaderRowContent(FDetailWidgetRow& NodeRow)
{
    auto PropertyHandle = GetPropertyHandle();
    TSharedPtr<SHorizontalBox> ContentHorizontalBox;
    SAssignNew(ContentHorizontalBox, SHorizontalBox);

    if constexpr (constexpr bool bShouldDisplayElementNum = true)
    {
        ContentHorizontalBox->AddSlot()
        [
            PropertyHandle->CreatePropertyValueWidget()
        ];
    }

    FUIAction CopyAction;
    FUIAction PasteAction;
    PropertyHandle->CreateDefaultPropertyCopyPasteActions(CopyAction, PasteAction);
    
    NodeRow
    .CopyAction(CopyAction)
    .PasteAction(PasteAction);
}

void FAssetViewerXElementArrayBuilder::GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder)
{
    uint32 NumChildren = 0;
    ArrayPropertyHandle->GetNumElements(NumChildren);

    for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
    {
        TSharedRef<IPropertyHandle> ArrayElementPropertyHandle = ArrayPropertyHandle->GetElement(ChildIndex);

        CustomizeArrayElementWidget(ArrayElementPropertyHandle, ChildrenBuilder);
    }
    
    FDetailArrayBuilder::GenerateChildContent(ChildrenBuilder);
}

void FAssetViewerXElementArrayBuilder::CustomizeArrayElementWidget(TSharedRef<IPropertyHandle> Property, IDetailChildrenBuilder& ChildrenBuilder)
{
    IDetailPropertyRow& PropertyRow = ChildrenBuilder.AddProperty(Property);
}

FAssetViewerXEntriesArrayBuilder::FAssetViewerXEntriesArrayBuilder(TSharedRef<IPropertyHandle> InArrayPropertyHandle, IDetailChildrenBuilder& InChildBuilder)
    : FDetailArrayBuilder(InArrayPropertyHandle, false, true), // No drag/drop, allow buttons
      ArrayPropertyHandle(InArrayPropertyHandle->AsArray()),
      ChildBuilder(InChildBuilder)
{
    OnGenerateArrayElementWidget(FOnGenerateArrayElementWidget::CreateLambda(
    [this](TSharedRef<IPropertyHandle> ElementHandle, int32 Index, IDetailChildrenBuilder& Builder)
    {
        //TODO ?
    }));
}

void FAssetViewerXEntriesArrayBuilder::GenerateHeaderRowContent(FDetailWidgetRow& NodeRow)
{
    auto PropertyHandle = GetPropertyHandle();
    TSharedPtr<SHorizontalBox> ContentHorizontalBox;
    SAssignNew(ContentHorizontalBox, SHorizontalBox);

    if constexpr (constexpr bool bShouldDisplayElementNum = true)
    {
        ContentHorizontalBox->AddSlot()
        [
            PropertyHandle->CreatePropertyValueWidget()
        ];
    }

    FUIAction CopyAction;
    FUIAction PasteAction;
    PropertyHandle->CreateDefaultPropertyCopyPasteActions(CopyAction, PasteAction);
    
    NodeRow
    .CopyAction(CopyAction)
    .PasteAction(PasteAction);
}

void FAssetViewerXEntriesArrayBuilder::GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder)
{
    uint32 NumChildren = 0;
    ArrayPropertyHandle->GetNumElements(NumChildren);

    for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
    {
        TSharedRef<IPropertyHandle> ArrayEntryPropertyHandle = ArrayPropertyHandle->GetElement(ChildIndex);

        CustomizeArrayEntryWidget(ArrayEntryPropertyHandle, ChildrenBuilder);
    }
    
    FDetailArrayBuilder::GenerateChildContent(ChildrenBuilder);
}

void FAssetViewerXEntriesArrayBuilder::CustomizeArrayEntryWidget(TSharedRef<IPropertyHandle> Property, IDetailChildrenBuilder& ChildrenBuilder)
{
    //IDetailPropertyRow& PropertyRow = ChildrenBuilder.AddProperty(Property);
    
    TSharedPtr<IPropertyHandle> NameHandle = Property->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXEntry, Name));
    TSharedPtr<IPropertyHandle> TypeHandle = Property->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAssetViewerXEntry, Type));

    IDetailPropertyRow& PropertyRow = ChildrenBuilder.AddProperty(Property);
    PropertyRow.CustomWidget()
    .NameContent()
    [
        TypeHandle->CreatePropertyValueWidget()
    ]
    .ValueContent()
    [
        NameHandle->CreatePropertyValueWidget()
    ];
}

#undef LOCTEXT_NAMESPACE
