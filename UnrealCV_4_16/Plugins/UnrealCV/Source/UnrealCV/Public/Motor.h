// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Motor.generated.h"

UENUM()
enum RotationDir { Roll, Pitch, Yaw }; // { x, y, z } {Roll, Pitch, Yaw}
/**
 *
 */
UCLASS()
class UNREALCV_API UMotor : public UObject
{
	GENERATED_BODY()

public:
	UMotor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ModelComponent;

	UFUNCTION(BlueprintCallable, Category="Robot")
	void Init(RotationDir dir, UStaticMeshComponent* model);

	UFUNCTION(BlueprintCallable, Category = "Robot")
	virtual void Update(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Robot")
	void SetTargetDegrees(float degree, float speed)
	{
		_targetDegrees = degree;
		_speed = speed;

		_targetRotator = GetTargetRotator();
	}

private:
	FRotator GetTargetRotator();
	float GetCurrentDegrees();

	RotationDir _rotationDir;
	
	float _targetDegrees;
	FRotator _targetRotator;

	float _speed;


	////TODO: Simulate Lego Ev3
	//void On(int power);
	//void OnForSeconds(int power, double seconds, bool brackAtEnd = true);
	//void OnForDegree(int power, double degrees, bool brackAtEnd = true);
	//void OnForRotations(int power, double rotations, bool brackAtEnd = true);
	
};