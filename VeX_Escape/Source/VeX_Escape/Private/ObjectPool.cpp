// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"

UObjectPool::UObjectPool()
{

}

void UObjectPool::AddActorToPool(AActor* Actor)
{
	SetActorActive(Actor, false);
	ObjectsInPool.Add(Actor);
}

AActor* UObjectPool::TakeActorFromPool(int Index)
{
	if (ObjectsInPool.IsValidIndex(Index))
	{
		AActor* Actor = ObjectsInPool[Index];
		SetActorActive(Actor, true);
		ObjectsInPool.RemoveAt(Index);
		return Actor;
	}
	return nullptr;
}

void UObjectPool::SetActorActive(AActor* Actor, bool Active)
{
	Actor->SetActorHiddenInGame(!Active);
	Actor->SetActorEnableCollision(Active);
	Actor->SetActorTickEnabled(Active);
}