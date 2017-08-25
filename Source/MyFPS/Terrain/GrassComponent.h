// Copyright CouchCodersUK created by Steve Barnes

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrassComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FBox SpawningBounds;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int SpawnCount;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnZOffset = 0.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void SpawnGrass();
		
};
