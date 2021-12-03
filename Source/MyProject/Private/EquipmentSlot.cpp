// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ToolTip.h"
#include "Kismet/GameplayStatics.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UEquipmentSlot::SlotButtonOnClick);
	}

	IsWindowSlot = false;

}

void UEquipmentSlot::NativeDestruct()
{
	Super::NativeDestruct();

	if (ToolTip)
	{
		ToolTip->RemoveFromViewport();
	}

	if (EquipmentInventory)
	{
		EquipmentInventory->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Dick"));
	}
}

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

		ToolTip = CreateWidget<UToolTip>(GetWorld(), ToolTip_Ref);
		ToolTip->SetData(ItemData);

		PlayerControler->GetMousePosition(MouseLoc.X, MouseLoc.Y);
		ToolTip->SetPositionInViewport(MouseLoc);
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
			ToolTip->RemoveFromViewport();
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
				EquipmentInventory->SetPositionInViewport(FVector2D(50, 100));
				EquipmentInventory->AddToViewport();
				return;
			}
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