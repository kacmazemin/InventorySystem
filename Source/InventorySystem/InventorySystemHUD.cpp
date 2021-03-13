// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemHUD.h"

#include "Engine/Canvas.h"

void AInventorySystemHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawRect(FLinearColor::Green, Canvas->SizeX / 2, Canvas->SizeY / 2,
						 5, 5);
	
}
