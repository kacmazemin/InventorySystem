// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DynamicInventoryGrid.generated.h"

class UGridPanel;
class UBorder;
class UBasicItemDataAsset;
class UInventoryItemDisplay;
class UGridSlot;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UDynamicInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditInstanceOnly, Category="Settings",  meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50", ExpseOnSpawn = true))
	FIntPoint InventoryDimension = {10, 10};

	UPROPERTY(EditInstanceOnly, Category="Settings",  meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50", ExpseOnSpawn = true))
	float TileSize = 25.f;

	UFUNCTION(BlueprintCallable)
	void AddItem(const UBasicItemDataAsset* ItemDataAsset, const int slotNo);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* InventoryGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	UBorder* GridPanelBorder = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "ClassSetting")
	TSubclassOf<UInventoryItemDisplay> ItemDisplayClass;

	
private:
	virtual void NativePreConstruct() override;
	
	void InitInventoryWidget();

	TArray<UInventoryItemDisplay*> ItemContainer;
	TArray<std::pair<UBorder*, FIntPoint>> Slots;
};
