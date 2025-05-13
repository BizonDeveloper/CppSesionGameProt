// (c) Developer Nikk All Rights Reserved.

#include "TP/InteractObjects/DoorInteractObject.h"

ADoorInteractObject::ADoorInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADoorInteractObject::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("HandleTimelineProgress"));
		DoorTimeline.AddInterpFloat(DoorCurve, TimelineProgress);

		FOnTimelineEvent TimelineFinished;
		TimelineFinished.BindUFunction(this, FName("HandleTimelineFinished"));
		DoorTimeline.SetTimelineFinishedFunc(TimelineFinished);
	}
}

void ADoorInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeline.TickTimeline(DeltaTime);
}

void ADoorInteractObject::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	if (DoorTimeline.IsPlaying()) return;
	
	bIsOpen = !bIsOpen;

	if (bIsOpen)
	{
		DoorTimeline.PlayFromStart();
	}
	else
	{
		DoorTimeline.ReverseFromEnd();
	}
	
}

void ADoorInteractObject::HandleTimelineProgress(float Value)
{
	const FRotator NewRotation = FRotator(0.f, Value * OpenAngle, 0.f);
	Body->SetRelativeRotation(NewRotation);
}

void ADoorInteractObject::HandleTimelineFinished()
{
	
}
