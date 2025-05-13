// (c) Developer Nikk All Rights Reserved.


#include "TP/InteractObjects/InteractObject.h"


AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;
	
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(SceneRoot);
	Body->SetIsReplicated(true);
}

void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractObject::InteractEvent_Implementation(AActor* InteractActor)
{
}

void AInteractObject::Interact(AActor* InteractActor)
{
	InteractEvent(InteractActor);
}

