// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "CharacterInventory.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParentMesh = CreateDefaultSubobject<UBoxComponent>(FName("Root"));
	RootComponent = ParentMesh;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	ItemMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetItem(UCharacterInventory* _Inventory) {
	this->Inventory = _Inventory;
}

void AItem::EquipItem() {

}

void AItem::RemoveItem() {

}

