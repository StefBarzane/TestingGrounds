// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "MyActorPoolComponent.h"

// Sets default values for this component's properties
UMyActorPoolComponent::UMyActorPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AActor * UMyActorPoolComponent::Checkout()
{
	UE_LOG(LogTemp, Warning, TEXT("Checkout() was called by: %s"), *FString(this->GetName()));
	
	if (Pool.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pool has popped[%s] by: %s"), *(Pool.Top()->GetName()), *(GetName()));
		return Pool.Pop();
	}
	else
	{
		return nullptr;
	}
}

void UMyActorPoolComponent::ReturnActor(AActor* ActorToReturn)
{
	Pool.Push(ActorToReturn);
	UE_LOG(LogTemp, Warning, TEXT("ReturnActor[%s]"), *FString(ActorToReturn->GetName()));
}

void UMyActorPoolComponent::AddActor(AActor* ActorToAdd)
{
	if (ActorToAdd) {
		UE_LOG(LogTemp, Warning, TEXT("AddActor[%s]"), *FString(ActorToAdd->GetName()));
		Pool.Push(ActorToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor found to add to pool!"));
	}
}
