// (c) Developer Nikk All Rights Reserved.


#include "TP/UI/UserWidget_Win_Lose.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"


void UUserWidget_Win_Lose::NativeConstruct()
{
	Super::NativeConstruct();

	if (TextBlock_WinLose)
	{
		TextBlock_WinLose->SetText(FText::FromString(bIsWin ? TEXT("YOU WIN") : TEXT("YOU LOSE")));
	}
	FTimerHandle TempHandle;
	GetWorld()->GetTimerManager().SetTimer(TempHandle, this, &UUserWidget_Win_Lose::RemoveSelf, 2.0f, false);
}

void UUserWidget_Win_Lose::RemoveSelf()
{
	RemoveFromParent();
}