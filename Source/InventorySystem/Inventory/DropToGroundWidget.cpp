// Fill out your copyright notice in the Description page of Project Settings.


#include "DropToGroundWidget.h"

#include "DragDropWidget.h"

bool UDropToGroundWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                       UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	if (DropWidget == nullptr)
	{
		return false;
	}


	return true;
}
