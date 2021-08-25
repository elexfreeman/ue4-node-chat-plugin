// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define default_room "default_room"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "NodeSocketAC.h"
#include "UNMessage.h"
#include "FUserListItem.h"
#include "NodeChatClient.generated.h"

// when did you get the string
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReserveChatMsg, const FString &, Msg);

// when did you get the string
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendChatMsg, const FString &, Msg);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateUserList);

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

    UNodeSocketAC *vNodeSocketAC;

    bool bIsInit = false;

public:
    UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = "AA_Net")
    FOnReserveChatMsg onReserveChatMsg;

    UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = "AA_Net")
    FOnSendChatMsg onSendChatMsg;

    UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = "AA_Net")
    FOnUpdateUserList onUpdateUserList;

    /** 
	 * reserverd messages 
	 */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_Net")
    TArray<FString> aMessage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_Net")
    TArray<FUserListItem> aUserList;


    bool fSendMsg(TSharedPtr<UNMessage> vMsg);

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

    UFUNCTION(BlueprintCallable, Category = "AA_Net")
    FString fGetContentFromMsg(const FString &msg);

    UFUNCTION(BlueprintCallable, Category = "AA_Net")
    FString fGetUserNameFromMsg(const FString &msg);

    UFUNCTION(BlueprintCallable, Category = "AA_Net")
    bool fInit(UNodeSocketAC * _vNodeSocketAC);

    UFUNCTION(BlueprintCallable, Category = "AA_Net")
    void fCallReserveMsg(const FString &msg);

    void fUpdateUserList(TSharedPtr<UNMessage> vMsg);

};
