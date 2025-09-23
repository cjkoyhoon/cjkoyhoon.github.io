#pragma once
#include"Class.h"
#include"Hooks.h"
#include"Render.h"
#include"Aimbot.h"

namespace Actors
{

    void PlayerStart(UCanvas* Canvas)
    {
        UWorld* World = Engine::GetEngine()->GameViewport->World;
        if (!SAFE_PTR(World)) return;
        ASolarCharacter* LocalPlayer = nullptr;
        APlayerController* PlayerController = nullptr;
        if (SAFE_PTR(World->OwningGameInstance))
        {
            LocalPlayer = World->OwningGameInstance->GetPlayer();
            PlayerController = World->OwningGameInstance->GetPlayerController();
            PlayerController->GetMousePosition(Hooks::Draw::MousePosition);
        }
        TArray<ASolarCharacter*> Actors;
        UGameplayStatics::GetAllActorsOfClass(World, UObject::GetPlayerClass(), &Actors);

        if (SAFE_PTR(PlayerController) && SAFE_PTR(LocalPlayer))
        {
            if (Actors.Count <= 0) return;
            for (size_t i = 0; i < Actors.Count; ++i)
            {
                if (!SAFE_PTR(Actors.Data[i])) continue;
                ASolarCharacter* Player = Actors.Data[i];
                if (Player->GetController() == PlayerController) {
                    LocalPlayer = Player;
                }
                if (!SAFE_PTR(Player)) continue;
                if (Player == LocalPlayer) continue;
                if (SAFE_PTR(LocalPlayer->PlayerState) && SAFE_PTR(Player->PlayerState))
                {
                    if (Hooks::Menu::烽火模式)
                    {
                        Hooks::Menu::战场模式 = false;
                    }
                    else if (Hooks::Menu::战场模式)
                    {
                        Hooks::Menu::烽火模式 = false;
                    }
                    if (Hooks::Menu::烽火模式)
                    {
                        if (LocalPlayer->PlayerState->GetTeamID() == Player->PlayerState->GetTeamID())
                        {
                            continue;
                        }
                    }
                    else if (Hooks::Menu::战场模式)
                    {

                        if (LocalPlayer->PlayerState->GetCamp() == Player->PlayerState->GetCamp())
                        {
                            continue;
                        }
                    }

                }
                if (Player->GetHealth() <= 0) continue;

                bool bHasLineOfSight = false;
                if (SAFE_PTR(PlayerController))
                {
                    bHasLineOfSight = PlayerController->LineOfSightTo(Player, FVector());
                }

                PlayerRender RenderObject(Player, LocalPlayer, Canvas);
                FLinearColor RenderColor = bHasLineOfSight ? FLinearColor(255, 0, 0) : Hooks::Menu::BoneColor;
                if (Hooks::Menu::DrawBone) RenderObject.DrawBone(RenderColor);
                if (Hooks::Menu::DrawName) RenderObject.DrawName();
                if (Hooks::Menu::LosLine) RenderObject.DrawLosLine(Hooks::Menu::ColorLosLine);
                if (Hooks::Menu::Box2D) RenderObject.DrawBox2D(Hooks::Menu::test_color);
                if (Hooks::Menu::ShowMagicCircle) RenderObject.ShowMagicCircle();
                if (Hooks::Menu::DrawRadar) RenderObject.DrawRadar();
                if (Hooks::Menu::DrawBlood) RenderObject.DrawBlood();
                if (Hooks::Menu::DrawBox3D) RenderObject.DrawBox3D(Hooks::Menu::test_color);
                if (Hooks::Menu::DrawTriangle) RenderObject.DrawTriangle(Hooks::Menu::Triangle_color);
                if (Hooks::Menu::Playerdistance) RenderObject.DrawPlayerdistance();
                if (Hooks::Menu::DrawTeamId) { RenderObject.DrawPlayerTeamId(); }

                if (bHasLineOfSight)
                {
                    Aimbot::GetInstance().PushTarget(Hooks::Menu::SilentRange, Player, LocalPlayer, Canvas);
                }
            }
            Aimbot::GetInstance().PopTarget();
            if (GetForegroundWindow() == reinterpret_cast<HWND>(Engine::GethWnd()) && Hooks::Menu::OpenAimbot)
            {
                if (SAFE_PTR(Canvas))
                {
                    Canvas->K2_DrawPolygon({ Engine::Width, Engine::Height }, { Hooks::Menu::SilentRange, Hooks::Menu::SilentRange }, 20, FLinearColor(255 / 255, 255 / 255, 255), 1.5);
                }
                Aimbot::GetInstance().MemoryAimbot();
            }

    
        }
    }


    void ItemStart(UCanvas* Canvas)
    {
        UWorld* World = Engine::GetEngine()->GameViewport->World;
        if (!SAFE_PTR(World)) return;
        APlayerController* PlayerController = nullptr;
        if (SAFE_PTR(World->OwningGameInstance))
        {
            PlayerController = World->OwningGameInstance->GetPlayerController();
        }

        if (SAFE_PTR(PlayerController))
        {
            TArray<AActor*> Actors;
            UGameplayStatics::GetAllIteamsOfClass(World, UObject::GetIteamClass(), &Actors);

            if (SAFE_PTR_SIZE(Actors.Data, 10))
            {
                for (size_t i = 0; i < Actors.Count; i++)
                {
                    if (SAFE_PTR(Actors.Data[i]) && SAFE_PTR(Actors.Data[i]->RootComponent))
                    {
                        AActor* PActor = Actors.Data[i];
                        IteamRender IteamRenderObject(PActor, PlayerController, Canvas);
                        if (Hooks::Menu::容器) { IteamRenderObject.DrawAInventoryPickup_OpenBox(); }
                        if (Hooks::Menu::盒子容器) { IteamRenderObject.DrawInventory_DeadBody(); }
                        if (Hooks::Menu::物资) { IteamRenderObject.DrawBP_InventoryPickup_(); }

                    }

                }


            }


        }


    }


}



