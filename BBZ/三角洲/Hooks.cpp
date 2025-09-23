#include"Hooks.h"
#include"iteam.h"
#include"hook.h"
#include"Spoofcall.h"
#include"AimText.h"
#include"Actors.h"
#include"Menu.h"

using FN = void(__fastcall*)(void*, UCanvas* Canvas);

namespace Hooks
{
	Utils::VTableHook RenderHook;
	
    namespace Draw
    {
        namespace Color
        {
            FColor 红色 = FColor(255, 0, 0);
            FColor 品红 = FColor(255, 0, 255);
            FColor 黄色 = FColor(255, 255, 0);
            FColor 灰蓝 = FColor(128, 128, 255);
            FColor 嫩绿 = FColor(128, 224, 0);
            FColor 深绿 = FColor(0, 224, 128);
            FColor 棕色 = FColor(192, 96, 0);
            FColor 粉色 = FColor(255, 168, 255);
            FColor 暗黄 = FColor(216, 216, 0);
            FColor 银白 = FColor(236, 236, 236);
            FColor 紫色 = FColor(144, 0, 255);
            FColor 藏蓝 = FColor(88, 48, 224);
            FColor 灰绿 = FColor(128, 160, 128);
            FColor 青蓝 = FColor(0, 96, 192);
            FColor 橙黄 = FColor(255, 128, 0);
            FColor 橙色 = FColor(254, 148, 13);
            FColor 桃红 = FColor(255, 80, 128);
            FColor 芙红 = FColor(255, 128, 192);
            FColor 深灰 = FColor(96, 96, 96);
            FColor 藏青 = FColor(0, 0, 128);
            FColor 墨绿 = FColor(0, 128, 0);
            FColor 深青 = FColor(0, 128, 128);
            FColor 红褐 = FColor(128, 0, 0);
            FColor 紫红 = FColor(128, 0, 128);
            FColor 绿色 = FColor(0, 255, 0);
            FColor 艳青 = FColor(0, 255, 255);
            FColor 黑色 = FColor(0, 0, 0);
            FColor 灰色 = FColor(128, 128, 128);
            FColor 白色 = FColor(255, 255, 255);
            FColor 天青 = FColor(135, 206, 250);
            FColor 春绿 = FColor(0, 255, 127);
            FColor 珊瑚 = FColor(255, 127, 80);
            FColor 灰紫 = FColor(169, 169, 255);
            FColor 靛青 = FColor(75, 0, 130);
            FColor 翠绿 = FColor(0, 128, 64);
            FColor 青白 = FColor(224, 255, 255);
            FColor 玫瑰红 = FColor(255, 36, 102);
            FColor 夜色 = FColor(25, 25, 112);
            FColor 亮紫 = FColor(153, 50, 204);
            FColor 精白 = FColor(245, 245, 245);
            FColor 赤橙 = FColor(255, 69, 0);
            FColor 蔚蓝 = FColor(0, 123, 167);
            FColor 金黄 = FColor(255, 215, 0);
            FColor 紫罗兰 = FColor(138, 43, 226);
            FColor 玉米黄 = FColor(255, 237, 160);
            FColor 橄榄绿 = FColor(128, 128, 0);
            FColor 嫩粉 = FColor(255, 182, 193);
            FColor 柠檬绿 = FColor(50, 205, 50);
            FColor 海藻绿 = FColor(46, 139, 87);
            FColor 栗色 = FColor(139, 69, 19);
            FColor 亮橙 = FColor(255, 165, 0);
            FColor 鲑红 = FColor(250, 128, 114);
            FColor 雪白 = FColor(255, 250, 250);
            FColor 灰钢 = FColor(169, 169, 169);
            FColor 珍珠白 = FColor(255, 253, 208);
            FColor 赭色 = FColor(128, 80, 80);
            FColor 草绿 = FColor(124, 252, 0);
            FColor 碧绿 = FColor(0, 255, 127);
            FColor 翡红 = FColor(240, 128, 128);
            FColor 丛绿 = FColor(100, 200, 50);
            FColor 蓝紫 = FColor(170, 90, 200);
            FColor 天蓝 = FColor(30, 150, 255);
            FColor 金橙 = FColor(255, 153, 51);
        }
        bool MouseInRegion(float x, float y, float x2, float y2)
        {
            return MousePosition.x > x && MousePosition.y > y && MousePosition.x < x2 + x && MousePosition.y < y2 + y;
        }
        void DrawLine(float x1, float y1, float x2, float y2, FColor Color, float thickness)
        {
            UCanvas::Canvas->K2_DrawLine(FVector2D(x1, y1), FVector2D(x2, y2), thickness, Color.ToLinearColor());
        }
        void DrawRect(float x, float y, float w, float h, FColor Color, float thickness)
        {
            UCanvas::Canvas->K2_DrawBox(FVector2D(x, y), FVector2D(w, h), thickness, Color.ToLinearColor());
        }
        void DrawFilled(float x, float y, float width, float height, FColor Color)
        {
            // 画矩形内的水平线，形成填充
            for (float i = y; i < y + height; ++i)
            {
                DrawLine(x, i, x + width, i, Color, 1.0f);
            }
        }
        void DrawMenuText(float x, float y, uint32_t Size, bool bCentreX, bool bCentreY, FColor Color, const wchar_t* text, ...)
        {
            wchar_t szBuffer[4096] = { 0 };
            va_list args;
            va_start(args, text);
            wvsprintfW(szBuffer, text, args);
            va_end(args);
            UObject::GetRoboto()->LegacyFontSize = 8;
            FVector2D TextScale = FVector2D{ 1, 1 };
            UCanvas::Canvas->K2_DrawText(UObject::GetRoboto(), szBuffer, FVector2D{ x, y }, TextScale, Color.ToLinearColor(), 1, FLinearColor(0, 0, 0), FVector2D(1, 1), bCentreX, bCentreY, true, FLinearColor(0, 0, 0));
        }

