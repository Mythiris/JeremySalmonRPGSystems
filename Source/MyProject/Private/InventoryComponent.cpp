// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryPanel.h"
#include "EquipmentScreen.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	NumberOfSlots = 8;

	FItemData ItemData;

	NullItem = { ItemData, 0 };

	EquipedArmor.Add(EArmorSlot::Head);
	EquipedArmor.Add(EArmorSlot::Chest);
	EquipedArmor.Add(EArmorSlot::Arms);
	EquipedArmor.Add(EArmorSlot::Legs);
	EquipedArmor.Add(EArmorSlot::Feet);

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	Inventory.Init(NullItem, NumberOfSlots);

	if (EquipmentScreen_Ref != NULL && GetWorld())
	{
		EquipmentScreen = CreateWidget<UEquipmentScreen>(GetWorld(), EquipmentScreen_Ref);
		EquipmentScreen->SetOwnersInventory(this);
	}
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddToInventory(FInventoryData ItemToAdd)
{
	FItemData ItemData = ItemToAdd.ItemData;

	/* Check if the current item can stack */
	if (ItemData.IsStackable)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			/* If this item is in the inventory, check the current stack size against the max stack size */
			if (ItemData.ItemRef == Inventory[i].ItemData.ItemRef && Inventory[i].Quantity < ItemData.MaxStackSize)
			{
				AddToStack(ItemToAdd, i);
				return(true);
			}
		}
	}

  CreateStack(ItemToAdd);
  return(true);
}

bool UInventoryComponent::AddToInventory(FItemData ItemData, int Quantity)
{
	return(AddToInventory(FInventoryData{ ItemData, Quantity }));
}

// Find an empty slot in the inventory and populate it with the item.
void UInventoryComponent::CreateStack(FInventoryData ItemToAdd)
{
	int Index;
	if (Inventory.Find(NullItem, Index))
	{
		Inventory[Index] = FInventoryData{ ItemToAdd.ItemData, 1};
		
		/* If more than one item was added, add the rest*/
		if (ItemToAdd.Quantity - 1 > 0)
		{
			ItemToAdd.Quantity -= 1;
			AddToInventory(ItemToAdd);
		}

		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Inventory Full"));
}

// Increase amount of the item in a single inventory slot. Any excess amount will be passed back to AddToInventory.
void UInventoryComponent::AddToStack(FInventoryData ItemToAdd, int Index)
{
	FItemData ItemData = ItemToAdd.ItemData;
	int TotalQuantity = Inventory[Index].Quantity + ItemToAdd.Quantity;

	/* Check if the total Quantity of the item supasses the max stack size */
	if (TotalQuantity > ItemData.MaxStackSize)
	{
		/* Set the Quantity for this slot to max */
		Inventory[Index].Quantity = ItemData.MaxStackSize;

		/* Set excess quantity */
		ItemToAdd.Quantity = TotalQuantity - ItemData.MaxStackSize;
		
		/* Add the excess to the inventoy  */
		AddToInventory(ItemToAdd);
		return;
	}

	Inventory[Index].Quantity = TotalQuantity;
}

// Check if the item is in the inventory.
bool UInventoryComponent::IsInInventory(FInventoryData Item)
{
	return(Inventory.Contains(Item));
}

void UInventoryComponent::RemoveFromInventory(FInventoryData ItemToRemove)
{
	return;
}

void UInventoryComponent::ToggleInventory()
{
//	if (InventoryWindow != NULL && PlayerController)
//	{
//		if (InventoryWindow->IsInViewport())
//		{
//			InventoryWindow->RemoveFromViewport();
//			PlayerController->SetInputMode(FInputModeGameOnly());
//			PlayerController->bShowMouseCursor = false;
//
//			return;
//		}
//
//		InventoryWindow->Refresh();
//		InventoryWindow->AddToViewport();
//
//		PlayerController->SetInputMode(FInputModeUIOnly());
//		PlayerController->bShowMouseCursor = true;
//		return;
//	}

}

void UInventoryComponent::SetInventorySize(int InvnSize)
{
	NumberOfSlots = InvnSize;
}

int UInventoryComponent::GetInventorySize() const
{
	return(NumberOfSlots);
}

FInventoryData UInventoryComponent::GetInventoryData(int Index)
{
	if (Inventory.IsValidIndex(Index))
	{
		return(Inventory[Index]);
	}

	return(NullItem);
}


/////////////////////////////	Equipment ///////////////////////////////////

void UInventoryComponent::ToggleEquipmet()
{
	if (EquipmentScreen != NULL && PlayerController)
	{
		if (EquipmentScreen->IsInViewport())
		{
			EquipmentScreen->RemoveFromViewport();
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			return;
		}

		//EquipmentScreen->Refresh();
		EquipmentScreen->AddToViewport();

		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		return;
	}
}


bool UInventoryComponent::IsArmorEquiped(FItemData _Armor)
{
	if (EquipedArmor.Contains(_Armor.ArmorData.ArmorSlot))
	{
		if (*EquipedArmor.Find(_Armor.ArmorData.ArmorSlot) == _Armor)
		{
			return(true);
		}
	}
	return(false);
}

void UInventoryComponent::EquipArmor(FItemData _Armor)
{
	if (EquipedArmor.Contains(_Armor.ArmorData.ArmorSlot))
	{
		if (IsArmorEquiped(_Armor))
		{
			UnEquipArmor(_Armor);
			return;
		}

		EquipedArmor.Emplace(_Armor.ArmorData.ArmorSlot, _Armor);
		EquipmentScreen->UpdateSlot(_Armor.ArmorData.ArmorSlot, _Armor);
	}
}

void UInventoryComponent::UnEquipArmor(FItemData _Armor)
{
	EquipedArmor.Emplace(_Armor.ArmorData.ArmorSlot);

	FItemData DeafultItem;
	EquipmentScreen->UpdateSlot(_Armor.ArmorData.ArmorSlot, DeafultItem);

}