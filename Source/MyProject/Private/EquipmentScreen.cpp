// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentScreen.h"
#include "EquipmentSlot.h"

void UEquipmentScreen::NativeConstruct()
{
	Super::NativeConstruct();


	HeadSlot->SetSlotType(EquipmentType::Head);
	ChestSlot->SetSlotType(EquipmentType::Chest);
	ArmSlot->SetSlotType(EquipmentType::Arms);
	LegSlot->SetSlotType(EquipmentType::Legs);
	FeetSlot->SetSlotType(EquipmentType::Feet);
	WeaponSlot->SetSlotType(EquipmentType::Weapon);

}

void UEquipmentScreen::SetOwnersInventory(UInventoryComponent* _OwnersInventory)
{
	OwnersInventory = _OwnersInventory;

	HeadSlot->SetInventoryRef(OwnersInventory);
	ChestSlot->SetInventoryRef(OwnersInventory);
	ArmSlot->SetInventoryRef(OwnersInventory);
	LegSlot->SetInventoryRef(OwnersInventory);
	FeetSlot->SetInventoryRef(OwnersInventory);
	WeaponSlot->SetInventoryRef(OwnersInventory);
}