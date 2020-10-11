// Copyright Nicholas Meyer 2020

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "OpenGate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UOpenGate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenGate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CheckFireplaceZ(float DeltaTime);
	void FindAudioComponent();

	UPROPERTY(EditAnywhere)
	AActor* fireplace = nullptr;

	bool GateClosed = true;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.9f;

	UPROPERTY(EditAnywhere)
	float TargetZ=90.f;

	float InitialZ;
	float CurrentZ;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
		
};
