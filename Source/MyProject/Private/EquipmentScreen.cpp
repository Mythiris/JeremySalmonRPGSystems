// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentScreen.h"
#include "EquipmentSlot.h"

void UEquipmentScreen::NativeConstruct()
{
	Super::NativeConstruct();


	HeadSlot->SetSlotType(EArmorSlot::Head);
	ChestSlot->SetSlotType(EArmorSlot::Chest);
	ArmSlot->SetSlotType(EArmorSlot::Arms);
	LegSlot->SetSlotType(EArmorSlot::Legs);
	FeetSlot->SetSlotType(EArmorSlot::Feet);

	HeadSlot->SetIsWindowSlot(true);
	ChestSlot->SetIsWindowSlot(true);
	ArmSlot->SetIsWindowSlot(true);
	LegSlot->SetIsWindowSlot(true);
	FeetSlot->SetIsWindowSlot(true);

}

void UEquipmentScreen::SetOwnersInventory(UInventoryComponent* _OwnersInventory)
{
	OwnersInventory = _OwnersInventory;

	HeadSlot->SetInventoryRef(OwnersInventory);
	ChestSlot->SetInventoryRef(OwnersInventory);
	ArmSlot->SetInventoryRef(OwnersInventory);
	LegSlot->SetInventoryRef(OwnersInventory);
	FeetSlot->SetInventoryRef(OwnersInventory);
}