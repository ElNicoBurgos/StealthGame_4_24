// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

class UBoxComponent;
class UDecalComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverLapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* ObjectiveMissingSound;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
