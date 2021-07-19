// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "VEXSectorManagerComponent.generated.h"

class AVEXWallBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXSectorManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UVEXSectorManagerComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall")
		TSubclassOf<AVEXWallBase> WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cube")
		int WallsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		float WallXExtent;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Displacement();

	UFUNCTION(BlueprintCallable)
		void ChangeDisplacementOrder(int YDisplacement, int ZDisplacement);


private:
	
	TArray<AVEXWallBase*> Walls;

	int YDisplacementOrder, ZDisplacementOrder;
		
};