// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "Components/Button.h"
#include "EquipmentInventory.h"
#include "Components/Image.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UEquipmentSlot::SlotButtonOnClick);
	}
}

void UEquipmentSlot::InitSlot(int Index, UInventoryComponent* _InventoryRef)
{
	SetInventoryRef(_InventoryRef);

	FInventoryData InvenData = InventoryRef->GetInventoryData(Index);

	if (InvenData.ItemData.ThumbNail)
	{
		ItemThumbnail->SetBrushFromTexture(InvenData.ItemData.ThumbNail);
	}
}

void UEquipmentSlot::SlotButtonOnClick()
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