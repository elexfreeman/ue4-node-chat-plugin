// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAddressType.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


/**
 * 
 */
class NODECHATPLUGIN_API NMessage
{
public:
	NMessage();
	~NMessage();

	/**
	 * msg text or content
	 */
	FString content;

	/**
	 * Type of resever Room or Private
	 * 1 - Private
	 * 2 - Room;
	 */
	int32 address_type = 1;

	/**
	 * resever of msg
	 */
	FString to;

	/**
	 * convert class to json 
	 * @return json 
	 */
	TSharedPtr<FJsonObject> toJson();


	/**
	 * convert class to string
	 * @return FString
	 */
	FString toFString();
};
