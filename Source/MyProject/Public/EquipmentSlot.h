// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "ItemData.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void InitSlot(int Index, UInventoryComponent* _InventoryRef);

	UFUNCTION()
		void SlotButtonOnClick();

	UFUNCTION()
		void SetSlotType(TEnumAsByte<EArmorSlot> _SlotType);

	UFUNCTION()
		TEnumAsByte<EArmorSlot> GetSlotType();

	void SetInventoryRef(UInventoryComponent* _InventoryRef);

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemThumbnail;

	UPROPERTY()
		TEnumAsByte<EArmorSlot> SlotType;
	
	UPROPERTY()
		class UInventoryComponent* InventoryRef;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UEquipmentInventory> EquipmentInventory_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UEquipmentInventory* EquipmentInventory;
};
