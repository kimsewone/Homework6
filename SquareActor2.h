// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquareActor2.generated.h"

UENUM(BlueprintType)
enum class EROTATIONTYPE : uint8
{
	E_RIGHT = 0,		
	E_LEFT = 1
};
UCLASS()
class PROJECT_6_1_API ASquareActor2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquareActor2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void SetRadius(float _radius);
	void SetDir(EROTATIONTYPE type);
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GamePlay|Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "GamePlay|Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	float Speed = 40.f;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	bool bPlayStart = true;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	EROTATIONTYPE RotationType = EROTATIONTYPE::E_RIGHT;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	float Radius = 800.f;

	float Dir = 1.f;

};
