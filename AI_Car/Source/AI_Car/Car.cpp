// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our mesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Our collision"));
	RootComponent = OurVisibleActor;

	BoxComponent->SetupAttachment(OurVisibleActor);

	OurVisibleActor->SetSimulatePhysics(true);
	CollisionParams.AddIgnoredActor(this);
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	FVector start = this->GetActorLocation();
	FRotator actorRot(this->GetActorRotation());
	actorRot.Yaw -= amplitude * 0.5;
	
	float rotation = amplitude / (StickNumber-1);
	for (int i = 0; i < StickNumber; ++i) {
		FVector end(actorRot.Vector() * 2000 + start);
		DrawDebugLine(GetWorld(), start, end, FColor::Green, false, DeltaTime+0.01, 0, 1);
		bool isHit = GetWorld()->LineTraceSingleByObjectType(OutHit, start, end, ECC_WorldStatic, CollisionParams);
		if (isHit && OutHit.bBlockingHit) {
			if (GEngine) {
				float distance = (OutHit.ImpactPoint - start).Size();
				//Input[i] = distance;
				GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Distance: %f"), distance));
				GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Actor: %s"), *OutHit.GetActor()->GetName()));
			}
		}
		else {
			//Input[i] = 2000;
		}
		actorRot.Yaw += rotation;
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
