// Copyright CouchCodersUK created by Steve Barnes

#pragma once

#include "MyFPSGameMode.h"
#include "MyInfinteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYFPS_API AMyInfinteTerrainGameMode : public AMyFPSGameMode
{
	GENERATED_BODY()

public:
	AMyInfinteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "BoundsPool")
	void PopulateBoundsVolumePool();

	UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	int32 GetGameScore();

	UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	void SetGameScore(int32 Score);
	
private:
	void AddToPool(class ANavMeshBoundsVolume *NavVolume);

protected:
	///UFUNCTION(BlueprintCallable, Category = "MyFuncs")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyProperties")
	class UMyActorPoolComponent* NavMeshBoundsVolumePool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyProperties")
	int GameScore;
};
