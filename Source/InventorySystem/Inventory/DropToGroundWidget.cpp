// Fill out your copyright notice in the Description page of Project Settings.


#include "DropToGroundWidget.h"

#include "DragDropWidget.h"
#include "InventoryItemDisplay.h"
#include "InventorySystem/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UDropToGroundWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                       UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	if (DropWidget == nullptr)
	{
		return false;
	}

	ABaseCharacter* MyPawn = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(MyPawn ==  nullptr)
	{
		return false;
	}
	
	if(UInventoryItemDisplay* ItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
	{
		MyPawn->DropItem(ItemDisplay->ItemData);
	}

	return true;
}
