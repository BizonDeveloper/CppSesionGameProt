// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP/Core/MyCustomeContainer.h"
#include "TPP_GamplayWidget.generated.h"

class UTextBlock;

UCLASS()
class TP_API UTPP_GamplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_CurrentValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_MaxValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_SessionTime;

	UFUNCTION()
	void UpdateSessionTime(int32 NewTime);

	UFUNCTION()
	void UpdateItemType(EMyItemTypes NewType);

	UFUNCTION()
	void UpdateCurrentCount(int32 Current);

	UFUNCTION()
	void UpdateMaxCount(int32 Max);
	
};
