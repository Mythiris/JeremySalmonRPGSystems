// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "InteractInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class MYPROJECT_API ABaseItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FItemData GetItemData();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere)
	FItemData ItemData;

	UPROPERTY(EditAnywhere)
	int Quantity;

};
