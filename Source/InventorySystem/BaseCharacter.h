// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UInventoryWidget;
class UInventoryComponent;

UCLASS()
class INVENTORYSYSTEM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInventoryComponent* InventoryComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleInventory();
	
	void MoveRight(float Value);
	void MoveForward(float Value);
	
private:
	
	bool bIsInventoryActive = false;
	void EnableUIMode(const bool IsEnable);
	
};