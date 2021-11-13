// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetupAttachment(Mesh);

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

FItemData ABaseItem::GetItemData()
{
	return(ItemData);
}

void ABaseItem::OnInteract_Implementation(AActor* Caller)
{
	/* Check that item was added to the inventory */
	if (Caller->FindComponentByClass<UInventoryComponent>()->AddToInventory(FInventoryData{ ItemData, Quantity }))
	{
		Destroy();
	}
}
