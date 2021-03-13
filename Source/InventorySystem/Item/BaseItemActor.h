// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "BaseItemActor.generated.h"

class UBasicItemDataAsset;
class UStaticMesh;
class UBoxComponent;


UCLASS()
class INVENTORYSYSTEM_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItemActor();

	void InitItemActor();
	
	UPROPERTY(EditDefaultsOnly)
	UBasicItemDataAsset* ItemData = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY()
	UBoxComponent* BoxCollision = nullptr;

	UPROPERTY()
	USceneComponent* SceneComponent = nullptr;

	virtual void OnConstruction(const FTransform& Transform) override;

};
