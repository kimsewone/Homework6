// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareActor2.h"

// Sets default values
ASquareActor2::ASquareActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(Root);

	Radius = 350.f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshAsset.Succeeded"));
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
		StaticMeshComponent->SetRelativeLocation(FVector(-200.f- Radius, -200.f, 0.f));
		StaticMeshComponent->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Material.Succeeded"));
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
	
}

// Called when the game starts or when spawned
void ASquareActor2::BeginPlay()
{
	Super::BeginPlay();
	SetDir((EROTATIONTYPE)FMath::RandRange(0, 1));
}

// Called every frame
void ASquareActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bPlayStart)
		return;

	AddActorWorldRotation( FRotator( 0.f, Dir, 0.f ) * DeltaTime*Speed ) ;
}
void ASquareActor2::SetRadius(float _radius)
{
	Radius = _radius;
	StaticMeshComponent->SetRelativeLocation(FVector(-200.f - Radius, -200.f, 0.f));
}
void ASquareActor2::SetDir(EROTATIONTYPE type)
{
	RotationType = type;
	if (EROTATIONTYPE::E_RIGHT == RotationType)
		Dir = 1.f;
	else if (EROTATIONTYPE::E_LEFT == RotationType)
		Dir = -1.f;
}

#if WITH_EDITOR
void ASquareActor2::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// 변경된 속성 이름 확인
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASquareActor2, Radius))
	{
		StaticMeshComponent->SetRelativeLocation(FVector(-200.f - Radius, -200.f, 0.f));
	}

	else if (PropertyName == GET_MEMBER_NAME_CHECKED(ASquareActor2, RotationType))
	{
		if (EROTATIONTYPE::E_RIGHT == RotationType)
			Dir = 1.f;
		else if (EROTATIONTYPE::E_LEFT == RotationType)
			Dir = -1.f;
	}
}
#endif

