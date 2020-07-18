// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define default_room "default_room"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NodeSocketAC.h"
#include "NMessage.h"
#include "NodeChatClient.generated.h"

/**
 * Node chat component
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NODECHATPLUGIN_API UNodeChatClient : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:

	/** 
	 * socket conector
	 */
	UPROPERTY(BlueprintReadWrite, Category = "AA_Net")
	UNodeSocketAC* vUNodeSocketAC;

	/** 
	 * reserverd messages 
	 */
	UPROPERTY(BlueprintReadWrite, Category = "AA_Net")
	TArray<FString> aMessage;

	/*
	 * Init socket
	 */
	UFUNCTION(BlueprintCallable, Category = "AA_Net")
		void fInit(UNodeSocketAC* _vUNodeSocketAC);

	
	bool fSendMsg(NMessage* msg);


	/**
	 * Send message to default connect room
	 * @param msg 
	 * @return true 
	 * @return false 
	 */
	UFUNCTION(BlueprintCallable, Category = "AA_Net")
		bool fSendMsgToDefaultRoom(FString msg);


	UFUNCTION(BlueprintCallable, Category = "AA_Net")
		FString fGetContentFromAMsg(int32 msgId);

	/**
	 * Reserve msg from node server
	 * @param msg FString
	 */
	void fOnReserveMsgCallback(const  FString& msg);
	
};
