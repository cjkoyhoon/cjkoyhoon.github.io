#include"Engine.h"
namespace Engine
{
	uint64_t EngineKey = 0;
	HWND hWnd = NULL;
	uint64_t ImageBase = NULL;
	float Width = 0;
	float Height = 0;
	UEngine* GEngine = NULL;
	FVector2D ScreenCenter = {}; // ÆÁÄ»ÖÐÐÄ
	FVector2D GetWindowSize()
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		return FVector2D{ (float)(rect.right - rect.left), (float)(rect.bottom - rect.top) };
	}
	bool Intialize()
	{
		hWnd = FindWindowA("UnrealWindow", NULL);
		RECT Rect;
		GetClientRect(hWnd, &Rect);
		ImageBase = (uint64_t)GetModuleHandleA(NULL);
		GEngine = GetEngine();
		Width = (float)(Rect.right / 2.f);
		Height = (float)(Rect.bottom / 2.f);
		FVector2D ScreenSize = GetWindowSize();
		ScreenCenter = FVector2D(ScreenSize.x / 2, ScreenSize.y / 2);
		return true;
	}

	HWND GethWnd()
	{
		return hWnd;
	}

	UEngine* GetEngine()
	{
		static UEngine* Engine = NULL;
		Engine = (UEngine*)UObject::StaticFindObject(NULL, NULL, L"/Engine/Transient.GPGameEngine_2147482527", false);
		return Engine;
	}
	
}
