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
	void SlotButtonOnClick();

	//UFUNCTION()
	//	void SetSlotType(TEnumAsByte<EquipmentType> _SlotType);

	//UFUNCTION()
//		TEnumAsByte<EquipmentType> GetSlotType();

	void SetInventoryRef(UInventoryComponent* _InventoryRef);

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemThumbnail;

	//UPROPERTY()
//	TEnumAsByte<EquipmentType> SlotType;
	
	UPROPERTY()
	class UInventoryComponent* InventoryRef;
};
