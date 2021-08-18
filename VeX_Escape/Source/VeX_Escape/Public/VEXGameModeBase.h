// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VEXGameModeBase.generated.h"

class UVEXSectorManagerComponent;

/**
 * 
 */
UCLASS()
class VEX_ESCAPE_API AVEXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AVEXGameModeBase();

	FORCEINLINE UVEXSectorManagerComponent* GetVEXSectorManagerComponent() { return VEXSectorManagerComponent; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVEXSectorManagerComponent* VEXSectorManagerComponent;
};
