// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "ToolTip.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UToolTip : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetData(FItemData _ItemData);

private:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemName;

	//UPROPERTY(meta = (BindWidget))
	//	class UTextBlock* ItemRanK;

	//UPROPERTY(meta = (BindWidget))
	//	class UTextBlock* ItemStats;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemInfo;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemThubnail;
	
	UPROPERTY()
		FItemData ItemData;
};
