// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define default_room "default_room"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NodeSocketAC.h"
#include "NMessage.h"
#include "NodeChatClient.generated.h"

/**
 * 
 */
UCLASS()
class NODECHATPLUGIN_API UNodeChatClient : public UObject
{
	GENERATED_BODY()

public:

	/** 
	 * socket conector
	 */
	UNodeSocketAC* vUNodeSocketAC;

	/*
	 * Init socket
	 */
	void fInit(UNodeSocketAC* _vUNodeSocketAC);

	/**
	 * Send msg to default room 
	 * @param msg 
	 * @return true 
	 * @return false 
	 */
	bool fSendMsg(NMessage* msg);


	bool fSendMsgToDefaultRoom(NMessage* msg);
	
};
