// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDisplay.h"
#include "../Item/BasicItemDataAsset.h"
#include "Components/Image.h"

void UInventoryItemDisplay::NativeConstruct()
{
	Super::NativeConstruct();

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

