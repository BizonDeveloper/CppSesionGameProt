// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Win_Lose.generated.h"

class UTextBlock;

UCLASS()
class TP_API UUserWidget_Win_Lose : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WinLose")
	bool bIsWin;

protected:
	virtual void NativeConstruct() override;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_WinLose;

private:

	UFUNCTION()
	void RemoveSelf();
};
