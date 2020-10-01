// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"


// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverLapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Comp"));
	OverLapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverLapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverLapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverLapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverLapComp;

	OverLapComp->SetHiddenInGame(false);


	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Comp"));
	DecalComp->DecalSize = FVector(200.f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	OverLapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);
}


void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone"));

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if(MyPawn == nullptr) { return; }


	
	if(MyPawn && MyPawn->bIsCarryingObjective)
	{
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if(GM)
		{
			GM->CompleteMission(MyPawn);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}