        void DrawEspText(UCanvas* Canvas, float x, float y, uint32_t Size, bool bCentreX, bool bCentreY, FLinearColor Color, const wchar_t* text, ...)
        {
            wchar_t szBuffer[4096] = { 0 };
            va_list args;
            va_start(args, text);
            wvsprintfW(szBuffer, text, args);
            va_end(args);
            UEngine::GetRoboto()->LegacyFontSize = Size;
            FVector2D TextScale = FVector2D(0.85f, 0.85f);
            Canvas->K2_DrawText(UEngine::GetRoboto(), szBuffer, FVector2D{ x, y }, TextScale, Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(1, 1), bCentreX, bCentreY, true, FLinearColor(0, 0, 0, 1));
        }

        FVector2D GetTextSize(const wchar_t* text, ...)
        {
            wchar_t szBuffer[4096] = { 0 };
            va_list args;
            va_start(args, text);
            wvsprintfW(szBuffer, text, args);
            va_end(args);
            FVector2D TextScale = FVector2D{ 1, 1 };
            return UCanvas::Canvas->K2_TextSize(UObject::GetRoboto(), szBuffer, TextScale);
        }
        void DrawCursor(FColor Color)
        {
            DrawFilled(MousePosition.x + 1, MousePosition.y, 1, 17, FColor(0, 0, 0));
            for (unsigned int i = 0; i < 11; i++)
            {
                DrawFilled(MousePosition.x + 2 + i, MousePosition.y + 1 + i, 1, 1, FColor(0, 0, 0));
            }
            DrawFilled(MousePosition.x + 8, MousePosition.y + 12, 5, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 8, MousePosition.y + 13, 1, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 9, MousePosition.y + 14, 1, 2, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 10, MousePosition.y + 16, 1, 2, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 8, MousePosition.y + 18, 2, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 7, MousePosition.y + 16, 1, 2, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 6, MousePosition.y + 14, 1, 2, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 5, MousePosition.y + 13, 1, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 4, MousePosition.y + 14, 1, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 3, MousePosition.y + 15, 1, 1, FColor(0, 0, 0));
            DrawFilled(MousePosition.x + 2, MousePosition.y + 16, 1, 1, FColor(0, 0, 0));
            for (unsigned int i = 0; i < 4; i++)
            {
                DrawFilled(MousePosition.x + 2 + i, MousePosition.y + 2 + i, 1, 14 - (i * 2.f), Color);
            }
            DrawFilled(MousePosition.x + 6, MousePosition.y + 6, 1, 8, Color);
            DrawFilled(MousePosition.x + 7, MousePosition.y + 7, 1, 9, Color);
            for (unsigned int i = 0; i < 4; i++)
            {
                DrawFilled(MousePosition.x + 8 + i, MousePosition.y + 8 + i, 1, 4.f - i, Color);
            }
            DrawFilled(MousePosition.x + 8, MousePosition.y + 14, 1, 4, Color);
            DrawFilled(MousePosition.x + 9, MousePosition.y + 16, 1, 2, Color);
        }
    }
    namespace Menu
    {
        float ControlsX, GroupTabBottom, OffsetY, OldOffsetY = 0;
        int PreviousControl = -1;
        FVector2D Menu_pos = FVector2D(500, 200);
        float GWidth, GHeight = 0;
        bool ControlHover, OpenMenu = true;
        std::unordered_map<string, float> SliderValues;
        bool IsKeyPressed(int key)
        {
            if (GetForegroundWindow() == Engine::GethWnd())
            {
                if (GetAsyncKeyState(key) & 1 && GetAsyncKeyState(key) & 0x8000)
                {
                    return true;
                }
            }
            return false;
        }
        bool IsAsyncKeyPressed(int key)
        {
            if (GetForegroundWindow() == Engine::GethWnd())
            {
                if (GetAsyncKeyState(key) & 0x8000)
                {
                    return true;
                }
            }
            return false;
        }
        bool Window()
        {
            if (!OpenMenu)
                return false;

            static float dragx = 300;
            static float dragy = 300;
            static float Width = 500;
            static float Height = 150;
            static float _width = 475;
            static float _height = 520;
            static bool Dragging = false;
            static int iScreenWidth, iScreenHeight;
            FVector2D ScreenSize = Engine::GetWindowSize();
            bool Click = false;

            if (IsAsyncKeyPressed(VK_LBUTTON))
                Click = true;

            FVector2D MousePos = Draw::MousePosition;
            if (Dragging && !Click)
            {
                Dragging = false;
            }

            if (Dragging && Click)
            {
                Menu_pos.x = MousePos.x - dragx;
                Menu_pos.y = MousePos.y - dragy;
            }

            if (PreviousControl != -1 && !Click)
            {
                PreviousControl = -1;
            }
            if (ControlHover && Click)
            {

            }
            else if ((Draw::MouseInRegion(Menu_pos.x, Menu_pos.y - 10, Width, Height)) && !ControlHover)
            {
                Dragging = true;
                dragx = MousePos.x - Menu_pos.x;
                dragy = MousePos.y - Menu_pos.y;
            }
            else
            {
                ControlHover = false;
            }


            Menu_pos.x = (Menu_pos.x < 0) ? 0 : (Menu_pos.x + Width > ScreenSize.x ? ScreenSize.x - Width : Menu_pos.x);
            Menu_pos.y = (Menu_pos.y < 0) ? 0 : (Menu_pos.y + Height > ScreenSize.y ? ScreenSize.y - Height : Menu_pos.y);
            Draw::DrawFilled(Menu_pos.x - 5, Menu_pos.y - 5, _width + 10, _height + 10 - 25, FColor(5, 5, 5));
            Draw::DrawRect(Menu_pos.x - 5, Menu_pos.y - 5, _width + 10, _height + 10 - 25, FColor(0, 0, 0), 1);
            Draw::DrawFilled(Menu_pos.x, Menu_pos.y, _width, _height - 25, FColor(5, 5, 5));
            Draw::DrawRect(Menu_pos.x - 1, Menu_pos.y - 1, _width + 2, _height + 2 - 25, FColor(0, 0, 0), 1);
            Draw::DrawFilled(Menu_pos.x + 13, Menu_pos.y + 13, _width - 26, 38, FColor(15, 15, 15));
            Draw::DrawRect(Menu_pos.x + 13, Menu_pos.y + 13, _width - 26, 38, FColor(0, 0, 0), 1);
            Draw::DrawFilled(Menu_pos.x + 13, Menu_pos.y + 80 - 25, _width - 26, _height - 68 - 25, FColor(15, 15, 15));
            Draw::DrawRect(Menu_pos.x + 13, Menu_pos.y + 80 - 25, _width - 26, _height - 68 - 25, FColor(0, 0, 0), 1);

            OldOffsetY = 0;
            GWidth = (_width - 60) / 2;
            GHeight = 400;
            return true;
        }
        bool Tab(const string name, FVector2D pos, FVector2D size, bool active)
        {
            static int tab_selected = 0;
            bool isTabHovered = Draw::MouseInRegion(pos.x, pos.y, size.x, size.y);
            if (isTabHovered) { ControlHover = true; }
            Draw::DrawRect(pos.x, pos.y, size.x, size.y, FColor(50, 50, 50), 1);
            if (active)
            {
                Draw::DrawFilled(pos.x, pos.y + 27, size.x, 2.2f, FColor(254, 158, 0));
                Draw::DrawFilled(pos.x, pos.y, size.x, size.y, FColor(9, 9, 9));
            }
            FColor textColor = active ? FColor(255, 255, 255) : FColor(142, 142, 142);
            Draw::DrawMenuText(pos.x + size.x / 2, pos.y + size.y / 2.f, 11, true, true, textColor, L"%hs", name.c_str());
            PreviousControl = -1;
            if (IsAsyncKeyPressed(VK_LBUTTON) && isTabHovered) return true;
            return false;
        }
        bool GroupBox(const string name, float x, float y, float w, float h, bool tab_enable, int* tab, int maxtab = 1)
        {
            y += 80;
            FVector2D text_size = FVector2D(w, h);
            Draw::DrawRect(x, y - 10.f, text_size.x, text_size.y + 10.f, FColor(15, 15, 15), 1);
            Draw::DrawRect(x - 1.f, y - 1.f - 10.f, text_size.x + 2.f, text_size.y + 2.f + 10.f, FColor(11, 11, 11), 1);
            Draw::DrawFilled(x + 1.f, y + 1.f - 10.f, text_size.x, text_size.y + 10.f, FColor(5, 5, 5));
            FColor textColor = Draw::MouseInRegion(x + 1.f, y + 1.f - 10.f, text_size.x, text_size.y + 10.f) ? FColor(142, 142, 142) : FColor(142, 142, 142);
            Draw::DrawFilled(x + 1.f + w / 2.f - text_size.x / 2.f, y + 15.f, text_size.x - 2.f, 1.f, FColor(25, 25, 25));
            Draw::DrawMenuText(x + 35.f, y + 3.f, 11, true, true, textColor, L"%hs", name.c_str());
            if (tab_enable)
            {
                static bool pressed_subtract = false;
                static bool pressed_add = false;
                static float Gety = -7.f;
                static int pressed_tab = 0;
                bool isSliderAddHovered = Draw::MouseInRegion(x + 1.f, y - 8.f + Gety, text_size.x - 2.f, text_size.y);
                bool isSliderSubHovered = Draw::MouseInRegion(x + 1.f, y - 8.f + Gety, text_size.x - 2.f, text_size.y);
                if (isSliderAddHovered || isSliderSubHovered)
                {
                    if (pressed_tab < 1)
                    {
                        // 减少按钮
                        if (!IsAsyncKeyPressed(VK_LBUTTON) && Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f))
                        {
                            if (pressed_subtract)
                            {
                                *tab = (*tab - 1 < 0) ? 0 : *tab - 1;
                            }
                            pressed_subtract = false;
                        }
                        if (IsAsyncKeyPressed(VK_LBUTTON) && Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f) && !pressed_subtract)
                        {
                            pressed_subtract = true;
                        }
                    }
                    else
                    {
                        // 增加按钮
                        if (!IsAsyncKeyPressed(VK_LBUTTON) && Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f))
                        {
                            if (pressed_add)
                            {
                                *tab = (*tab + 1 > maxtab) ? maxtab : *tab + 1;
                            }
                            pressed_add = false;
                        }
                        if (IsAsyncKeyPressed(VK_LBUTTON) && Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f) && !pressed_add)
                        {
                            pressed_add = true;
                        }
                    }
                    //在左侧绘制
                    if (*tab < maxtab)
                    {
                        pressed_tab = 1;
                        Draw::DrawFilled(x + 187.f, y + 5.f + Gety, 15.f, 12.f, Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f) ? FColor(40, 40, 40) : FColor(15, 15, 15));
                        Draw::DrawRect(x + 187.f, y + 5.f + Gety, 15.f, 12.f, FColor(30, 30, 30), 1);
                        Draw::DrawMenuText(x + 190.f, y + 1.f + Gety, 11, false, false, FColor(240, 240, 240), L"%hs", "+");
                    }
                    else
                    {
                        pressed_tab = 0;
                        Draw::DrawFilled(x + 187.f, y + 5.f + Gety, 15.f, 12.f, Draw::MouseInRegion(x + 187.f, y + 5.f + Gety, 15.f, 12.f) ? FColor(40, 40, 40) : FColor(15, 15, 15));
                        Draw::DrawRect(x + 187.f, y + 5.f + Gety, 15.f, 12.f, FColor(30, 30, 30), 1);
                        Draw::DrawMenuText(x + 190.f, y + 1.f + Gety, 11, false, false, FColor(240, 240, 240), L"%hs", "-");
                    }
                }
            }
            else
            {
                *tab = 0;
                maxtab = false;
            }
            OffsetY = y + 20.f;
            ControlsX = x + 8.f;
            GroupTabBottom = (y + text_size.y);
            PreviousControl = -1;
            return true;
        }
        void Keybinds(const std::string& name, int* item)
        {
            if (GroupTabBottom <= OffsetY + 23)
                return;

            bool isKeybindsHovered = Draw::MouseInRegion(ControlsX + 6.f, OffsetY + 16 + 5.f, 140.f, 16 + 5.f);
            if (isKeybindsHovered) { ControlHover = true; }

            static bool bIsGettingKey = false;
            static std::string selectedName;
            static auto keyTime = std::chrono::steady_clock::now();

            if (IsAsyncKeyPressed(VK_LBUTTON) && isKeybindsHovered)
            {
                bIsGettingKey = true;
                selectedName = name;
                keyTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(150);
                for (int i = 0; i < 256; ++i) { GetAsyncKeyState(i); }
            }

            const char* keyName = "None";
            if (bIsGettingKey && selectedName == name)
            {
                keyName = "...";
                bool keySet = false;
                for (int i = 1; i < 254 && !keySet; i++)
                {
                    if (GetAsyncKeyState(i) & 1)
                    {
                        if (i == VK_ESCAPE)
                        {
                            *item = -1;
                        }
                        else
                        {
                            *item = i;
                        }
                        keySet = true;
                    }
                }
                if (keySet) { bIsGettingKey = false; }
            }
            else
            {
                auto it = KeyStrings.find(*item);
                if (it != KeyStrings.end())
                {
                    keyName = it->second.c_str();
                }
            }

            FColor bgColor = isKeybindsHovered ? FColor(40, 40, 40) : FColor(25, 25, 25);
            Draw::DrawMenuText(ControlsX + 5, OffsetY, 11, false, false, FColor(240, 240, 240), L"%hs", name.c_str());
            Draw::DrawFilled(ControlsX + 6, OffsetY + 16 + 5, 140, 18, FColor(15, 15, 15));
            Draw::DrawRect(ControlsX + 6, OffsetY + 16 + 5, 140, 18, bgColor, 1);
            FColor textColor = isKeybindsHovered ? FColor(255, 255, 255) : FColor(182, 182, 182);
            Draw::DrawMenuText(ControlsX + 11, OffsetY + 16 + 5, 11, false, false, textColor, L"%hs", keyName);

            OffsetY += 38 + 5;
            OldOffsetY = OffsetY;
            PreviousControl = 4;
        }
        void CheckBox(const string& name, bool* item, bool sameLine = false)
        {
            if (GroupTabBottom <= OffsetY + 23)
                return;

            static bool pressed = false;
            int sameLineOffset = sameLine ? 95 : 0;
            bool isCheckBoxHovered = Draw::MouseInRegion(ControlsX + 4 + sameLineOffset, OffsetY, 80, 20);
            if (isCheckBoxHovered) { ControlHover = true; }
            if (!IsAsyncKeyPressed(VK_LBUTTON) && isCheckBoxHovered)
            {
                if (pressed)
                {
                    *item = !*item;
                }
                pressed = false;
            }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isCheckBoxHovered && !pressed)
            {
                pressed = true;
            }
            FColor bgColor = isCheckBoxHovered ? FColor(40, 40, 40) : FColor(25, 25, 25);
            FColor textColor = *item ? FColor(240, 240, 240) : FColor(150, 150, 150);
            Draw::DrawFilled(ControlsX + 6 + sameLineOffset, OffsetY + 4, 15, 13, bgColor);
            Draw::DrawFilled(ControlsX + 8 + sameLineOffset, OffsetY + 6, 11, 9, *item ? FColor(254, 158, 0) : FColor(35, 35, 35));
            Draw::DrawMenuText(ControlsX + 25 + sameLineOffset, OffsetY + 2, 11, false, false, textColor, L"%hs", name.c_str());
            OffsetY += sameLine ? 0 : 26;
            OldOffsetY = OffsetY;
            PreviousControl = 0;
        }
        void Slider(int min, int max, const string name, int* item, int step = 1)
        {
            if (GroupTabBottom <= OffsetY + 43)
                return;

            static float sub = 7.f;
            float pixelValue = max / 93.f;
            static bool pressed_subtract = false;
            static bool pressed_add = false;
            // 处理悬停位置
            bool isSliderHovered = Draw::MouseInRegion(ControlsX + 6, OffsetY + 15 + sub, 100, 17);
            bool isSliderAddHovered = Draw::MouseInRegion(ControlsX + 113, OffsetY + 11 + sub + 3, 17, 12);
            bool isSliderSubHovered = Draw::MouseInRegion(ControlsX + 133, OffsetY + 11 + sub + 3, 17, 12);
            if (isSliderHovered || isSliderAddHovered || isSliderSubHovered) { ControlHover = true; }
            // 处理滑块输入
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderHovered) *item = static_cast<int>((Draw::MousePosition.x - (ControlsX + 8)) * pixelValue);
            *item = (*item > max) ? max : (*item < 0) ? 0 : *item;
            // 增加按钮
            if (!IsAsyncKeyPressed(VK_LBUTTON) && isSliderAddHovered) { if (pressed_add) *item = (*item + step > max) ? max : *item + step; pressed_add = false; }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderAddHovered && !pressed_add) pressed_add = true;
            // 减少按钮
            if (!IsAsyncKeyPressed(VK_LBUTTON) && isSliderSubHovered) { if (pressed_subtract) *item = (*item - step < 0) ? 0 : *item - step; pressed_subtract = false; }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderSubHovered && !pressed_subtract) pressed_subtract = true;
            Draw::DrawMenuText(ControlsX + 6.f, OffsetY - 5.f + sub, 11, false, false, FColor(240, 240, 240), L"%hs [%d]", name.c_str(), *item);
            // 绘制滑块和按钮
            Draw::DrawFilled(ControlsX + 6, OffsetY + 15 + sub, 100, 10, isSliderHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawFilled(ControlsX + 6, OffsetY + 15 + sub, (*item / pixelValue), 10, FColor(254, 158, 0));
            Draw::DrawFilled(ControlsX + 6 + (*item / pixelValue), OffsetY + 15 + sub, 7, 10, FColor(81, 81, 81));
            Draw::DrawRect(ControlsX + 6, OffsetY + 15 + sub, 100, 10, FColor(15, 15, 15), 1);
            // 在左侧绘制按钮
            Draw::DrawFilled(ControlsX + 113.f, OffsetY + 11.f + sub + 3.f, 15.f, 12.f, isSliderAddHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawRect(ControlsX + 113.f, OffsetY + 11.f + sub + 3.f, 15.f, 12.f, FColor(40, 40, 40), 1);
            Draw::DrawMenuText(ControlsX + 117.f, OffsetY + 12.f + sub, 10, false, false, FColor(240, 240, 240), L"%hs", "+");
            // 在右侧绘制按钮
            Draw::DrawFilled(ControlsX + 133.f, OffsetY + 11.f + sub + 3.f, 15.f, 12.f, isSliderSubHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawRect(ControlsX + 133.f, OffsetY + 11.f + sub + 3.f, 15.f, 12.f, FColor(40, 40, 40), 1);
            Draw::DrawMenuText(ControlsX + 136.f, OffsetY + 10.f + sub, 11, false, false, FColor(240, 240, 240), L"%hs", "-");
            OldOffsetY = OffsetY;
            OffsetY += 45 - sub;
            PreviousControl = 1;
        }
        void Slider(float min, float max, const string name, float* item, float step = 0.1f)
        {
            if (GroupTabBottom <= OffsetY + 43)
                return;

            static int sub = 7;
            float pixelValue = max / 93.f;
            static bool pressed_subtract = false;
            static bool pressed_add = false;
            // 处理悬停位置
            bool isSliderHovered = Draw::MouseInRegion(ControlsX + 6, OffsetY + 15 + sub, 100, 17);
            bool isSliderAddHovered = Draw::MouseInRegion(ControlsX + 113, OffsetY + 11 + sub + 3, 17, 12);
            bool isSliderSubHovered = Draw::MouseInRegion(ControlsX + 133, OffsetY + 11 + sub + 3, 17, 12);
            if (isSliderHovered || isSliderAddHovered || isSliderSubHovered) { ControlHover = true; }
            // 处理滑块输入
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderHovered) *item = (Draw::MousePosition.x - (ControlsX + 8)) * pixelValue;
            *item = (*item > max) ? max : (*item < 0) ? 0 : *item;
            // 增加按钮
            if (!IsAsyncKeyPressed(VK_LBUTTON) && isSliderAddHovered) { if (pressed_add) *item = (*item + step > max) ? max : *item + step; pressed_add = false; }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderAddHovered && !pressed_add) pressed_add = true;
            // 减少按钮
            if (!IsAsyncKeyPressed(VK_LBUTTON) && isSliderSubHovered) { if (pressed_subtract) *item = (*item - step < 0) ? 0 : *item - step; pressed_subtract = false; }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isSliderSubHovered && !pressed_subtract) pressed_subtract = true;
            char Convert[32];
            snprintf(Convert, sizeof(Convert), "%.2f", *item);
            Convert[sizeof(Convert) - 1] = '\0';
            string itemName = name + " [" + Convert + "]";
            Draw::DrawMenuText(ControlsX + 6, OffsetY - 5 + sub, 11, false, false, FColor(240, 240, 240), L"%hs", itemName.c_str());
            // 绘制滑块和按钮
            Draw::DrawFilled(ControlsX + 6, OffsetY + 15 + sub, 100, 10, isSliderHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawFilled(ControlsX + 6, OffsetY + 15 + sub, (*item / pixelValue), 10, FColor(254, 158, 0));
            Draw::DrawFilled(ControlsX + 6 + (*item / pixelValue), OffsetY + 15 + sub, 7, 10, FColor(81, 81, 81));
            Draw::DrawRect(ControlsX + 6, OffsetY + 15 + sub, 100, 10, FColor(15, 15, 15), 1);
            // 在左侧绘制按钮
            Draw::DrawFilled(ControlsX + 113, OffsetY + 11 + sub + 3, 15, 12, isSliderAddHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawRect(ControlsX + 113, OffsetY + 11 + sub + 3, 15, 12, FColor(40, 40, 40), 1);
            Draw::DrawMenuText(ControlsX + 117, OffsetY + 12 + sub, 10, false, false, FColor(240, 240, 240), L"%hs", "+");
            // 在右侧绘制按钮
            Draw::DrawFilled(ControlsX + 133, OffsetY + 11 + sub + 3, 15, 12, isSliderSubHovered ? FColor(40, 40, 40) : FColor(25, 25, 25));
            Draw::DrawRect(ControlsX + 133, OffsetY + 11 + sub + 3, 15, 12, FColor(40, 40, 40), 1);
            Draw::DrawMenuText(ControlsX + 136, OffsetY + 10 + sub, 11, false, false, FColor(240, 240, 240), L"%hs", "-");
            OldOffsetY = OffsetY;
            OffsetY += 45 - sub;
            PreviousControl = 1;
        }
        void MultiComboBox(const string name, vector<string> itemname, bool* item, float scrollStep = 20.0f)
        {
            if (GroupTabBottom <= OffsetY + 21)
                return;

            static bool multiPressed = false;
            bool pressed = false;
            bool open = false;
            static bool selectedOpened = false;
            static bool clickRest;
            static bool rest;
            static string nameSelected;
            string itemsSelected = "";
            bool isMultiComboBoxHovered = Draw::MouseInRegion(ControlsX + 6.f, OffsetY + 16.f + 5.f, 140.f, 16.f + 5.f);
            if (isMultiComboBoxHovered) { ControlHover = true; }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isMultiComboBoxHovered && !clickRest) { nameSelected = name; pressed = true; clickRest = true; }
            else if (!IsAsyncKeyPressed(VK_LBUTTON) && isMultiComboBoxHovered) { clickRest = false; }
            if (pressed) { if (!rest) { selectedOpened = !selectedOpened; }rest = true; }
            else { rest = false; }
            if (nameSelected == name) { open = selectedOpened; }
            Draw::DrawMenuText(ControlsX + 5, OffsetY, 11, false, false, FColor(240, 240, 240), L"%hs", name.c_str());
            Draw::DrawFilled(ControlsX + 6, OffsetY + 21, 140, 18, FColor(15, 15, 15));
            Draw::DrawRect(ControlsX + 6, OffsetY + 21, 140, 18, FColor(40, 40, 40), 1);
            const float visibleItemCount = 5; // 可见的项目数
            const float itemHeight = 20; // 每个项目的高度
            const float scrollBarWidth = 10; // 滚动条宽度
            float& scrollY = SliderValues[name];
            int startIndex = 0; // 起始显示的项目索引
            if (open)
            {
                float totalHeight = itemname.size() * itemHeight;
                float visibleHeight = visibleItemCount * itemHeight;
                Draw::DrawFilled(ControlsX + 6.f, OffsetY + 45.f, 140.f, visibleHeight, FColor(15, 15, 15));
                Draw::DrawRect(ControlsX + 6.f, OffsetY + 45.f, 140.f, visibleHeight, FColor(40, 40, 40), 1);
                if (totalHeight > visibleHeight) // 如果总高度大于可见高度，需要滚动条
                {
                    // 绘制滚动条背景
                    Draw::DrawFilled(ControlsX + 136, OffsetY + 45, scrollBarWidth, visibleHeight, FColor(20, 20, 20));

                    // 绘制滚动条
                    float scrollBarHeight = visibleHeight / totalHeight * visibleHeight;
                    float maxScrollY = visibleHeight - scrollBarHeight;
                    bool isScrollBarHovered = Draw::MouseInRegion(ControlsX + 136, OffsetY + 45, scrollBarWidth, visibleHeight);

                    if (isScrollBarHovered && IsAsyncKeyPressed(VK_LBUTTON))
                    {
                        float mouseY = Draw::MousePosition.y;
                        scrollY = std::clamp(mouseY - OffsetY - 45 - scrollBarHeight / 2, 0.f, maxScrollY);
                    }

                    float scrollFactor = scrollY / maxScrollY;
                    float scrollOffset = scrollFactor * (totalHeight - visibleHeight);
                    startIndex = static_cast<int>(scrollOffset / itemHeight);

                    Draw::DrawRect(ControlsX + 136, OffsetY + 45 + scrollY, scrollBarWidth, scrollBarHeight, FColor(15, 15, 15), 1);
                    Draw::DrawFilled(ControlsX + 136, OffsetY + 45 + scrollY, scrollBarWidth, scrollBarHeight, FColor(254, 158, 0));
                }
                for (int i = startIndex; i < itemname.size() && i < startIndex + visibleItemCount; i++)
                {
                    bool isHovered = Draw::MouseInRegion(ControlsX + 11.f, OffsetY + 45.f + (i - startIndex) * itemHeight, 110.f, itemHeight - 2.f);
                    if (!IsAsyncKeyPressed(VK_LBUTTON) && isHovered)
                    {
                        if (multiPressed)
                        {
                            item[i] = !item[i];
                            rest = true;
                            clickRest = false;
                        }
                        multiPressed = false;
                    }
                    if (IsAsyncKeyPressed(VK_LBUTTON) && isHovered && !multiPressed)
                    {
                        multiPressed = true;
                    }
                    if (item[i])
                    {
                        Draw::DrawFilled(ControlsX + 6, OffsetY + 45 + (i - startIndex) * itemHeight, totalHeight > visibleHeight ? 130 : 140, itemHeight, FColor(20, 20, 20));
                        Draw::DrawRect(ControlsX + 6, OffsetY + 45 + (i - startIndex) * itemHeight, totalHeight > visibleHeight ? 130 : 140, itemHeight, FColor(40, 40, 40), 1);
                    }
                    else
                    {
                        Draw::DrawRect(ControlsX + 6, OffsetY + 45 + (i - startIndex) * itemHeight, totalHeight > visibleHeight ? 130 : 140, itemHeight, FColor(40, 40, 40), 1);
                    }
                    if (item[i])
                    {
                        Draw::DrawMenuText(ControlsX + 11, OffsetY + 46 + (i - startIndex) * itemHeight, 11, false, false, FColor(240, 240, 240), L"%hs", itemname.at(i).c_str());
                        // 在选定的项下方绘制垂直线
                        float lineStartY = OffsetY + 45 + (i - startIndex) * itemHeight;
                        float lineEndY = OffsetY + 45 + ((i - startIndex + 1) * itemHeight); // 下一个选项的 Y 坐标
                        Draw::DrawLine(ControlsX + 6, lineStartY, ControlsX + 6, lineEndY, FColor(254, 158, 0), 1);
                    }
                    else
                    {
                        Draw::DrawMenuText(ControlsX + 11, OffsetY + 46 + (i - startIndex) * itemHeight, 11, false, false, FColor(210, 210, 210), L"%hs", itemname.at(i).c_str());
                    }
                }

                Draw::DrawMenuText(ControlsX + 92 + 38, OffsetY + 14 + 8, 9, false, false, FColor(240, 240, 240), L"%hs", "▲");
            }
            else {
                Draw::DrawMenuText(ControlsX + 92 + 38, OffsetY + 14 + 5, 15, false, false, FColor(240, 240, 240), L"%hs", "▼");
            }

            bool items = false;
            int lastItem = 0;
            for (int i = 0; i < itemname.size(); i++)
            {
                if (item[i])
                {
                    if (lastItem < i)
                        lastItem = i;
                }
            }
            for (int i = 0; i < itemname.size(); i++)
            {
                if (item[i])
                {
                    items = true;

                    FVector2D TextSize = Draw::GetTextSize(L"%hs", itemsSelected.c_str());
                    FVector2D TextSizeGonaAdd = Draw::GetTextSize(L"%hs", itemname.at(i).c_str());
                    if (TextSize.x + TextSizeGonaAdd.x < 98)
                    {
                        itemsSelected += itemname.at(i) + ((lastItem == i) ? "" : " ");
                    }
                }
            }
            if (!items) itemsSelected = "None";
            Draw::DrawMenuText(ControlsX + 11, OffsetY + 21, 11, false, false, FColor(240, 240, 240), L"%hs", itemsSelected.c_str());
            OldOffsetY = OffsetY;
            OffsetY += open ? 48.f + 5.f + (visibleItemCount * itemHeight) : 38.f + 5.f;
            PreviousControl = 3;
        }
        void ComboBox(const string name, vector<string> itemname, int* item)
        {
            if (GroupTabBottom <= OffsetY + 16 + 5)
                return;

            bool pressed = false;
            bool open = false;
            static bool selectedOpened = false;
            static bool clickRest;
            static bool rest;
            static string nameSelected;
            bool isComBoxHovered = false;
            // 处理悬停位置
            isComBoxHovered = Draw::MouseInRegion(ControlsX + 6, OffsetY + 16 + 5, 140, 16 + 5);
            if (isComBoxHovered)
            {
                ControlHover = true;
            }
            if (IsAsyncKeyPressed(VK_LBUTTON) && isComBoxHovered && !clickRest) { nameSelected = name; pressed = true; clickRest = true; }
            else if (!IsAsyncKeyPressed(VK_LBUTTON) && isComBoxHovered) { clickRest = false; }
            if (pressed) { if (!rest) { selectedOpened = !selectedOpened; }rest = true; }
            else { rest = false; }
            if (nameSelected == name) { open = selectedOpened; }
            Draw::DrawMenuText(ControlsX + 5.f, OffsetY, 11, false, false, FColor(240, 240, 240), L"%hs", name.c_str());
            Draw::DrawFilled(ControlsX + 6.f, OffsetY + 16.f + 5.f, 140.f, 18.f, FColor(15, 15, 15));
            Draw::DrawRect(ControlsX + 6.f, OffsetY + 16.f + 5.f, 140.f, 18.f, FColor(40, 40, 40), 1);
            if (open)
            {
                Draw::DrawFilled(ControlsX + 6.f, OffsetY + 45.f, 140.f, (itemname.size() * 20.f), FColor(15, 15, 15));
                Draw::DrawRect(ControlsX + 6.f, OffsetY + 45.f, 140.f, (itemname.size() * 20.f), FColor(40, 40, 40), 1);
                for (int i = 0; i < itemname.size(); i++)
                {
                    bool isHovered = Draw::MouseInRegion(ControlsX + 11.f, OffsetY + 45.f + (i * 21.f), 140.f, 18.f);
                    bool isSelected = (*item == i);
                    if (IsAsyncKeyPressed(VK_LBUTTON) && isHovered)
                    {
                        *item = i;
                        open = false;
                        rest = true;
                        clickRest = false;
                        selectedOpened = false;
                    }
                    // 绘制项的背景
                    Draw::DrawRect(ControlsX + 6, OffsetY + 45 + (i * 20), 140, 20, FColor(40, 40, 40), 1);
                    if (isSelected)
                    {
                        Draw::DrawFilled(ControlsX + 6, OffsetY + 45 + (i * 20), 140, 20, FColor(20, 20, 20));
                        Draw::DrawRect(ControlsX + 6, OffsetY + 45 + (i * 20), 140, 20, FColor(40, 40, 40), 1);
                    }
                    else
                    {
                        Draw::DrawRect(ControlsX + 6, OffsetY + 45 + (i * 20), 140, 20, FColor(40, 40, 40), 1);
                    }
                    // 绘制文本
                    if (isSelected)
                    {
                        Draw::DrawMenuText(ControlsX + 11, OffsetY + 45 + (i * 21), 11, false, false, FColor(240, 240, 240), L"%hs", itemname.at(i).c_str());
                        // 在选定的项下方绘制垂直线
                        float lineStartY = OffsetY + 45 + (i * 20);
                        float lineEndY = OffsetY + 45 + ((i + 1) * 20); // 下一个选项的 Y 坐标
                        Draw::DrawLine(ControlsX + 6, lineStartY, ControlsX + 6, lineEndY, FColor(254, 158, 0), 1);
                    }
                    else
                    {
                        Draw::DrawMenuText(ControlsX + 11, OffsetY + 45 + (i * 21), 11, false, false, FColor(210, 210, 210), L"%hs", itemname.at(i).c_str());
                    }
                }
                Draw::DrawMenuText(ControlsX + 92 + 38, OffsetY + 14 + 8, 9, false, false, FColor(240, 240, 240), L"%hs", "▲");
            }
            else {
                Draw::DrawMenuText(ControlsX + 92 + 38, OffsetY + 14 + 5, 15, false, false, FColor(240, 240, 240), L"%hs", "▼");
            }
            Draw::DrawMenuText(ControlsX + 11, OffsetY + 16 + 5, 11, false, false, FColor(240, 240, 240), L"%hs", itemname.at(*item).c_str());

            OldOffsetY = OffsetY;
            OffsetY += open ? 48 + 5.f + (itemname.size() * 18.f) : 38.f + 5.f;
            PreviousControl = 2;
        }

        void Init()
        {
            if (IsKeyPressed(VK_F1)) { OpenMenu = !OpenMenu; }
            if (Window())
            {
                static int tab = 0;
                float GRoup1 = Menu_pos.x + 23.f;
                float GRoup2 = Menu_pos.x + 240.f;
                float GY = Menu_pos.y - 10.f;
                if (Tab(xorstr("透视设置"), FVector2D{ Menu_pos.x + 45.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 0)) tab = 0;
                if (Tab(xorstr("自瞄设置"), FVector2D{ Menu_pos.x + 140.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 1)) tab = 1;
                if (Tab(xorstr("功能设置"), FVector2D{ Menu_pos.x + 235.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 2)) tab = 2;
                if (Tab(xorstr("按键设置"), FVector2D{ Menu_pos.x + 330.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 3)) tab = 3;

                if (tab == 0)
                {
                    static int main_tab, misc_tab;
                    if (GroupBox(xorstr("主要设置"), GRoup1, GY, GWidth, GHeight, false, &main_tab))
                    {
                        if (main_tab == 0)
                        {
                           
                            CheckBox(xorstr("烽火模式"), &Menu::烽火模式, true);
                            CheckBox(xorstr("战场模式"), &Menu::战场模式);
                            CheckBox(xorstr("绘制矩形"), &Menu::Box2D, true);
                            CheckBox(xorstr("显示骨骼"), &Menu::DrawBone);

                            CheckBox(xorstr("显示名称"), &Menu::DrawName, true);
                            CheckBox(xorstr("显示视线"), &Menu::LosLine);
                            CheckBox(xorstr("显示雷达"), &Menu::DrawRadar, true);
                            CheckBox(xorstr("显示血条"), &Menu::DrawBlood);

                            CheckBox(xorstr("3D方框"), &Menu::DrawBox3D, true);
                            CheckBox(xorstr("雷达向标"), &Menu::DrawTriangle);
                            CheckBox(xorstr("显示距离"), &Menu::Playerdistance, true);
                            CheckBox(xorstr("显示团队"), &Menu::DrawTeamId);


                            CheckBox(xorstr("显魔法阵"), &Menu::ShowMagicCircle, true);
                            CheckBox(xorstr("显示容器"), &Menu::容器);
                            CheckBox(xorstr("显示盒子"), &Menu::盒子容器, true);
                            CheckBox(xorstr("显示物资"), &Menu::物资);
                        }
                        else if (main_tab == 1)
                        {

                        }
                    }
                    if (GroupBox(xorstr("杂项设置"), GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                    {
                        if (misc_tab == 0)
                        {
                            Slider(0, 100000, xorstr("价值过滤"), &Menu::价值);
                            Slider(0, 500, xorstr("容器距离"), &Menu::容器距离);
                            Slider(0, 500, xorstr("物资距离"), &Menu::物资距离);
                            Slider(0, 500, xorstr("盒子距离"), &Menu::盒子距离);
                        }
                        else if (misc_tab == 1)
                        {

                        }
                    }
                }
                else if (tab == 1)
                {
                    static int main_tab, misc_tab;
                    if (GroupBox(xorstr("主要设置"), GRoup1, GY, GWidth, GHeight, false, &main_tab))
                    {
                        if (main_tab == 0)
                        {
                            CheckBox(xorstr("自瞄开关"), &Menu::OpenAimbot);
                        }
                        else if (main_tab == 1)
                        {

                        }
                    }
                    if (GroupBox(xorstr("杂项设置"), GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                    {
                        if (misc_tab == 0)
                        {
                            Slider(0, 500, xorstr("自瞄范围"), &Menu::SilentRange);
                            ComboBox(xorstr("自瞄模式"), Menu::AimBotMod, &Menu::AimMod);
                            ComboBox(xorstr("自瞄部位"), Menu::AimBotPos, &Menu::AimBith);
                        }
                        else if (misc_tab == 1)
                        {

                        }
                    }
                }
                else if (tab == 2)
                {
                    static int main_tab, misc_tab;
                    if (GroupBox(xorstr("主要设置"), GRoup1, GY, GWidth, GHeight, false, &main_tab))
                    {
                        if (main_tab == 0)
                        {

                        }
                        else if (main_tab == 1)
                        {

                        }
                    }
                    if (GroupBox(xorstr("杂项设置"), GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                    {
                        if (misc_tab == 0)
                        {

                        }
                        else if (misc_tab == 1)
                        {

                        }
                    }
                }
                else if (tab == 3)
                {
                    static int main_tab, misc_tab;
                    if (GroupBox(xorstr("主要设置"), GRoup1, GY, GWidth, GHeight, false, &main_tab))
                    {
                        if (main_tab == 0)
                        {
                            Keybinds(xorstr("自瞄锁定"), &Menu::AimBotKey);
                        }
                        else if (main_tab == 1)
                        {

                        }
                    }
                    if (GroupBox(xorstr("杂项设置"), GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                    {
                        if (misc_tab == 0)
                        {

                        }
                        else if (misc_tab == 1)
                        {

                        }
                    }
                }


                Draw::DrawCursor(FColor(255, 124, 79));
            }
        }

    }


	void Initialize()
	{
		RenderHook.Initialize(Engine::GetEngine()->GameViewport);	
		RenderHook.Bind(95, hkPostRender);
       HookInitialize();
	}

	void hkPostRender(void* GameViewport, UCanvas* Canvas)
	{
        UCanvas::Canvas = Canvas;
        Menu::Init();
        AimBotText::RenderText(Canvas);
        Actors::PlayerStart(Canvas);
        Actors::ItemStart(Canvas);
        return RenderHook.GetOriginal<FN>(95)(GameViewport, Canvas);
	}
}