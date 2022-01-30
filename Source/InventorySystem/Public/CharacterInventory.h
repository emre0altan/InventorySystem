// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemCharacter.h"
#include "Item.h"
#include "CharacterInventory.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UCharacterInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterInventory();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AInventorySystemCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<class AItem>> AllOwnedItemsClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AItem* CurrentWeaponItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UItemData*> OwnedWeaponItemDatas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AItem> DefaultWeaponItemClass;

	UPROPERTY(BlueprintReadOnly)
	UItemData* CurrentHeadItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UItemData*> OwnedHeadItemDatas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AItem> DefaultHeadItemClass;

	UPROPERTY(BlueprintReadOnly)
		UItemData* CurrentTorsoItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UItemData*> OwnedTorsoItemDatas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AItem> DefaultTorsoItemClass;

	UPROPERTY(BlueprintReadOnly)
		UItemData* CurrentPantsItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UItemData*> OwnedPantsItemDatas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AItem> DefaultPantsItemClass;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void CollectItem(AItem* Item);

	virtual UItemData* GetItemData(AItem* Item);

	UFUNCTION(BlueprintCallable)
	virtual void EquipItem(UItemData* ItemData);

	virtual void RemoveItemToBackpack(TEnumAsByte<EItemType> ItemType);

	virtual void SpawnItemFromBackPack(UItemData* ItemData);	

};
