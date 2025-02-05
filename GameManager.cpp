// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Engine/World.h"
#include "SquareActor1.h"
#include "SquareActor2.h"

AGameManager* AGameManager::Instance = nullptr;
// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SpwanActor();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::SpwanActor()
{
	FVector LocationArr[3] = { FVector(-800.f,0.f, 100.f),FVector(-1500.f,0.f, 100.f), FVector(-2000.f,0.f, 100.f) };
	FRotator RotationArr[3] = { FRotator(0.f,0.f,0.f),FRotator(0.f,0.f,0.f),FRotator(0.f,0.f,0.f) };

	for (int i = 0; i < 3;++i)
	{
		ASquareActor1* SqActor = GetWorld()->SpawnActor <ASquareActor1>(ASquareActor1::StaticClass(), LocationArr[i], RotationArr[i]);
		//EPINGPONGTYPE MoveType = (EPINGPONGTYPE)FMath::RandRange(0, 2);
		SqActor->SetDir((EPINGPONGTYPE)i);
		SqActorMoveArr.Add(SqActor);
	}

	

	FVector LocationArr2[9] =
	{ 
		FVector(-2900.f, 0.f, 100.f),
		FVector(-3600.f, 0.f, 100.f),
		FVector(-4300.f, 0.f, 100.f),
		FVector(-5000.f, 0.f, 100.f),
		FVector(-5700.f, 0.f, 100.f),
		FVector(-6400.f, 0.f, 100.f),
		FVector(-7100.f, 0.f, 100.f),
		FVector(-7900.f, 0.f, 100.f),
		FVector(-8600.f, 0.f, 100.f)
	};

	EROTATIONTYPE rotActorIdx = EROTATIONTYPE::E_RIGHT;
	for (int i = 0; i < 9;++i)
	{
		ASquareActor2* SqActor2 = GetWorld()->SpawnActor<ASquareActor2>(ASquareActor2::StaticClass(), LocationArr2[i], FRotator::ZeroRotator);
		SqActor2->SetDir(rotActorIdx);
		SqActorRotArr.Add(SqActor2);
		rotActorIdx = rotActorIdx == EROTATIONTYPE::E_RIGHT ? EROTATIONTYPE::E_LEFT : EROTATIONTYPE::E_RIGHT;
	}
}

