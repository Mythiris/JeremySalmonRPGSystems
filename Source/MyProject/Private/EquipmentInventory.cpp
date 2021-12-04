// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInventory.h"
#include "Components/UniformGridPanel.h"
#include "EquipmentSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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
}

// Find and add children to the inventory.
void UEquipmentInventory::InitWid(UInventoryComponent* InventoryRef, TEnumAsByte<EArmorSlot> ArmorSlot)
{
	int Row = 0;
	int Col = 0;
	FItemData ItemData;

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
