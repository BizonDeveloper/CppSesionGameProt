// (c) Developer Nikk All Rights Reserved.

#include "TP/Core/TPGameState.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "TP/InteractObjects/ItemInteractObject.h"
#include "TP/UI/UserWidget_Win_Lose.h"
#include "TP/WorldObjects/TP_PointTarget.h"

ATPGameState::ATPGameState()
{
	bReplicates = true;
	SessionTime = 30; 
}

void ATPGameState::BeginPlay()
{
	Super::BeginPlay();

	check(WinLoseWidgetClass);
	
	if (HasAuthority())
	{
	
		MaxItemCount = FMath::RandRange(3, 5);
		
		const int32 EnumIndex = FMath::RandRange(0, static_cast<int32>(EMyItemTypes::MAX) - 1);
		EItemTypes = static_cast<EMyItemTypes>(EnumIndex);
		
		GetWorldTimerManager().SetTimer(TimerHandle_SessionTick, this, &ATPGameState::TickSessionTimer, 1.0f, true);

		SpawnItemsByRoomTag("1", RoomCubesCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cube);
		SpawnItemsByRoomTag("1", RoomCylindersCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cylinder);
		SpawnItemsByRoomTag("1", RoomSpheresCount, AItemInteractObject::StaticClass(), EMyItemTypes::Sphere);

		SpawnItemsByRoomTag("2", RoomCubesCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cube);
		SpawnItemsByRoomTag("2", RoomCylindersCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cylinder);
		SpawnItemsByRoomTag("2", RoomSpheresCount, AItemInteractObject::StaticClass(), EMyItemTypes::Sphere);

		SpawnItemsByRoomTag("3", RoomCubesCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cube);
		SpawnItemsByRoomTag("3", RoomCylindersCount, AItemInteractObject::StaticClass(), EMyItemTypes::Cylinder);
		SpawnItemsByRoomTag("3", RoomSpheresCount, AItemInteractObject::StaticClass(), EMyItemTypes::Sphere);
	}
}

void ATPGameState::SpawnItemsByRoomTag(FName RoomTag, int32 ItemsPerRoom,
	TSubclassOf<class AItemInteractObject> ItemClass, EMyItemTypes InItemType)
{
	if (!HasAuthority() || !ItemClass) return;
	
	TArray<AActor*> AllPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATP_PointTarget::StaticClass(), AllPoints);
	
	TArray<AActor*> FilteredPoints;
	for (AActor* Actor : AllPoints)
	{
		ATP_PointTarget* Point = Cast<ATP_PointTarget>(Actor);
		if (Point && !Point->bHasSpawnedItem && Point->Tags.Contains(RoomTag))
		{
			FilteredPoints.Add(Point);
		}
	}
	
	FilteredPoints.Sort([](const AActor& A, const AActor& B) {
		return FMath::RandBool();
	});
	
	for (int32 i = 0; i < FMath::Min(ItemsPerRoom, FilteredPoints.Num()); ++i)
	{
		ATP_PointTarget* Point = Cast<ATP_PointTarget>(FilteredPoints[i]);
		if (!Point) continue;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AItemInteractObject* SpawnedItem = GetWorld()->SpawnActor<AItemInteractObject>(
			ItemClass,
			Point->GetActorLocation(),
			Point->GetActorRotation(),
			SpawnParams
		);

		if (SpawnedItem)
		{
			SpawnedItem->SetItemBody(InItemType);
			Point->bHasSpawnedItem = true;
		}
	}
}


void ATPGameState::TickSessionTimer()
{
	if (SessionTime > 0)
	{
		SessionTime--;

		if ( CurrentItemCount >= MaxItemCount)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_SessionTick);
			Multicast_ShowEndGameWidget(true);
			GetWorldTimerManager().SetTimer(TimerHandle_RestartLevel, this, &ATPGameState::RestartLevel, 2.0f, false);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_SessionTick);
		Multicast_ShowEndGameWidget(false);
		GetWorldTimerManager().SetTimer(TimerHandle_RestartLevel, this, &ATPGameState::RestartLevel, 2.0f, false);
	}
}

void ATPGameState::RestartLevel()
{
	if (HasAuthority())
	{
		GetWorld()->ServerTravel(TEXT("/Game/ThirdPerson/Maps/ThirdPersonMap?listen"));
	}
}

void ATPGameState::OnRep_SessionTime()
{
	OnSessionTimeUpdated.Broadcast(SessionTime);
}

void ATPGameState::OnRep_EMyItemTypes()
{
	OnEItemTypesUpdatedSignature.Broadcast(EItemTypes);
}

void ATPGameState::OnRep_CurrentItemCount()
{
	OnCurrentItemCountUpdatedSignature.Broadcast(CurrentItemCount);
}

void ATPGameState::OnRep_MaxItemCount()
{
	OnMaxItemCountUpdatedSignature.Broadcast(MaxItemCount);
}

void ATPGameState::Multicast_ShowEndGameWidget_Implementation(bool bIsWin)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && PC->IsLocalController())
	{
		if (WinLoseWidgetClass)
		{
			UUserWidget_Win_Lose* WinLoseWidget = CreateWidget<UUserWidget_Win_Lose>(PC, WinLoseWidgetClass);
			if (WinLoseWidget)
			{
				WinLoseWidget->bIsWin = bIsWin;
				WinLoseWidget->AddToViewport();
			}
		}
	}
}

void ATPGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPGameState, SessionTime);
	DOREPLIFETIME(ATPGameState, EItemTypes);
	DOREPLIFETIME(ATPGameState, CurrentItemCount);
	DOREPLIFETIME(ATPGameState, MaxItemCount);
}
