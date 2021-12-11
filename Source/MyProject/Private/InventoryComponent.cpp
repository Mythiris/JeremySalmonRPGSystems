// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipmentScreen.h"
#include "Kismet/GameplayStatics.h"
#include "MyProjectCharacter.h"
#include "InventoryScreen.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default amount of slots to 8.
	NumberOfSlots = 64;

	static ConstructorHelpers::FClassFinder<UInventoryScreen> FindInventoryScreen_Ref (TEXT("/Game/UserInterface/Inventory/InventoyScreen_Wid"));

	if (FindInventoryScreen_Ref.Class != nullptr)
	{
		InventoryScreen_Ref = FindInventoryScreen_Ref.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UEquipmentScreen> FindEquipmentScreen_Ref(TEXT("/Game/UserInterface/Equipment/EquipmentScreen_Wid"));

	if (FindEquipmentScreen_Ref.Class != nullptr)
	{
		EquipmentScreen_Ref = FindEquipmentScreen_Ref.Class;
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	Inventory.Init(NullItem, NumberOfSlots);

	if (GetWorld())
	{
		if (EquipmentScreen_Ref)
		{
			// Create the EquipmentScreen widget for later use.
			EquipmentScreen = CreateWidget<UEquipmentScreen>(GetWorld(), EquipmentScreen_Ref);
			EquipmentScreen->SetOwnersInventory(this);
		}

		if (InventoryScreen_Ref)
		{
			InventoryScreen = CreateWidget<UInventoryScreen>(GetWorld(), InventoryScreen_Ref);
			 
		}
	}
	// Get the Players Controller.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter  = Cast<AMyProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Set Null item to have a display ThumbNail.
	NullItemData.ThumbNail = NullThumbnail;
	NullItem = { NullItemData, 0 };

	// Init EquipedEquipment Tmap to have its keys and a nullitem.
	EquipedEquipment.Add(EEquipmentSlots::Head, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::Body, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::Arms, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::Legs, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::Feet, NullItemData);

	EquipedEquipment.Add(EEquipmentSlots::LeftHand, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::RightHand, NullItemData);
	EquipedEquipment.Add(EEquipmentSlots::Ranged, NullItemData);
}

// Add an item to the inventoy, return true if the item is added.
bool UInventoryComponent::AddToInventory(FInventoryData ItemToAdd)
{
	FItemData ItemData = ItemToAdd.ItemData;

	// Check if the current item can stack.
	if (ItemData.IsStackable)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			// If this item is in the inventory, check the current stack size against the max stack size.
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

// Add an item to the inventoy, return true if the item is added.
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
		
		// If more than one item was added, add the rest*/
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

	// Check if the total Quantity of the item supasses the max stack size.
	if (TotalQuantity > ItemData.MaxStackSize)
	{
		// Set the Quantity for this slot to max.
		Inventory[Index].Quantity = ItemData.MaxStackSize;

		// Set excess quantity.
		ItemToAdd.Quantity = TotalQuantity - ItemData.MaxStackSize;
		
		// Add the excess to the inventoy.
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

// Toggle Inventory Open and close.
void UInventoryComponent::ToggleInventory()
{
	if (InventoryScreen && PlayerController)
	{

		if (EquipmentScreen->IsInViewport())
		{
			// Remove the widget from the screen and set input back to the game.
			EquipmentScreen->RemoveFromViewport();
		}

		// If Inventory is in viewport Remove it.
		if (InventoryScreen->IsInViewport())
		{
			InventoryScreen->RemoveFromViewport();
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			return;
		}

		// Send Data to inventory and add it to the viewport.
		InventoryScreen->InitWid(this);
		InventoryScreen->AddToViewport();

		// Set input mode to UI.
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		return;
	}

}

// Resize the Inventoy.
void UInventoryComponent::SetInventorySize(int InvnSize)
{
	NumberOfSlots = InvnSize;
}

// Return Inventory size.
int UInventoryComponent::GetInventorySize() const
{
	return(NumberOfSlots);
}

 // Return the data in the inventory at the given slot.
FInventoryData UInventoryComponent::GetInventoryData(int Index)
{
	// Check if the slot is vaild.
	if (Inventory.IsValidIndex(Index))
	{
		return(Inventory[Index]);
	}

	// Return nullitem is the slot is not valid.
	return(NullItem);
}


/////////////////////////////	Equipment ///////////////////////////////////

// Open or close the equipment screen.
void UInventoryComponent::ToggleEquipmet()
{
	if (EquipmentScreen != NULL && PlayerController)
	{
		// If Inventory is in viewport Remove it.
		if (InventoryScreen->IsInViewport())
		{
			InventoryScreen->RemoveFromViewport();
		}

		if (EquipmentScreen->IsInViewport())
		{
			// Remove the widget from the screen and set input back to the game.
			EquipmentScreen->RemoveFromViewport();
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			return;
		}

		// Update the Equipment Screen slots from the data in the EquipedEquipment TMap.
		for (const auto Itter : EquipedEquipment)
		{
			EquipmentScreen->UpdateSlot(Itter.Key, Itter.Value);	
		}

		EquipmentScreen->AddToViewport();

		// Set input to UI.
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		return;
	}
}

// Returns true if the Armordata is in EquipedEquipment.
bool UInventoryComponent::IsItemEquiped(FItemData _Item)
{
	if (_Item.ItemType == Armor)
	{
		// Check that the map has the sent key.
		if (EquipedEquipment.Contains(_Item.ArmorData.ArmorSlot))
		{
			// Check if the data matches.
			if (*EquipedEquipment.Find(_Item.ArmorData.ArmorSlot) == _Item)
			{
				return(true);
			}
		}
		return(false);
	}

	// Check that the map has the sent key.
	if (EquipedEquipment.Contains(_Item.WeaponData.EquipedSlot))
	{
		// Check if the data matches.
		if (*EquipedEquipment.Find(_Item.WeaponData.EquipedSlot) == _Item )
		{
			return(true);
		}
	}
	return(false);
}

// Replaces the current Armor data at the correct slot.
void UInventoryComponent::EquipItem(FItemData _Item)
{
	if (PlayerCharacter)
	{
		if (_Item.ItemType == Armor)
		{
			// Check that the map has the sent key.
			if (EquipedEquipment.Contains(_Item.ArmorData.ArmorSlot))
			{
				// If this item is equiped unequip it. 
				if (IsItemEquiped(_Item))
				{
					UnEquipItem(_Item);
					return;
				}

				// Replace Item in map with the new item. 
				EquipedEquipment.Emplace(_Item.ArmorData.ArmorSlot, _Item);
				// Update the Display slot.
				EquipmentScreen->UpdateSlot(_Item.ArmorData.ArmorSlot, _Item);
				// Update players mesh.
				PlayerCharacter->UpdateEquipmentMesh(_Item.ArmorData.ArmorSlot, _Item);
				return;
			}
		}
		// Check that the map has the sent key.
		if (EquipedEquipment.Contains(_Item.WeaponData.EquipedSlot))
		{
			if (IsItemEquiped(_Item))
			{
				// If this item is equiped unequip it. 
				UnEquipItem(_Item);
				return;
			}
			// Replace Item in map with the new item. 
			EquipedEquipment.Emplace(_Item.WeaponData.EquipedSlot, _Item);
			// Update the Display slot.
			EquipmentScreen->UpdateSlot(_Item.WeaponData.EquipedSlot, _Item);
			// Update players mesh.
			PlayerCharacter->UpdateEquipmentMesh(_Item.WeaponData.EquipedSlot, _Item);
		}
	}
}


// Removes the Armordata at the correct slot.
void UInventoryComponent::UnEquipItem(FItemData _Item)
{
	if (PlayerCharacter)
	{
		if (_Item.ItemType == Armor)
		{
			// Replace Item in map with nothing.
			EquipedEquipment.Emplace(_Item.ArmorData.ArmorSlot);
			// Update the Display slot.
			EquipmentScreen->UpdateSlot(_Item.ArmorData.ArmorSlot, NullItemData);
			// Update players mesh.
			PlayerCharacter->UpdateEquipmentMesh(_Item.ArmorData.ArmorSlot, NullItemData);
		}
		else // Weapon
		{
			// Replace Item in map with nothing.
			EquipedEquipment.Emplace(_Item.WeaponData.EquipedSlot);
			// Update the Display slot.
			EquipmentScreen->UpdateSlot(_Item.WeaponData.EquipedSlot, NullItemData);
			// Update players mesh.
			PlayerCharacter->UpdateEquipmentMesh(_Item.WeaponData.EquipedSlot, NullItemData);
		}
	}

}