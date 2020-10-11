// Copyright Nicholas Meyer 2020


#include "LightFire.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/EngineTypes.h"
#include "Math/Vector.h"

#define OUT

// Sets default values for this component's properties
ULightFire::ULightFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightFire::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComponent();
	HideFire();
}


// Called every frame
void ULightFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(FireLit==false)
		CheckIfLit();
}

void ULightFire::HideFire()
{
	InitialTransform=GetOwner()->GetTransform();
	InitialLocation=InitialTransform.GetLocation();
	InitialLocation.Z+=-900.f;
	GetOwner()->SetActorLocation(InitialLocation);
}

void ULightFire::CheckIfLit()
{
	if (AddMassOfActors()==30.f)
	{
		FireLit=true;
		AudioComponent->Play();
		InitialLocation.Z+=900.f;
		GetOwner()->SetActorLocation(InitialLocation);
	}

}

void ULightFire::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Audio Component"), *GetOwner()->GetName());
	}
}

float ULightFire::AddMassOfActors()
{
	TArray<AActor*> PressurePlate2Actor;
	TArray<AActor*> PressurePlate1Actor;
	TArray<AActor*> PressurePlate3Actor;

	PressurePlate1->GetOverlappingActors(OUT PressurePlate1Actor);
	PressurePlate2->GetOverlappingActors(OUT PressurePlate2Actor);
	PressurePlate3->GetOverlappingActors(OUT PressurePlate3Actor);
	
	if (PressurePlate1&&PressurePlate2&&PressurePlate3&&PressurePlate1Actor.Num()>0&&PressurePlate2Actor.Num()>0&&PressurePlate3Actor.Num()>0)
	{

		//UE_LOG(LogTemp, Error, TEXT("Actors: %d"),PressurePlate2Actor.Num());
			float Mass1=PressurePlate1Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			float Mass2=PressurePlate2Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			float Mass3=PressurePlate3Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			
			UE_LOG(LogTemp, Warning, TEXT("Mass1: (%f)"),PressurePlate1Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass());
			UE_LOG(LogTemp, Warning, TEXT("Mass2: (%f)"),PressurePlate2Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass());
			UE_LOG(LogTemp, Warning, TEXT("Mass3: (%f)"),PressurePlate3Actor[0]->FindComponentByClass<UPrimitiveComponent>()->GetMass());
			return Mass1+Mass2+Mass3;



	} else {
		//UE_LOG(LogTemp, Error, TEXT("No Pressure Plate 2"));
	}


	return 0.f;
}

