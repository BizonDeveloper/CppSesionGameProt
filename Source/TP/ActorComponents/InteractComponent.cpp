// (c) Developer Nikk All Rights Reserved.

#include "TP/ActorComponents/InteractComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TP/Interfaces/InteractInterface.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetOwner()->GetLocalRole() == ROLE_Authority)PerformTrace();
}

void UInteractComponent::PerformTrace()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	if (!PC) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

	UCapsuleComponent* Capsule = OwnerCharacter->GetCapsuleComponent();
	if (!Capsule) return;

	FVector Start = Capsule->GetComponentLocation() + FVector(0.f, 0.f, Capsule->GetScaledCapsuleHalfHeight() * 0.9f);
	FVector End = Start + CameraRotation.Vector() * TraceDistance;

	FHitResult HitResult;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(OwnerCharacter);

	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Start,
		End,
		TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		IgnoredActors,
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	if (bHit && HitResult.GetActor() && HitResult.GetActor()->Implements<UInteractInterface>())
	{
		CurrentInteractActor = HitResult.GetActor();
	}
	else
	{
		CurrentInteractActor = nullptr;
	}
}

void UInteractComponent::Interact()
{
	if (IInteractInterface* Interface = Cast<IInteractInterface>(CurrentInteractActor))
	{
		Interface->Interact(GetOwner());
	}
}