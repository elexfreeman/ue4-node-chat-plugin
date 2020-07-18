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
	resp->SetNumberField("address_type", this->address_type);

	return resp;
}

FString NMessage::toFString()
{
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(this->toJson().ToSharedRef(), Writer);

	return OutputString;
}

NMessage* NMessage::fMakeMsgFromString(const FString& str)
{
	NMessage* resp = new NMessage;

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(str);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	request->TryGetStringField("content", resp->content);
	request->TryGetNumberField("address_type", resp->address_type);
	request->TryGetStringField("from", resp->from);
	request->TryGetStringField("to", resp->to);

	return resp;
}
