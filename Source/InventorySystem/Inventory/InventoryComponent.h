// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UBasicItemDataAsset;
class UInventoryWidget;
class UInventoryItemDisplay;

UCLASS(ClassGroup = "Inventory", BlueprintType, Blueprintable)

class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool PickUpItem(UBasicItemDataAsset* ItemData) ;

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UBasicItemDataAsset* ItemData) ;

	UPROPERTY(EditDefaultsOnly, Category= "UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidget = nullptr;

	UPROPERTY()
	TArray<const UBasicItemDataAsset*> ItemContainer;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	
};
