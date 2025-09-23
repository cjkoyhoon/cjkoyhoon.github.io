#include "Tools.h"

EXTERN_C DWORD Asm_Call(...);
EXTERN_C DWORD FuncIndex = 0;

namespace Tools
{

	DWORD GetFuncIndex()
	{

		HMODULE hModule = GetModuleHandleA("win32u.dll");
		if (hModule == NULL) return 0;
		FARPROC PFunc = GetProcAddress(hModule, "NtUserSendInput");

		return *(DWORD*)((DWORD64)PFunc + 4);
	}

	DWORD NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize)
	{
		if (!FuncIndex)
		{
			FuncIndex = GetFuncIndex();
		}

		return Asm_Call(cInputs, pInputs, cbSize);
	}

	DWORD MouseInput(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
	{
		INPUT Input[3] = { 0 };
		Input[0].type = INPUT_MOUSE;
		Input[0].mi.dx = dx;
		Input[0].mi.dy = dy;
		Input[0].mi.mouseData = dwData;
		Input[0].mi.dwFlags = dwFlags;
		Input[0].mi.time = 0;
		Input[0].mi.dwExtraInfo = dwExtraInfo;

		return NtUserSendInput(1, (LPINPUT)&Input, sizeof(INPUT));
	}


}