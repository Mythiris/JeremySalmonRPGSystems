// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM()
enum ItemType
{
	Misc,
	Armor,
	Crafting,
	Quest,
	Consumable
};

UENUM()
enum EquipmentType
{
	Head,
	Chest,
	Arms,
	Legs,
	Feet,
	Weapon,
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ItemType> ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* ThumbNail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsStackable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ABaseItem>  ItemRef;

	FItemData()
	{
		Name = "None";
		ItemType = ItemType::Misc;
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