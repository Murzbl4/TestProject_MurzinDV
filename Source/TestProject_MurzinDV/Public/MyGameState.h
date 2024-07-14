// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_MURZINDV_API AMyGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AMyGameState();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Timer")
    int32 TimerValue;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Timer")
    bool ThrowToy;

    UFUNCTION(BlueprintCallable, Category = "Timer")
    void StartTimer(int32 Duration);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ShowEndGameUI(AActor* Winner, int32 Score, bool bIsDraw);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game")
    void ShowEndGameUI(AActor* Winner, int32 Score, bool bIsDraw);

private:
    FTimerHandle TimerHandle;
    void UpdateTimer();

    void NotifyGameEnd();
};
