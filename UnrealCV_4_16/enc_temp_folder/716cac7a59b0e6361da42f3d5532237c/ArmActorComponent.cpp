// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmActorComponent.h"
#include "EngineUtils.h"


// Sets default values for this component's properties
UArmActorComponent::UArmActorComponent() {
	// Set this component to be initialized when the game starts, and to be ticked
	// every frame.  You can turn these features off to improve performance if you
	// don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UArmActorComponent::BeginPlay() {
	Super::BeginPlay();

	AActor *joint1 = FindObject<AActor>(nullptr, TEXT("joint1"));

	UE_LOG(LogTemp, Warning, TEXT("Joint1 is %s"),
		joint1 ? TEXT("True") : TEXT("False"));
	// ...
	// GameObject mygo = GameObject.find("Arm2");
}

// Called every frame
void UArmActorComponent::TickComponent(
	float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	AActor *parentActor = this->GetOwner();

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	RunningTime += DeltaTime;

	//   FVector newLocation = parentActor->GetActorLocation();
	//   newLocation.Z += DeltaHeight * 20.0f;
	//   parentActor->SetActorLocation(newLocation);

	auto msg = GEngine == nullptr ? "true" : "false";
	FString DebugMsg =
		FString::Printf(TEXT("GEngine : %s"), *FString::SanitizeFloat(124.5f));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Green,
			TEXT("joint1"));

	// Find Actor by name (also works on UObjects)
	// auto parent = GetOwner()->GetRootComponent()->GetAttachParent();

	// EngineUtils.h

	auto ActorItr = TActorIterator<AStaticMeshActor>(GetWorld());

	const FString JointName = FString("Joint");

	// While not reached end (overloaded bool operator)
	// while (ActorItr)
	// {
	// 	print(ActorItr->GetName());

	// 	print(ActorItr->GetActorLocation().ToString());

	// 	//next actor
	// 	++ActorItr;
	// }
	FRotator newRotation;

	newRotation = Joints[0]->GetActorRotation();
	newRotation.Yaw += DeltaHeight * 20.0f;
	Joints[0]->SetActorRotation(newRotation);

	newRotation = Joints[1]->GetActorRotation();
	newRotation.Roll += DeltaHeight * 20.0f;
	Joints[1]->SetActorRotation(newRotation);

	newRotation = Joints[3]->GetActorRotation();
	newRotation.Roll += DeltaHeight * 50.0f;
	Joints[3]->SetActorRotation(newRotation);
}
