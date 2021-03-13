// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemNameDisplayer.h"

#include "Components/TextBlock.h"

void UItemNameDisplayer::SetTextName(const FText& Name)
{
	if(!Name.IsEmpty())
	{
		this->SetVisibility(ESlateVisibility::Visible);
		NameTextBlock->SetText(Name);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}
