// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInventory.h"
#include "Weapon.h"
#include "Clothing.h"
#include "ItemData.h"

// Sets default values for this component's properties
UCharacterInventory::UCharacterInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCharacterInventory::BeginPlay()
{
	Super::BeginPlay();

	Character = (AInventorySystemCharacter*)GetOwner();
	CurrentWeaponItem = (AItem*)(GetWorld()->SpawnActor<AItem>(DefaultWeaponItemClass));
	//CurrentWeaponItem->SetItem(this);
	CurrentWeaponItem->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Weapon"));
	AllOwnedItemsClasses.Add(DefaultWeaponItemClass);

	UItemData* itemData = NewObject<UItemData>(UItemData::StaticClass());
	itemData->ItemName = "Head1";
	itemData->ItemClass = DefaultHeadItemClass;
	itemData->ItemType = Head;
	CurrentHeadItem = itemData;
	AllOwnedItemsClasses.Add(DefaultHeadItemClass);

	itemData = NewObject<UItemData>(UItemData::StaticClass());
	itemData->ItemName = "Torso1";
	itemData->ItemClass = DefaultTorsoItemClass;
	itemData->ItemType = Torso;
	CurrentTorsoItem = itemData;
	AllOwnedItemsClasses.Add(DefaultTorsoItemClass);

	itemData = NewObject<UItemData>(UItemData::StaticClass());
	itemData->ItemName = "Pants1";
	itemData->ItemClass = DefaultPantsItemClass;
	itemData->ItemType = Legs;
	CurrentPantsItem = itemData;
	AllOwnedItemsClasses.Add(DefaultPantsItemClass);
}


// Called every frame
void UCharacterInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UCharacterInventory::CollectItem(AItem* Item) {
	if (!AllOwnedItemsClasses.Contains(Item->GetClass())) {
		AllOwnedItemsClasses.Add(Item->GetClass());
		GetWorld()->DestroyActor(Item);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Item->ItemName + " picked up!");

		if (Item->ItemType == Weapon) {
			OwnedWeaponItemDatas.Add(GetItemData(Item));
		}
		else if (Item->ItemType == Head) {
			OwnedHeadItemDatas.Add(GetItemData(Item));
		}
		else if (Item->ItemType == Torso) {
			OwnedTorsoItemDatas.Add(GetItemData(Item));
		}
		else if (Item->ItemType == Legs) {
			OwnedPantsItemDatas.Add(GetItemData(Item));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Item->ItemName + "Item already exist!");
	}
}

UItemData* UCharacterInventory::GetItemData(AItem* Item) {
	UItemData* itemData = NewObject<UItemData>(UItemData::StaticClass());
	itemData->ItemName = Item->ItemName;
	itemData->ItemClass = Item->GetClass();
	itemData->ItemType = Item->ItemType;
	return itemData;
}

void UCharacterInventory::EquipItem(UItemData* ItemData) {
	RemoveItemToBackpack(ItemData->ItemType);
	SpawnItemFromBackPack(ItemData);

	Character->OnOwnedItemsUpdate();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ItemData->ItemName + " equipped!");
}

void UCharacterInventory::RemoveItemToBackpack(TEnumAsByte<EItemType> ItemType) {
	if (ItemType == Weapon && CurrentWeaponItem != nullptr) {
		OwnedWeaponItemDatas.Add(GetItemData(CurrentWeaponItem));
		CurrentWeaponItem->RemoveItem();
		GetWorld()->DestroyActor(CurrentWeaponItem);
	}
	else if (ItemType == Head) {
		OwnedHeadItemDatas.Add(CurrentHeadItem);
	}
	else if (ItemType == Torso) {
		OwnedTorsoItemDatas.Add(CurrentTorsoItem);
	}
	else if (ItemType == Legs) {
		OwnedPantsItemDatas.Add(CurrentPantsItem);
	}
}

