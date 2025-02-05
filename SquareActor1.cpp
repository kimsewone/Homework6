// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareActor1.h"
#include "Components/BoxComponent.h"

// Sets default values
ASquareActor1::ASquareActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(Root);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Floor_400x400.Floor_400x400"));
	if (MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshAsset.Succeeded"));
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
		StaticMeshComponent->SetRelativeLocation(FVector(-200.f, -200.f,0.f));

		//BoxComponet = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
		//BoxComponet->SetupAttachment(StaticMeshComponent);
		//FRotator Rotation(0.f, 0.f, 0.f);
		//FVector BoxPos(200.f, 200.f, -10.f);
		//FVector Scale(1.f, 1.f, 1.f);
		//FTransform BoxTransform(Rotation, BoxPos, Scale);
		//BoxComponet->SetRelativeTransform(BoxTransform);
		//BoxComponet->SetBoxExtent(FVector(200.f, 200.f, 10.f));
		//BoxComponet->SetCollisionProfileName("BlockAllDynamic");
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Material.Succeeded"));
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
	//MoveType = (EPINGPONGTYPE)FMath::RandRange(0, 2);
	//SetDir((EPINGPONGTYPE)FMath::RandRange(0, 2));
}

// Called when the game starts or when spawned
void ASquareActor1::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASquareActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bPlayStart)
		return;
	//UE_LOG(LogTemp, Warning, TEXT("CurPosX : %f"), FMath::Abs(Root->GetRelativeLocation().X));
	//UE_LOG(LogTemp, Warning, TEXT("CurPosY : %f"), FMath::Abs(Root->GetRelativeLocation().Y));
	StaticMeshComponent->AddLocalOffset(Dir * Speed * DeltaTime);//AddActorWorldOffset(Dir * Speed * DeltaTime);
	if (EPINGPONGTYPE::ERIGHT_LEFT == MoveType)
	{
		if (MoveDistanceLimmit <= FMath::Abs(StaticMeshComponent->GetRelativeLocation().Y))
			Dir *= -1.f;
	}
	else if (EPINGPONGTYPE::EFORWERD_BACK == MoveType)
	{
		if (MoveDistanceLimmit <= FMath::Abs(StaticMeshComponent->GetRelativeLocation().X))
			Dir *= -1.f;
	}
	else if (EPINGPONGTYPE::ETOP_DOWN == MoveType)
	{
		if (MoveDistanceLimmit <= FMath::Abs(StaticMeshComponent->GetRelativeLocation().Z))
			Dir *= -1.f;
	}
}
#if WITH_EDITOR
void ASquareActor1::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// 변경된 속성 이름 확인
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASquareActor1, MoveType))
	{
		//SetDir();
		if (EPINGPONGTYPE::ERIGHT_LEFT == MoveType)
			Dir = FVector::RightVector;
		else if (EPINGPONGTYPE::EFORWERD_BACK == MoveType)
			Dir = FVector::ForwardVector;
		else if (EPINGPONGTYPE::ETOP_DOWN == MoveType)
			Dir = FVector::UpVector;
	}
}
#endif

void ASquareActor1::SetDir(EPINGPONGTYPE type )
{
	MoveType = type;//EPINGPONGTYPE::EFORWERD_BACK;
	if (EPINGPONGTYPE::ERIGHT_LEFT == MoveType)
		Dir = FVector::RightVector;
	else if (EPINGPONGTYPE::EFORWERD_BACK == MoveType)
		Dir = FVector::ForwardVector;
	else if (EPINGPONGTYPE::ETOP_DOWN == MoveType)
		Dir = FVector::UpVector;

	UE_LOG(LogTemp, Warning, TEXT("MoveType :%d"),MoveType);
}

