#include "HackerShell.h"
#include "ConsoleWidget.h"
#include "HackSession.h"
#include "NetworkManager.h"

void UHackerShell::HandleCommandLine(FString InCommandLine)
{
	this->GetConsole()->WriteLine(FText::FromString(InCommandLine));
}

void UHackerShell::NativeRun()
{
	// get an ip/host from arguments.
	if (this->GetArguments().Num())
	{
		this->HackedHost = this->GetArguments()[0];
	}
	else
	{
		this->GetConsole()->WriteLine(FText::FromString("%2error: missing hostname/ip%1"));
		this->Complete();
		return;
	}

	// Start a hack session on that IP address we found above.
	UHackSession* hackSession = this->GetNetworkManager()->BeginHack(this->HackedHost);
	
	// if we get nullptr then the host was unreachable.
	if (!hackSession)
	{
		this->GetConsole()->WriteLine(FText::FromString("%2error: host unreachable%1"));
		this->Complete();
		return;
	}

	// keep the hacking session on record because duh
	this->CurrentHack = hackSession;

	// Let's make sure the fucking console gives us the fucking text input we fucking need in this fucking program.
	this->GetConsole()->OnTextSubmitted.AddUniqueDynamic(this, &UHackerShell::UHackerShell::HandleCommandLine);
	
	this->Complete();
}
