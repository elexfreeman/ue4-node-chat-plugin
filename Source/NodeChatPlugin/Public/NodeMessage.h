// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EAddressType.h"
#include "NodeMessage.generated.h"

/**
 * 
 */
UCLASS()
class NODECHATPLUGIN_API UNodeMessage : public UObject
{
	GENERATED_BODY()

public:

	/** 
	 * msg text or content
	 */
	FString content;

	/** 
	 * Type of resever Room or Private
	 */
	EAddressType address_type = EAddressType::Room;

	/** 
	 * resever of msg
	 */
	FString to;
	
};
