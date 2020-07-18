// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeChatClient.h"
#include "EAddressType.h"

void UNodeChatClient::fInit(UNodeSocketAC* _vUNodeSocketAC)
{
	vUNodeSocketAC = _vUNodeSocketAC;
}

bool UNodeChatClient::fSendMsg(NMessage* msg)
{
	return false;
}

bool UNodeChatClient::fSendMsgToDefaultRoom(NMessage* msg)
{
	bool bOk = true;
	if (msg != nullptr)
	{
		msg->address_type = EAddressType::Room;
		msg->to = TEXT(default_room);
		bOk = fSendMsg(msg);
	}

	return bOk;

}
