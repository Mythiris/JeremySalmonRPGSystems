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
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void SetOwnersInventory(UInventoryComponent* _OwnersInventory);

	void UpdateSlot(EEquipmentSlots _ItemSlot, FItemData _Item);

protected:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* HeadSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* BodySlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* ArmSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* LegSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* FeetSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* LeftHand;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* RightHand;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEquipmentSlot* Ranged;

	UPROPERTY()
	class UInventoryComponent* OwnersInventory;

};
