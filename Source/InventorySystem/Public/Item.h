// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum EItemType {
	Weapon      UMETA(DisplayName = "Weapon"),
	Head   UMETA(DisplayName = "Head"),
	Torso   UMETA(DisplayName = "Torso"),
	Legs   UMETA(DisplayName = "Legs"),
};

UCLASS()
class INVENTORYSYSTEM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	class UCharacterInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	UBoxComponent* ParentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TEnumAsByte<EItemType> ItemType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetItem(UCharacterInventory* Inventory);

	virtual void EquipItem();

	virtual void RemoveItem();
};
