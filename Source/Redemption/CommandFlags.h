#pragma once

#include "CoreMinimal.h"
#include "ExpectedFileType.h"
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

	/**
	 * Graphical apps only - determines whether the player must specify a path to an existing file
	 * on disk when launching the app from the Shell.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags")
	bool bExpectsFileArgument = false;

	/**
	 * Defines what type of file argument should be given by the player if Expects File Argument is true.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Command Flags", meta = (EditCondition = "bExpectsFileArgument"))
	EExpectedFileType ExpectedFileType = EExpectedFileType::Any;
};
