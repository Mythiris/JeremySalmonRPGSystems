// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryPanel.h"
#include "EquipmentScreen.h"
#include "Kismet/GameplayStatics.h"
#include "MyProjectCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default amount of slots to 8.
	NumberOfSlots = 8;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	Inventory.Init(NullItem, NumberOfSlots);

	if (EquipmentScreen_Ref != NULL && GetWorld())
	{
		// Create the EquipmentScreen widget for later use.
		EquipmentScreen = CreateWidget<UEquipmentScreen>(GetWorld(), EquipmentScreen_Ref);
		EquipmentScreen->SetOwnersInventory(this);
	}
	
	// Get the Players Controller.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter  = Cast<AMyProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Set Null item to have a display ThumbNail.
	NullItemData.ThumbNail = NullThumbnail;
	NullItem = { NullItemData, 0 };

	// Init EquipedArmor Tmap to have its keys and a nullitem.
	EquipedArmor.Add(EArmorSlot::Head, NullItemData);
	EquipedArmor.Add(EArmorSlot::Body, NullItemData);
	EquipedArmor.Add(EArmorSlot::Arms, NullItemData);
	EquipedArmor.Add(EArmorSlot::Legs, NullItemData);
	EquipedArmor.Add(EArmorSlot::Feet, NullItemData);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Add an item to the inventoy, return true if the item is added.
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
		if (EquipmentScreen->IsInViewport())
		{
			// Remove the widget from the screen and set input back to the game.
			EquipmentScreen->RemoveFromViewport();
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			return;
		}

		// Update the Equipment Screen slots from the data in the EquipedArmor TMap.
		for (const auto Itter : EquipedArmor)
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

// Returns true if the Armordata is in EquipedArmor.
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

// Replaces the current Armor data at the correct slot.
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
		
		if (PlayerCharacter)
		{
			PlayerCharacter->UpdateArmorMesh(_Armor.ArmorData.ArmorSlot, _Armor.ArmorData.ArmorMesh);
		}
	}
}

// Removes the Armordata at the correct slot.
void UInventoryComponent::UnEquipArmor(FItemData _Armor)
{
	EquipedArmor.Emplace(_Armor.ArmorData.ArmorSlot);

	EquipmentScreen->UpdateSlot(_Armor.ArmorData.ArmorSlot, NullItemData);

	if (PlayerCharacter)
	{
		PlayerCharacter->UpdateArmorMesh(_Armor.ArmorData.ArmorSlot, NullItemData.ArmorData.ArmorMesh);
	}

}