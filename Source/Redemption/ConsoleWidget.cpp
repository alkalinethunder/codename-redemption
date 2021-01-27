// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsoleWidget.h"
#include "Engine/Font.h"
#include "Fonts/FontMeasure.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Framework/Application/SlateApplication.h"
#include "Windows/Accessibility/WindowsUIAControlProvider.h"

void UConsoleWidget::MeasureText(const FGeometry& MyGeometry, FString InText, float& OutWidth, float& OutHeight)
{
	TSharedRef<FSlateFontMeasure> measurer = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	
	FVector2D result = measurer->Measure(InText, this->Font, this->ZoomFactor);
	
	OutWidth = result.X;
	OutHeight = result.Y;
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
	TSharedRef<FSlateFontMeasure> measurer = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

	TCHAR lastChar;
	
	int heightAccum = 0;
	FVector2D alottedSize = MyGeometry.GetLocalSize();
	FVector2D loc = MyGeometry.GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FConsoleTextData item;
	float prevW = 0;
	float prevH = 0;
	bool cursor = false;
	
	this->TextIsDirty = false;
	this->DrawItems.Empty();

	item.Background = FLinearColor::Transparent;
	item.Foreground = this->ColorAndOpacity;
	item.Location = loc;
	item.Line = 0;
	
	for (int i = 0; i < this->OutputBuffer.Len(); i++)
	{
		TCHAR c = this->OutputBuffer[i];

		if (c == '\r') continue;

		if (c == BackgroundChar && i < this->OutputBuffer.Len() - 1)
		{
			TCHAR code = OutputBuffer[i + 1];
			FLinearColor bg;
			if (this->GetColor(code, bg))
			{
				this->DrawItems.Add(item);
				item.Background = bg;
				item.Location.X += item.Size.X;
				item.Size.X = 0;
				item.Text = "";
				i++;
				continue;
			}
		}
		
		
		if (c == ForegroundChar && i < this->OutputBuffer.Len() - 1)
		{
			TCHAR code = OutputBuffer[i + 1];
			FLinearColor fg;
			if (this->GetColor(code, fg))
			{
				this->DrawItems.Add(item);
				item.Foreground = fg;
				item.Location.X += item.Size.X;
				item.Size.X = 0;
				item.Text = "";
				i++;
				continue;
			}
		}
		
		if (c == '\n')
		{
			lastChar = c;
			this->DrawItems.Add(item);
			item.Line++;
			item.Location.X = loc.X;
			item.Location.Y += item.Size.Y;
			item.Text = "";
			item.Size.X = 0;
			continue;
		}

		FString prev = item.Text;
		prev += c;

		this->MeasureText(MyGeometry, prev, prevW, prevH);
		if (item.Location.X + prevW >= loc.X + alottedSize.X)
		{
			this->DrawItems.Add(item);
			item.Location.X = loc.X;
			item.Line++;
			item.Location.Y += item.Size.Y;
			item.Size.X = 0;
			item.Text = "";
		}

		item.Text += c;
		this->MeasureText(MyGeometry, item.Text, prevW, prevH);
		item.Size.X = prevW;
		item.Size.Y = prevH;

		lastChar = c;
	}

	for (int i = 0; i <= this->InputBuffer.Len(); i++)
	{
		TCHAR c = (i < this->InputBuffer.Len()) ? this->InputBuffer[i] : ' ';
		if (i == this->InputPos)
		{
			if (item.Text.Len() > 0)
			{
				this->DrawItems.Add(item);
				item.Location.X += item.Size.X;
			}
			
			cursor = true;
			FLinearColor s = item.Background;
			item.Background = item.Foreground;
			item.Foreground = s;
			item.Text = FString::Chr(c);

			this->MeasureText(MyGeometry, item.Text, prevW, prevH);

			if (item.Location.X + prevW >= loc.X + alottedSize.X)
			{
				item.Location.X = loc.X;
				item.Location.Y += prevH;
				item.Line++;
			}

			item.Size.X = prevW;
			item.Size.Y = prevH;

			lastChar = c;
			
			continue;
		}

		if (cursor)
		{
			if (item.Text.Len() > 0)
			{
				this->DrawItems.Add(item);
				item.Location.X += item.Size.X;
			}
			
			cursor = false;

			FLinearColor s = item.Background;
			item.Background = item.Foreground;
			item.Foreground=s;
			item.Text = FString::Chr(c);

			this->MeasureText(MyGeometry, item.Text, prevW, prevH);

			if (item.Location.X + prevW >= loc.X + alottedSize.X)
			{
				item.Location.X = loc.X;
				item.Location.Y += prevH;
				item.Line++;
			}

			item.Size.X = prevW;
			item.Size.Y = prevH;

			lastChar = c;
			
			continue;
		}

		FString prev = item.Text;
		prev += c;

		this->MeasureText(MyGeometry, prev, prevW, prevH);
		if (item.Location.X + prevW >= loc.X + alottedSize.X)
		{
			this->DrawItems.Add(item);
			item.Location.X = loc.X;
			item.Location.Y += item.Size.Y;
			item.Size.X = 0;
			item.Line++;
			item.Text = "";
		}

		item.Text += c;
		this->MeasureText(MyGeometry, item.Text, prevW, prevH);
		item.Size.X = prevW;
		item.Size.Y = prevH;

		lastChar = c;
	}

	this->DrawItems.Add(item);
}

