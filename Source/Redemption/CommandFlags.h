#pragma once

#include "CoreMinimal.h"
#include "CommandFlags.generated.h"

USTRUCT(BlueprintType)
struct FCommandFlags
{
	GENERATED_BODY()

public:
	/**
	 * Command can be run by the player directly rather than by game
	 * script.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsRunnableByPlayer = true;

	/**
	 * Command can be run over network shells (on NPC systems).
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsRunnableOverNetShell = false;

	/**
	 * Command must be run as root.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsAdminCommand = false;

	/**
	 * Command is completed when its script calls the Complete node.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool ManualCompletionTrigger = false;

	/**
	 * (Graphical Apps only) Whether the close button is visible on the app's
	 * tab or title bar.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsUserCloseable = true;
	
	/**
	 * (Graphical apps only) Command will not launch more than
	 * one GUI if a GUI has already been created.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsSingleInstance = false;

	/**
	 * (Graphical Apps only) Command will run on game load.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool IsStartup = false;
};
