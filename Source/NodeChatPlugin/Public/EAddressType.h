#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"


UENUM(BlueprintType)
enum class EAddressType : uint8
{
	Private = 1 UMETA(DisplayName = "PRIVATE", ToolTip = "PRIVATE"),
	Room = 2 UMETA(DisplayName = "Room", ToolTip = "Room"),
};
