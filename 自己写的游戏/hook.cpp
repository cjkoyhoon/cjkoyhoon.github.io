#include "hook.h"
#include "engine.h"
#include "aimbot.h"
#include"Hooks.h"
#include"Utils.h"
Int3Hook Hook;

LONG NTAPI AimbotException(_EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo->ExceptionRecord->ExceptionAddress == Hook.GetHookAddr())
    {
        Hook.UnHook();
        Hook.HookJmpAddr();
        Aimbot& Instance = Aimbot::GetInstance();
        FVector* SpawnLocation = (FVector*)(ExceptionInfo->ContextRecord->Rcx);
        if (SAFE_PTR(SpawnLocation))
        {
            bool IsAim = Instance.CanAim();
            if (IsAim && Hooks::Menu::OpenAimbot && Hooks::Menu::AimMod == 1)
            {
                float Distance = Instance.GetAimDistance();
                FRotator AimRota = Instance.GetAimRotation();
                FVector AimVector = UKismetStringLibrary::GetForwardVector(&AimRota);
                if (Hooks::Menu::SilentRange >= Distance && AimVector.x != 0 && AimVector.y != 0)
                {
                    if (GetAsyncKeyState(Hooks::Menu::AimBotKey))
                    {
                        SpawnLocation->x = AimVector.x;
                        SpawnLocation->y = AimVector.y;
                        SpawnLocation->z = AimVector.z;
                    }
                }
            }

        }
       
        return -1;
    }
    else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == Hook.GetJmpAddr())
    {
        Hook.Hook();
        Hook.UnHookJmpAddr();
        return -1;
    }
    return 0;
}

void HookInitialize()
{
    ULONG64 SpawAddress = Utils::Pattern::FindPattern("E8 ?? ?? ?? ?? 48 8B BC 24 18 04 00 00 48 8B F0 B9 0C 00 00 00 F3 A4 4C 8D 8C 24 ?? ?? ?? ??").get();
    Hook.Initialize((LPVOID)(SpawAddress), 5, AimbotException);
    Hook.Hook();
}
