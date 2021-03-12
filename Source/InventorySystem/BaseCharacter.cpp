// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "../InventorySystem/Inventory/InventoryWidget.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if(InventoryComponent)
		{
			InventoryComponent->InventoryWidget = CreateWidget<UInventoryWidget>(PC, InventoryComponent->InventoryWidgetClass);
			InventoryComponent->InventoryWidget->AddToViewport();
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
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

void ABaseCharacter::EnableUIMode(const bool IsEnable)
{

	if (APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GWorld))
	{
		if(IsEnable)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, this);
			PlayerController->bShowMouseCursor = true;
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}

}

void ABaseCharacter::ToggleInventory()
{
	if(InventoryComponent->InventoryWidget)
	{
		if(bIsInventoryActive)
		{
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			InventoryComponent->InventoryWidget->SetUIMode(false);
			bIsInventoryActive = false;
		}
		else
		{
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			InventoryComponent->InventoryWidget->SetUIMode(true);

			bIsInventoryActive = true;
		}
	}
}
