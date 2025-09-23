#ifndef HOOK_H
#define HOOK_H

#include "Base.h"

void HookInitialize();

class Int3Hook
{
public:
    void Initialize(void* HookAddr, int Size, PVECTORED_EXCEPTION_HANDLER VehFunc)
    {
        hVEH = AddVectoredExceptionHandler(1, VehFunc);//����VEH�쳣
        this->HookAddr = (BYTE*)HookAddr;
        oHookbyte = *(BYTE*)HookAddr;//����ԭʼ�ֽ�
        JmpAddr = (BYTE*)(this->HookAddr + Size);//������һ��ָ��ĵ�ַ
        oJmpbyte = *(BYTE*)JmpAddr;
    }
    void Hook()
    {
        DWORD Protect;
        VirtualProtect(HookAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//�ɶ���д
        *HookAddr = 0xCC;//int3�쳣hook
        VirtualProtect(HookAddr, 1, Protect, &Protect);//��ԭ����
    }
    void HookJmpAddr()
    {
        DWORD Protect;
        VirtualProtect((BYTE*)JmpAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//�ɶ���д
        *(BYTE*)JmpAddr = 0xCC;//int3�쳣hook
        VirtualProtect((BYTE*)JmpAddr, 1, Protect, &Protect);//��ԭ����
    }
    void UnHook()
    {
        DWORD Protect;
        VirtualProtect(HookAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//�ɶ���д
        *HookAddr = oHookbyte;//��ԭԭʼ�ֽ�
        VirtualProtect(HookAddr, 1, Protect, &Protect);//��ԭ����

    }
    void UnHookJmpAddr()
    {
        DWORD Protect;
        VirtualProtect((BYTE*)JmpAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//�ɶ���д
        *(BYTE*)JmpAddr = oJmpbyte;//��ԭԭʼ�ֽ�
        VirtualProtect((BYTE*)JmpAddr, 1, Protect, &Protect);//��ԭ����
    }
    void* GetHookAddr()
    {
        return HookAddr;
    }
    BYTE* GetJmpAddr()
    {
        return JmpAddr;
    }
private:
    BYTE oHookbyte;//ԭʼ�ֽ�
    BYTE oJmpbyte;
    void* hVEH;//�쳣���������
    BYTE* HookAddr;//Hook��ַ
    BYTE* JmpAddr;//��һ��ָ��ĵ�ַ
};

#endif // !HOOK_H