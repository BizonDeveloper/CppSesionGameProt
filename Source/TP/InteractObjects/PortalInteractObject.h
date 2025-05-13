// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TP/InteractObjects/InteractObject.h"
#include "PortalInteractObject.generated.h"


class ATargetPoint;

UCLASS()
class TP_API APortalInteractObject : public AInteractObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = "true"),Category="TP")
	TObjectPtr<ATargetPoint> PortalEndPoint;
	
protected:
	
	virtual void Interact(AActor* InteractActor) override;
	
};
