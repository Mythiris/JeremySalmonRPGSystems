// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoryScreen.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UInventoryScreen : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	void InitWid(UInventoryComponent* _InventoyRef);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;


protected:

	UPROPERTY(meta = (BindWidget))
	class UInventoryPanel* QuestItems;

	UPROPERTY(meta = (BindWidget))
	class UInventoryPanel* CraftingItems;

	UPROPERTY(meta = (BindWidget))
	class UInventoryPanel* ConsumableItems;

	UPROPERTY(meta = (BindWidget))
	class UInventoryPanel* MiscItems;

	UPROPERTY()
		UInventoryComponent* InventoyRef;
	
};
