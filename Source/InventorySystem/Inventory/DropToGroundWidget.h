// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropToGroundWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UDropToGroundWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
