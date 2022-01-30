// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UItemData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TSubclassOf<class AItem> ItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EItemType> ItemType;
};
