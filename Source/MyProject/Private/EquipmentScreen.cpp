// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentScreen.h"
#include "EquipmentSlot.h"
#include "GameFramework/InputSettings.h"
#include "InventoryComponent.h"

void UEquipmentScreen::NativeConstruct()
{
	Super::NativeConstruct();


	HeadSlot->SetSlotType(EArmorSlot::Head);
	BodySlot->SetSlotType(EArmorSlot::Body);
	ArmSlot->SetSlotType(EArmorSlot::Arms);
	LegSlot->SetSlotType(EArmorSlot::Legs);
	FeetSlot->SetSlotType(EArmorSlot::Feet);

	HeadSlot->SetIsWindowSlot(true);
	BodySlot->SetIsWindowSlot(true);
	ArmSlot->SetIsWindowSlot(true);
	LegSlot->SetIsWindowSlot(true);
	FeetSlot->SetIsWindowSlot(true);

}

void UEquipmentScreen::SetOwnersInventory(UInventoryComponent* _OwnersInventory)
{
	OwnersInventory = _OwnersInventory;

	HeadSlot->SetInventoryRef(OwnersInventory);
	BodySlot->SetInventoryRef(OwnersInventory);
	ArmSlot->SetInventoryRef(OwnersInventory);
	LegSlot->SetInventoryRef(OwnersInventory);
	FeetSlot->SetInventoryRef(OwnersInventory);
}

void UEquipmentScreen::UpdateSlot(EArmorSlot _ArmorSlot, FItemData _Item)
{
	switch (_ArmorSlot)
	{
	case EArmorSlot::Head:
		HeadSlot->InitSlot(_Item);
		break;
	case EArmorSlot::Body:
		BodySlot->InitSlot(_Item);
		break;
	case EArmorSlot::Arms:
		ArmSlot->InitSlot(_Item);
		break;
	case EArmorSlot::Legs:
		LegSlot->InitSlot(_Item);
		break;
	case EArmorSlot::Feet:
		FeetSlot->InitSlot(_Item);
		break;
	default:
		break;
	}
}

FReply UEquipmentScreen::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	TArray<FInputActionKeyMapping> ActionMaping;
	UInputSettings::GetInputSettings()->GetActionMappingByName("ToggleInventory", ActionMaping);

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