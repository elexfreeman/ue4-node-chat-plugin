// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeChatClient.h"


void UNodeChatClient::BeginPlay()
{
	Super::BeginPlay();
}

void UNodeChatClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}


void UNodeChatClient::fInit(UNodeSocketAC* _vUNodeSocketAC)
{
	vUNodeSocketAC = _vUNodeSocketAC;
	vUNodeSocketAC->OnReceivedStr.AddDynamic(this, &UNodeChatClient::fOnReserveMsgCallback);
}

bool UNodeChatClient::fSendMsg(NMessage* msg)
{
	this->vUNodeSocketAC->EmitStr(msg->toFString());
	return true;
}

bool UNodeChatClient::fSendMsgToDefaultRoom(FString msg)
{
	bool bOk = true;

	NMessage* vMsg = new NMessage;

	vMsg->address_type = 2;
	vMsg->to = TEXT(default_room);
	vMsg->content = msg;
	bOk = fSendMsg(vMsg);

	delete vMsg;

	return bOk;

}

FString UNodeChatClient::fGetContentFromAMsg(int32 msgId)
{
	TSharedPtr<NMessage> msg = MakeShareable(NMessage::fMakeMsgFromString(aMessage[msgId]));
	return msg->content;
}

void UNodeChatClient::fOnReserveMsgCallback(const FString& msg)
{
	aMessage.Add(msg);
}
