// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "BaseItem.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FItemData ItemData;

	UPROPERTY(BlueprintReadWrite)
		int Quantity;

	// Used to compare this Enum with another copy.
	bool operator==(const FInventoryData &Other) const
	{
		if (ItemData == Other.ItemData)
		{
			return true;
		}
		else return false;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	
	bool AddToInventory(FInventoryData ItemToAdd);
	bool AddToInventory(FItemData ItemData, int Quantity);

	UFUNCTION()
	void RemoveFromInventory(FInventoryData ItemToRemove);

	UFUNCTION()
	void AddToStack(FInventoryData ItemToAdd, int Index);
	UFUNCTION()
	void CreateStack(FInventoryData ItemToAdd);

	UFUNCTION()
	bool IsInInventory(FInventoryData Item);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
	UFUNCTION()
	void SetInventorySize(int InvnSize);
	UFUNCTION()
	int GetInventorySize() const;

	FInventoryData GetInventoryData(int Index);


	////////// Equipment Functions ////////////////

	UFUNCTION(BlueprintCallable)
		void ToggleEquipmet();

	UFUNCTION()
		bool IsItemEquiped(FItemData _Item);
	UFUNCTION()
		void EquipItem(FItemData _Item);
	UFUNCTION()
		void UnEquipItem(FItemData _Item);


protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		FItemData NullItemData;

	UPROPERTY()
		FInventoryData NullItem;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* NullThumbnail;

	UPROPERTY(EditAnywhere)
		int NumberOfSlots;

	UPROPERTY()
	TArray<FInventoryData> Inventory;

	//Equiped Items
	UPROPERTY()
		TMap<TEnumAsByte<EEquipmentSlots>, FItemData> EquipedEquipment;


	////////// Widgets ////////////////
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UEquipmentScreen> EquipmentScreen_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UEquipmentScreen* EquipmentScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UInventoryScreen> InventoryScreen_Ref;
	
	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UInventoryScreen* InventoryScreen;

	////////// Player + Controller ////////////////
	UPROPERTY()
	class APlayerController* PlayerController;

	UPROPERTY()
	class AMyProjectCharacter* PlayerCharacter;
};
