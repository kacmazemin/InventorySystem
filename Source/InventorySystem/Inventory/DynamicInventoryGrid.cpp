// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicInventoryGrid.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"

void UDynamicInventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();

	InitInventoryWidget();
}

void UDynamicInventoryGrid::InitInventoryWidget() 
{
	if(UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(InventoryGridPanel->Slot))
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
			
			Border->SetBrushColor(FLinearColor::Green);
				
			UPanelSlot* PanelSlot = InventoryGridPanel->AddChild(Border);

			if(UGridSlot* GridSlot = Cast<UGridSlot>(PanelSlot))
			{
				GridSlot->SetColumn(Column);
				GridSlot->SetRow(Row);
				GridSlot->SetColumnSpan(1);
				GridSlot->SetRowSpan(1);

				GridSlot->SetPadding(FMargin{1.f,1.f,1.f,1.f});
			}
		}
	}
}
