// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "WeaponSlot.generated.h"

/**
 * 
 */

UENUM()
enum ESlotType
{
	LeftHand,
	RightHand,
	Ranged,
};

UCLASS()
class MYPROJECT_API UWeaponSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void SetSlotType(TEnumAsByte<ESlotType> _SlotType);

	void SetIsWindowSlot(bool _WindowSlot);
	
	UFUNCTION()
		TEnumAsByte<ESlotType> GetSlotType();
	UFUNCTION()
	void InitWidget(FItemData _Item);

	UFUNCTION()
		void SetInventoryRef(UInventoryComponent* _InventoryRef);

	UFUNCTION()
	void SlotButtonOnClick();


protected:

	UPROPERTY()
		UInventoryComponent* InventoryRef;

	UPROPERTY()
		TEnumAsByte<ESlotType> SlotType;

	UPROPERTY()
		TEnumAsByte<EWeaponType> WeaponType;

	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemThumbnail;

	UPROPERTY()
		bool IsWindowSlot;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UToolTip> ToolTip_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UToolTip* ToolTip;

	UPROPERTY()
		FItemData ItemData;

	UPROPERTY()
		class APlayerController* PlayerControler;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UEquipmentInventory> EquipmentInventory_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UEquipmentInventory* EquipmentInventory;
};
