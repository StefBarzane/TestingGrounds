// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "MyActorPoolComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GroundOffset = FVector(0, 0, 50);
}

FVector ATile::FindEmptyLocation(float Radius, float LocationZOffset)
{
	FVector ZOffSetVector(0, 0, LocationZOffset);
	FBox SpawnBounds(MinExtents + ZOffSetVector, MaxExtents + ZOffSetVector);
	FVector CandidateSpawnPoint = FMath::RandPointInBox(SpawnBounds);

	if (CanSpawnAtLocation(CandidateSpawnPoint, Radius)) {
		return CandidateSpawnPoint;
	}
	else return FVector::ZeroVector;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnTransform& SpawnTransform)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRelativeLocation(SpawnTransform.Location + GroundOffset);
	Spawned->SetActorRelativeRotation(SpawnTransform.Rotation);
	Spawned->SetActorScale3D(FVector(SpawnTransform.Scale));
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnTransform& SpawnTransform)
{
	UE_LOG(LogTemp, Warning, TEXT("PlaceActor [Pawn] was called: %s"), *(ToSpawn->GetName()));
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRelativeLocation(SpawnTransform.Location + GroundOffset);
	Spawned->SetActorRelativeRotation(SpawnTransform.Rotation);
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}

TArray<FSpawnTransform> ATile::RandomSpawnTransforms(int MinObjects, int MaxObjects, float Radius, float ZOffset, float MinScale, float MaxScale)
{
	TArray<FSpawnTransform> SpawnTransforms;
	int NumToSpawn = FMath::RandRange(MinObjects, MaxObjects);
	
	for (size_t i = 0; i < NumToSpawn; i++) // TODO: maybe we could give each object a value based on size and spawn until a max value is reached
	{
		FSpawnTransform SpawnTransform;
		SpawnTransform.Scale = FMath::RandRange(MinScale, MaxScale);
		SpawnTransform.Location = FindEmptyLocation(Radius * SpawnTransform.Scale, ZOffset);

		if (SpawnTransform.Location != FVector::ZeroVector) {
			SpawnTransform.Rotation = FRotator::MakeFromEuler(FVector(0, 0, FMath::RandRange(-180.0f, 180.0f)));
			SpawnTransform.Location -= FVector(0, 0, ZOffset);
			SpawnTransforms.Add(SpawnTransform);
		}
	}
	return SpawnTransforms;
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult HitResult; ///required for function call but unused at present
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	FColor ResultColour;

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	
	if (HasHit) {
		ResultColour = FColor::Red;
	}
	else {
		ResultColour = FColor::Green;
	}
	///DrawDebugSphere(GetWorld(), Location, Radius, 32, ResultColour, true);
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColour, true);

	return !HasHit;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale, float ZOffset)
{
	for (FSpawnTransform SpawnTransform : RandomSpawnTransforms(MinSpawn, MaxSpawn, Radius, ZOffset, MinScale, MaxScale))
	{
		PlaceActor(ToSpawn, SpawnTransform);
	}

	///UE_LOG (LogTemp, Warning, TEXT("Spawn point is %s"), *SpawnPoint.ToCompactString());
}

void ATile::PlaceAICharacters(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float ZOffset)
{
	for (FSpawnTransform SpawnTransform : RandomSpawnTransforms(MinSpawn, MaxSpawn, Radius, ZOffset))
	{
		//ToSpawn->
		PlaceActor(ToSpawn, SpawnTransform);
		
	}
}

void ATile::SetPool(UMyActorPoolComponent * InPool)
{
	Pool = InPool;
	UE_LOG(LogTemp, Warning, TEXT("SetPool was called: %s"), *(InPool->GetName()));
	///UE_LOG(LogTemp, Warning, TEXT("SomeText"));
	PositionNavMeshVolume();
}

void ATile::PositionNavMeshVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume)
	{
		FVector NewLocation = GetActorLocation() + FVector(2000, 0 , 0); //TODO: remove magic number - use Min/MaxExtents member variables
		NavMeshBoundsVolume->SetActorLocation(NewLocation);
		GetWorld()->GetNavigationSystem()->Build();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NavMeshBoundsVolume not found in pool!"));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	///CastSphere(FVector(0, 0, 1000), 100);
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("EndPlay called on: %s"), *FString(this->GetName()));
	
	if (NavMeshBoundsVolume) {
		Pool->ReturnActor(NavMeshBoundsVolume);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No NavMesh to return!"));
	}
}
