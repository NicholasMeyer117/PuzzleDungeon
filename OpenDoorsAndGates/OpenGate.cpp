// Copyright Nicholas Meyer 2020


#include "OpenGate.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UOpenGate::UOpenGate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenGate::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComponent();
	InitialZ=GetOwner()->GetTransform().GetLocation().Z;
	CurrentZ=InitialZ;
	TargetZ+=InitialZ;

	// ...
	
}


// Called every frame
void UOpenGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (GateClosed==true)
		CheckFireplaceZ(DeltaTime);

}

void UOpenGate::CheckFireplaceZ(float DeltaTime){

	if (fireplace && fireplace->GetTransform().GetLocation().Z>0.f)
	{
		CurrentZ = FMath::FInterpTo(CurrentZ, TargetZ, DeltaTime, DoorOpenSpeed);
		FVector DoorLocation=GetOwner()->GetTransform().GetLocation();
		DoorLocation.Z=CurrentZ;
		GetOwner()->SetActorLocation(DoorLocation);

		if(AudioComponent&&GateClosed==true)
		{
			AudioComponent->Play();
		}

		UE_LOG(LogTemp, Error, TEXT("Door will open"));
		GateClosed=false;
	}

}

void UOpenGate::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Audio Component"), *GetOwner()->GetName());
	}
}