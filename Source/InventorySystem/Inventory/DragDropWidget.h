// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UDragDropWidget : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY()	
	UUserWidget* WidgetToDrag = nullptr;
	
	FVector2D MouseOffset = FVector2D::ZeroVector;
};
