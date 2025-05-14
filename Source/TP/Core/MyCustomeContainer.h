// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyCustomeContainer.generated.h"

UENUM(BlueprintType)
enum class EMyItemTypes : uint8
{
	Sphere     UMETA(DisplayName = "Sphere"),
	Cylinder   UMETA(DisplayName = "Cylinder"),
	Cube       UMETA(DisplayName = "Cube"),
	MAX        UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;
	
};
