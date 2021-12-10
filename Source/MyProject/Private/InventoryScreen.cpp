// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryScreen.h"
#include "InventoryPanel.h"
#include "GameFramework/InputSettings.h"

void UInventoryScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

// Initalse the Inventoy panel with its name and data.
void UInventoryScreen::InitWid(UInventoryComponent* _InventoyRef)
{
	InventoyRef = _InventoyRef;

	QuestItems->InitWidget(FString("Quest Items"), InventoyRef, EItemType::Quest);
	CraftingItems->InitWidget(FString("Crafting Items"), InventoyRef, EItemType::Crafting);
	ConsumableItems->InitWidget(FString("Consumable Items"), InventoyRef, EItemType::Consumable);
	MiscItems->InitWidget(FString("Misc Items"), InventoyRef, EItemType::Misc);
}

// Called when a key is pressed.
FReply UInventoryScreen::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// Find the ActionMapping key. 
	TArray<FInputActionKeyMapping> ActionMaping;
	UInputSettings::GetInputSettings()->GetActionMappingByName("ToggleInventory", ActionMaping);

	// Check if the key pressed is the action key.
	for (auto Action : ActionMaping)
	{
		if (Action.Key == InKeyEvent.GetKey())
		{
			InventoyRef->ToggleInventory();
			return FReply::Handled();
		}
	}

	return FReply::Handled();
}