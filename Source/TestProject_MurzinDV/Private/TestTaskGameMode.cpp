#include "TestTaskGameMode.h"
#include "AICharacter.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "ToyActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameState.h"
#include "Net/UnrealNetwork.h"

ATestTaskGameMode::ATestTaskGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATestTaskGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnAICharacters();
}

// Called every frame
void ATestTaskGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentToy)
    {
        EvaluateAICharacters(CurrentToy);
    }
}

void ATestTaskGameMode::EvaluateAICharacters(AActor* Toy)
{
    CurrentToy = Toy;
    TArray<AActor*> FoundAICharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), FoundAICharacters);

    AAICharacter* FarthestAI = nullptr;
    float MaxDistance = 0.0f;

    for (AActor* Actor : FoundAICharacters)
    {
        AAICharacter* AICharacter = Cast<AAICharacter>(Actor);
        if (AICharacter && CurrentToy)
        {
            float Distance = AICharacter->GetDistanceToToy(CurrentToy);
            if (Distance > MaxDistance)
            {
                MaxDistance = Distance;
                FarthestAI = AICharacter;
            }
        }
    }

    for (AActor* Actor : FoundAICharacters)
    {
        AAICharacter* AICharacter = Cast<AAICharacter>(Actor);
        if (AICharacter)
        {
            if (AICharacter == FarthestAI)
            {
                AICharacter->SetWaiting();
            }
            else
            {
                AICharacter->MoveToToy(CurrentToy);
            }
        }
    }
}

void ATestTaskGameMode::SpawnAICharacters()
{
    for (int32 i = 0; i < NumberOfAI; i++)
    {
        FVector SpawnLocation = FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), 100.0f);
        FRotator SpawnRotation = FRotator::ZeroRotator;
        AAICharacter* AICharacter = GetWorld()->SpawnActor<AAICharacter>(AICharacterClass, SpawnLocation, SpawnRotation);
    }
}


