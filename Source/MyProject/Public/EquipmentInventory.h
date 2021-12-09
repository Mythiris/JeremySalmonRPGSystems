// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
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
	void InitWid(UInventoryComponent* _InventoryRef, TEnumAsByte<EEquipmentSlots> EquiptmentSlot);

	UFUNCTION()
	void CloseWidget();

	UFUNCTION()
	void PopulateWidget(FItemData _ItemData);

protected:

	UPROPERTY()
	TEnumAsByte<EEquipmentSlots> SlotType;
	
	UPROPERTY()
		UInventoryComponent* InventoryRef;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* DisplayGrid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UEquipmentSlot> EquipmentSlots_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		TArray<class UEquipmentSlot*> EquipmentSlots;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Close_Bttn;

	int Row;
	int Col;
};
