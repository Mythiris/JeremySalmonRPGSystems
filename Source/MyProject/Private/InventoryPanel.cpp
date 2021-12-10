// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanel.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "InventoySlot.h"

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

// Set Default values and display them.
void UInventoryPanel::InitWidget(FString _PanelName, UInventoryComponent* _InventoyRef, TEnumAsByte<EItemType> _DisplayType)
{
	PanelName->SetText(FText::FromString(_PanelName));
	InventoyRef = _InventoyRef;
	DisplayType = _DisplayType;
	UpdateDisplay();
}

// Load data to the InventoySlot and add it to the display grid.
void UInventoryPanel::UpdateDisplay()
{
	int Row = 0, Col = 0;

	if (InventoyRef)
	{
		// Itterate through the inventory.
		for (int i = 0; i < InventoyRef->GetInventorySize(); i++)
		{
			FItemData Item = InventoyRef->GetInventoryData(i).ItemData;

			if (Item.ItemType == DisplayType)
			{
				if (InventoySlot_Ref != NULL && GetWorld())
				{
					// Create the inventorySlot widget.
					InventoySlot.Add(CreateWidget<UInventoySlot>(GetWorld(), InventoySlot_Ref));
					InventoySlot[InventoySlot.Num() - 1]->InitSlot(Item);
					DisplayGrid->AddChildToUniformGrid(InventoySlot[InventoySlot.Num() - 1], Row, Col);
					Col++;

					// Addjust location in the uniform grid.
					if (Col == 4)
					{
						Col = 0;
						Row++;
					}

				}
			}
		}
	}
}