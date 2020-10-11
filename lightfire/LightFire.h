// Copyright Nicholas Meyer 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "LightFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API ULightFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HideFire();
	float AddMassOfActors();
	void CheckIfLit();
	void FindAudioComponent();

	bool FireLit=false;
	float InitialZ;
	FVector InitialLocation;
	FTransform InitialTransform;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate1 = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate3 = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

		
};
