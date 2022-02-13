// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VeX_Escape.h"
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

protected:
	UVEXSectorManagerComponent* VEXSectorManagerComponent;

public:
	AVEXGameModeBase();

	inline UVEXSectorManagerComponent* GetVEXSectorManagerComponent();
	
protected:
	virtual void BeginPlay();
};