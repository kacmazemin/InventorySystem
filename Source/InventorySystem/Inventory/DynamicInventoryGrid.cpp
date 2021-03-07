// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicInventoryGrid.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "InventoryItemDisplay.h"
#include "Components/BorderSlot.h"
#include "Components/Image.h"
#include "InventorySystem/Item/BasicItemDataAsset.h"

void UDynamicInventoryGrid::AddItem(const UBasicItemDataAsset* ItemDataAsset, const int slotNo)
{
	UInventoryItemDisplay* InventoryItemDisplay = CreateWidget<UInventoryItemDisplay>(this, ItemDisplayClass);
	InventoryItemDisplay->Init(ItemDataAsset);

	Slots[slotNo].first->AddChild(InventoryItemDisplay);
	ItemContainer.Add(InventoryItemDisplay);

	if(Slots[slotNo].first)
	{
		UPanelSlot* PanelSlot = Cast<UPanelSlot>(Slots[slotNo].first);
	
		if(UGridSlot* GridSlot = Cast<UGridSlot>(PanelSlot))
		{
			GridSlot->SetColumnSpan(ItemDataAsset->GetItemSize().Y);
			GridSlot->SetRowSpan(ItemDataAsset->GetItemSize().X);
		}
	}

}

void UDynamicInventoryGrid::NativePreConstruct()
{
	Super::NativeConstruct();

	InitInventoryWidget();
}

void UDynamicInventoryGrid::InitInventoryWidget() 
{
	InventoryGridPanel->RowFill.Empty();
	InventoryGridPanel->ColumnFill.Empty();
	
	if(UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridPanelBorder->Slot))
	{
		//Y is column count. column * tileSize calculate X size of PanelSlot.
		CanvasPanelSlot->SetSize({TileSize * InventoryDimension.Y, TileSize * InventoryDimension.X});
	}

	for (int Row = 0; Row < InventoryDimension.X; Row++)
	{
		if(InventoryGridPanel)
		{
			InventoryGridPanel->RowFill.Add(Row);
			InventoryGridPanel->SetRowFill(Row, 1.f);
		}
		
		for (int Column = 0; Column < InventoryDimension.Y; Column++)
		{
			if(Row == 0)
			{
				if(InventoryGridPanel)
				{
					InventoryGridPanel->ColumnFill.Add(Column);
					InventoryGridPanel->SetColumnFill(Column, 1.f);
				}
			}
			UBorder* Border = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
			Border->SetPadding(FMargin{0, 0, 0, 0});
			Border->RenderTransformPivot = FVector2D{0,0};
			
			Border->SetBrushColor({0.1, 0.1, 0.1, 0.4});
				
			UPanelSlot* PanelSlot = InventoryGridPanel->AddChild(Border);

			if(UGridSlot* GridSlot = Cast<UGridSlot>(PanelSlot))
			{
				GridSlot->SetColumn(Column);
				GridSlot->SetRow(Row);
				GridSlot->SetColumnSpan(1);
				GridSlot->SetRowSpan(1);

				GridSlot->SetPadding(FMargin{1.f,1.f,1.f,1.f});
			}
			
			Slots.Add(std::make_pair(Border, FIntPoint{Row,Column}));
		}
	}
}
