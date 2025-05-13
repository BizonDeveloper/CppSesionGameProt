// (c) Developer Nikk All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMyItemTypes : uint8
{
	Sphere     UMETA(DisplayName = "Sphere"),
	Cylinder   UMETA(DisplayName = "Cylinder"),
	Cube       UMETA(DisplayName = "Cube"),
	MAX        UMETA(Hidden)
};
