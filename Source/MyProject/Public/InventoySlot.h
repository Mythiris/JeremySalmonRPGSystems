// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventoySlot : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
		void InitSlot(FItemData _Item);

protected:

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemThumbnail;
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UToolTip> ToolTip_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		class UToolTip* ToolTip;

	UPROPERTY()
		FItemData ItemData;

	UPROPERTY()
		class APlayerController* PlayerControler;
};
