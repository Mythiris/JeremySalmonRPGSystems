// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "EquipmentScreen.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEquipmentScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetOwnersInventory(UInventoryComponent* _OwnersInventory);

	void UpdateSlot(EArmorSlot _ArmorSlot, FItemData _Item);

private:

	UPROPERTY(meta = (BindWidget))
		class UEquipmentSlot* HeadSlot;

	UPROPERTY(meta = (BindWidget))
		class UEquipmentSlot* ChestSlot;

	UPROPERTY(meta = (BindWidget))
		class UEquipmentSlot* ArmSlot;

	UPROPERTY(meta = (BindWidget))
		class UEquipmentSlot* LegSlot;

	UPROPERTY(meta = (BindWidget))
		class UEquipmentSlot* FeetSlot;

	UPROPERTY()
	class UInventoryComponent* OwnersInventory;
	
};
