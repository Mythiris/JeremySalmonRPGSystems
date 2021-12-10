// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInventory.h"
#include "Components/UniformGridPanel.h"
#include "EquipmentSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"

void UEquipmentInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetWorld())
	{
		// Find all widgets of the same type.
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, this->GetClass());

		for (auto Itter : FoundWidgets)
		{
			// Remove all widgets of the same type.
			Itter->RemoveFromParent();
		}
	}

	if (Close_Bttn)
	{
		// Bind function to this button.
		Close_Bttn->OnClicked.AddDynamic(this, &UEquipmentInventory::CloseWidget);
	}
	
}

// Find and add children to the inventory.
void UEquipmentInventory::InitWid(UInventoryComponent* _InventoryRef, TEnumAsByte<EEquipmentSlots> EquiptmentSlot)
{

	Row = 0;
	Col = 0;

	InventoryRef = _InventoryRef;
	SlotType = EquiptmentSlot;

	// Itterate through the inventory.
	for (int i = 0; i < InventoryRef->GetInventorySize(); i++)
	{
		FItemData ItemData = InventoryRef->GetInventoryData(i).ItemData;

		if (ItemData.ItemType == EItemType::Armor)
		{		
			// If this Item's slot matches the given one, add to the display.
			if (ItemData.ArmorData.ArmorSlot == EquiptmentSlot)
			{
				PopulateWidget(ItemData);
			}
		}
		else if (ItemData.ItemType == EItemType::Weapon)
		{
			// Used to bind the weapon type to the correct slot.
			switch (EquiptmentSlot)
			{
			case LeftHand:
				if (ItemData.WeaponData.WeaponSlot == EWeaponTypes::OneHanded || ItemData.WeaponData.WeaponSlot == EWeaponTypes::TwoHanded)
				{
					PopulateWidget(ItemData);
				}
				break;

			case RightHand:
				if (ItemData.WeaponData.WeaponSlot == EWeaponTypes::OneHanded)
				{
					PopulateWidget(ItemData);
				}
				break;

			case Ranged:
				if (ItemData.WeaponData.WeaponSlot == EWeaponTypes::RangedWeapon)
				{
					PopulateWidget(ItemData);
				}
				break;

			default:
				break;
			}
		}	
	}	

	// Make sure the row is allways full.
	if (Col != 3 || Col != 0)
	{
		while(Col != 3)
		{
			EquipmentSlots.Add(CreateWidget<UEquipmentSlot>(GetWorld(), EquipmentSlots_Ref));

			DisplayGrid->AddChildToUniformGrid(EquipmentSlots[EquipmentSlots.Num() - 1], Row, Col);

			Col++;
		}
	}
}

// Remove this widget from parent.
void UEquipmentInventory::CloseWidget()
{
	RemoveFromParent();
}

// Create an EquipmentSlot with data and add it to the dispaly grid.
void UEquipmentInventory::PopulateWidget(FItemData _ItemData)
{
	if (EquipmentSlots_Ref != NULL, GetWorld())
	{
		// Create a new EquipmentSlot and add the data to it.
		EquipmentSlots.Add(CreateWidget<UEquipmentSlot>(GetWorld(), EquipmentSlots_Ref));
		EquipmentSlots[EquipmentSlots.Num() - 1]->InitSlot(_ItemData);
		EquipmentSlots[EquipmentSlots.Num() - 1]->SetSlotType(SlotType);
		EquipmentSlots[EquipmentSlots.Num() - 1]->SetInventoryRef(InventoryRef);

		// Add EquipmentSlot to a Uniform Grid.
		DisplayGrid->AddChildToUniformGrid(EquipmentSlots[EquipmentSlots.Num() - 1], Row, Col);

		// Adjust location in the Uniform Grid.
		if (Col == 2)
		{
			Col = 0;
			Row++;
		}
		else
		{
			Col++;
		}
	}
}
	
