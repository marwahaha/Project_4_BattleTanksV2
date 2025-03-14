// CopyRight Maximum LTD.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AmingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AmingComponent)) { return; }
	FoundAimingComponent(AmingComponent);
}

void ATankPlayerController::AimTowardsCrossHair()
{
	auto AmingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AmingComponent)) { return; }

	FVector HitLocation; // Out parameter 
	if (GetSightRayHitLocation(HitLocation)) // Has "Side-effect" id going to Raytrace 
	{
		AmingComponent->AimAt(HitLocation);
	}
}

// Get world location of Raytrace through Crosshair, true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLoaction) const
{
	// Find the crosshair position in pixal cordaintes 
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLoaction, ViewportSizeY * CrossHairYLoaction);

	// "De-Project" the screen position pof the crosshair to a world direction
	FVector LookDiraction;
	if (GetLookDiration(ScreenLocation, LookDiraction))
	{
		// RayTrace along that look direction, and see whats is hit (limted range)
		GetLookVectorHitLocation(LookDiraction, HitLoaction);
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDiraction, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDiraction * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line Trace failed
}

bool ATankPlayerController::GetLookDiration(FVector2D ScreenLocation, FVector& LookDiraction) const
{
	FVector CameraWorldLocation; // To be disguarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDiraction
	);
}

