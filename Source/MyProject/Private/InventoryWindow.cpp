// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWindow.h"
#include "Components/GridPanel.h"
#include "GameFramework/InputSettings.h"


void UInventoryWindow::NativeConstruct()
{
	Super::NativeConstruct();

	// Allow this wiget to take inputs.
	this->bIsFocusable = true;
}


void UInventoryWindow::InitWidget(UInventoryComponent* _Inventory)
{
	Inventory = _Inventory;

	InventoryGrid->SetColumnFill(8, 0.0f);
	InventoryGrid->SetRowFill(3, 0.0f);

	InventorySlot.Init(NULL, Inventory->GetInventorySize());

	if (InvenSlot_ref != NULL && GetWorld())
	{
		int row;
		int col;

		for (int i = 0; i < Inventory->GetInventorySize(); i++)
		{
			col = i % 8;
			row = i / 8;
			
			InventorySlot[i] = CreateWidget<UInventorySlot>(GetWorld(), InvenSlot_ref);
			InventorySlot[i]->SetData(Inventory->GetInventoryData(i));
			
			InventoryGrid->AddChildToGrid(InventorySlot[i], row, col);
				
		}
	}
}

void UInventoryWindow::Refresh()
{
	if (Inventory != NULL)
	{
		for (int i = 0; i < Inventory->GetInventorySize(); i++)
		{
			InventorySlot[i]->SetData(Inventory->GetInventoryData(i));
		}
	}
}

FReply UInventoryWindow::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	TArray<FInputActionKeyMapping> ActionMaping;
	UInputSettings::GetInputSettings()->GetActionMappingByName("ToggleInventory", ActionMaping);

	for (auto Action : ActionMaping)
	{
		if (Action.Key == InKeyEvent.GetKey())
		{
			Inventory->ToggleInventory();
			return FReply::Handled();
		}
	}

	return FReply::Handled();
}