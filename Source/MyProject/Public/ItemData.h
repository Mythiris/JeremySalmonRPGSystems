// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM()
enum EItemType
{
	Misc,
	Armor,
	Weapon,
	Crafting,
	Quest,
	Consumable
};

UENUM()
enum EEquipmentSlots
{
	Head,
	Body,
	Arms,
	Legs,
	Feet,
	LeftHand,
	RightHand,
	Ranged,
};

UENUM()
enum EWeaponTypes
{
	OneHanded,
	TwoHanded,
	RangedWeapon,
};

USTRUCT(BlueprintType)
struct FArmorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EEquipmentSlots> ArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		int ArmorValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* ArmorMesh;

	FArmorData()
	{
		ArmorValue = 1;
		ArmorMesh = nullptr;
	}

};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EWeaponTypes> WeaponSlot;

	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<EEquipmentSlots> EquipedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		int WeaponValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* WeaponMesh;

	FWeaponData()
	{
		WeaponValue = 1;
		WeaponMesh = nullptr;
	}

};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<EItemType> ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* ThumbNail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsStackable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ABaseItem>  ItemRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData", meta = (EditCondition = "ItemType == EItemType::Armor ", EditConditionHides))
		FArmorData ArmorData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData", meta = (EditCondition = "ItemType == EItemType::Weapon ", EditConditionHides))
		FWeaponData WeaponData;

	FItemData()
	{
		Name = "None";
		ItemType = EItemType::Misc;
		ThumbNail = nullptr;
		IsStackable = false;
		MaxStackSize = 0;
		ItemRef = nullptr;
	}


	bool operator==(const FItemData &Other) const
	{
		if (Name == Other.Name && ItemType == Other.ItemType && IsStackable == Other.IsStackable && MaxStackSize == Other.MaxStackSize)
		{
			return true;
		}
		else return false;
	}
};