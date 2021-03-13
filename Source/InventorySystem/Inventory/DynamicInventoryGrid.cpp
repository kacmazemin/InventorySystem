// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicInventoryGrid.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "InventoryItemDisplay.h"
#include "Components/Image.h"
#include "InventorySlot.h"
#include "InventorySystem/Item/BasicItemDataAsset.h"

bool UDynamicInventoryGrid::AddItem(UBasicItemDataAsset* ItemDataAsset)
{
	const int Index = GetFirstAvailableSlotIndex(ItemDataAsset->GetItemSize());

	if(ItemDataAsset->IsStackable())
	{
		for(const auto ItemRef : ItemDisplayContainer)
		{
			if(ItemRef->ItemData->GetId() == ItemDataAsset->GetId())
			{
				ItemRef->IncreaseCount();
				return true;
			}
		}
	}
	
	if(Index != -1)
	{
		UInventoryItemDisplay* InventoryItemDisplay = CreateWidget<UInventoryItemDisplay>(this, ItemDisplayClass);
		InventoryItemDisplay->Init(ItemDataAsset);
		InventoryItemDisplay->SetInventoryIndex(Index);
		InventoryItemDisplay->Owner = this;
		
		const FIntPoint ItemStartPoint = GetCoordinateByIndex(Index);
	
		InventoryGridPanel->AddChildToGrid(InventoryItemDisplay, ItemStartPoint.Y, ItemStartPoint.X);
		
		ItemDisplayContainer.Add(InventoryItemDisplay);

		FillSlots(ItemStartPoint, ItemDataAsset->GetItemSize());
		
		return true;
	}

	return false;
}

void UDynamicInventoryGrid::RemoveItem(UBasicItemDataAsset* ItemDataAsset)
{
	UInventoryItemDisplay* DeleteItem = nullptr;
	
	for	(const auto ItemDisplay: ItemDisplayContainer)
	{
		if(ItemDataAsset == ItemDisplay->ItemData)
		{
			DeleteItem = ItemDisplay;
		}
	}

	if(DeleteItem)
	{
		ItemDisplayContainer.Remove(DeleteItem);
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

	int count = 0;
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

			UInventorySlot* InventorySlot = WidgetTree->ConstructWidget<UInventorySlot>(InventorySlotClass);
			InventorySlot->SetCoordinate(Row, Column);
			InventorySlot->SetPadding(FMargin{0, 0, 0, 0});
			InventorySlot->RenderTransformPivot = FVector2D{0,0};
			InventorySlot->Owner = this;
			InventorySlot->SetIndex(count);
			count++;
							
			UPanelSlot* PanelSlot = InventoryGridPanel->AddChild(InventorySlot);

			if(UGridSlot* GridSlot = Cast<UGridSlot>(PanelSlot))
			{
				GridSlot->SetColumn(Column);
				GridSlot->SetRow(Row);
				GridSlot->SetColumnSpan(1);
				GridSlot->SetRowSpan(1);
			}
			
			Slots.Add(InventorySlot);
			SlotMap.Add(InventorySlot, false);
		}
	}
}

int UDynamicInventoryGrid::GetFirstAvailableSlotIndex(const FIntPoint& ItemSize) const
{
	int i = 0;
	
	for (const auto& SingleSlot : SlotMap)
	{
		if(IsItemAvailableForSlot(i, ItemSize))
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
		if(UInventorySlot* InvSlot = Cast<UInventorySlot>(Slots[Index]))
		{
			if(UGridSlot* GridSlot = Cast<UGridSlot>(InvSlot->Slot))
			{
				return FIntPoint{GridSlot->Column, GridSlot->Row};
			}	
		}
	}

	return FIntPoint{-1,-1};
}

void UDynamicInventoryGrid::SortItems()
{
	ClearSlots({0,0}, {RowCount, ColumnCount});
	
	ItemDisplayContainer.Sort([=](const auto& Left, const auto& Right)
	{
		return Left.GetTotalSlotForItem() > Right.GetTotalSlotForItem();
	});
	
	for (const auto& Item : ItemDisplayContainer)
	{
		const int Index = GetFirstAvailableSlotIndex(Item->ItemData->GetItemSize());
		const FIntPoint ItemStartPoint = GetCoordinateByIndex(Index);

		Item->SetInventoryIndex(Index);
		
		InventoryGridPanel->AddChildToGrid(Item, ItemStartPoint.Y, ItemStartPoint.X);

		FillSlots(ItemStartPoint, Item->GetItemSize());
	}
	
}

void UDynamicInventoryGrid::FillSlots(const FIntPoint& StartPoint, const FIntPoint& ItemSize)
{
	for (int i = 0; i < ItemSize.X ; i++)
	{
		for (int j = 0; j < ItemSize.Y; j++)
		{
			auto& SingleSlot = Slots[GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount)];
			SlotMap.Add(SingleSlot, true);
			// SingleSlot->EnableFillorReFill(true);
		}
	}
}

void UDynamicInventoryGrid::ClearSlots(const FIntPoint& StartPoint, const FIntPoint& ItemSize)
{
	for (int i = 0; i < ItemSize.X ; i++)
	{
		for (int j = 0; j < ItemSize.Y; j++)
		{
			auto& SingleSlot = Slots[GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount)];
			SlotMap.Add(SingleSlot, false);
			// SingleSlot->EnableFillorReFill(false);			
		}
	}
}

void UDynamicInventoryGrid::SetInventoryComponent(UInventoryComponent* InvComp)
{
	InventoryComponent = InvComp;
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
			if(SlotMap[Slots[GetSlotIndexByCoordinate((Coordinate.X + i) % ColumnCount , (Coordinate.Y + j) % RowCount)]])
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
