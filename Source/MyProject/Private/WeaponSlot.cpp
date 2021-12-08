// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "EquipmentInventory.h"

// Called on creation.
void UWeaponSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		// Bind function to the button.
		SlotButton->OnClicked.AddDynamic(this, &UWeaponSlot::SlotButtonOnClick);
	}

	IsWindowSlot = false;
}

void UWeaponSlot::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWeaponSlot::InitWidget(FItemData _Item)
{
	ItemData = _Item;

	if (ItemData.ThumbNail)
	{
		// Set slot thumbnail from data.
		ItemThumbnail->SetBrushFromTexture(ItemData.ThumbNail);
	}

	WeaponType = ItemData.WeaponData.WeaponType;
}

// Callled on button click.
void UWeaponSlot::SlotButtonOnClick()
{
	if (IsWindowSlot)
	{
		if (EquipmentInventory_Ref != NULL && GetWorld())
		{
			// Create the equipment inventory widget.
			EquipmentInventory = CreateWidget<UEquipmentInventory>(GetWorld(), EquipmentInventory_Ref);
			// Set the data type for the equipment inventory widget to display.

			EquipmentInventory->InitWeaponsWid(InventoryRef, SlotType);
			EquipmentInventory->SetPositionInViewport(FVector2D(50, 100));
			EquipmentInventory->AddToViewport();
			return;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Equip"));
}

void UWeaponSlot::SetSlotType(TEnumAsByte<ESlotType> _SlotType)
{
	SlotType =	_SlotType;
}

TEnumAsByte<ESlotType> UWeaponSlot::GetSlotType()
{
	return(SlotType);
}

void UWeaponSlot::SetInventoryRef(UInventoryComponent* _InventoryRef)
{
	InventoryRef = _InventoryRef;
}

void UWeaponSlot::SetIsWindowSlot(bool _WindowSlot)
{
	IsWindowSlot = _WindowSlot;
}