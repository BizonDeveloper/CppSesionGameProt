// (c) Developer Nikk All Rights Reserved.


#include "TP/InteractObjects/ItemInteractObject.h"
#include "TP/Core/TPGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AItemInteractObject::AItemInteractObject()
{

	bReplicates = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Game/ThirdPerson/Maps/_GENERATED/user/SM_BoxItem"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/ThirdPerson/Maps/_GENERATED/user/SM_Sphere_Item"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/ThirdPerson/Maps/_GENERATED/user/SM_Cilinder_Item"));

	if (CubeAsset.Succeeded())
	{
		CubeMesh = CubeAsset.Object;
	}
	if (SphereAsset.Succeeded())
	{
		SphereMesh = SphereAsset.Object;
	}
	if (CylinderAsset.Succeeded())
	{
		CylinderMesh = CylinderAsset.Object;
	}
}

void AItemInteractObject::SetItemBody(EMyItemTypes InEMyItemTypes)
{
	CurrentItemType = InEMyItemTypes;
	InitBody();

}

void AItemInteractObject::InitBody()
{
	if (Body)
	{
		switch (CurrentItemType)
		{
		case EMyItemTypes::Cube:
			if (CubeMesh.IsValid()) Body->SetStaticMesh(CubeMesh.Get());
			break;
		case EMyItemTypes::Sphere:
			if (SphereMesh.IsValid()) Body->SetStaticMesh(SphereMesh.Get());
			break;
		case EMyItemTypes::Cylinder:
			if (CylinderMesh.IsValid()) Body->SetStaticMesh(CylinderMesh.Get());
			break;
		default:
			break;
		}
	}
}

void AItemInteractObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		TPGameState = Cast<ATPGameState>(UGameplayStatics::GetGameState(this));
	
		InitBody();
	}

}

void AItemInteractObject::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	if (!TPGameState) return;
	
	if (CurrentItemType == TPGameState->GetCurrentTargetItemType())
	{
		TPGameState->IcrementCurrentItemCount();
		Destroy();
	}
}
