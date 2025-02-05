// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SquareActor1.generated.h"

UENUM(BlueprintType)
enum class EPINGPONGTYPE : uint8
{
	ERIGHT_LEFT = 0,		//UMETA(DisplayName = "EMOVE RIGHT_LEFT"),
	EFORWERD_BACK =1,		//UMETA(DisplayName = "EMOVE FORWERD_BACK"),
	ETOP_DOWN = 2			//UMETA(DisplayName = "EMOVE TOP_DOWN")
};
//출처: https://wergia.tistory.com/150 [베르의 프로그래밍 노트:티스토리]

UCLASS()
class PROJECT_6_1_API ASquareActor1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquareActor1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
public:

	//UFUNCTION(BlueprintCallable )
	void SetDir(EPINGPONGTYPE type);
	
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GamePlay|Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "GamePlay|Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	float Speed = 250.f;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	float MoveDistanceLimmit = 350.f;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	bool bPlayStart = true;

	UPROPERTY(EditAnywhere, Category = "GamePlay|Properties")
	EPINGPONGTYPE MoveType = EPINGPONGTYPE::ERIGHT_LEFT;

	//UPROPERTY(VisibleAnywhere, Category = "GamePlay|Components")
	//UBoxComponent* BoxComponet;
private:
	FVector Dir = FVector::ForwardVector;
};
