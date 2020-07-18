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
