// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterTank.h"

FVector Position;
float Velocity = 0.0f;
float Acceleration = -0.1f;

// Sets default values
AWaterTank::AWaterTank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	RootComponent = TankMesh;

	BallInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BallInstances"));
	BallInstances->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWaterTank::BeginPlay()
{
	Super::BeginPlay();


	if (BallMesh)
	{
		//debug text "here"

		
		Acceleration = -0.1f;
		BallInstances->SetStaticMesh(BallMesh);

		// Spawn one ball at the actor's center
		FTransform BallTransform;

		FVector ParentScale = TankMesh->GetComponentScale();
		FVector desiredScale = FVector(0.1f);
		BallTransform.SetScale3D(desiredScale / ParentScale );
		Position = FVector(0.0);
		BallTransform.SetLocation(Position);
		BallInstances->AddInstance(BallTransform);

		float BallWidth = BallMesh->GetBoundingBox().GetSize().X / 50.0f;

		// Spawn one ball at the actor's center
		BallTransform.SetLocation(GetActorRightVector() * BallWidth);
		BallInstances->AddInstance(BallTransform);

		BallTransform.SetLocation(-GetActorRightVector() * BallWidth);
		BallInstances->AddInstance(BallTransform);

		FVector MeshSize = TankMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		FVector MeshSize2 = BallMesh->GetBounds().GetBox().GetSize();
		FString HeightString = FString::Printf(TEXT("Tank Height: %.2f , %.2f"), MeshSize.Z / 2.0f, (MeshSize2.Z * (desiredScale.Z / ParentScale.Z) / 2.0f ));
		DrawDebugString(GetWorld(), GetActorLocation(), HeightString, nullptr, FColor::Red, 5.0f, true);
	}
	
}

// Called every frame
void AWaterTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform BallTransform;
	BallInstances->GetInstanceTransform(0, BallTransform, /*bWorldSpace=*/false);
	Velocity += Acceleration;
	Position.Z  += Velocity; // Move down by 1 unit
	if (abs(Position.Z) > 46.8f)
	{
		Position.Z -= Velocity;
		Velocity *= -0.8;

	}
		
	BallTransform.SetLocation(Position);

	BallInstances->UpdateInstanceTransform(0, BallTransform, /*bWorldSpace=*/false, /*bMarkRenderStateDirty=*/true, /*bTeleport=*/false);

}

