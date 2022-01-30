// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Clothing.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AClothing : public AItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AClothing> HairMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AClothing> BeardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AClothing> GlassesMesh;
};
