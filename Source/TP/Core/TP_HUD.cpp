// (c) Developer Nikk All Rights Reserved.


#include "TP/Core/TP_HUD.h"
#include "TP/UI/TPP_GamplayWidget.h"

void ATP_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UTPP_GamplayWidget>(GetWorld(), GameplayWidgetClass);
		if (GameplayWidget)
		{
			GameplayWidget->AddToViewport();
		}
	}
}