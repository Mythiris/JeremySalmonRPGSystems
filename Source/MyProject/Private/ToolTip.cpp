// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTip.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UToolTip::SetData(FItemData _ItemData)
{
	ItemData = _ItemData;

	ItemName->SetText(FText::FromString(ItemData.Name));
	ItemInfo->SetText(FText::FromString(ItemData.ItemDescription));

	ItemThubnail->SetBrushFromTexture(ItemData.ThumbNail);
}