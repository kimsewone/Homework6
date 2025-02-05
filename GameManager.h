// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameManager.generated.h"

class ASquareActor1;
class ASquareActor2;
UCLASS()
class PROJECT_6_1_API AGameManager : public AActor
{
	GENERATED_BODY()
	
private:
	static AGameManager* Instance;
public:	
	static AGameManager* GetInstance(UWorld* world)
	{
		if (NULL == Instance)
			Instance = world->SpawnActor<AGameManager>();
		return Instance;
	}
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpwanActor();

public:
	TArray<ASquareActor1*> SqActorMoveArr;
	TArray<ASquareActor2*> SqActorRotArr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GamePlay|Components")
	USceneComponent* Root;
};
