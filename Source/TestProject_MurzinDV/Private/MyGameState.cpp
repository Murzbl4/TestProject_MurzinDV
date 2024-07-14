#include "MyGameState.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "GameFramework/PlayerState.h" 
#include "GameFramework/Controller.h"  
#include "UObject/ConstructorHelpers.h"
#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"

AMyGameState::AMyGameState()
{
    TimerValue = 300;
}

void AMyGameState::BeginPlay()
{
    Super::BeginPlay();
    
}

void AMyGameState::StartTimer(int32 Duration)
{
    TimerValue = Duration;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyGameState::UpdateTimer, 1.0f, true);
}



void AMyGameState::UpdateTimer()
{
    if (TimerValue > 0)
    {
        TimerValue--;
        if (TimerValue == 0)
        {
            GetWorldTimerManager().ClearTimer(TimerHandle);

            NotifyGameEnd();
        }
    }
}

void AMyGameState::NotifyGameEnd()
{
    AAICharacter* WinningAI = nullptr;
    int32 MaxScore = 0;
    bool bIsDraw = false;

    TArray<AActor*> FoundAICharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), FoundAICharacters);

    for (AActor* Actor : FoundAICharacters)
    {
        AAICharacter* AICharacter = Cast<AAICharacter>(Actor);
        if (AICharacter)
        {
            int32 Score = AICharacter->Score;
            if (Score > MaxScore)
            {
                MaxScore = Score;
                WinningAI = AICharacter;
                bIsDraw = false;
            }
            else if (Score == MaxScore)
            {
                bIsDraw = true;
            }
        }
    }

    if (bIsDraw)
    {
        Multicast_ShowEndGameUI(WinningAI, MaxScore, true);
    }
    else if (WinningAI)
    {
        Multicast_ShowEndGameUI(WinningAI, MaxScore, false);
    }
}

void AMyGameState::Multicast_ShowEndGameUI_Implementation(AActor* Winner, int32 Score, bool bIsDraw)
{
    ShowEndGameUI(Winner, Score, bIsDraw);
}


void AMyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyGameState, TimerValue);
}
