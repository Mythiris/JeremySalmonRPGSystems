// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentScreen.h"
#include "EquipmentSlot.h"
#include "GameFramework/InputSettings.h"
#include "InventoryComponent.h"

// Called when created.
void UEquipmentScreen::NativeConstruct()
{
	Super::NativeConstruct();

	// Init the slots display type.
	HeadSlot->SetSlotType(EEquipmentSlots::Head);
	BodySlot->SetSlotType(EEquipmentSlots::Body);
	ArmSlot->SetSlotType(EEquipmentSlots::Arms);
	LegSlot->SetSlotType(EEquipmentSlots::Legs);
	FeetSlot->SetSlotType(EEquipmentSlots::Feet);
	LeftHand->SetSlotType(EEquipmentSlots::LeftHand);
	RightHand->SetSlotType(EEquipmentSlots::RightHand);
	Ranged->SetSlotType(EEquipmentSlots::Ranged);

	// This sets the slot as the display slot. 
	HeadSlot->SetIsWindowSlot(true);
	BodySlot->SetIsWindowSlot(true);
	ArmSlot->SetIsWindowSlot(true);
	LegSlot->SetIsWindowSlot(true);
	FeetSlot->SetIsWindowSlot(true);
	LeftHand->SetIsWindowSlot(true);
	RightHand->SetIsWindowSlot(true);
	Ranged->SetIsWindowSlot(true);
}

// Sets the UInventoryComponent referance.
void UEquipmentScreen::SetOwnersInventory(UInventoryComponent* _OwnersInventory)
{
	OwnersInventory = _OwnersInventory;

	// Pass the ref to its children.
	HeadSlot->SetInventoryRef(OwnersInventory);
	BodySlot->SetInventoryRef(OwnersInventory);
	ArmSlot->SetInventoryRef(OwnersInventory);
	LegSlot->SetInventoryRef(OwnersInventory);
	FeetSlot->SetInventoryRef(OwnersInventory);

	LeftHand->SetInventoryRef(OwnersInventory);
	RightHand->SetInventoryRef(OwnersInventory);
	Ranged->SetInventoryRef(OwnersInventory);
}

// Update slot with the new item data.
void UEquipmentScreen::UpdateSlot(EEquipmentSlots _ArmorSlot, FItemData _Item)
{
	switch (_ArmorSlot)
	{
	case EEquipmentSlots::Head:
		HeadSlot->InitSlot(_Item);
		break;
	case EEquipmentSlots::Body:
		BodySlot->InitSlot(_Item);
		break;
	case EEquipmentSlots::Arms:
		ArmSlot->InitSlot(_Item);
		break;
	case EEquipmentSlots::Legs:
		LegSlot->InitSlot(_Item);
		break;
	case EEquipmentSlots::Feet:
		FeetSlot->InitSlot(_Item);
		break;
	default:
		break;
	}
}

// Called when a key is pressed.
FReply UEquipmentScreen::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// Find the ActionMapping key. 
	TArray<FInputActionKeyMapping> ActionMaping;
	UInputSettings::GetInputSettings()->GetActionMappingByName("ToggleInventory", ActionMaping);

	// Check if the key pressed is the action key.
	for (auto Action : ActionMaping)
	{
		if (Action.Key == InKeyEvent.GetKey())
		{
			OwnersInventory->ToggleEquipmet();
			return FReply::Handled();
		}
	}

	return FReply::Handled();
}