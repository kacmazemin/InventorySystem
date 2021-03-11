// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

#include "DragDropWidget.h"
#include "DynamicInventoryGrid.h"
#include "Components/GridPanel.h"
#include "InventoryItemDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/GridSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Rendering/DrawElements.h"

void UInventorySlot::SetCoordinate(const int RowNo, const int ColumnNo)
{
	Row = RowNo;
	Column = ColumnNo;
}

void UInventorySlot::EnableFillorReFill(const bool IsFill)
{
	if(IsFill)
	{
		Border->SetBrushColor(FLinearColor::Red);
	}
	else
	{
		Border->SetBrushColor(FLinearColor::Green);
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                  UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	if (DropWidget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, "FALSE");
		return false;
	}
	
	const FString Message = FString::Printf(TEXT("ROW [%d] COLUMN [%d]"), Row, Column);
	GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, Message);

	if(UGridPanel* GridPanel = Cast<UGridPanel>(GetParent()))
	{
		if(UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
		{
			if(Owner)
			{	
				if(Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize()))
				{
					InventoryItemDisplay->SetVisibility(ESlateVisibility::Visible);
					if(UGridSlot* GridSlot = Cast<UGridSlot>(InventoryItemDisplay->Slot))
					{
						GridSlot->SetColumn(Column);
						GridSlot->SetRow(Row);
					}
				
					Owner->FillSlots(Owner->GetCoordinateByIndex(SlotIndex), InventoryItemDisplay->GetItemSize());
					InventoryItemDisplay->SetInventoryIndex(SlotIndex);
				}
				else
				{
					canDraw = false;
					return false;
				}
			}
		}
	}
	
	canDraw = false;

	return true;
}

bool UInventorySlot::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	
	if (DropWidget == nullptr)
	{
		return false;
	}

	if(Owner)
	{
		if(UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
		{
			const bool IsSlotValid = Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize());

			DrawSize = {50 * InventoryItemDisplay->GetItemSize()};
			
			Color = IsSlotValid ?  ValidPlaceColor : InvalidPlaceColor;
        }

	}

	if(UGridPanel* GridPanel = Cast<UGridPanel>(GetParent()))
	{
		const FString Message = FString::Printf(TEXT("ROW [%d] COLUMN [%d]"), Row, Column);
		GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, Message);

		canDraw = true;
	}

	return true;
}

int32 UInventorySlot::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                  const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                  const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	
	if ( canDraw )
	{
		FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
		OnPaint( Context );
		
		UWidgetBlueprintLibrary::DrawBox(Context, {0,0}, DrawSize, BrushAsset, Color);
	
		return FMath::Max(LayerId, Context.MaxLayer);
	}

	return LayerId;
}

void UInventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	canDraw = false;
}

void UInventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	canDraw = false;
}
