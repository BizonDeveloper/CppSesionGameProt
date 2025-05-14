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

	FORCEINLINE bool GetbIsWin(){return bIsWin;}
	FORCEINLINE void SetbIsWin(bool InBool){ bIsWin = InBool;}

protected:
	
	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void RemoveSelf();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category="WinLose")
	bool bIsWin;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_WinLose;
};
