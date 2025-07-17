// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "WaterTank.generated.h"

UCLASS()
class WATERSIMULATION_API AWaterTank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Instanced mesh component for balls
	UPROPERTY(VisibleAnywhere, Category = "Water Simulation")
	UInstancedStaticMeshComponent* BallInstances;

	// The mesh to use for the balls
	UPROPERTY(EditAnywhere, Category = "Water Simulation")
	UStaticMesh* BallMesh;

	//mesh for the tank
	UPROPERTY(VisibleAnywhere, Category = "Water Simulation")
	UStaticMeshComponent* TankMesh;

	UPROPERTY(EditAnywhere, Category = "Water Simulation")
	int numBalls = 0.0;

};
