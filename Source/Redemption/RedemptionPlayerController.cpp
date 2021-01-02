// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARedemptionPlayerController::ARedemptionPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedemptionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->GameMode = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (this->GameMode)
	{
		this->Desktop = CreateWidget<UUserWidget, APlayerController>(this, this->GameMode->DesktopWidget);
		this->Desktop->AddToViewport();

		this->SetShowMouseCursor(true);
	}
}

// Called every frame
void ARedemptionPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

