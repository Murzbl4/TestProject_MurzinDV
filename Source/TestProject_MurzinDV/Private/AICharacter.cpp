// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TestTaskGameMode.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "ToyActor.h"
#include "Net/UnrealNetwork.h"


AAICharacter::AAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    Speed = FMath::FRandRange(50.0f, 1000.0f);
    Score = 0;
    NameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidget"));
    NameWidget->SetupAttachment(RootComponent);
    CurrentToy = nullptr;
    AIState = EAIState::Idle;

    bReplicates = true;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (AIState)
    {
    case EAIState::Idle:
        LookAtPlayer();
        break;
    default:
        break;
    }
}

void AAICharacter::MoveToToy(AActor* Toy)
{
    if (Toy)
    {
        CurrentToy = Toy;
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToActor(Toy, 5.0f);
        }
        SetAIState(EAIState::ChasingToy);
    }
}

void AAICharacter::SetWaiting()
{
    CurrentToy = nullptr;
    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
    AIController->StopMovement();
    }
    SetAIState(EAIState::Idle);
}

void AAICharacter::LookAtPlayer()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
        FRotator LookAtRotation = (PlayerLocation - GetActorLocation()).Rotation();
        SetActorRotation(LookAtRotation);
    }
}

void AAICharacter::SetAIState(EAIState NewState)
{
    if (AIState != NewState)
    {
        AIState = NewState;
        OnRep_AIState();
    }
}

void AAICharacter::OnRep_AIState()
{
    switch (AIState)
    {
    case EAIState::Idle:
        LookAtPlayer();
        break;
    default:
        break;
    }
}

void AAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAICharacter, AIState);
    DOREPLIFETIME(AAICharacter, Score);
}

float AAICharacter::GetDistanceToToy(AActor* Toy)
{
    if (Toy)
    {
        return FVector::Dist(GetActorLocation(), Toy->GetActorLocation());
    }
    return FLT_MAX;
}
