#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AICharacter.h"
#include "TestTaskGameMode.generated.h"

UCLASS()
class TESTPROJECT_MURZINDV_API ATestTaskGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    ATestTaskGameMode();

    UFUNCTION(BlueprintCallable)
    void EvaluateAICharacters(AActor* Toy);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* CurrentToy;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    TSubclassOf<AAICharacter> AICharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    int32 NumberOfAI;

    void SpawnAICharacters();

protected:
    virtual void BeginPlay() override;

};
