// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterTank.h"
#include <cmath>
#include <iostream>

FVector* Positions;
float* Velocities;
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
		float BallWidth = BallMesh->GetBoundingBox().GetSize().X / 50.0f;

		int numCols = std::ceil(std::sqrt(numBalls)); // Calculate number of columns based on the square root of numBalls
		int numRows = std::ceil(static_cast<double>(numBalls) / static_cast<double>(numCols));

		Positions = new FVector[numBalls];
		Velocities = new float[numBalls];

		BallInstances->SetStaticMesh(BallMesh);

		FTransform BallTransform;
		FVector ParentScale = TankMesh->GetComponentScale();
		FVector desiredScale = FVector(0.1f);
		BallTransform.SetScale3D(desiredScale / ParentScale);
		



		int b = 0;

		
		for (int j = (-numRows / 2); j < numRows - (numRows / 2); j++)
		{
			for (int i = (-numCols / 2); i < numCols - (numCols / 2); i++)
			{
				Positions[b] = (-GetActorRightVector() * i * BallWidth) + (GetActorUpVector() * j * BallWidth);
				Velocities[b] = 0.0;
				BallTransform.SetLocation(Positions[b]);
				BallInstances->AddInstance(BallTransform);
				b++;
				if (b == numBalls)
					break;
			}
			
		}

		Acceleration = -0.1f;
	}
	
}

// Called every frame
void AWaterTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform BallTransform;
	BallInstances->GetInstanceTransform(0, BallTransform, /*bWorldSpace=*/false);

	for (int i = 0; i < numBalls; i++)
	{
		Velocities[i] += Acceleration;
		Positions[i].Z += Velocities[i];
		if (abs(Positions[i].Z) > 46.8f)
		{
			Positions[i].Z -= Velocities[i];
			Velocities[i] *= -0.8; // multiply by -1 * decayFactor

		}
		BallTransform.SetLocation(Positions[i]);

		BallInstances->UpdateInstanceTransform(i, BallTransform, /*bWorldSpace=*/false, /*bMarkRenderStateDirty=*/true, /*bTeleport=*/false);
	}

		
	

}

