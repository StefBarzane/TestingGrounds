// Copyright CouchCodersUK created by Steve Barnes

#pragma once

#include "Components/ActorComponent.h"
#include "MyActorPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPS_API UMyActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorPoolComponent();

	AActor* Checkout();
	void ReturnActor(AActor* ActorToReturn);
	void AddActor(AActor* ActorToAdd);

private:
	TArray<AActor*> Pool;
	
};