void UCharacterInventory::SpawnItemFromBackPack(UItemData* ItemData) {
	
	if (ItemData->ItemType == Weapon) {
		OwnedWeaponItemDatas.Remove(ItemData);
		CurrentWeaponItem = (AItem*)(GetWorld()->SpawnActor<AItem>(ItemData->ItemClass));
		CurrentWeaponItem->SetItem(this);
		CurrentWeaponItem->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Weapon"));
	}
	else if(ItemData->ItemType == Head){
		OwnedHeadItemDatas.Remove(ItemData);
		AClothing* HeadBP = ItemData->ItemClass->GetDefaultObject<AClothing>();
		Character->GetMesh()->SetSkeletalMesh(HeadBP->ItemMesh->SkeletalMesh);
		Character->GetMesh()->SetAnimClass(Character->TorsoMesh->GetAnimClass());

		if (HeadBP->HairMesh) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "HAS HAIR MESH");
			Character->HairMesh->SetSkeletalMesh(HeadBP->HairMesh->GetDefaultObject<AClothing>()->ItemMesh->SkeletalMesh);
			Character->HairMesh->SetAnimClass(Character->TorsoMesh->GetAnimClass());
			Character->HairMesh->SetMasterPoseComponent(Character->GetMesh());
		}
		else {
			Character->HairMesh->SetSkeletalMesh(nullptr);
			Character->HairMesh->SetAnimClass(nullptr);
		}

		if (HeadBP->BeardMesh) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "HAS HAIR MESH");
			Character->BeardMesh->SetSkeletalMesh(HeadBP->BeardMesh->GetDefaultObject<AClothing>()->ItemMesh->SkeletalMesh);
			Character->BeardMesh->SetAnimClass(Character->TorsoMesh->GetAnimClass());
			Character->BeardMesh->SetMasterPoseComponent(Character->GetMesh());
		}
		else {
			Character->BeardMesh->SetSkeletalMesh(nullptr);
			Character->BeardMesh->SetAnimClass(nullptr);
		}

		if (HeadBP->GlassesMesh) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "HAS HAIR MESH");
			Character->GlassesMesh->SetSkeletalMesh(HeadBP->GlassesMesh->GetDefaultObject<AClothing>()->ItemMesh->SkeletalMesh);
			Character->GlassesMesh->SetAnimClass(Character->TorsoMesh->GetAnimClass());
			Character->GlassesMesh->SetMasterPoseComponent(Character->GetMesh());
		}
		else {
			Character->GlassesMesh->SetSkeletalMesh(nullptr);
			Character->GlassesMesh->SetAnimClass(nullptr);
		}

		Character->TorsoMesh->SetMasterPoseComponent(Character->GetMesh());
		Character->LegsMesh->SetMasterPoseComponent(Character->GetMesh());
		Character->HandMesh->SetMasterPoseComponent(Character->GetMesh());
		CurrentHeadItem = ItemData;
	}
	else if (ItemData->ItemType == Torso) {
		OwnedTorsoItemDatas.Remove(ItemData);
		AClothing* TorsoBP = ItemData->ItemClass->GetDefaultObject<AClothing>();
		Character->TorsoMesh->SetSkeletalMesh(TorsoBP->ItemMesh->SkeletalMesh);
		Character->TorsoMesh->SetAnimClass(Character->GetMesh()->GetAnimClass());
		Character->TorsoMesh->SetMasterPoseComponent(Character->GetMesh());
		Character->TorsoMesh->SetMaterial(0,TorsoBP->ItemMesh->GetMaterial(0));
		CurrentTorsoItem = ItemData;
	}
	else if (ItemData->ItemType == Legs) {
		OwnedPantsItemDatas.Remove(ItemData);
		AClothing* PantsBP = ItemData->ItemClass->GetDefaultObject<AClothing>();
		Character->LegsMesh->SetSkeletalMesh(PantsBP->ItemMesh->SkeletalMesh);
		Character->LegsMesh->SetAnimClass(Character->GetMesh()->GetAnimClass());
		Character->LegsMesh->SetMasterPoseComponent(Character->GetMesh());
		Character->LegsMesh->SetMaterial(0, PantsBP->ItemMesh->GetMaterial(0));
		CurrentPantsItem = ItemData;
	}
}

