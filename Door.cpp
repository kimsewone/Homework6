// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "SpartaCharacter.h"
#include "TimerManager.h"
// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Door.SM_Door"));
	if (MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshAsset.Succeeded"));
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
		StaticMeshComponent->SetRelativeLocation( FVector( 0.f, 0.f, 0.f ) );
		StaticMeshComponent->SetRelativeScale3D( FVector( 3.f, 3.f, 3.f ) );
		//StaticMeshComponent->SetupAttachment(RootComponent);
	}
	RootComponent = StaticMeshComponent;
	Trigger = CreateDefaultSubobject< UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(50.f, 50.f, 100.f));  // 박스 크기 설정
	Trigger->SetCollisionProfileName(TEXT("Trigger"));  // 오버랩이 감지되도록 설정

	Trigger->SetupAttachment(RootComponent);

	OpenRotation = FRotator(0.f, -130.f, 0.f);   // 90도 회전
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
}
void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (bOpenDoor)
		return;

	auto Character = Cast< ASpartaCharacter>(OtherActor);
	if (Character != nullptr )
	{
		bOpenDoor = true;

		GetWorldTimerManager().SetTimer(OpenDoorTimerHandle, this, &ADoor::OpenDoor, 0.01f, true);
		UE_LOG(LogTemp, Warning, TEXT("Door Overlapped with: %s"), *OtherActor->GetName());
	}
}
// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor()
{
	TimeElapsed += 0.01f;

	float Alpha = FMath::Clamp(TimeElapsed / OpenTime, 0.0f, 1.0f); // 0~1 보간 비율
	FRotator NewRotation = FMath::Lerp(FRotator::ZeroRotator, OpenRotation, Alpha);
	StaticMeshComponent->SetRelativeRotation(NewRotation);

	if (Alpha >= 1.0f)
		GetWorldTimerManager().ClearTimer(OpenDoorTimerHandle); // 🚀 타이머 정지
}

