// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeChatClient.h"

void UNodeChatClient::BeginPlay()
{
    Super::BeginPlay();
}

void UNodeChatClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

bool UNodeChatClient::fSendMsg(NMessage *msg)
{
    this->aMessage.Add(msg->toFString());
    onSendChatMsg.Broadcast(msg->toFString());
    this->vNodeSocketAC->EmitStr(msg->toFString());
    return true;
}

bool UNodeChatClient::fSendMsgToDefaultRoom(FString msg)
{
    bool bOk = true;

    TSharedPtr<NMessage> vMsg = MakeShareable(new NMessage);

    vMsg->route = TEXT("msg_room");
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

FString UNodeChatClient::fGetContentFromMsg(const FString &sMsg)
{
    TSharedPtr<NMessage> msg = MakeShareable(NMessage::fMakeMsgFromString(sMsg));
    return msg->content;
}


void UNodeChatClient::fCallReserveMsg(const FString &msg)
{
    UE_LOG(LogTemp, Log, TEXT("Broadcast data >>>>> : %s"), *(msg));
    this->aMessage.Add(msg);
    onReserveChatMsg.Broadcast(msg);
}

bool UNodeChatClient::fInit(UNodeSocketAC *_vNodeSocketAC)
{
    this->vNodeSocketAC = _vNodeSocketAC;
    this->bIsInit = true;

    this->vNodeSocketAC->OnReceivedStr.AddDynamic(this, &UNodeChatClient::fCallReserveMsg);
    return true;
}
