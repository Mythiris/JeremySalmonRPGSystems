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
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, this->GetClass());

		for (auto Itter : FoundWidgets)
		{
			Itter->RemoveFromParent();
		}
	}
}

void UEquipmentInventory::InitWid(UInventoryComponent* InventoryRef, TEnumAsByte<EArmorSlot> ArmorSlot)
{
	int Row = 0;
	int Col = 0;


	for (int i = 0; i < InventoryRef->GetInventorySize(); i++)
	{
		if (InventoryRef->GetInventoryData(i).ItemData.ItemType == EItemType::Armor)
		{
			if (InventoryRef->GetInventoryData(i).ItemData.ArmorData.ArmorSlot == ArmorSlot)
			{
				if (EquipmentSlots_Ref != NULL, GetWorld())
				{
					EquipmentSlots.Add(CreateWidget<UEquipmentSlot>(GetWorld(), EquipmentSlots_Ref));
					EquipmentSlots[EquipmentSlots.Num() - 1]->InitSlot(InventoryRef->GetInventoryData(i).ItemData);
					EquipmentSlots[EquipmentSlots.Num() - 1]->SetInventoryRef(InventoryRef);

					DisplayGrid->AddChildToUniformGrid(EquipmentSlots[EquipmentSlots.Num() - 1], Row, Col);

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
