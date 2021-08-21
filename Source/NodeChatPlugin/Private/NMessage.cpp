// Fill out your copyright notice in the Description page of Project Settings.

#include "NMessage.h"

NMessage::NMessage()
{
}

NMessage::~NMessage()
{
}

TSharedPtr<FJsonObject> NMessage::toJson()
{
    TSharedPtr<FJsonObject> resp = MakeShareable(new FJsonObject);

    resp->SetStringField("content", this->content);
    resp->SetStringField("to", this->to);
    resp->SetStringField("route", this->route);

    return resp;
}

FString NMessage::toFString()
{
    FString OutputString;
    TSharedRef<TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(this->toJson().ToSharedRef(), Writer);

    return OutputString;
}

NMessage *NMessage::fMakeMsgFromString(const FString &str)
{
    NMessage *resp = new NMessage;

    TSharedRef<TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(str);
    TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
    FJsonSerializer::Deserialize(JsonReader, request);

    request->TryGetStringField("content", resp->content);
    request->TryGetStringField("route", resp->route);
    request->TryGetStringField("from", resp->from);
    request->TryGetStringField("to", resp->to);

    return resp;
}
