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

UMotor* ARoboticActor::FindMotor(FName modelName)
{
	UE_LOG(LogTemp, Warning, TEXT("--- %s 's Motors Count:%d"), *GetFName().ToString(), Motors.Num());

	return *Motors.FindByPredicate([&modelName](const UMotor* m) {
		return m->ModelComponent->GetFName().IsEqual(modelName);
	});
}

UMotor* ARoboticActor::FindMotorByIndex(int modelIndex)
{
	return nullptr;
}

void ARoboticActor::InsertMotor(RotationDir dir, UStaticMeshComponent* model)
{
	auto* m = NewObject<UMotor>();
	m->Init(dir, model);

	Motors.Add(m);

	UE_LOG(LogTemp, Warning, TEXT("--- %s 's Motors Count:%d"), *GetFName().ToString(), Motors.Num());
}

void ARoboticActor::Say()
{
	UE_LOG(LogTemp, Warning, TEXT("name:%s, Say hello"), *GetFName().ToString());
}