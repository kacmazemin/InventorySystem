// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryItemDisplay.generated.h"

class UBasicItemDataAsset;
class UImage;
class UBorder;
class UDynamicInventoryGrid;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryItemDisplay : public UUserWidget
{
	GENERATED_BODY()

public:

	class UUserWidget* OwnerWidget = nullptr;
	
	void Init(const UBasicItemDataAsset* BasicItemData);

	void SetInventoryIndex(const int Index)
	{
			SlotIndexOnInventory = Index;
	};

	int GetInventoryIndex() const
	{
		return SlotIndexOnInventory;
	}

	FIntPoint GetItemSize() const;

	UPROPERTY()
	UDynamicInventoryGrid* Owner = nullptr;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	const UBasicItemDataAsset* ItemData = nullptr;
	
private:
	int SlotIndexOnInventory = -1;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon = nullptr;

	UPROPERTY(meta = (BindWidget))
	UBorder* SlotBorder = nullptr;

	FLinearColor BorderInitialColor;
	
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;

	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;


};
