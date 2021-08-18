// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VEXPlayerControllerBase.generated.h"

/**
 * 
 */

class UVEXFloatingPawnMovementComponent;

UCLASS()
class VEX_ESCAPE_API AVEXPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	AVEXPlayerControllerBase();

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:

	virtual void BeginPlay() override;

private:

	UVEXFloatingPawnMovementComponent* VEXFloatingPawnMovementComponentReference;

	void MoveUp(float Val);
	void MoveRight(float Val);
	
};
