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
            if (Hooks::Menu::Tab("͸������", FVector2D{ Menu_pos.x + 45.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 0)) tab = 0;
            if (Hooks::Menu::Tab("��������", FVector2D{ Menu_pos.x + 140.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 1)) tab = 1;
            if (Hooks::Menu::Tab("��������", FVector2D{ Menu_pos.x + 235.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 2)) tab = 2;
            if (Hooks::Menu::Tab("��������", FVector2D{ Menu_pos.x + 330.f, Menu_pos.y + 20.f }, FVector2D{ 95.f, 26.f }, tab == 3)) tab = 3;

            if (tab == 0)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("��Ҫ����", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::CheckBox("���ģʽ", &Hooks::Menu::���ģʽ, true);
                        Hooks::Menu::CheckBox("ս��ģʽ", &Hooks::Menu::ս��ģʽ);
                        Hooks::Menu::CheckBox("2D����", &Hooks::Menu::Box2D, true);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::DrawBone);

                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::DrawName, true);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::LosLine);
                        Hooks::Menu::CheckBox("��ʾ�״�", &Hooks::Menu::DrawRadar, true);
                        Hooks::Menu::CheckBox("��ʾѪ��", &Hooks::Menu::DrawBlood);

                        Hooks::Menu::CheckBox("3D����", &Hooks::Menu::DrawBox3D, true);
                        Hooks::Menu::CheckBox("�״����", &Hooks::Menu::DrawTriangle);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::Playerdistance, true);
                        Hooks::Menu::CheckBox("��ʾ�Ŷ�", &Hooks::Menu::DrawTeamId);


                        Hooks::Menu::CheckBox("��ħ����", &Hooks::Menu::ShowMagicCircle, true);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::����);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::��������, true);
                        Hooks::Menu::CheckBox("��ʾ����", &Hooks::Menu::����);


                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("��������", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                {
                    if (misc_tab == 0)
                    {
                        Hooks::Menu::Slider(0, 100000, "��ֵ����", &Hooks::Menu::��ֵ);
                        Hooks::Menu::Slider(0, 500, "��������", &Hooks::Menu::��������);
                        Hooks::Menu::Slider(0, 500, "���ʾ���", &Hooks::Menu::���ʾ���);
                        Hooks::Menu::Slider(0, 500, "���Ӿ���", &Hooks::Menu::���Ӿ���);
                    }
                    else if (misc_tab == 1)
                    {

                    }
                }
            }
            else if (tab == 1)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("��Ҫ����", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::CheckBox("���鿪��", &Hooks::Menu::OpenAimbot);
                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("��������", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
                {
                    if (misc_tab == 0)
                    {
                        Hooks::Menu::Slider(0, 500, "���鷶Χ", &Hooks::Menu::SilentRange);
                        Hooks::Menu::ComboBox("����ģʽ", Hooks::Menu::AimBotMod, &Hooks::Menu::AimMod);
                        Hooks::Menu::ComboBox("���鲿λ", Hooks::Menu::AimBotPos, &Hooks::Menu::AimBith);
                    }
                    else if (misc_tab == 1)
                    {

                    }
                }
            }
            else if (tab == 2)
            {
                static int main_tab, misc_tab;
                if (Hooks::Menu::GroupBox("��Ҫ����", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {

                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("��������", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
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
                if (Hooks::Menu::GroupBox("��Ҫ����", GRoup1, GY, GWidth, GHeight, false, &main_tab))
                {
                    if (main_tab == 0)
                    {
                        Hooks::Menu::Keybinds("��������", &Hooks::Menu::AimBotKey);
                    }
                    else if (main_tab == 1)
                    {

                    }
                }
                if (Hooks::Menu::GroupBox("��������", GRoup2, GY, GWidth, GHeight, false, &misc_tab))
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

