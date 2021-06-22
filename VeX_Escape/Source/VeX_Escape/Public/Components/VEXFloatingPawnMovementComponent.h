// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "VEXFloatingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class VEX_ESCAPE_API UVEXFloatingPawnMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:

	UVEXFloatingPawnMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveUp(float Val);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveRight(float Val);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float ReturnTo0RotationSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RollSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float PitchAngle;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float YawAngle;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RollAngle;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float IncreaseAccelerationValue;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float IncreaseAccelerationRatio;

private:

	void IncreaseMaxSpeed();

	FTimerHandle IncreaseAccelerationTimer;
	
};
