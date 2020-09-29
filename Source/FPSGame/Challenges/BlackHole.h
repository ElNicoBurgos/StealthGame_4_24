// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* InnerSphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* OutSphereComponent;

	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
