// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

/**
 * 
 */
class UNMessage
{
public:
	UNMessage();
	~UNMessage();

	/**
	 * msg text or content
	 */
	FString content = TEXT("");

	FString route = TEXT("");

	/**
	 * resever of msg
	 */
	FString to = TEXT("");

	/**
	 * sender msg
	 */
	FString from = TEXT("");

	/**
	 * sender user
	 */
	int32 sender = -1;

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

	/**
	 * Create new class from text message
	 * @param str FSting
	 * @return UNMessage*
	 */
	static UNMessage *fMakeMsgFromString(const FString &str);
};
