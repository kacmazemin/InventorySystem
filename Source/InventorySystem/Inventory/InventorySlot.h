// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class USlateBrushAsset;
class UDynamicInventoryGrid;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCoordinate(const int RowNo, const int ColumnNo);

	UPROPERTY(EditDefaultsOnly)
	USlateBrushAsset* BrushAsset = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ValidPlaceColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor InvalidPlaceColor;

	UPROPERTY()
	UDynamicInventoryGrid* Owner = nullptr;

	void SetIndex(const int Index) { this->Index = Index; };
	
private:

	bool canDraw = false;
	int Index = -1;
	int Row = -1;
	int Column = -1;
	
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
							  FSlateWindowElementList& OutDrawElements, int32 LayerId,
							  const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
	
	virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;


	
};
