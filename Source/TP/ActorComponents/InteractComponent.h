// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TP_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UInteractComponent();
	void Interact();

protected:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractActor = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	float TraceDistance = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	float TraceRadius = 20.f;
	
	void PerformTrace();
	
};
