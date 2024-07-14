#include "ToyActor.h"
#include "Components/StaticMeshComponent.h"
#include "AICharacter.h"
#include "TestTaskGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

// Sets default values
AToyActor::AToyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AToyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





