// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	FString route; 

	/**
	 * resever of msg
	 */
	FString to;


	/**
	 * sender msg
	 */
	FString from;

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
	 * @return NMessage*
	 */
	static NMessage* fMakeMsgFromString(const FString& str);
};
