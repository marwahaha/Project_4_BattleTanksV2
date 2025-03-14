// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Coillision"))
class BATTLETANKV2_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and 1+ is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreePerSecond = 5; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 40; 
};
