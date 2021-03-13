// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"

#include "BasicItemDataAsset.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseItemActor::ABaseItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComponent);
	BoxCollision->SetRelativeLocation({0,0,0});
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(BoxCollision);
	MeshComponent->SetRelativeLocation({0,0,0});
	
}

void ABaseItemActor::InitItemActor()
{
	if(ItemData)
	{
		if(ItemData->GetMeshComponent())
		{
			UStaticMesh& SM = *ItemData->GetMeshComponent();
		
			MeshComponent->SetStaticMesh(&SM);
			MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			// MeshComponent->SetRelativeLocation(MeshComponent->GetRelativeLocation());
			BoxCollision->SetBoxExtent(SM.GetBounds().BoxExtent);

		
			BoxCollision->SetRelativeLocation(FVector{0,0,SM.GetBounds().BoxExtent.Z});
			MeshComponent->SetRelativeLocation({BoxCollision->GetRelativeLocation().X, BoxCollision->GetRelativeLocation().Y,
                                             BoxCollision->GetRelativeLocation().Z -SM.GetBounds().BoxExtent.Z });
		}
	}
}

// Called when the game starts or when spawned
void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItemActor::OnConstruction(const FTransform& Transform)
{
	InitItemActor();
}
