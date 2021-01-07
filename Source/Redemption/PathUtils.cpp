// Fill out your copyright notice in the Description page of Project Settings.


#include "PathUtils.h"

void UPathUtils::GetPathParts(FString InPath, TArray<FString>& OutParts)
{
	OutParts.Empty();

	FString word;

	for (int i = 0; i <= InPath.Len(); i++)
	{
		if (i < InPath.Len())
		{
			TCHAR c = InPath[i];
			if (FString::Chr(c) == GetPathSeparatorString())
			{
				if (word.Len() > 0)
				{
					OutParts.Add(word);
					word = "";
				}
				continue;
			}

			word += c;
		}
		else
		{
			if (word.Len() > 0)
			{
				OutParts.Add(word);
			}
		}
	}
}


FString UPathUtils::GetAbsolutePath(FString InWorkingDirectory, FString InRelativePath)
{
	FString result;
	TArray<FString> workParts;
	TArray<FString> relParts;
	TArray<FString> stack;
	
	GetPathParts(InWorkingDirectory, workParts);
	GetPathParts(InRelativePath, relParts);

	for (FString part : workParts)
	{
		if (part == GetThisDirectoryString()) continue;
		if (part == GetUpOneDirectoryString())
		{
			if (stack.Num() > 0)
			{
				stack.RemoveAt(stack.Num() - 1);
			}
			continue;
		}
		
		if (part == GetHomeDelimeterString())
		{
			stack.Empty();
			stack.Add(GetHomeDelimeterString());
			continue;
		}

		stack.Add(part);
	}

	for (FString part : relParts)
	{
		if (part == GetThisDirectoryString()) continue;
		if (part == GetUpOneDirectoryString())
		{
			if (stack.Num() > 0)
			{
				stack.RemoveAt(stack.Num() - 1);
			}
			
			continue;
		}
		
		if (part == GetHomeDelimeterString())
		{ 
			stack.Empty();
			stack.Add(GetHomeDelimeterString());
			continue;
		}

		stack.Add(part);
	}

	if (stack.Num() > 0)
	{
		for (FString part : stack)
		{
			result += "/" + part;
		}
	}
	else
	{
		result = "/";
	}

	return result;
}
