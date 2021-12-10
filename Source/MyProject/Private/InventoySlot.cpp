// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoySlot.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "ToolTip.h"

void UInventoySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UInventoySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
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

void UInventoySlot::InitSlot(FItemData _Item)
{
	ItemData = _Item;

	if (ItemThumbnail)
	{
		ItemThumbnail->SetBrushFromTexture(ItemData.ThumbNail);
	}
}
