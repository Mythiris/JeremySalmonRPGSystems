// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ToolTip.h"
#include "Kismet/GameplayStatics.h"

// Called on creation.
void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		// Bind function to the button.
		SlotButton->OnClicked.AddDynamic(this, &UEquipmentSlot::SlotButtonOnClick);
	}

	IsWindowSlot = false;
}

// Called when the object is destoryed.
void UEquipmentSlot::NativeDestruct()
{
	Super::NativeDestruct();

	// Remove children from viewport.
	if (ToolTip)
	{
		ToolTip->RemoveFromViewport();
	}

	if (EquipmentInventory)
	{
		EquipmentInventory->RemoveFromParent();
	}
}

// Called when the mouse enters the widget.
void UEquipmentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (!PlayerControler)
	{
		PlayerControler = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}

	if (ToolTip_Ref != NULL && GetWorld())
	{
		FVector2D MouseLoc;

		// Set ToolTip data.
		ToolTip = CreateWidget<UToolTip>(GetWorld(), ToolTip_Ref);
		ToolTip->SetData(ItemData);

		PlayerControler->GetMousePosition(MouseLoc.X, MouseLoc.Y);

		// Set widget location to mouse location.
		ToolTip->SetPositionInViewport(MouseLoc);
		ToolTip->AddToViewport();
	}
}

// Called when the mouse leaves this widget.
void UEquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	// If tooltip is active remove it from the viewport.
	if (ToolTip_Ref != NULL)
	{
		if (ToolTip->IsInViewport())
		{
			ToolTip->RemoveFromViewport();
		}
	}
}

// Used to set the display slot.
void UEquipmentSlot::SetIsWindowSlot(bool _IsWindowSlot)
{
	IsWindowSlot = _IsWindowSlot;
}

// Init slot data.
void UEquipmentSlot::InitSlot(FItemData _Item)
{
	ItemData = _Item;

	if (ItemData.ThumbNail)
	{
		// Set slot thumbnail from data.
		ItemThumbnail->SetBrushFromTexture(ItemData.ThumbNail);
	}

	if (ItemData.ItemType == EItemType::Armor)
	{
		SlotType = ItemData.ArmorData.ArmorSlot;
	}
	
}

// Callled on button click.
void UEquipmentSlot::SlotButtonOnClick()
{
	if (InventoryRef)
	{
		// If this slot is in the equipment screen.
		if (IsWindowSlot)
		{
			if (EquipmentInventory_Ref != NULL && GetWorld())
			{
				// Create the equipment inventory widget.
				EquipmentInventory = CreateWidget<UEquipmentInventory>(GetWorld(), EquipmentInventory_Ref);
				// Set the data type for the equipment inventory widget to display.

				EquipmentInventory->InitWid(InventoryRef, SlotType);
				EquipmentInventory->SetPositionInViewport(FVector2D(50, 100));
				EquipmentInventory->AddToViewport();
				return;
			}
		}
		// If this widget is not on the equipment screen, equip the armor displayed.
		InventoryRef->EquipArmor(ItemData);
		
	}
}

// Set the slots type.
void UEquipmentSlot::SetSlotType(TEnumAsByte<EEquipmentSlots> _SlotType)
{
	SlotType = _SlotType;
}

// Return slot type.
TEnumAsByte<EEquipmentSlots> UEquipmentSlot::GetSlotType()
{
	return(SlotType);
}

// Sets the inventory referance. 
void UEquipmentSlot::SetInventoryRef(UInventoryComponent* _InventoryRef)
{
	InventoryRef = _InventoryRef;
}