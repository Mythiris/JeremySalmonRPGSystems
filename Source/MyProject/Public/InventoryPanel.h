// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventorySlot.h"
#include "InventoryPanel.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION(BlueprintCallable)
	void InitWidget(UInventoryComponent* Inventory);

	void Refresh();

	//UFUNCTION(BlueprintCallable)
	//void ChangeDisplayType(TEnumAsByte<ItemType> _DisplayType);

protected:
	 
	UPROPERTY()
	class UInventoryComponent* Inventory;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//	TEnumAsByte<ItemType> DisplayType;

	UPROPERTY(meta = (BindWidget))
	class UGridPanel* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InventoryName;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UInventorySlot> InvenSlot_ref;

	UPROPERTY()
		TArray<UInventorySlot*> InventorySlot;
};
