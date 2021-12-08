// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "WeaponSlot.h"
#include "EquipmentInventory.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEquipmentInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void InitWid(UInventoryComponent* _InventoryRef, TEnumAsByte<EArmorSlot> ArmorSlot);

	UFUNCTION()
		void InitWeaponsWid(UInventoryComponent* _InventoryRef, TEnumAsByte<ESlotType> SlotType);

	UFUNCTION()
	void CloseWidget();

	void PopulateWidgetWithWeapon(TEnumAsByte<EWeaponType> WeaponType);

protected:

	UPROPERTY()
		UInventoryComponent* InventoryRef;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* DisplayGrid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UEquipmentSlot> EquipmentSlots_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		TArray<class UEquipmentSlot*> EquipmentSlots;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UWeaponSlot> WeaponSlots_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		TArray<class UWeaponSlot*> WeaponSlots;

	UPROPERTY(meta = (BindWidget))
	class UButton* Close_Bttn;

	FItemData ItemData;
	int Row;
	int Col;
};
