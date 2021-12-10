// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
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

	void InitWidget(FString _PanelName, UInventoryComponent* _InventoyRef, TEnumAsByte<EItemType> _DisplayType);
	void UpdateDisplay();

protected:

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* DisplayGrid;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PanelName;

	UPROPERTY()
	UInventoryComponent* InventoyRef;

	UPROPERTY()
	TEnumAsByte<EItemType> DisplayType;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UInventoySlot> InventoySlot_Ref;

	// Variable to hold the widget After Creating it.
	UPROPERTY()
		TArray<class UInventoySlot*> InventoySlot;
};
