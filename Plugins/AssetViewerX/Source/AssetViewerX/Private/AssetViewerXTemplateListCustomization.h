#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Views/SListView.h"

struct FAssetViewerXTemplate;

class FAssetViewerXTemplateListCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();

    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
    void OnAddTemplate();
    void OnRemoveTemplate(int32 TemplateIndex);
    void RefreshCachedData();
    TSharedRef<SWidget> CreateTemplateWidget(int32 TemplateIndex);

    TSharedPtr<IPropertyHandle> StructPropertyHandle;
    TSharedPtr<IPropertyHandleArray> TemplatesHandle;
    TArray<TSharedPtr<FAssetViewerXTemplate>> CachedTemplates;
};

class FAssetViewerXTemplateCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();

    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
};

class FAssetViewerXElementCustomization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();
    
    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
    void OnEntriesChanged();

    TSharedPtr<IPropertyHandle> ThisPropertyHandle;
    TSharedPtr<IPropertyUtilities> PropertyUtilities;
};

class FAssetViewerXElementArrayBuilder : public FDetailArrayBuilder
{
public:
    FAssetViewerXElementArrayBuilder(TSharedRef<IPropertyHandle> InArrayPropertyHandle, IDetailChildrenBuilder& InChildBuilder);

    virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;
    virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;

private:
    void CustomizeArrayElementWidget(TSharedRef<IPropertyHandle> Property, IDetailChildrenBuilder& ChildrenBuilder);
    
    TSharedPtr<IPropertyHandleArray> ArrayPropertyHandle;
    IDetailChildrenBuilder& ChildBuilder;
};

class FAssetViewerXEntriesArrayBuilder : public FDetailArrayBuilder
{
public:
    FAssetViewerXEntriesArrayBuilder(TSharedRef<IPropertyHandle> InArrayPropertyHandle, IDetailChildrenBuilder& InChildBuilder);

    virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;
    virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;

private:
    void CustomizeArrayEntryWidget(TSharedRef<IPropertyHandle> Property, IDetailChildrenBuilder& ChildrenBuilder);
    
    TSharedPtr<IPropertyHandleArray> ArrayPropertyHandle;
    IDetailChildrenBuilder& ChildBuilder;
};
