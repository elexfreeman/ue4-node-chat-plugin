// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeChatClient.h"


void UNodeChatClient::BeginPlay()
{
	Super::BeginPlay();
}

void UNodeChatClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}


bool UNodeChatClient::fSendMsg(NMessage* msg)
{
	this->aMessage.Add(msg->toFString());
	onSendChatMsg.Broadcast(msg->toFString());
	return true;
}

bool UNodeChatClient::fSendMsgToDefaultRoom(FString msg)
{
	bool bOk = true;

	TSharedPtr<NMessage> vMsg = MakeShareable(new NMessage);

	vMsg->address_type = 2;
	vMsg->to = TEXT(default_room);
	vMsg->content = msg;
	bOk = fSendMsg(vMsg.Get());

	return bOk;

}

FString UNodeChatClient::fGetContentFromAMsg(int32 msgId)
{
	TSharedPtr<NMessage> msg = MakeShareable(NMessage::fMakeMsgFromString(aMessage[msgId]));
	return msg->content;
}

FString UNodeChatClient::fGetContentFromMsg(const FString& sMsg)
{
	TSharedPtr<NMessage> msg = MakeShareable(NMessage::fMakeMsgFromString(sMsg));
	return msg->content;
}

void UNodeChatClient::fOnReserveMsg(const FString& msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("MSMSS"));
	this->aMessage.Add(msg);
	onReserveChatMsg.Broadcast(msg);
}
