// Fill out your copyright notice in the Description page of Project Settings.


#include "NetBrowserApp.h"

#include "Blueprint/WidgetTree.h"

void UNetBrowserApp::HandleHtmlUrlChanged(const FText& InText)
{
	this->CurrentUrl = InText.ToString();
	this->AddressBar->SetText(InText);
}

void UNetBrowserApp::HandleGoButton()
{
	this->NavigateToUrl(this->AddressBar->GetText().ToString());
}

void UNetBrowserApp::NavigateInternal(FString InUrl, bool AddToHistory)
{
	if (AddToHistory)
	{
		this->History.Add(this->CurrentUrl);
	}

	this->CurrentUrl = InUrl;
	this->AddressBar->SetText(FText::FromString(this->CurrentUrl));

	// TODO: in-game websites
	if (false)
	{
		
	}
	else
	{
		this->WebContent->SetVisibility(ESlateVisibility::Collapsed);
		this->HtmlBrowser->SetVisibility(ESlateVisibility::Visible);
		this->HtmlBrowser->LoadURL(this->CurrentUrl);
	}
}

void UNetBrowserApp::NativeConstruct()
{
	Super::NativeConstruct();

	this->HtmlBrowser->OnUrlChanged.AddUniqueDynamic(this, &UNetBrowserApp::HandleHtmlUrlChanged);

	this->BackButton->OnClicked.AddUniqueDynamic(this, &UNetBrowserApp::GoBack);
	this->ForwardButton->OnClicked.AddUniqueDynamic(this, &UNetBrowserApp::GoForward);
	this->GoButton->OnClicked.AddUniqueDynamic(this, &UNetBrowserApp::HandleGoButton);

	this->AddressBar->OnTextCommitted.AddUniqueDynamic(this, &UNetBrowserApp::HandleAddressSubmission);
}

void UNetBrowserApp::HandleAddressSubmission(const FText& InText, ETextCommit::Type InCommitType)
{
	if (InCommitType == ETextCommit::OnEnter)
	{
		this->NavigateToUrl(InText.ToString());
	}
}


void UNetBrowserApp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UNetBrowserApp::GoBack()
{
	if (this->History.Num())
	{
		FString newUrl = this->History[this->History.Num() - 1];
		this->History.RemoveAt(this->History.Num() - 1);
		this->Future.Insert(newUrl, 0);
		this->NavigateInternal(newUrl, false);
	}
}

void UNetBrowserApp::GoForward()
{
	if (this->Future.Num())
	{
		FString newUrl = this->Future[0];
		this->Future.RemoveAt(0);
		this->NavigateInternal(newUrl, true);
	}
}

void UNetBrowserApp::NavigateToUrl(FString InUrl)
{
	if (this->CurrentUrl != InUrl)
	{
		this->Future.Empty();
		this->NavigateInternal(InUrl, true);
	}
}
