// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "MyUtils.h"

UMyUtils::UMyUtils(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMyUtils::MyDebug(FString DebugString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(DebugString));
}
