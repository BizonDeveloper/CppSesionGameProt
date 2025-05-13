// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TP_HUD.generated.h"

class UTPP_GamplayWidget;

UCLASS()
class TP_API ATP_HUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTPP_GamplayWidget> GameplayWidgetClass;

	UPROPERTY()
	TObjectPtr<UTPP_GamplayWidget> GameplayWidget;
	
};
