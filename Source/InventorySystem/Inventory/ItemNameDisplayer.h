// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemNameDisplayer.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemNameDisplayer : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameTextBlock = nullptr;

	void SetTextName(const FText& Name);
	
};
