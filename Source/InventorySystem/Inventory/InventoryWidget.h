// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UDynamicInventoryGrid;
class UButton;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UDynamicInventoryGrid* InventoryGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* SortButton = nullptr;

	UFUNCTION()
	void OnClickSortButton();	

protected:
	
	virtual void NativeConstruct() override;

};