void UConsoleWidget::RecalculateTextSizes_Pass2(const FGeometry& MyGeometry)
{
	FVector2D loc = MyGeometry.GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FVector2D textLoc = loc;
	FVector2D csize = FVector2D(this->CharWidth, this->CharHeight);
	FVector2D asize = MyGeometry.GetLocalSize();
	int line = -1;
	float accum = 0.f;
	float lHeight = 0.f;
	
	for (FConsoleTextData data : this->DrawItems)
	{
		if (line != data.Line)
		{
			line = data.Line;
			accum += data.Size.Y;
			if (lHeight < data.Size.Y)
				lHeight = data.Size.Y;
		}
	}

	this->LineHeight = lHeight;
	this->TextHeight = accum;
}

void UConsoleWidget::RecalculateTextSizes()
{
	FString AllText = this->StripFormatting(this->OutputBuffer) + this->InputBuffer;

	float width;
	float height;
	this->MeasureText(this->GetCachedGeometry(), AllText, width, height);

	if (this->bEnableDesiredSizeMeasurement)
	{
		this->SetMinimumDesiredSize(FVector2D(width, height));
	}
}

bool UConsoleWidget::GetColor(TCHAR InColorCode, FLinearColor& OutColor)
{
	// I'm gonna be too feckin high to understand the ue4 docs to do this more
	// efficiently so it's uh
	// time for phil code
	switch (InColorCode)
	{
		case '0':
			OutColor = FLinearColor::Transparent;
			break;
		case '1':
			OutColor = this->ColorAndOpacity;
			break;
		case '2':
			OutColor = FLinearColor(1, 0, 1);
			break;
		case '3':
			OutColor = FColor::Red;
			break;
		case '4':
			OutColor = FColor::Green;
			break;
		case '5':
			OutColor = FLinearColor::Blue;
			break;
		case '6':
			OutColor = FColor::Orange;
			break;
		case '7':
			OutColor = FColor::Yellow;
			break;
		case '8':
			OutColor = FColor::Cyan;
			break;
		case '9':
			OutColor = FColor::Purple;
			break;
		case 'A':
		case 'a':
			OutColor = FColor::Magenta;
			break;
		case 'B':
		case 'b':
			OutColor = FColor::Emerald;
			break;
		case 'C':
		case 'c':
			OutColor = FColor::Silver;
			break;
		case 'D':
		case 'd':
			OutColor = FColor::Turquoise;
			break;
		case 'E':
		case 'e':
			OutColor = FColor::Black;
			break;
		case 'F':
		case 'f':
		default:
			return false;				
	}

	return true;
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

	float y = AllottedGeometry.GetLocalPositionAtCoordinates(FVector2D::UnitVector).Y - this->TextHeight + (this->ScrollBack * this->LineHeight);
	int line = 0;
	
	for (const FConsoleTextData& TextData : this->DrawItems)
	{
		if (line != TextData.Line)
		{
			y += this->LineHeight;
			line = TextData.Line;
		}
		
		bg = TextData.Background;
		fg = TextData.Foreground;
		fg.A = 1;

		if (y >= 0 && y <= AllottedGeometry.GetLocalSize().Y)
		{
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(FVector2D(TextData.Location.X, y), TextData.Size), &Brush, ESlateDrawEffect::None, bg);

			if (TextData.Text.TrimEnd().Len() > 0)
			{
				LayerId++;
				FSlateDrawElement::MakeText(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(FVector2D(TextData.Location.X, y), TextData.Size), TextData.Text, this->Font, ESlateDrawEffect::None, fg);
			}
		}
	}
	
	return LayerId;
}

FReply UConsoleWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
{
	TCHAR c = InCharEvent.GetCharacter();

	FString input = this->InputBuffer;

	switch (c)
	
	{
		case '\r':
			this->WriteLine(FText::FromString(this->InputBuffer));
			this->InputBuffer = "";
			this->InputPos = 0;
			this->OnTextSubmitted.Broadcast(input);
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

FReply UConsoleWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	int delta = InMouseEvent.GetWheelDelta();
	
	if (delta < 0)
	{
		if (this->ScrollBack > 0)
		{
			this->ScrollBack--;
		}
	}
	else if (delta > 0)
	{
		this->ScrollBack++;
	}
	
	return FReply::Handled();
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
