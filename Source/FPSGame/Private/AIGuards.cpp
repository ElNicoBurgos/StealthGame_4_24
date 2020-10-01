// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuards.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIGuards::AAIGuards()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->HearingThreshold = 750.f;
	PawnSensingComp->LOSHearingThreshold = 1500.f;
	PawnSensingComp->SightRadius = 3170.f;
	PawnSensingComp->SetPeripheralVisionAngle(30.f);

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuards::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuards::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AAIGuards::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIGuards::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIGuards::OnSeenPawn(APawn* SeenPawn)
{
	if(SeenPawn == nullptr) { return; }

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 16, FColor::Magenta, false, 5.f);

}

void AAIGuards::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.f, 32, FColor::Red, false, 5.f);

}

