// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemDisplay.generated.h"

class UBasicItemDataAsset;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryItemDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const UBasicItemDataAsset* BasicItemData);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	const UBasicItemDataAsset* ItemData = nullptr;
	
private:

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon = nullptr;
	
	virtual void NativeConstruct() override;

};
