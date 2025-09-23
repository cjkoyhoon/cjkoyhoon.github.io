#pragma once
#include"Hooks.h"


namespace UMenu
{
    FVector2D Menu_pos = FVector2D(500, 200);
    float GWidth, GHeight = 0;
    bool OpenMenu = true;

  /*  void MenuInit()
    {
        if (Hooks::Menu::IsKeyPressed(VK_F1)) { OpenMenu = !OpenMenu; }
        if (Hooks::Menu::Window())
        {
            static int tab = 0;
            float GRoup1 = Menu_pos.x + 23.f;
            float GRoup2 = Menu_pos.x + 240.f;
            float GY = Menu_pos.y - 10.f;
            if (Hooks::Menu::Tab("透视设置", FVector2D{ Menu_pos.x + 45.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 0)) tab = 0;
            if (Hooks::Menu::Tab("自瞄设置", FVector2D{ Menu_pos.x + 140.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 1)) tab = 1;
            if (Hooks::Menu::Tab("功能设置", FVector2D{ Menu_pos.x + 235.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 2)) tab = 2;
            if (Hooks::Menu::Tab("按键设置", FVector2D{ Menu_pos.x + 330.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 3)) tab = 3;

            if (tab == 0)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("主要设置", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::CheckBox("烽火模式", &Hooks::Menu::烽火模式, true);
                        Hooks::Menu::CheckBox("战场模式", &Hooks::Menu::战场模式);
                        Hooks::Menu::CheckBox("2D矩形", &Hooks::Menu::Box2D, true);
                        Hooks::Menu::CheckBox("显示骨骼", &Hooks::Menu::DrawBone);

                        Hooks::Menu::CheckBox("显示名称", &Hooks::Menu::DrawName, true);
                        Hooks::Menu::CheckBox("显示视线", &Hooks::Menu::LosLine);
                        Hooks::Menu::CheckBox("显示雷达", &Hooks::Menu::DrawRadar, true);
                        Hooks::Menu::CheckBox("显示血条", &Hooks::Menu::DrawBlood);

                        Hooks::Menu::CheckBox("3D矩形", &Hooks::Menu::DrawBox3D, true);
                        Hooks::Menu::CheckBox("雷达向标", &Hooks::Menu::DrawTriangle);
                        Hooks::Menu::CheckBox("显示距离", &Hooks::Menu::Playerdistance, true);
                        Hooks::Menu::CheckBox("显示团队", &Hooks::Menu::DrawTeamId);


                        Hooks::Menu::CheckBox("显魔法阵", &Hooks::Menu::ShowMagicCircle, true);
                        Hooks::Menu::CheckBox("显示容器", &Hooks::Menu::容器);
                        Hooks::Menu::CheckBox("显示盒子", &Hooks::Menu::盒子容器, true);
                        Hooks::Menu::CheckBox("显示物资", &Hooks::Menu::物资);


                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("杂项设置", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                {
                    if (misc_tab == 0)
                    {
                        Hooks::Menu::Slider(0, 100000, "价值过滤", &Hooks::Menu::价值);
                        Hooks::Menu::Slider(0, 500, "容器距离", &Hooks::Menu::容器距离);
                        Hooks::Menu::Slider(0, 500, "物资距离", &Hooks::Menu::物资距离);
                        Hooks::Menu::Slider(0, 500, "盒子距离", &Hooks::Menu::盒子距离);
                    }
                    else if (misc_tab == 1)
                    {

                    }
                }
            }
            else if (tab == 1)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("主要设置", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::CheckBox("自瞄开关", &Hooks::Menu::OpenAimbot);
                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("杂项设置", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                {
                    if (misc_tab == 0)
                    {
                        Hooks::Menu::Slider(0, 500, "自瞄范围", &Hooks::Menu::SilentRange);
                        Hooks::Menu::ComboBox("自瞄模式", Hooks::Menu::AimBotMod, &Hooks::Menu::AimMod);
                        Hooks::Menu::ComboBox("自瞄部位", Hooks::Menu::AimBotPos, &Hooks::Menu::AimBith);
                    }
                    else if (misc_tab == 1)
                    {

                    }
                }
            }
            else if (tab == 2)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("主要设置", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {

                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("杂项设置", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
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
                if (Hooks::Menu::GroupBox("主要设置", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::Keybinds("自瞄锁定", &Hooks::Menu::AimBotKey);
                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("杂项设置", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                {
                    if (misc_tab == 0)
                    {

                    }
                    else if (misc_tab == 1)
                    {

                    }
                }
            }


            Hooks::Draw::DrawCursor(FColor(255, 124, 79));
        }


    }*/
	

}

