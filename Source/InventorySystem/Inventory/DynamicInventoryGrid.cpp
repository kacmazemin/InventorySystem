// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicInventoryGrid.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "InventoryItemDisplay.h"
#include "Components/Image.h"
#include "InventorySystem/Item/BasicItemDataAsset.h"

void UDynamicInventoryGrid::AddItem(const UBasicItemDataAsset* ItemDataAsset)
{
	const int Index = GetFirstAvailableSlotIndex(ItemDataAsset->GetItemSize());
	
	if(Index != -1)
	{
		UInventoryItemDisplay* InventoryItemDisplay = CreateWidget<UInventoryItemDisplay>(this, ItemDisplayClass);
		InventoryItemDisplay->Init(ItemDataAsset);
		const FIntPoint ItemStartPoint = GetCoordinateByIndex(Index);
	
		Slots[Index]->AddChild(InventoryItemDisplay);
		ItemContainer.Add(InventoryItemDisplay);

		const int ItemColumnSize = ItemDataAsset->GetItemSize().Y;
		const int ItemRowSize = ItemDataAsset->GetItemSize().X;
	
		for (int i = 0; i < ItemRowSize ; i++)
		{
			for (int j = 0; j < ItemColumnSize; j++)
			{
				SlotMap.Add(Slots[GetSlotIndexByCoordinate((ItemStartPoint.X + i) % ColumnCount, (ItemStartPoint.Y + j) % RowCount)], true);					
			}
		}
	
		if(Slots[Index])
		{
			UPanelSlot* PanelSlot = Cast<UPanelSlot>(Slots[Index]);
	
			if(UGridSlot* GridSlot = Cast<UGridSlot>(PanelSlot))
			{
				GridSlot->SetColumnSpan(ItemDataAsset->GetItemSize().Y);
				GridSlot->SetRowSpan(ItemDataAsset->GetItemSize().X);
			}
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

		CanvasPanelSlot->SetSize({TileSize * ColumnCount, TileSize * RowCount});
	}

	for (int Row = 0; Row < RowCount; Row++)
	{
		if(InventoryGridPanel)
		{
			InventoryGridPanel->RowFill.Add(Row);
			InventoryGridPanel->SetRowFill(Row, 1.f);
		}
		
		for (int Column = 0; Column < ColumnCount; Column++)
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
			
			Slots.Add(Border);
			SlotMap.Add(Border, false);
		}
	}
}

int UDynamicInventoryGrid::GetFirstAvailableSlotIndex(const FIntPoint& ItemSize) const
{
	int i = 0;
	for (const auto& SingleSlot : SlotMap)
	{
		if(IsItemAvailableForSlot(i,ItemSize))
		{
			return i;
		}
		
		i++;
	}
	
	return -1;
}

FIntPoint UDynamicInventoryGrid::GetCoordinateByIndex(const int Index) const
{
	if(Index >= 0 && Index < Slots.Num())
	{
		if(UBorder* Border = Cast<UBorder>(Slots[Index]))
		{
			if(UGridSlot* GridSlot = Cast<UGridSlot>(Border->Slot))
			{
				return FIntPoint{GridSlot->Column, GridSlot->Row};
			}	
		}
	}

	return FIntPoint{-1,-1};
}

int UDynamicInventoryGrid::GetSlotIndexByCoordinate(const int Column, const int Row) const
{
	if(Column > ColumnCount || Row > RowCount )
	{
		return -1;
	}
	
	return (Column + (Row * RowCount));
}

bool UDynamicInventoryGrid::IsItemAvailableForSlot(const int Index, const FIntPoint& ItemSize) const
{
	const auto Coordinate = GetCoordinateByIndex(Index);

	const int ItemColumnSize = ItemSize.Y;
	const int ItemRowSize = ItemSize.X;

	//check neighbours
	for (int i = 0; i < ItemRowSize ; i++)
	{
		for (int j = 0; j < ItemColumnSize; j++)
		{
			if(SlotMap[Slots[GetSlotIndexByCoordinate((Coordinate.X + i) , (Coordinate.Y + j))]])
			{
				return false;
			}
		}
	}
	
	if((Coordinate.X + ItemSize.X  > RowCount) || (Coordinate.Y + ItemSize.Y  > ColumnCount))
	{
		return false;
	}

	return true;
}
