// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "MyInfinteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "MyActorPoolComponent.h"

//Constructor
AMyInfinteTerrainGameMode::AMyInfinteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UMyActorPoolComponent>(FName("Nav Mesh Bounds Volume Pool"));
}

void AMyInfinteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *NavVolume)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Volume: %s"), *NavVolume->GetName());
	NavMeshBoundsVolumePool->AddActor(NavVolume);
}

void AMyInfinteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (VolumeIterator)
	{
		///AActor* FoundVolume = *VolumeIterator; /// strange overloaded use of *
		///UE_LOG(LogTemp, Warning, TEXT("Found Volume: %s"), *FoundVolume->GetName());

		AddToPool(*VolumeIterator);
		++VolumeIterator; ///advance iterator
	}
}

int32 AMyInfinteTerrainGameMode::GetGameScore()
{
	return GameScore;
}

void AMyInfinteTerrainGameMode::SetGameScore(int32 Score)
{
	GameScore = Score;
}
