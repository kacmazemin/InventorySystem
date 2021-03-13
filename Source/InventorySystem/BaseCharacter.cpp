// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"


#include "DrawDebugHelpers.h"
#include "../InventorySystem/Inventory/InventoryWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Inventory/DynamicInventoryGrid.h"
#include "Item/BaseItemActor.h"
#include "Inventory/ItemNameDisplayer.h"
#include "Item/BasicItemDataAsset.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetRelativeLocation({0,0, 80});
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		ItemName = CreateWidget<UItemNameDisplayer>(PC, ItemNameWidgetClass);
		ItemName->AddToViewport();
		ItemName->SetVisibility(ESlateVisibility::Hidden);
		
		if(InventoryComponent)
		{
			InventoryComponent->InventoryWidget = CreateWidget<UInventoryWidget>(PC, InventoryComponent->InventoryWidgetClass);
			InventoryComponent->InventoryWidget->AddToViewport();
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);

			InventoryComponent->InventoryWidget->InventoryGridPanel->SetInventoryComponent(InventoryComponent);
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();
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
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ABaseCharacter::PressPickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &ABaseCharacter::ReleasePickUp);
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
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, InventoryComponent->InventoryWidget);
			PlayerController->bShowMouseCursor = true;
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}
}

void ABaseCharacter::LineTrace()
{
	FVector Loc;
	FRotator Rot;

	GetController()->GetPlayerViewPoint(Loc, Rot);

	const FVector Start = Loc;
	const FVector End = Start + (Rot.Vector() * TraceDistance);

	const FCollisionQueryParams TraceParams;

	const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	if(bHit && Hit.GetActor())
	{
		if(ABaseItemActor* ItemActor = Cast<ABaseItemActor>(Hit.GetActor()))
		{
			// DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 2.f,FColor::Yellow, false, 2.f);
			
			ItemName->SetTextName(ItemActor->ItemData->GetItemName());

			if(bIsPressPickUp)
			{
				if(InventoryComponent->PickUpItem(ItemActor->ItemData))
				{
					ItemActor->Destroy();
				}
			}
		}
		else
		{
			ItemName->SetTextName(FText::FromString(""));
		}
	}
}

void ABaseCharacter::PressPickUp()
{
	bIsPressPickUp = true;
}

void ABaseCharacter::ReleasePickUp()
{
	bIsPressPickUp = false;
}

void ABaseCharacter::ToggleInventory()
{
	if(InventoryComponent->InventoryWidget)
	{
		if(bIsInventoryActive)
		{
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			bIsInventoryActive = false;
		}
		else
		{
			InventoryComponent->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			bIsInventoryActive = true;
		}
		EnableUIMode(bIsInventoryActive);

	}
}
