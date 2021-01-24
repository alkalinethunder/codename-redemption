// Fill out your copyright notice in the Description page of Project Settings.


#include "GuiHelpers.h"

FText UGuiHelpers::GetTimeFromNow(const FDateTime& InUtcDateTime)
{
	FDateTime utcNow = FDateTime::UtcNow();
	FTimespan timeSpan = utcNow - InUtcDateTime;

	int seconds = timeSpan.GetTotalSeconds();

	if (seconds < 0)
	{
		return FText::FromString("in the future");
	}

	if (seconds <= 3)
	{
		return FText::FromString("just now");
	}

	if (seconds <= 30)
	{
		return FText::FromString("moments ago");
	}
	else
	{
		if (seconds >= 60)
		{
			int minutes = seconds / 60;
			if (minutes >= 60)
			{
				int hours = minutes / 60;
				if (hours >= 24)
				{
					int days = hours / 24;
					if (days >= 7)
					{
						int weeks = days / 7;
						if (weeks >= 3)
						{
							return FText::FromString("a long time ago");
						}
						return FText::FromString(FString::FromInt(weeks) + " weeks ago");
					}
					return FText::FromString(FString::FromInt(days) + " days ago");
				}
				return FText::FromString(FString::FromInt(hours) + " hours ago");
			}
			return FText::FromString(FString::FromInt(minutes) + " minutes ago");
		}
		else
		{
			return FText::FromString(FString::FromInt(seconds) + " seconds ago");
		}
	}
}

void UGuiHelpers::InsertChildAtStart(UVerticalBox* Target, UWidget* InChild)
{
	int childCount = Target->GetChildrenCount();
	Target->AddChild(InChild);
	for(int i = 0; i < childCount; i++)
	{
		UWidget* child = Target->GetChildAt(0);
		Target->RemoveChildAt(0);
		Target->AddChild(child);
	}
}
