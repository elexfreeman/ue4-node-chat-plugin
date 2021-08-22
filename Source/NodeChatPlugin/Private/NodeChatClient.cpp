// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeChatClient.h"

void UNodeChatClient::BeginPlay()
{
    Super::BeginPlay();
}

void UNodeChatClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

bool UNodeChatClient::fSendMsg(UNMessage *msg)
{
    this->aMessage.Add(msg->toFString());
    onSendChatMsg.Broadcast(msg->toFString());
    this->vNodeSocketAC->EmitStr(msg->toFString());
    return true;
}

bool UNodeChatClient::fSendMsgToDefaultRoom(FString msg)
{
    bool bOk = true;

    TSharedPtr<UNMessage> vMsg = MakeShareable(new UNMessage);

    vMsg->route = TEXT("msg_room");
    vMsg->to = TEXT(default_room);
    vMsg->content = msg;
    bOk = fSendMsg(vMsg.Get());

    return bOk;
}

FString UNodeChatClient::fGetContentFromAMsg(int32 msgId)
{
    TSharedPtr<UNMessage> msg = MakeShareable(UNMessage::fMakeMsgFromString(aMessage[msgId]));
    return msg->content;
}

FString UNodeChatClient::fGetContentFromMsg(const FString &sMsg)
{
    TSharedPtr<UNMessage> msg = MakeShareable(UNMessage::fMakeMsgFromString(sMsg));
    return msg->content;
}

FString UNodeChatClient::fGetUserNameFromMsg(const FString &sMsg)
{
    FString resp = TEXT("");
    TSharedPtr<UNMessage> msg = MakeShareable(UNMessage::fMakeMsgFromString(sMsg));

    for (int32 k = 0; k < this->aUserList.Num(); k++)
    {
        if(this->aUserList[k].id == msg->sender)
        {
            resp = this->aUserList[k].username;
        }
    }

    return resp;
}

void UNodeChatClient::fCallReserveMsg(const FString &sMsg)
{
    UE_LOG(LogTemp, Log, TEXT("Broadcast data >>>>> : %s"), *(sMsg));
    TSharedPtr<UNMessage> vMsg = MakeShareable(UNMessage::fMakeMsgFromString(sMsg));
    this->aMessage.Add(sMsg);

    if (vMsg->route == TEXT("user_list"))
    {
        this->fUpdateUserList(vMsg);
        this->onUpdateUserList.Broadcast();
    }

    if (vMsg->route == TEXT("msg_room"))
    {
        this->onReserveChatMsg.Broadcast(sMsg);
    }
}

bool UNodeChatClient::fInit(UNodeSocketAC *_vNodeSocketAC)
{
    this->vNodeSocketAC = _vNodeSocketAC;
    this->bIsInit = true;

    this->vNodeSocketAC->OnReceivedStr.AddDynamic(this, &UNodeChatClient::fCallReserveMsg);

    // getting user list
    TSharedPtr<UNMessage> vMsg = MakeShareable(new UNMessage);

    vMsg->route = TEXT("user_list");
    vMsg->to = TEXT(default_room);
    vMsg->content = TEXT("");
    fSendMsg(vMsg.Get());

    return true;
}

void UNodeChatClient::fUpdateUserList(TSharedPtr<UNMessage> vMsg)
{
    TSharedRef<TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(vMsg->content);
    TSharedPtr<FJsonObject> vData = MakeShareable(new FJsonObject);
    FJsonSerializer::Deserialize(JsonReader, vData);

    TArray<TSharedPtr<FJsonValue> > aUserJson = vData->GetArrayField("user_list");

    this->aUserList.Empty();
    for (int32 k = 0; k < aUserJson.Num(); k++)
    {
        TSharedRef<FUserListItem> vUser = MakeShared<FUserListItem>();

        TSharedPtr<FJsonValue> value = aUserJson[k];
        TSharedPtr<FJsonObject> json = value->AsObject();

        vUser->id = json->GetNumberField("id");
        vUser->username = json->GetStringField("username");
        vUser->token = json->GetStringField("username");
        UE_LOG(LogTemp, Log, TEXT("Update user data >>>>> : %s"), *(vUser->username));

        this->aUserList.Add(vUser.Get());
    }
}