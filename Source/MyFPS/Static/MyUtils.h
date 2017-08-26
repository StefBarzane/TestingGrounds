// Copyright CouchCodersUK created by Steve Barnes

#pragma once

///#include "UObject/NoExportTypes.h"
#include "MyUtils.generated.h"

/**
 * ///class MYFPS_API UMyUtils : public UObject  //changed from this!
 */
UCLASS()
class UMyUtils : public UObject
{
	GENERATED_UCLASS_BODY()
	
	//FORCEINLINE functions
	static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}
	
	//cpp functions
	static void MyDebug(FString DebugString);
	
};
