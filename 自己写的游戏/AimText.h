#pragma once
#include"Class.h"
#include"Hooks.h"

namespace AimBotText
{
	wchar_t Buffer[1024]{ 0 };
	void RenderText(UCanvas* Canvas)
	{
		if (Hooks::Menu::OpenAimbot)
		{
			FLinearColor AimBotTextColor = FLinearColor(0.1f, 0.7f, 0.9f, 1.0f);
			const float indicator_x = Engine::ScreenCenter.x;
			const float indicator_y = Engine::ScreenCenter.y + 200;
			float indicator_y_offset = 0;
			swprintf(Buffer, _countof(Buffer), xorstr(L"当前自瞄热键: %hs\n"), Hooks::Menu::KeyStrings[Hooks::Menu::AimBotKey].c_str());
			Canvas->K2_StrokeText(FString(Buffer), AimBotTextColor, { indicator_x, indicator_y + indicator_y_offset * 20 });
			indicator_y_offset = indicator_y_offset + 1;

			swprintf(Buffer, _countof(Buffer), xorstr(L"F4键调节 当前部位: %hs\n"), Hooks::Menu::AimBotPos[Hooks::Menu::AimBith].c_str());
			Canvas->K2_StrokeText(FString(Buffer), AimBotTextColor, { indicator_x, indicator_y + indicator_y_offset * 20 });
			indicator_y_offset = indicator_y_offset + 1;
			if (GetAsyncKeyState(VK_F4) & 1) Hooks::Menu::AimBith = (Hooks::Menu::AimBith + 1 > 2) ? 0 : Hooks::Menu::AimBith + 1;

			swprintf(Buffer, _countof(Buffer), xorstr(L"F10键调节 当前自瞄范围: %d\n"), (uint32_t)Hooks::Menu::SilentRange);
			Canvas->K2_StrokeText(FString(Buffer), AimBotTextColor, { indicator_x, indicator_y + indicator_y_offset * 20 });
			indicator_y_offset = indicator_y_offset + 1;
			if (GetAsyncKeyState(VK_F10) & 1) Hooks::Menu::SilentRange = (Hooks::Menu::SilentRange + 50 > 500) ? 150 : Hooks::Menu::SilentRange + 50;

			swprintf(Buffer, _countof(Buffer), xorstr(L"F12键调节 当前类型: %hs\n"), Hooks::Menu::AimBotMod[Hooks::Menu::AimMod].c_str());
			Canvas->K2_StrokeText(FString(Buffer), AimBotTextColor, { indicator_x, indicator_y + indicator_y_offset * 20 });
			indicator_y_offset = indicator_y_offset + 1;
			if (GetAsyncKeyState(VK_F12) & 1) Hooks::Menu::AimMod = (Hooks::Menu::AimMod + 1 > 1) ? 0 : Hooks::Menu::AimMod + 1;
		}
	}
}