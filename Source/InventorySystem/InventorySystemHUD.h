// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AInventorySystemHUD : public AHUD
{
	GENERATED_BODY()

private:
	virtual void DrawHUD() override;

	
};
