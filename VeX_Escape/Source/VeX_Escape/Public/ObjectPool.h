// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class VEX_ESCAPE_API UObjectPool : public UObject
{
	GENERATED_BODY()

public:

	UObjectPool();

	void AddActorToPool(AActor* Object);
	AActor* TakeActorFromPool(int Index);

private:

	TArray<AActor*> ObjectsInPool;

	void SetActorActive(AActor* Object, bool Active);
	
};
