// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "GrassComponent.h"


// Sets default values for this component's properties
UGrassComponent::UGrassComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnCount; i++) {
		FVector Location = FMath::RandPointInBox(SpawningBounds);
		AddInstance(FTransform(Location + FVector(0, 0, SpawnZOffset)));
	}
}


