// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TP/Core/MyCustomeContainer.h"
#include "TPGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionTimeUpdatedSignature, int32, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEItemTypesUpdatedSignature, EMyItemTypes, NewEItemTypes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentItemCountUpdatedSignature, int32, NewCurrentItemCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxItemCountUpdatedSignature, int32, NewMaxItemCount);

class AItemInteractObject;

UCLASS()
class TP_API ATPGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	ATPGameState();
	
	FOnSessionTimeUpdatedSignature OnSessionTimeUpdated;
	FOnEItemTypesUpdatedSignature OnEItemTypesUpdatedSignature;
	FOnCurrentItemCountUpdatedSignature OnCurrentItemCountUpdatedSignature;
	FOnMaxItemCountUpdatedSignature OnMaxItemCountUpdatedSignature;
	
	UFUNCTION(BlueprintCallable, Category = "TP")
	int32 GetSessionTime() const { return SessionTime; }
	
	FORCEINLINE void IcrementCurrentItemCount() { CurrentItemCount++;}
	FORCEINLINE EMyItemTypes GetCurrentTargetItemType() { return EItemTypes;}

protected:
	
	virtual void BeginPlay() override;

private:

	void SpawnItemsForAllRooms();

	UFUNCTION(BlueprintCallable, Category = "TP|Spawning")
	void SpawnItemsByRoomTag(FName RoomTag, int32 ItemsPerRoom, TSubclassOf<class AItemInteractObject> ItemClass, EMyItemTypes InItemType);

	UPROPERTY(EditDefaultsOnly, Category="TP")
	TSubclassOf<UUserWidget> WinLoseWidgetClass;

	UPROPERTY(ReplicatedUsing = OnRep_SessionTime,meta = (AllowPrivateAccess = true), BlueprintReadOnly, Category = "TP")
	int32 SessionTime;

	UPROPERTY(ReplicatedUsing = OnRep_EMyItemTypes,meta = (AllowPrivateAccess = true), BlueprintReadOnly, Category = "TP")
	EMyItemTypes EItemTypes = EMyItemTypes::Cube;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentItemCount,meta = (AllowPrivateAccess = true), BlueprintReadOnly, Category = "TP")
	uint8 CurrentItemCount = 0;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxItemCount,meta = (AllowPrivateAccess = true), BlueprintReadOnly, Category = "TP")
	uint8 MaxItemCount = 3;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ShowEndGameWidget(bool bIsWin);

	FTimerHandle TimerHandle_SessionTick;
	FTimerHandle TimerHandle_RestartLevel;
	FTimerHandle TimerHandle_BindItems;

	UFUNCTION()
	void OnRep_SessionTime();

	UFUNCTION()
	void OnRep_EMyItemTypes();

	UFUNCTION()
	void OnRep_CurrentItemCount();

	UFUNCTION()
	void OnRep_MaxItemCount();

	UFUNCTION()
	void TickSessionTimer();

	UFUNCTION()
	void RestartLevel();

	UFUNCTION()
	void BindItemDelegates();

	UFUNCTION()
	void ItemInteract(AItemInteractObject* InItemInteractObject);

	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category = "TP")
	uint8 RoomCubesCount = 2;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category = "TP")
	uint8 RoomSpheresCount= 2;

	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category = "TP")
	uint8 RoomCylindersCount= 2;
};
