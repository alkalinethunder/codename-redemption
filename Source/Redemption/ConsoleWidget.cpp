// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsoleWidget.h"

#include "Engine/Font.h"

void UConsoleWidget::MeasureText(FString InText, int& OutWidth, int& OutHeight)
{
	const UFont* UnrealFont = Cast<UFont>(this->Font.FontObject);

	OutWidth=0;
	OutHeight=0;

	float accumW = 0, accumH = 0;
	
	if (UnrealFont)
	{
		TArray<FString> Lines;
		InText.ParseIntoArray(Lines, TEXT("\r\n"), false);

		if (Lines.Num() == 0)
		{
			accumH += this->CharHeight;
		}
		else
		{
			for (FString Line : Lines)
			{
				float w = Line.Len() * this->CharWidth;
				if (accumW < w)
					accumW = w;
				accumH += this->CharHeight;
			}
		}

		OutWidth = accumW;
		OutHeight = accumH;
	}
	else
	{
		OutWidth = 0;
		OutHeight = 0;
		return;
	}
}

FString UConsoleWidget::StripFormatting(FString InText)
{
	bool formatDelimeter = false;
	FString res;

	for (TCHAR c : InText)
	{
		if (c == this->ColorDelimeter)
		{
			if (!formatDelimeter)
			{
				formatDelimeter = true;
				continue;
			}

			formatDelimeter = false;
			res += c;
			continue;
		}

		if (formatDelimeter)
		{
			formatDelimeter = false;
			continue;
		}

		res += c;
	}
	
	return res;
}

void UConsoleWidget::RebuildTextItems(const FGeometry& MyGeometry)
{
	int heightAccum = 0;
	FVector2D alottedSize = MyGeometry.GetLocalSize();
	FVector2D loc = MyGeometry.GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FConsoleTextData item;
	int prevW = 0;
	int prevH = 0;
	bool cursor = false;
	
	this->TextIsDirty = false;
	this->DrawItems.Empty();

	item.Background = FLinearColor::Transparent;
	item.Foreground = this->ColorAndOpacity;
	item.Location = loc;

	for (int i = 0; i < this->OutputBuffer.Len(); i++)
	{
		TCHAR c = this->OutputBuffer[i];
		item.Text += c;
	}

	for (int i = 0; i <= this->InputBuffer.Len(); i++)
	{
		TCHAR c = (i < this->InputBuffer.Len()) ? this->InputBuffer[i] : ' ';

		if (i == this->InputPos)
		{
			if (item.Text.Len() > 0)
			{
				this->DrawItems.Add(item);
			}
			
			cursor = true;
			FLinearColor s = item.Background;
			item.Background = item.Foreground;
			item.Foreground = s;
			item.Text = FString::Chr(c);			
			continue;
		}

		if (cursor)
		{
			if (item.Text.Len() > 0)
			{
				this->DrawItems.Add(item);
			}
			
			cursor = false;

			FLinearColor s = item.Background;
			item.Background = item.Foreground;
			item.Foreground=s;
			item.Text = FString::Chr(c);
			continue;
		}

		item.Text += c;
	}

	this->DrawItems.Add(item);
}

void UConsoleWidget::RecalculateTextSizes_Pass2(const FGeometry& MyGeometry)
{
	FVector2D loc = MyGeometry.GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FVector2D textLoc = loc;
	FVector2D csize = FVector2D(this->CharWidth, this->CharHeight);
	FVector2D asize = MyGeometry.GetLocalSize();

	float accum = this->CharHeight;
	
	for (FConsoleTextData data : this->DrawItems)
	{
		for(int i = 0; i < data.Text.Len(); i++)
		{
			TCHAR c = data.Text[i];

			if (c == '\0') continue;
			if (c == '\r') continue;
			if (c == '\n')
			{
				accum += this->CharHeight;
				textLoc.X = loc.X;
				continue;
			}

			if (textLoc.X + this->CharWidth > loc.X + asize.X)
			{
				accum += this->CharHeight;
				textLoc.X = loc.X;
			}

			textLoc.X += this->CharWidth;
		}
	}
	
	this->TextHeight = accum;
}

void UConsoleWidget::RecalculateTextSizes()
{
	FString AllText = this->StripFormatting(this->OutputBuffer) + this->InputBuffer;

	int width;
	int height;
	this->MeasureText(AllText, width, height);
	this->SetMinimumDesiredSize(FVector2D(width, height));
}

void UConsoleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	const UFont* font = Cast<UFont>(this->Font.FontObject);

	if (font)
	{
		float scale = (float) font->LegacyFontSize / (float) this->Font.Size;

		float w = 0, h = 0;
		font->GetCharSize('#', w, h);

		this->CharWidth = w / scale;
		this->CharHeight = h / scale;
	}
}

void UConsoleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (this->TextIsDirty)
	{
		this->ScrollBack = 0;
		this->RebuildTextItems(MyGeometry);
		this->RecalculateTextSizes_Pass2(MyGeometry);
		this->OnTextWritten.Broadcast();
	}
}

int32 UConsoleWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FLinearColor fg;
	FLinearColor bg;
	FVector2D loc = AllottedGeometry.GetLocalPositionAtCoordinates(FVector2D(0, 1));
	loc.Y -= this->TextHeight;
	loc.Y += (this->CharHeight * this->ScrollBack);
	FVector2D textLoc = loc;
	FVector2D csize = FVector2D(this->CharWidth, this->CharHeight);
	FVector2D asize = AllottedGeometry.GetLocalSize();

	FVector2D cullBottom = AllottedGeometry.GetLocalPositionAtCoordinates(FVector2D(0, 1));
	FVector2D cullTop = AllottedGeometry.GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	
	
	for (const FConsoleTextData& TextData : this->DrawItems)
	{
		bg = TextData.Background;
		fg = TextData.Foreground;
		fg.A = 1;

		for (int i = 0; i < TextData.Text.Len(); i++)
		{
			TCHAR c = TextData.Text[i];
			
			if (c == '\r') continue;
			if (c == '\0') continue;
			if (c == '\n')
			{
				textLoc.X = loc.X;
				textLoc.Y += this->CharHeight;
				continue;
			}

			if (textLoc.X + this->CharWidth > loc.X + asize.X)
			{
				textLoc.X = loc.X;
				textLoc.Y += this->CharHeight;
			}

			if (textLoc.Y >= cullTop.Y && textLoc.Y <= cullBottom.Y)
			{
				FString str = FString::Chr(c);
			
				FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(textLoc, csize), &Brush, ESlateDrawEffect::None, bg);

				if (!FChar::IsWhitespace(c))
				{
					FSlateDrawElement::MakeText(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(textLoc, csize), str, this->Font, ESlateDrawEffect::None, fg);
				}
				
				textLoc.X += this->CharWidth;
			}
		}
	}
	
	return LayerId;
}

FReply UConsoleWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
{
	TCHAR c = InCharEvent.GetCharacter();

	switch (c)
	{
		case '\r':
			this->WriteLine(FText::FromString(this->InputBuffer));
			this->InputBuffer = "";
			this->InputPos = 0;
			break;
		case '\b':
			if (this->InputPos > 0)
			{
				this->InputPos--;
				this->InputBuffer.RemoveAt(this->InputPos, 1);
			}
			break;
		default:
			this->InputBuffer.InsertAt(this->InputPos, c);
			this->InputPos++;
			break;
	}
	
	this->TextIsDirty=true;
	this->RecalculateTextSizes();
	return FReply::Handled();
}

bool UConsoleWidget::NativeIsInteractable() const
{
	return true;
}

bool UConsoleWidget::NativeSupportsKeyboardFocus() const
{
	return true;
}

FReply UConsoleWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->SetUserFocus(this->GetOwningPlayer());
	return FReply::Handled();
}

FReply UConsoleWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey key = InKeyEvent.GetKey();

	if (key == EKeys::Left)
	{
		if (InputPos > 0)
		{
			InputPos--;
			this->TextIsDirty=true;
			return FReply::Handled();
		}
	}
	else if (key == EKeys::Right)
	{
		if (InputPos < this->InputBuffer.Len())
		{
			this->InputPos++;
			this->TextIsDirty=true;
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}

void UConsoleWidget::Write(FText InText)
{
	this->OutputBuffer += InText.ToString();
	this->TextIsDirty = true;
	this->RecalculateTextSizes();
}

void UConsoleWidget::WriteLine(FText InText)
{
	this->OutputBuffer += InText.ToString();
	this->OutputBuffer += "\r\n";
	this->TextIsDirty = true;
	this->RecalculateTextSizes();
}

void UConsoleWidget::ClearScreen()
{
	this->OutputBuffer = "";
	this->TextIsDirty = true;
	this->RecalculateTextSizes();
}
