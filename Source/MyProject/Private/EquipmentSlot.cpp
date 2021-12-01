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
		ToolTip->SetData(InvenData.ItemData);
		ToolTip->SetPositionInViewport(FVector2D(0,0));
		ToolTip->AddToViewport();
	}
}

void UEquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Some debug message!"));

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

void UEquipmentSlot::InitSlot(int Index, UInventoryComponent* _InventoryRef)
{
	SetInventoryRef(_InventoryRef);

	InvenData = InventoryRef->GetInventoryData(Index);

	if (InvenData.ItemData.ThumbNail)
	{
		ItemThumbnail->SetBrushFromTexture(InvenData.ItemData.ThumbNail);
	}
}

void UEquipmentSlot::SlotButtonOnClick()
{
	if (IsWindowSlot)
	{
		if (InventoryRef)
		{
			if (EquipmentInventory_Ref != NULL && GetWorld())
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("ButtonClick"));
				EquipmentInventory = CreateWidget<UEquipmentInventory>(GetWorld(), EquipmentInventory_Ref);
				EquipmentInventory->InitWid(InventoryRef, SlotType);
				EquipmentInventory->AddToViewport();
			}
		}
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