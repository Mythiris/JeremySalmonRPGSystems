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
enum EArmorSlot
{
	Head,
	Chest,
	Arms,
	Legs,
	Feet,
};

USTRUCT(BlueprintType)
struct FArmorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EArmorSlot> ArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		int ArmorValue;

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
		bool IsStackable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ABaseItem>  ItemRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData", meta = (EditCondition = "ItemType == EItemType::Armor ", EditConditionHides))
		FArmorData ArmorData;

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