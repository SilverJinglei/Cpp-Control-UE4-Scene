// Fill out your copyright notice in the Description page of Project Settings.
#include "Motor.h"

void UMotor::Init(RotationDir dir, UStaticMeshComponent* model)
{
	_rotationDir = dir;
	ModelComponent = model;
}

UMotor::UMotor()
{

}


void UMotor::Update(float DeltaTime)
{
	if (ModelComponent->RelativeRotation.Equals(_targetRotator))
		return;

	auto newRotation = FMath::RInterpConstantTo(ModelComponent->RelativeRotation, _targetRotator, DeltaTime, _speed);

	// SetRelativeRotation has been detect rotator near equal
	ModelComponent->SetRelativeRotation(newRotation);
}

FRotator UMotor::GetTargetRotator()
{
	FRotator r = ModelComponent->RelativeRotation;
	
	switch (_rotationDir)
	{
	case Roll:
		return r.Add(r.Pitch, r.Yaw, _targetDegrees);
	case Pitch:
		return r.Add(_targetDegrees, r.Yaw, r.Roll);
	default:
	case Yaw:
		return r.Add(r.Pitch, _targetDegrees, r.Roll);
	}
}

float UMotor::GetCurrentDegrees()
{
	FRotator r = ModelComponent->RelativeRotation;

	switch (_rotationDir)
	{
	case Roll:
		return r.Roll;
	case Pitch:
		return r.Pitch;
	default:
	case Yaw:
		return r.Yaw;
	}
}
