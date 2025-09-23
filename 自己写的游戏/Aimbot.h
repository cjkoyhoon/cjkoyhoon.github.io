#pragma once
#include"engine.h"
#include "Tools.h"
#include"hooks.h"
class Aimbot
{
public:
	static Aimbot& GetInstance() {
		static Aimbot Instance;
		return Instance;
	}
	void PushTarget(float distance, ASolarCharacter* PTR, ASolarCharacter* Local, UCanvas* Canvas);

	void PopTarget();
	bool CanAim();
	void MemoryAimbot();
	FRotator GetAimRotation();

	float GetAimDistance();
private:

	uint32_t m_BoneNum = 0; // 代表当前人物骨骼的数量 完全可以用骨骼数量来区分使用哪套骨骼

	FVector HeadPos{};

	FVector2D ScreenHandPoint{};
	Aimbot() {};
	Aimbot(Aimbot&) {};
	ASolarCharacter* TempEnemy = NULL;
	ASolarCharacter* TempLocal = NULL;
	FVector2D TempPos2D;
	double TempPreviousDistance = 100000.f;

	UCanvas* Render = NULL;
	FVector* AimBonePos = NULL;
	FVector2D EnemyPos2D;
	FVector HeadAimPos{};
	ASolarCharacter* Enemy = NULL;

	FVector AimPos{};
	ASolarCharacter* LocalPlayer = NULL;

	double PreviousDistance = 100000.f;


};