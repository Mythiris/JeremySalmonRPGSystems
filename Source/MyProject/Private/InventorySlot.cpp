// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlot::SetData(FInventoryData _SlotData)
{
	SlotData = _SlotData;

	if (SlotData.ItemData.ThumbNail != nullptr)
	{
		ItemImage->SetBrushFromTexture(SlotData.ItemData.ThumbNail);
	}
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("MouseOver"));
}