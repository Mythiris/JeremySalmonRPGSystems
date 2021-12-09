// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "ItemData.h"
#include "EquipmentInventory.h"
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
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
		void InitSlot(FItemData _Item);

	UFUNCTION()
		void SlotButtonOnClick();

	UFUNCTION()
		void SetSlotType(TEnumAsByte<EEquipmentSlots> _SlotType);

	UFUNCTION()
		TEnumAsByte<EEquipmentSlots> GetSlotType();

	void SetInventoryRef(UInventoryComponent* _InventoryRef);

	UFUNCTION()
	void SetIsWindowSlot(bool _IsWindowSlot);


private:

	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemThumbnail;

	UPROPERTY()
		TEnumAsByte<EEquipmentSlots> SlotType;

	UPROPERTY()
		bool IsWindowSlot;
	
	UPROPERTY()
		class UInventoryComponent* InventoryRef;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UEquipmentInventory> EquipmentInventory_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UEquipmentInventory* EquipmentInventory;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UToolTip> ToolTip_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UToolTip* ToolTip;

	UPROPERTY()
		FItemData ItemData;

	UPROPERTY()
		class APlayerController* PlayerControler;
};
