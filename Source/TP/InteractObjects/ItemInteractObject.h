// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TP/InteractObjects/InteractObject.h"
#include "TP/Core/MyCustomeContainer.h"
#include "ItemInteractObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInteractSignature, AItemInteractObject*, NewEItemTypes);

UCLASS()
class TP_API AItemInteractObject : public AInteractObject
{
	GENERATED_BODY()

public:

	AItemInteractObject();
	FOnItemInteractSignature OnItemInteractSignature;
	
	UFUNCTION()
	void SetItemBody(EMyItemTypes InEMyItemTypes);

	FORCEINLINE EMyItemTypes GetEMyItemType() {return CurrentItemType;}

protected:

	virtual void BeginPlay() override;
	virtual void Interact(AActor* InteractActor) override;

private:
	
	UPROPERTY(EditAnywhere, Category="TP")
	EMyItemTypes CurrentItemType = EMyItemTypes::Cube;

	UPROPERTY(EditAnywhere, Category="TP")
	TObjectPtr<UDataTable> ItemTable;

	UFUNCTION(BlueprintCallable, Category="TP")
	void InitBody();
	
};
