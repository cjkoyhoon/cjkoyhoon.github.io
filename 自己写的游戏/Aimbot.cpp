#include"Aimbot.h"


void Aimbot::PushTarget(float distance, ASolarCharacter* PTR, ASolarCharacter* Local, UCanvas* Canvas)
{
	Render = Canvas;
	LocalPlayer = Local;
	TArray<uint64_t> BoneNames = PTR->Mesh->GetAllSocketNames();
	m_BoneNum = BoneNames.Count;
	AimBonePos = new FVector[m_BoneNum];
	for (uint32_t i = 0; i < m_BoneNum; i++)
	{
		BoneIndex* Idx = PTR->Mesh->GetBoneIndex(m_BoneNum);
		if (Idx == nullptr) {
			continue;
		}
		AimBonePos[i] = PTR->Mesh->GetSocketTransform(BoneNames.Data[i]);
		if (Idx->head < 0)
			continue;
		if (Hooks::Menu::AimBith == 0)
			HeadPos = AimBonePos[Idx->head];
		else if (Hooks::Menu::AimBith == 1)
			HeadPos = AimBonePos[Idx->pelvis];
		else if (Hooks::Menu::AimBith == 2)
			HeadPos = AimBonePos[Idx->foot_r];
		if (Local->GetController()->WorldToScreen(HeadPos, ScreenHandPoint))
		{
			float Distance = sqrtf(powf(ScreenHandPoint.x - Engine::Width, 2) + powf(ScreenHandPoint.y - Engine::Height, 2));
			if (TempPreviousDistance > Distance && Distance < distance)
			{
				HeadAimPos = HeadPos;
				TempEnemy = PTR;
				TempPos2D = ScreenHandPoint;
				TempPreviousDistance = Distance;
			}
		}

	}


}


void Aimbot::PopTarget()
{
	AimPos = HeadAimPos;
	Enemy = TempEnemy;
	EnemyPos2D = TempPos2D;
	PreviousDistance = TempPreviousDistance;
	RtlZeroMemory(&TempPos2D, sizeof(TempPos2D));

	TempEnemy = NULL;
	TempPreviousDistance = 100000.f;
	HeadAimPos = {};
}

float Aimbot::GetAimDistance()
{
	return PreviousDistance;
}
bool Aimbot::CanAim()
{
	if (!Enemy)
		return false;

	return true;
}

void Aimbot::MemoryAimbot()
{
	if (CanAim())
	{
		if (EnemyPos2D.x != 0 && EnemyPos2D.y != 0) {
			Render->K2_DrawLine({ Engine::Width, Engine::Height }, { EnemyPos2D.x,EnemyPos2D.y }, 1.5, FLinearColor(255, 255, 255));
		}
		if (Hooks::Menu::AimMod == 0)
		{
			if (GetAsyncKeyState(Hooks::Menu::AimBotKey))
			{
				FRotator AimRota = Aimbot::GetInstance().GetAimRotation();
				LocalPlayer->GetController()->Pitch = AimRota.yaw;
				LocalPlayer->GetController()->Yaw = AimRota.pitch;


			}

		}	
	}
}



FRotator Aimbot::GetAimRotation()
{
	FVector EnemyPos = AimPos;
	FVector CameraPos = LocalPlayer->GetController()->PlayerCameraManager->GetCameraLocation();

	FVector diff{ EnemyPos.x - CameraPos.x, EnemyPos.y - CameraPos.y,EnemyPos.z - CameraPos.z, };

	FRotator AimRotation;
	AimRotation.yaw = atan2f(diff.y, diff.x) * 180 / (float)3.1415926;
	AimRotation.pitch = atan2f(diff.z, sqrt(diff.x * diff.x + diff.y * diff.y)) * 180 / (float)3.1415926;

	return AimRotation;
}