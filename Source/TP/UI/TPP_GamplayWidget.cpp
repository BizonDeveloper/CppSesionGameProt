// (c) Developer Nikk All Rights Reserved.


#include "TP/UI/TPP_GamplayWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TP/Core/TPGameState.h"

void UTPP_GamplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ATPGameState* GameState = Cast<ATPGameState>(UGameplayStatics::GetGameState(this)))
	{
		GameState->OnSessionTimeUpdated.AddDynamic(this, &UTPP_GamplayWidget::UpdateSessionTime);
		GameState->OnEItemTypesUpdatedSignature.AddDynamic(this, &UTPP_GamplayWidget::UpdateItemType);
		GameState->OnCurrentItemCountUpdatedSignature.AddDynamic(this, &UTPP_GamplayWidget::UpdateCurrentCount);
		GameState->OnMaxItemCountUpdatedSignature.AddDynamic(this, &UTPP_GamplayWidget::UpdateMaxCount);
		UpdateSessionTime(GameState->GetSessionTime());
	}
}

void UTPP_GamplayWidget::UpdateSessionTime(int32 NewTime)
{
	if (TextBlock_SessionTime)
	{
		int32 Minutes = NewTime / 60;
		int32 Seconds = NewTime % 60;
		FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

		TextBlock_SessionTime->SetText(FText::FromString(TimeString));
	}
}

void UTPP_GamplayWidget::UpdateItemType(EMyItemTypes NewType)
{
	if (TextBlock_ItemName)
	{
		FString TypeName;
		switch (NewType)
		{
		case EMyItemTypes::Sphere:   TypeName = TEXT("Sphere"); break;
		case EMyItemTypes::Cylinder: TypeName = TEXT("Cylinder"); break;
		case EMyItemTypes::Cube:     TypeName = TEXT("Cube"); break;
		default:                   TypeName = TEXT("Unknown"); break;
		}
		TextBlock_ItemName->SetText(FText::FromString(TypeName));
	}
}

void UTPP_GamplayWidget::UpdateCurrentCount(int32 Current)
{
	if (TextBlock_CurrentValue)
	{
		TextBlock_CurrentValue->SetText(FText::AsNumber(Current));
	}
}

void UTPP_GamplayWidget::UpdateMaxCount(int32 Max)
{
	if (TextBlock_MaxValue)
	{
		TextBlock_MaxValue->SetText(FText::AsNumber(Max));
	}
}