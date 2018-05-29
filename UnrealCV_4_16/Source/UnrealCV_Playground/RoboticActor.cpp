// Fill out your copyright notice in the Description page of Project Settings.
#include "RoboticActor.h"


// Sets default values
ARoboticActor::ARoboticActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoboticActor::BeginPlay()
{
	Super::BeginPlay();

	Motors.Empty();
}

// Called every frame
void ARoboticActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Motors.Num() == 0)
		return;

	for (UMotor* m: Motors)
	{
		m->Update(DeltaTime);
	}
}

void ARoboticActor::InsertMotor(RotationDir dir, UStaticMeshComponent* model)
{
	auto* m = NewObject<UMotor>();
	m->Init(dir, model);

	Motors.Add(m);
}

