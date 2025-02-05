// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class PROJECT_6_1_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	

	UPROPERTY(VisibleAnywhere, Category = "BoxCollider")
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "StaticMeshComponent")
	UStaticMeshComponent* StaticMeshComponent;
	
private:
	bool bOpenDoor = false;
	FRotator OpenRotation;

	FTimerHandle OpenDoorTimerHandle;
	float OpenTime = 2.0f;
	float TimeElapsed = 0.0f;

	void OpenDoor();
};
