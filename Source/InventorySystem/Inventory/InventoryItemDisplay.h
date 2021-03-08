// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryItemDisplay.generated.h"

class UBasicItemDataAsset;
class UImage;
class UBorder;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryItemDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const UBasicItemDataAsset* BasicItemData);

	FIntPoint GetItemSize() const;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	const UBasicItemDataAsset* ItemData = nullptr;
	
private:

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon = nullptr;

	UPROPERTY(meta = (BindWidget))
	UBorder* SlotBorder = nullptr;

	FLinearColor BorderInitialColor;
	
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;


};
