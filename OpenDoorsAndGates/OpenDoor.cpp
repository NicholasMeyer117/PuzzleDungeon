// Copyright Nicholas Meyer 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Containers/Array.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw=GetOwner()->GetActorRotation().Yaw;
	CurrentYaw=InitialYaw;
	TargetYaw+=InitialYaw;

	FindPressurePlate();
	FindAudioComponent();

	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PressurePlate && TotalMassOfActors()>=MassToOpen){
		
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();

	} else {
		if (DoorLastOpened<GetWorld()->GetTimeSeconds()-DoorCloseDelay)
			CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	bool DoorOpen=0;
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation=GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	
	if (!AudioComponent){return;}
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound=true;
		CloseDoorSound=false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation=GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	if (!AudioComponent){return;}
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound=true;
		OpenDoorSound=false;
	}

}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass=0.f;

	TArray<AActor*> OverLappingActors;
	if (PressurePlate)
		PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for(int i=0; i<OverLappingActors.Num(); i++){
		TotalMass+=OverLappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Audio Component"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate()
{
	if(!PressurePlate){
			UE_LOG(LogTemp, Warning, TEXT("%s has open door component but no pressure plate"),*GetOwner()->GetName());
		}
}