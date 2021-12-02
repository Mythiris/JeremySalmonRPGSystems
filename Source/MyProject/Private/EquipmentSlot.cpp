// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ToolTip.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UEquipmentSlot::SlotButtonOnClick);
	}

	IsWindowSlot = false;
}

void UEquipmentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (ToolTip_Ref != NULL && GetWorld())
	{
		ToolTip = CreateWidget<UToolTip>(GetWorld(), ToolTip_Ref);
		ToolTip->SetData(ItemData);
		ToolTip->SetPositionInViewport(FVector2D(0,0));
		ToolTip->AddToViewport();
	}
}

void UEquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (ToolTip_Ref != NULL)
	{
		if (ToolTip->IsInViewport())
		{
			ToolTip->RemoveFromParent();
		}
	}
}

void UEquipmentSlot::SetIsWindowSlot(bool _IsWindowSlot)
{
	IsWindowSlot = _IsWindowSlot;
}

void UEquipmentSlot::InitSlot(FItemData _Item)
{
	ItemData = _Item;

	if (ItemData.ThumbNail)
	{
		ItemThumbnail->SetBrushFromTexture(ItemData.ThumbNail);
	}

	if (ItemData.ItemType == EItemType::Armor)
	{
		SlotType = ItemData.ArmorData.ArmorSlot;
	}
	
}

void UEquipmentSlot::SlotButtonOnClick()
{
	if (InventoryRef)
	{
		if (IsWindowSlot)
		{

			if (EquipmentInventory_Ref != NULL && GetWorld())
			{
				EquipmentInventory = CreateWidget<UEquipmentInventory>(GetWorld(), EquipmentInventory_Ref);
				EquipmentInventory->InitWid(InventoryRef, SlotType);
				EquipmentInventory->AddToViewport();
			}
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("tt"));
			return;
		}
		
		InventoryRef->EquipArmor(ItemData);
		
	}
}

void UEquipmentSlot::SetSlotType(TEnumAsByte<EArmorSlot> _SlotType)
{
	SlotType = _SlotType;
}

TEnumAsByte<EArmorSlot> UEquipmentSlot::GetSlotType()
{
	return(SlotType);
}

void UEquipmentSlot::SetInventoryRef(UInventoryComponent* _InventoryRef)
{
	InventoryRef = _InventoryRef;
}