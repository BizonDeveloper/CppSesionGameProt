// (c) Developer Nikk All Rights Reserved.


#include "TP/InteractObjects/ItemInteractObject.h"
#include "UObject/ConstructorHelpers.h"

AItemInteractObject::AItemInteractObject()
{
	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTableAsset(TEXT("/Game/DT_ItemData"));
	if (ItemTableAsset.Succeeded())
	{
		ItemTable = ItemTableAsset.Object;
	}
}

void AItemInteractObject::SetItemBody(EMyItemTypes InEMyItemTypes)
{
	CurrentItemType = InEMyItemTypes;
	InitBody();
}

void AItemInteractObject::BeginPlay()
{
	Super::BeginPlay();

	ensureAlwaysMsgf(ItemTable != nullptr, TEXT("ItemTable is null in %s"), *GetName());
	
	if (HasAuthority())
	{
		InitBody();
	}
}

void AItemInteractObject::InitBody()
{
	if (!ItemTable || !Body) return;

	FName RowName;
	
	switch (CurrentItemType)
	{
	case EMyItemTypes::Sphere:
		RowName = FName("1");
		break;
	case EMyItemTypes::Cylinder:
		RowName = FName("2");
		break;
	case EMyItemTypes::Cube:
		RowName = FName("3");
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Unknown item type"));
		return;
	}

	const FItemData* Row = ItemTable->FindRow<FItemData>(RowName, TEXT("InitBody"));
	if (Row && Row->Mesh)
	{
		Body->SetStaticMesh(Row->Mesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Row not found or Mesh is null for RowName: %s"), *RowName.ToString());
	}
}

void AItemInteractObject::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	if (HasAuthority())
	{
		OnItemInteractSignature.Broadcast(this);
	}
}
