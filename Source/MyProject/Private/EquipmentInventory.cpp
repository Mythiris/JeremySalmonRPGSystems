// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInventory.h"
#include "Components/UniformGridPanel.h"
#include "EquipmentSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "WeaponSlot.h"

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
		Close_Bttn->OnClicked.AddDynamic(this, &UEquipmentInventory::CloseWidget);
	}
	
}

// Find and add children to the inventory.
void UEquipmentInventory::InitWid(UInventoryComponent* _InventoryRef, TEnumAsByte<EArmorSlot> ArmorSlot)
{
	Row = 0;
	Col = 0;
	InventoryRef = _InventoryRef;

	for (int i = 0; i < InventoryRef->GetInventorySize(); i++)
	{
		ItemData = InventoryRef->GetInventoryData(i).ItemData;

		if (ItemData.ItemType == EItemType::Armor)
		{
			if (ItemData.ArmorData.ArmorSlot == ArmorSlot)
			{
				if (EquipmentSlots_Ref != NULL, GetWorld())
				{
					// Create a new EquipmentSlot and add the data to it.
					EquipmentSlots.Add(CreateWidget<UEquipmentSlot>(GetWorld(), EquipmentSlots_Ref));
					EquipmentSlots[EquipmentSlots.Num() - 1]->InitSlot(ItemData);
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

void UEquipmentInventory::CloseWidget()
{
	RemoveFromParent();
}

void UEquipmentInventory::InitWeaponsWid(UInventoryComponent* _InventoryRef, TEnumAsByte<ESlotType> SlotType)
{
	InventoryRef = _InventoryRef;
	Row = 0;
	Col = 0;

	if (InventoryRef)
	{
		if (WeaponSlots_Ref != NULL && GetWorld())
		{
			switch (SlotType)
			{
			case ESlotType::LeftHand:
				PopulateWidgetWithWeapon(EWeaponType::OneHandWeapon);
				PopulateWidgetWithWeapon(EWeaponType::TwoHandWeapon);
				break;

			case ESlotType::RightHand:
				PopulateWidgetWithWeapon(EWeaponType::OneHandWeapon);
				break;

			case ESlotType::Ranged:
				PopulateWidgetWithWeapon(EWeaponType::RangedWeapon);
				break;

			default:
				break;
			}



			// Make sure the row is allways full.
			if (Col != 3 || Col != 0)
			{
				while (Col != 3)
				{
					WeaponSlots.Add(CreateWidget<UWeaponSlot>(GetWorld(), WeaponSlots_Ref));

					DisplayGrid->AddChildToUniformGrid(WeaponSlots[WeaponSlots.Num() - 1], Row, Col);

					Col++;
				}
			}
		}
	}
}

void UEquipmentInventory::PopulateWidgetWithWeapon(TEnumAsByte<EWeaponType> WeaponType)
{

	for (int i = 0; i < InventoryRef->GetInventorySize(); i++)
	{
		ItemData = InventoryRef->GetInventoryData(i).ItemData;

		if (ItemData.ItemType == Weapon && ItemData.WeaponData.WeaponType == WeaponType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Some debug message!"));
			// Create a new EquipmentSlot and add the data to it.
			WeaponSlots.Add(CreateWidget<UWeaponSlot>(GetWorld(), WeaponSlots_Ref));
			WeaponSlots[WeaponSlots.Num() - 1]->InitWidget(ItemData);
			WeaponSlots[WeaponSlots.Num() - 1]->SetInventoryRef(InventoryRef);

			// Add EquipmentSlot to a Uniform Grid.
			DisplayGrid->AddChildToUniformGrid(WeaponSlots[WeaponSlots.Num() - 1], Row, Col);

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
}
