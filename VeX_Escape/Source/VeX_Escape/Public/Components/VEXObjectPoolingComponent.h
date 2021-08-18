// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.h"
#include "VEXObjectPoolingComponent.generated.h"

UENUM(BlueprintType)
enum class EVEXItemType : uint8
{
	Coin = 0,
	Mine = 1,
	Turret = 2,
	LaserBlocks = 3,

	END
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXObjectPoolingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UVEXObjectPoolingComponent();

private:

	TMap<EVEXItemType, UObjectPool*> ObjectPools;

};
