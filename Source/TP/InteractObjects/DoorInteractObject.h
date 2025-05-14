// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "TP/InteractObjects/InteractObject.h"
#include "DoorInteractObject.generated.h"


UCLASS()
class TP_API ADoorInteractObject : public AInteractObject
{
	GENERATED_BODY()
	
public:
	
	ADoorInteractObject();
	
protected:
	
	virtual void Interact(AActor* InteractActor) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditAnywhere)
	FTimeline DoorTimeline;

	UPROPERTY(EditAnywhere, Category = "Door")
	TObjectPtr<UCurveFloat> DoorCurve;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenAngle = 90.0f;

	UPROPERTY()
	bool bIsOpen = false;
	
	UFUNCTION()
	void HandleTimelineProgress(float Value);
	
	UFUNCTION()
	void HandleTimelineFinished();
};




