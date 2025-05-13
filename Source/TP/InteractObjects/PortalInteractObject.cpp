// (c) Developer Nikk All Rights Reserved.


#include "TP/InteractObjects/PortalInteractObject.h"
#include "Engine/TargetPoint.h"

void APortalInteractObject::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	if (PortalEndPoint)InteractActor->SetActorLocation(PortalEndPoint->GetActorLocation());
}
