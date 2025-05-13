// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TP/InteractObjects/InteractObject.h"
#include "TP/Core/MyCustomeContainer.h"
#include "ItemInteractObject.generated.h"

class ATPGameState;

UCLASS()
class TP_API AItemInteractObject : public AInteractObject
{
	GENERATED_BODY()

public:

	AItemInteractObject();

	void SetItemBody(EMyItemTypes InEMyItemTypes);
	void InitBody();

	UPROPERTY(EditAnywhere, Category="TP")
	EMyItemTypes CurrentItemType = EMyItemTypes::Cube;

	protected:

	virtual void BeginPlay() override;
	virtual void Interact(AActor* InteractActor) override;
	
	UPROPERTY()
	TSoftObjectPtr<UStaticMesh> CubeMesh;

	UPROPERTY()
	TSoftObjectPtr<UStaticMesh> SphereMesh;

	UPROPERTY()
	TSoftObjectPtr<UStaticMesh> CylinderMesh;

	UPROPERTY()
	TObjectPtr<ATPGameState> TPGameState;
};
