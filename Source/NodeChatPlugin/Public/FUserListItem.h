// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "FUserListItem.generated.h"


USTRUCT(BlueprintType)
struct NODECHATPLUGIN_API FUserListItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AA")
    int32 id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AA")
    FString username;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AA")
    FString token;
};