// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_PointTarget.generated.h"

UCLASS()
class TP_API ATP_PointTarget : public AActor
{
	GENERATED_BODY()
	
public:	

	ATP_PointTarget();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TP|Spawn")
	bool bHasSpawnedItem = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TP|Spawn")
	FName RoomTag;

};
