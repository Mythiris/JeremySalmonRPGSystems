// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// Create Collision sphere component. 
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetupAttachment(Mesh);

	// Init itemdata.
	ItemData.Name = this->GetName();
	ItemData.ItemRef = this->StaticClass();
	Quantity = 1;
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Return this objects ItemData
FItemData ABaseItem::GetItemData()
{
	return(ItemData);
}

// Check if item is added to invenotry, then destroy.
void ABaseItem::OnInteract_Implementation(AActor* Caller)
{
	/* Check that item was added to the inventory */
	if (Caller->FindComponentByClass<UInventoryComponent>()->AddToInventory(FInventoryData{ ItemData, Quantity }))
	{
		Destroy();
	}
}
