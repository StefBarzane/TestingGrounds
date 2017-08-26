// Copyright CouchCodersUK created by Steve Barnes

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnTransform
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	FRotator Rotation;
	float Scale;
};

class UMyActorPoolComponent;

UCLASS()
class MYFPS_API ATile : public AActor
{
	GENERATED_BODY()

private:
	UMyActorPoolComponent* Pool;
	AActor* NavMeshBoundsVolume;
		
	bool CanSpawnAtLocation(FVector Location, float Radius);
	FVector FindEmptyLocation(float Radius, float LocationZOffset);
	void PositionNavMeshVolume();

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 10, float Radius = 200.0f, float ZOffset = 0.0f, float MinScale = 1.0f, float MaxScale = 1.0f);

	TArray<FSpawnTransform> RandomSpawnTransforms(int MinObjects, int MaxObjects, float Radius, float ZOffset, float MinScale = 1.0f, float MaxScale = 1.0f);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnTransform& SpawnTransform);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnTransform& SpawnTransform);
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 10, float Radius = 200.0f, float ZOffset = 0.0f, float MinScale = 1.0f, float MaxScale = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	void PlaceAICharacters(TSubclassOf<APawn> ToSpawn, int MinSpawn = 1, int MaxSpawn = 10, float Radius = 200.0f, float ZOffSet = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	void SetPool(UMyActorPoolComponent* Pool);

	UPROPERTY(EditDefaultsOnly, Category = "MyProperties")
	FVector GroundOffset;

	UPROPERTY(EditDefaultsOnly, Category = "MyProperties")
	FVector MinExtents = FVector(0, -2000, 0);

	UPROPERTY(EditDefaultsOnly, Category = "MyProperties")
	FVector MaxExtents = FVector(4000, 2000, 0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};

