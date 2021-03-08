// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDisplay.h"
#include "../Item/BasicItemDataAsset.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UInventoryItemDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	if(SlotBorder)
	{
		BorderInitialColor = SlotBorder->BrushColor;		
	}
}

void UInventoryItemDisplay::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if(SlotBorder)
	{
		SlotBorder->SetBrushColor(FLinearColor{1, 1, 0, .5});
	}
}

void UInventoryItemDisplay::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if(SlotBorder)
	{
		SlotBorder->SetBrushColor(BorderInitialColor);
	}
}

void UInventoryItemDisplay::Init(const UBasicItemDataAsset* BasicItemData)
{
	ItemData = BasicItemData;

	if(ItemData)
	{
		ItemIcon->SetBrushFromTexture(ItemData->GetThumbnail());
		//todo replace tile size with global variable
		ItemIcon->Brush.SetImageSize(ItemData->GetItemSize() * 49);
	}
}

FIntPoint UInventoryItemDisplay::GetItemSize() const
{
	if(ItemData)
	{
		return ItemData->GetItemSize();
	}
	else
	{
		return FIntPoint::ZeroValue;
	}
}

