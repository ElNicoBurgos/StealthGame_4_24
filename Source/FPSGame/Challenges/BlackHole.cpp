// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black Hole"));
	MeshComp->SetCollisionEnabled((ECollisionEnabled::NoCollision));
	RootComponent = MeshComp;

	OutSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Out Sphere"));
	OutSphereComponent->SetSphereRadius(3000.f);
	OutSphereComponent->SetupAttachment(MeshComp);


	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere"));
	InnerSphereComponent->SetSphereRadius(100.f);
	InnerSphereComponent->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind to Event
	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Find all overlapping components that can collide and may be physically simulating.
	TArray<UPrimitiveComponent *> ActorsOverlapping;
	OutSphereComponent->GetOverlappingComponents(ActorsOverlapping);

	
	for(int i = 0; i < ActorsOverlapping.Num(); i++)
	{
		UPrimitiveComponent* PrimCompRef = Cast<UPrimitiveComponent>(ActorsOverlapping[i]);
		if(PrimCompRef && PrimCompRef->IsSimulatingPhysics())
		{

			const float ForceStrenght = -2000.f; // Negative value to make it pull towards the origin instead of pushing away
			PrimCompRef->AddRadialForce(GetActorLocation(), OutSphereComponent->GetScaledSphereRadius(), ForceStrenght , ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
	

}


void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		OtherActor->Destroy();
	}
}
