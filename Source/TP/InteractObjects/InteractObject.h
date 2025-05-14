// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP/Interfaces/InteractInterface.h"
#include "InteractObject.generated.h"

class USphereComponent;


UCLASS()
class TP_API AInteractObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	
	AInteractObject();

protected:
	
	virtual void BeginPlay() override;
	virtual void Interact(AActor* InteractActor) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TP")
	void InteractEvent(AActor* InteractActor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="TP")
	TObjectPtr<UStaticMeshComponent> Body;

};
