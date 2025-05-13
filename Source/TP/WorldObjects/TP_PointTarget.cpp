// Fill out your copyright notice in the Description page of Project Settings.


#include "TP/WorldObjects/TP_PointTarget.h"


ATP_PointTarget::ATP_PointTarget()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
}


void ATP_PointTarget::BeginPlay()
{
	Super::BeginPlay();

	if (!RoomTag.IsNone())
	{
		Tags.Add(RoomTag);
	}
}


void ATP_PointTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

