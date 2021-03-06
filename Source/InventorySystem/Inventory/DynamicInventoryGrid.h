// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DynamicInventoryGrid.generated.h"

class UGridPanel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UDynamicInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditDefaultsOnly, Category="Settings",  meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50", ExpseOnSpawn = true))
	FIntPoint InventoryDimension = {10, 10};

	UPROPERTY(EditDefaultsOnly, Category="Settings",  meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50", ExpseOnSpawn = true))
	float TileSize = 25.f;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* InventoryGridPanel = nullptr;
	
private:
	virtual void NativeConstruct() override;
	
	void InitInventoryWidget();
};
