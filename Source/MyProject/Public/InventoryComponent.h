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

	bool operator==(const FInventoryData &Other) const
	{
		if (ItemData == Other.ItemData)
		{
			return true;
		}
		else return false;
	}
};

USTRUCT(BlueprintType)
struct FEquipedArmor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<EArmorSlot> ArmorSlot;

	UPROPERTY(BlueprintReadWrite)
		FItemData ItemData;

	bool operator==(const FEquipedArmor& Other) const
	{
		if (ItemData == Other.ItemData && ArmorSlot == Other.ArmorSlot)
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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool AddToInventory(FInventoryData ItemToAdd);
	bool AddToInventory(FItemData ItemData, int Quantity);
	void RemoveFromInventory(FInventoryData ItemToRemove);

	void AddToStack(FInventoryData ItemToAdd, int Index);
	void CreateStack(FInventoryData ItemToAdd);


	bool IsInInventory(FInventoryData Item);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	void SetInventorySize(int InvnSize);
	int GetInventorySize() const;

	FInventoryData GetInventoryData(int Index);



	//Equipement

	UFUNCTION(BlueprintCallable)
		void ToggleEquipmet();

	UFUNCTION()
	bool IsEquiped(FItemData _CurrentItem, TEnumAsByte<EArmorSlot> _SlotType);

	UFUNCTION()
	void Unequip(TEnumAsByte<EArmorSlot> _SlotType);

	UFUNCTION()
		void Equip(FItemData _Item, TEnumAsByte<EArmorSlot> _SlotType);

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FInventoryData> Inventory;

	//Equiped Items
	UPROPERTY()
		TArray<FEquipedArmor>EquipedArmor;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Inventory")
		int NumberOfSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UEquipmentScreen> EquipmentScreen_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UEquipmentScreen* EquipmentScreen;

	UPROPERTY()
	FInventoryData NullItem;

	UPROPERTY()
	class APlayerController* PlayerController;
};
