// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	ChasingToy UMETA(DisplayName = "ChasingToy")
};

UCLASS()
class TESTPROJECT_MURZINDV_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MoveToToy(AActor* Toy);

	UFUNCTION(BlueprintCallable)
	void SetWaiting();

	void LookAtPlayer();
	void SetAIState(EAIState NewState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AI")
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AI")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UWidgetComponent* NameWidget;

	float GetDistanceToToy(AActor* CurrentToy);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "AI", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentToy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AIState, Category = "AI", meta = (AllowPrivateAccess = "true"))
	EAIState AIState;

	UFUNCTION()
	void OnRep_AIState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
