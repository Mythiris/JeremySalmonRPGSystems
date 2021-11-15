// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "Components/Button.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UEquipmentSlot::SlotButtonOnClick);
	}
}

void UEquipmentSlot::SlotButtonOnClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("ButtonClick"));
	
	if (InventoryRef)
	{

	}
}

void UEquipmentSlot::SetSlotType(TEnumAsByte<EquipmentType> _SlotType)
{
	SlotType = _SlotType;
}

TEnumAsByte<EquipmentType> UEquipmentSlot::GetSlotType()
{
	return(SlotType);
}

void UEquipmentSlot::SetInventoryRef(UInventoryComponent* _InventoryRef)
{
	InventoryRef = _InventoryRef;
}