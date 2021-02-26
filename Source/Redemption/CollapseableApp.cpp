#include "CollapseableApp.h"

#include "Components/NamedSlot.h"

void UCollapseableApp::BindApp(UOperatingSystemApp* InApp)
{
	check (InApp);

	this->OperatingSystemApp = InApp;

	this->AppTitle->SetText(InApp->AppAsset->Title);

	if (this->OperatingSystemApp->AppAsset->CommandFlags.IsUserCloseable)
	{
		this->CloseButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		this->CloseButton->SetVisibility(ESlateVisibility::Visible);
	}

	this->CollapsePanel->SetIsExpanded(true);

	this->AppArea->AddChild(this->OperatingSystemApp->AppWidget);
}
