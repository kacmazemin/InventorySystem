// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"



#include "DynamicInventoryGrid.h"
#include "InventoryWidget.h"
#include "InventorySystem/BaseCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddItem(const UBasicItemDataAsset* ItemData)
{
	
	if(InventoryWidget)
	{
		if(InventoryWidget->InventoryGridPanel->AddItem(ItemData))
		{
			//to keep inventoryData
			ItemContainer.Add(ItemData);
		}
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
