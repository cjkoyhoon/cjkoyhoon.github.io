#pragma once
#include"base.h"
#include"Class.h"
namespace Utils
{
	void StartConsole();

	string WstrToUtf8(const wstring Wstr);

	 int ContainsNaN(FVector V);

	 float Fmod(float X, float Y);

	 void SinCos(float* OutSin, float* OutCos, float Radians);

	class VTableHook
	{
	public:

		void Initialize(void* pTarget);

		void Bind(uint32_t Index, void* Function);

		void UnBind(uint32_t Index);

		void UnAllBind();

		template <typename T>
		T GetOriginal(uint32_t Index)
		{
			return (T)oVTable[Index];
		}

	private:

		uint32_t CalcVTableSize();

		void* Target = NULL;
		void** VTable = NULL;
		void** oVTable = NULL;
	};

	class Pattern
	{
	public:
		Pattern() = default;
		Pattern(uint64_t Address) : Address(Address) {}
		static Pattern FindPattern(const char* pattern);
		Pattern add(uint32_t val);
		Pattern sub(uint32_t val);
		Pattern Absolute();
		Pattern Deref();
		uint64_t get() const;
	private:
		uint64_t Address = 0;

	};

	

	


}
