// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Motor.h"
#include "RoboticActor.generated.h"

UCLASS()
class UNREALCV_PLAYGROUND_API ARoboticActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoboticActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Robot")
	TArray<UMotor*> Motors;

	UFUNCTION(BlueprintCallable, Category = "Robot")
	void InsertMotor(RotationDir dir, UStaticMeshComponent* model);
};
