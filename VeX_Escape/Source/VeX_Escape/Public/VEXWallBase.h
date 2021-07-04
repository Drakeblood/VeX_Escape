// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VEXWallBase.generated.h"

UCLASS()
class VEX_ESCAPE_API AVEXWallBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AVEXWallBase();

protected:

	virtual void BeginPlay() override;

private:

};
