// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetData(FInventoryData _SlotData);

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:

	UPROPERTY(meta = (BindWidget))
	class UBorder* ItemBorder;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY()
	FInventoryData SlotData;
	
};
