// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "base.h"
#include"Utils.h"
#include"Engine.h"
#include"Hooks.h"

void MainThread()
{
    //Utils::StartConsole();
    Engine::Intialize();
    Hooks::Initialize();

  

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        MainThread();


    }
    return TRUE;
}

