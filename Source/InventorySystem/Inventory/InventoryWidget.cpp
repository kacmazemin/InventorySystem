// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	
	if (APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GWorld))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this);
	}

}
