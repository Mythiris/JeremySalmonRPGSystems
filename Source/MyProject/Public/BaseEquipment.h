// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BaseEquipment.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABaseEquipment : public ABaseItem
{
	GENERATED_BODY()

public:

private:

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EquipmentType> EquipType;
	
};
