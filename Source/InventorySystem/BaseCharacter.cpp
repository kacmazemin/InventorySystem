// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "../InventorySystem/Inventory/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(PC, InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &ABaseCharacter::ToggleInventory);
}

void ABaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
	
}

void ABaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}


void ABaseCharacter::ToggleInventory()
{
	if(InventoryWidget)
	{
		if(bIsInventoryActive)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			bIsInventoryActive = false;
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			bIsInventoryActive = true;
		}
	}
}
