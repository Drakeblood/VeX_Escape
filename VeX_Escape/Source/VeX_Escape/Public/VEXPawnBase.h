// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VEXPawnBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UVEXFloatingPawnMovementComponent;

UCLASS()
class VEX_ESCAPE_API AVEXPawnBase : public APawn
{
	GENERATED_BODY()

public:

	AVEXPawnBase();

	virtual void Tick(float DeltaSeconds) override;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* PlaneMesh;

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadOnly)
		UVEXFloatingPawnMovementComponent* VEXFloatingPawnMovement;

private:


};
