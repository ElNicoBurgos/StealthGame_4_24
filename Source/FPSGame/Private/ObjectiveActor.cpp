// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGame/Public/FPSCharacter.h"


// Sets default values
AObjectiveActor::AObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;


	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetSphereRadius(290.f);
	
}

// Called when the game starts or when spawned

void AObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEfects();
}

void AObjectiveActor::PlayEfects()
{
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUpParticle, GetActorLocation());
}

void AObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) 
	{
		MyCharacter->bIsCarryingObjective = true;
		PlayEfects();
		Destroy();
	}

}


