#pragma once
#include"base.h"
#include"Class.h"
#include<vector>
namespace Engine
{
	

	bool Intialize();

	HWND GethWnd();

	UEngine* GetEngine();

	FVector2D GetWindowSize();

	extern uint64_t ImageBase;

	extern float Width;

	extern float Height;

	extern FVector2D ScreenCenter;
}