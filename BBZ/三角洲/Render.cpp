#include "render.h"
#include "utils.h"
#include"engine.h"
#include"Hooks.h"
#include <chrono>
auto startTime = std::chrono::high_resolution_clock::now();

PlayerRender::PlayerRender(ASolarCharacter* Enemy, ASolarCharacter* LocalPlayer, UCanvas* Canvas)
{
	RendCanvas = Canvas;
	m_Enemy = Enemy;
	m_LocalPlayer = LocalPlayer;

	TArray<uint64_t> BoneNames = m_Enemy->Mesh->GetAllSocketNames();
	m_BoneNum = BoneNames.Count;

	m_BoneIs = new bool[m_BoneNum]; 
	m_BonePos = new FVector[m_BoneNum]; 
	m_BonePoint = new FVector2D[m_BoneNum]; 

	for (uint32_t i = 0; i < m_BoneNum; i++)
	{
		m_BonePos[i] = m_Enemy->Mesh->GetSocketTransform(BoneNames.Data[i]);
		if (m_BonePoint)
		{
			m_BoneIs[i] = LocalPlayer->GetController()->WorldToScreen(m_BonePos[i], m_BonePoint[i]);
		}
		
	}

	m_LeftIdx = FindLeftPoint();
	m_RightIdx = FindRightPoint();
	m_LowestIdx = FindLowestPoint();
	m_HighestIdx = FindHighestPoint();
}

PlayerRender::~PlayerRender()
{
	if (m_BoneIs) {
		delete[] m_BoneIs;
	}
	if (m_BonePos) {
		delete[] m_BonePos;
	}
	if (m_BonePoint) {
		delete[] m_BonePoint;
	}
}

void PlayerRender::DrawBox2D(FLinearColor Color)
{	
	if (m_BoneIs[m_LeftIdx] && m_BoneIs[m_RightIdx]
		&& m_BoneIs[m_LowestIdx] && m_BoneIs[m_HighestIdx])
	{
		RendCanvas->K2_DrawBox({ m_BonePoint[m_LeftIdx].x,m_BonePoint[m_HighestIdx].y },
			{ m_BonePoint[m_RightIdx].x - m_BonePoint[m_LeftIdx].x,m_BonePoint[m_LowestIdx].y - m_BonePoint[m_HighestIdx].y }, 2, Color);

	}
}

void PlayerRender::DrawBlood()
{
	if (m_BoneIs[m_LeftIdx] && m_BoneIs[m_LowestIdx] && m_BoneIs[m_HighestIdx])
	{
		if (SAFE_PTR(m_Enemy->PlayerState))
		{
			FVector2D HeadScreenPoint = m_BonePoint[m_HighestIdx];
			const float FixedHealthBarWidth = 80.0f;
			const float HealthBarHeight = 4.0f;
			const float VerticalOffset = -25.0f;
			const float BorderThickness = 1.5f;

			FVector2D HealthBarPosition = { HeadScreenPoint.x - FixedHealthBarWidth * 0.5f,HeadScreenPoint.y + VerticalOffset };
			float Health = m_Enemy->GetHealth();
			float MaxHealth = m_Enemy->GetHealthMax();
			float HealthRatio = Health / MaxHealth;
			FLinearColor HealthBarColor;
			
			if (HealthRatio > 0.75f) {
				HealthBarColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
			else if (HealthRatio > 0.5f) {
				float Lerp = (HealthRatio - 0.5f) * 4.0f;
				HealthBarColor = FLinearColor(Lerp, 1.0f, 0.0f, 1.0f);
			}
			else if (HealthRatio > 0.25f) {
				float Lerp = (0.5f - HealthRatio) * 4.0f;
				HealthBarColor = FLinearColor(1.0f, Lerp, 0.0f, 1.0f);
			}
			else {
				HealthBarColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
			}

			RendCanvas->K2_DrawBox(HealthBarPosition, { FixedHealthBarWidth, HealthBarHeight }, BorderThickness * 2.0f, FLinearColor(0.1f, 0.1f, 0.1f, 1.0f));

			RendCanvas->K2_DrawBox(HealthBarPosition, { FixedHealthBarWidth, HealthBarHeight }, 0.0f, FLinearColor(0.3f, 0.3f, 0.3f, 0.7f));

			FVector2D InnerBarPosition = { HealthBarPosition.x + BorderThickness,HealthBarPosition.y + BorderThickness };
			FVector2D HealthBarSize = { (FixedHealthBarWidth - BorderThickness * 2) * HealthRatio,HealthBarHeight - BorderThickness * 2 };
			RendCanvas->K2_DrawTexture(NULL, InnerBarPosition, HealthBarSize, HealthBarColor);

			if (HealthRatio < 0.25f) {
				RendCanvas->K2_DrawBox(HealthBarPosition, { FixedHealthBarWidth, HealthBarHeight }, BorderThickness, FLinearColor(1.0f, 0.3f, 0.3f, 0.5f));
			}
		}
	


	}
}
void PlayerRender::DrawRadar()
{
	int RadarWidth = 6; // 减小方块的大小
	int CrossLength = 100; // 调整十字线的长度
	float RadarScale = 50.f;

	FVector Pos = m_BonePos[0]; // 敌人坐标 
	APlayerController* Controller = m_LocalPlayer->GetController();
	FRotator Rotator = Controller->PlayerCameraManager->GetCameraRotation();
	FVector CameraPos = Controller->PlayerCameraManager->GetCameraLocation();

	Pos.x = (Pos.x - CameraPos.x) / RadarScale;
	Pos.y = (Pos.y - CameraPos.y) / RadarScale;

	float R = sqrtf(powf(Pos.x, 2) + powf(Pos.y, 2));

	float Angle = atan2f(Pos.y, Pos.x) * 180 / 3.1415926f;
	Angle = Rotator.yaw - Angle;
	Angle = Angle * 3.1415926f / 180;

	float Width = Engine::Width ;
	float Height = Engine::Height ;

	FVector2D Point;
	Point.x = Width + -(R * sinf(Angle));
	Point.y = Height - (R * cosf(Angle));

	// 画敌人
	FVector2D EnemySize = FVector2D(RadarWidth, RadarWidth); // 敌人大小
	RendCanvas->K2_DrawTexture(NULL, { Point.x - EnemySize.x /2, Point .y - EnemySize.y /2  }, EnemySize,FLinearColor(255, 255, 0));
   RendCanvas->K2_DrawBox({ Point.x - EnemySize.x / 2, Point.y - EnemySize.y / 2 }, EnemySize, 1.0f, FLinearColor(0, 0, 0));


	// 画十字
	FVector2D CrossStartHorizontal = FVector2D(Width - CrossLength, Height);
	FVector2D CrossEndHorizontal = FVector2D(Width + CrossLength, Height);
	FVector2D CrossStartVertical = FVector2D(Width, Height - CrossLength);
	FVector2D CrossEndVertical = FVector2D(Width, Height + CrossLength);

	RendCanvas->K2_DrawLine(CrossStartHorizontal, CrossEndHorizontal, 1.0f, FLinearColor(0, 0, 0));
	RendCanvas->K2_DrawLine(CrossStartVertical, CrossEndVertical, 1.0f, FLinearColor(0, 0, 0));

	// 画自己
	FVector2D PlayerSize = FVector2D(RadarWidth, RadarWidth); // 玩家大小
	RendCanvas->K2_DrawTexture(NULL, { Width - PlayerSize.x / 2 , Height - PlayerSize.y / 2 }, PlayerSize,FLinearColor(255, 250, 250));
	RendCanvas->K2_DrawBox({ Width - PlayerSize.x / 2 , Height - PlayerSize.y / 2 }, PlayerSize, 1.0f, FLinearColor(0, 0, 0));
}

void PlayerRender::DrawTriangle(FLinearColor Color)
{
	int RadarWidth = 6; // 减小方块的大小
	int CrossLength = 100; // 调整十字线的长度
	float RadarScale = 50.f;

	FVector Pos = m_BonePos[0]; // 敌人坐标 
	APlayerController* Controller = m_LocalPlayer->GetController();
	FRotator Rotator = Controller->PlayerCameraManager->GetCameraRotation();
	FVector CameraPos = Controller->PlayerCameraManager->GetCameraLocation();

	Pos.x = (Pos.x - CameraPos.x) / RadarScale;
	Pos.y = (Pos.y - CameraPos.y) / RadarScale;

	float R = sqrtf(powf(Pos.x, 2) + powf(Pos.y, 2));

	float Angle = atan2f(Pos.y, Pos.x) * 180 / 3.1415926f;
	Angle = Rotator.yaw - Angle;
	Angle = Angle * 3.1415926f / 180;

	float Width = Engine::Width;
	float Height = Engine::Height;

	FVector2D Point;
	Point.x = Width + -(R * sinf(Angle));
	Point.y = Height - (R * cosf(Angle));

	FVector2D RadarCenter = { Width, Height }; // 雷达中心点

	float TriangleSize = 20.0f; // 三角形的大小

	FLinearColor TriangleColor = Color;

	float AAngle = atan2f(Point.y - RadarCenter.y, Point.x - RadarCenter.x); // 计算敌人方位角度

	float RadarRadius = 100.0f; // 雷达半径
	FVector2D TrianglePosition;
	TrianglePosition.x = RadarCenter.x + RadarRadius * cosf(AAngle);
	TrianglePosition.y = RadarCenter.y + RadarRadius * sinf(AAngle);

	FVector2D TriangleTip;
	TriangleTip.x = TrianglePosition.x + TriangleSize * cosf(AAngle);
	TriangleTip.y = TrianglePosition.y + TriangleSize * sinf(AAngle);

	FVector2D TriangleLeft;
	TriangleLeft.x = TrianglePosition.x + TriangleSize / 2 * cosf(AAngle + 3.1415926f / 2);
	TriangleLeft.y = TrianglePosition.y + TriangleSize / 2 * sinf(AAngle + 3.1415926f / 2); 

	FVector2D TriangleRight;
	TriangleRight.x = TrianglePosition.x + TriangleSize / 2 * cosf(AAngle - 3.1415926f / 2);
	TriangleRight.y = TrianglePosition.y + TriangleSize / 2 * sinf(AAngle - 3.1415926f / 2);

	RendCanvas->K2_StroKeLine(TriangleTip, TriangleLeft, TriangleColor);
	RendCanvas->K2_StroKeLine(TriangleLeft, TriangleRight, TriangleColor);
	RendCanvas->K2_StroKeLine(TriangleRight, TriangleTip, TriangleColor);
}

void PlayerRender::DrawPlayerdistance()
{
	wchar_t Buffer[256] = { 0 };
	FString distanceStr;
	FVector2D Center;
	FVector HeadPos;
	if (m_BoneIs[m_LeftIdx] && m_BoneIs[m_RightIdx]
		&& m_BoneIs[m_LowestIdx] && m_BoneIs[m_HighestIdx])
	{
		Center.x = m_BonePoint[m_LeftIdx].x + ((m_BonePoint[m_RightIdx].x - m_BonePoint[m_LeftIdx].x) * 0.5f);
		Center.y = m_BonePoint[m_HighestIdx].y;
		APlayerController* Controller = m_LocalPlayer->GetController();
		if (SAFE_PTR(m_Enemy->Mesh) && m_BoneNum > 0 && Controller)
		{
			BoneIndex* BoneIdx = m_Enemy->Mesh->GetBoneIndex(m_BoneNum);

			if (SAFE_PTR(BoneIdx) && SAFE_PTR(Controller) && BoneIdx)
			{
				APlayerCameraManager* pCameraManager = Controller->PlayerCameraManager;
				if (SAFE_PTR(pCameraManager))
				{
					FVector CameraPos = pCameraManager->GetCameraLocation();
					HeadPos = m_BonePos[BoneIdx->head];
					if (!isnan(HeadPos.x) && !isnan(CameraPos.y) && !isnan(HeadPos.y) && !isnan(CameraPos.x))
					{
						float distance = FVector::Distance(HeadPos, CameraPos) / 100.f;
						if (!isnan(distance))
						{
							if (swprintf(Buffer, _countof(Buffer), L"[%0.2f/m]\n", distance) > 0)
							{
								distanceStr.Data = Buffer;
								distanceStr.Count = static_cast<int32_t>(wcslen(Buffer)) + 1;
								distanceStr.Max = distanceStr.Count;

								if (distanceStr.Data)
								{
									RendCanvas->K2_StrokeText(distanceStr, FLinearColor(1.f, 1.f, 1.f, 1.f), FVector2D(Center.x, Center.y - 5.f));
								}


							}
						}
						
					}
					
				}

			}
		}

	}

	
}
FLinearColor GetTeamColor(uint32_t TeamID)
{
	switch (TeamID)
	{
	case 1: return FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);    // 红色 (Red)
	case 2: return FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);    // 绿色 (Green)
	case 3: return FLinearColor(0.65f, 0.85f, 1.00f, 1.0f);
	case 4: return FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);    // 黄色 (Yellow)
	case 5: return FLinearColor(0.5f, 0.2f, 0.8f, 1.0f);    // 紫罗兰色 (Violet)
	case 6: return FLinearColor(0.1f, 0.7f, 0.9f, 1.0f);    // 天蓝色 (Sky Blue)
	default: return FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);   // 默认灰色 (Gray)
	}
}

void PlayerRender::DrawPlayerTeamId()
{
	wchar_t Buffer[256] = { 0 };
	FString TeamPtr;
	if (m_BoneIs[m_LeftIdx] && m_BoneIs[m_RightIdx]
		&& m_BoneIs[m_LowestIdx] && m_BoneIs[m_HighestIdx])
	{
		if (SAFE_PTR(m_Enemy->PlayerState))
		{
			uint32_t TeamID = m_Enemy->PlayerState->GetTeamID();
			FVector2D LowestIdx;
			LowestIdx.x = m_BonePoint[m_LeftIdx].x + ((m_BonePoint[m_RightIdx].x - m_BonePoint[m_LeftIdx].x) / 2);
			LowestIdx.y = m_BonePoint[m_LowestIdx].y;
			if (SAFE_PTR(m_Enemy->PlayerState))
			{
				const FVector2D LineStart(LowestIdx.x - 30, LowestIdx.y); 
				const FVector2D LineEnd(LowestIdx.x + 30, LowestIdx.y);
				constexpr float LineThickness = 2.0f;
				if (swprintf(Buffer, _countof(Buffer), L"队: %d\n", TeamID) > 0)
				{
					TeamPtr.Data = Buffer;
					TeamPtr.Count = static_cast<int32_t>(wcslen(Buffer));
					TeamPtr.Max = TeamPtr.Count + 1;

					RendCanvas->K2_StroKeLine(LineStart, LineEnd, FLinearColor(1.f, 1.f, 1.f, 1.f));
					FLinearColor TeamColor = GetTeamColor(TeamID);

					RendCanvas->K2_StrokeText(TeamPtr, TeamColor, { LowestIdx.x,LowestIdx.y + 10 });
				

				}


			}

		}

		
	}
	



}

void PlayerRender::DrawName()
{
	if (m_BoneIs[m_LeftIdx] && m_BoneIs[m_RightIdx]
		&& m_BoneIs[m_LowestIdx] && m_BoneIs[m_HighestIdx])
	{
		FVector2D Center;
		Center.x = m_BonePoint[m_LeftIdx].x + ((m_BonePoint[m_RightIdx].x - m_BonePoint[m_LeftIdx].x) / 2);
		Center.y = m_BonePoint[m_HighestIdx].y;

		if (SAFE_PTR(m_Enemy->PlayerState))
		{
			FString Name = m_Enemy->PlayerState->GetPlayerName();
			if (SAFE_PTR(Name.Data))
			{
				RendCanvas->K2_StrokeText(Name, { 1,1,1,1 }, { Center.x,Center.y - 2 });

			
			}
		}
		else
		{
			RendCanvas->K2_StrokeText(FString(L"守卫"), { 0,1,0,1 }, { Center.x,Center.y - 2 });
		}
	}
}

void PlayerRender::DrawBone(FLinearColor Color)
{
	BoneIndex* Idx = m_Enemy->Mesh->GetBoneIndex(m_BoneNum);
	if (Idx)
	{
		DrawPartBone(0, 6, Idx, Color);
		DrawPartBone(6, 8, Idx, Color);
		DrawPartBone(14, 6, Idx, Color);

	}

}	

void PlayerRender::DrawPartBone(uint32_t Start, uint32_t End, BoneIndex* IdxArray, FLinearColor Color)
{
	FVector2D Point, oPoint;
	uint32_t BoneIdx, oBoneIdx;
	uint32_t* BoneArray = (uint32_t*)IdxArray;

	for (uint32_t i = Start; i < Start + End; i++)
	{
		BoneIdx = BoneArray[i];
		if (BoneIdx != 0 && m_BonePoint)
		{
			Point = m_BonePoint[BoneIdx];
			if (i != Start
				&& m_BoneIs[BoneIdx]
				&& m_BoneIs[oBoneIdx])
			{
				RendCanvas->K2_StroKeLine({ oPoint.x,oPoint.y }, { Point.x,Point.y }, Color);
				

			}
		}
		
		oPoint = Point;
		oBoneIdx = BoneIdx;
	}
}
uint32_t PlayerRender::FindLeftPoint()
{
	uint32_t ReturnValue = 0;

	for (uint32_t i = 1; i < m_BoneNum; i++)
	{
		if (m_BonePoint[i].x < m_BonePoint[ReturnValue].x
			&& m_BonePoint[i].x != 0)
		{
			ReturnValue = i;
		}
	}

	return ReturnValue;
}

uint32_t PlayerRender::FindRightPoint()
{
	uint32_t ReturnValue = 0;

	for (uint32_t i = 1; i < m_BoneNum; i++)
	{
		if (m_BonePoint[i].x > m_BonePoint[ReturnValue].x
			&& m_BonePoint[i].x != 0)
		{
			ReturnValue = i;
		}
	}

	return ReturnValue;
}

uint32_t PlayerRender::FindHighestPoint()
{
	uint32_t ReturnValue = 0;

	for (uint32_t i = 1; i < m_BoneNum; i++)
	{
		if (m_BonePoint[i].y < m_BonePoint[ReturnValue].y
			&& m_BonePoint[i].y != 0)
		{
			ReturnValue = i;
		}
	}

	return ReturnValue;
}

uint32_t PlayerRender::FindLowestPoint()
{
	uint32_t ReturnValue = 0;

	for (uint32_t i = 1; i < m_BoneNum; i++)
	{
		if (m_BonePoint[i].y > m_BonePoint[ReturnValue].y
			&& m_BonePoint[i].y != 0)
		{
			ReturnValue = i;
		}
	}

	return ReturnValue;
}

void PlayerRender::DrawBox3D(FLinearColor Color)
{
	BoneIndex* BoneIdx = m_Enemy->Mesh->GetBoneIndex(m_BoneNum);
	APlayerController* Controller = m_LocalPlayer->GetController();
	FVector CenterPos = m_BonePos[BoneIdx->pelvis];
	float BottomZ = m_BonePos[0].z - 120;

	float TopZ = m_BonePos[BoneIdx->head].z + 20;

	FVector Top_Pos[4], Bottom_Pos[4];
	FVector2D Top_Point[4], Bottom_Point[4];

	for (int i = 0; i < 4; i++)
	{
		int offset = 45 + i * 90;
		float ControlRotation = m_Enemy->GetBaseAimRotation().yaw;
		Bottom_Pos[i].x = CenterPos.x + (float)cos((ControlRotation + offset) * 3.1415926 / 180.f) * 55.f;
		Bottom_Pos[i].y = CenterPos.y + (float)sin((ControlRotation + offset) * 3.1415926 / 180.f) * 55.f;
		Bottom_Pos[i].z = BottomZ;

		Top_Pos[i] = Bottom_Pos[i];
		Top_Pos[i].z = TopZ;

		if (!(Controller->WorldToScreen(Bottom_Pos[i], Bottom_Point[i]))
			|| !(Controller->WorldToScreen(Top_Pos[i], Top_Point[i])))
		{
			break;
		}
	}

	for (int i = 0; i < 4; i++)
	{

		RendCanvas->K2_DrawLine(Bottom_Point[i], Top_Point[i], 1.5f, Color);
		if (i > 0)
		{
	
			RendCanvas->K2_DrawLine(Bottom_Point[i - 1], Bottom_Point[i], 1.5f, Color);

			RendCanvas->K2_DrawLine(Top_Point[i - 1], Top_Point[i], 1.5f, Color);
		}

		if (i == 3)
		{
			RendCanvas->K2_DrawLine(Bottom_Point[3], Bottom_Point[0], 1.5f, Color);
			RendCanvas->K2_DrawLine(Top_Point[3], Top_Point[0], 1.5f, Color);
		}
	}


}
void LightChange(FLinearColor& Color)
{
	float Speed = 10000.0f;
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = now - startTime;
	float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();

	Color.r = std::sin(Speed / 1500 * elapsedTime * 0.5f) * 0.5f + 0.5f;
	Color.b = std::sin(Speed / 1500 * elapsedTime + 2 * (float)3.1415926 / 3) * 0.5f + 0.5f;
	Color.g = std::sin(Speed / 1500 * elapsedTime + 4 * (float)3.1415926 / 3) * 0.5f + 0.5f;

}

void PlayerRender::DrawLosLine(FLinearColor Color)
{
	FVector2D StartPoint, EndPoint;
	FVector StartPos, EndPos;

	FRotator Rotator = m_Enemy->GetBaseAimRotation();
	BoneIndex* BoneIdx = m_Enemy->Mesh->GetBoneIndex(m_BoneNum);
	APlayerController* Controller = m_LocalPlayer->GetController();
	if (!IsBadReadPtr(BoneIdx, 8) && !IsBadReadPtr(Controller, 8) && !IsBadReadPtr(m_Enemy->Mesh,8) && BoneIdx)
	{
		StartPos = m_BonePos[BoneIdx->head];
		EndPos.x = StartPos.x + cos(Rotator.yaw * 3.1415926f / 180.f) * 200;
		EndPos.y = StartPos.y + sin(Rotator.yaw * 3.1415926f / 180.f) * 200;
		EndPos.z = StartPos.z + sin(Rotator.pitch * 3.1415926f / 180.f) * 200;

		if (Controller->WorldToScreen(StartPos, StartPoint)
			&& Controller->WorldToScreen(EndPos, EndPoint))
		{
			RendCanvas->K2_StroKeLine({ StartPoint.x,StartPoint.y }, { EndPoint.x,EndPoint.y }, Color);
			

		}
	}
	
}
MagicCircle PMagicCircle;
void PlayerRender::ShowMagicCircle()
{
	FVector vecArray[9];
	FVector PlayerPoint{};
	FVector2D ScreenPoint{};
	FVector2D BottomPoint{};
	APlayerController* Controller = m_LocalPlayer->GetController();
	BoneIndex* BoneIdx = m_Enemy->Mesh->GetBoneIndex(m_BoneNum);
	if (!IsBadReadPtr(Controller, 8) && !IsBadReadPtr(BoneIdx,8))
	{

		for (int A = 0; A < 9; A++)
		{
			if ((GetTickCount64() - PMagicCircle.MagicCircleTime) >= 8)
			{

				PMagicCircle.MagicCircleAngle += 1;
				PMagicCircle.MagicCircleTime = static_cast<uint32_t>(GetTickCount64());
			}

			if (PMagicCircle.MagicCircleAngle == 360)
			{
				PMagicCircle.MagicCircleAngle = 0;
			}

			LightChange(PMagicCircle.Color);

			PMagicCircle.Rad = 360 / 9 * (float)3.375 * A;

			PlayerPoint = m_BonePos[BoneIdx->foot_r];
			vecArray[A].x = PlayerPoint.x + std::sin((PMagicCircle.MagicCircleAngle + PMagicCircle.Rad) * 3.1415926 / 180) * 145;
			vecArray[A].y = PlayerPoint.y + std::cos((PMagicCircle.MagicCircleAngle + PMagicCircle.Rad) * 3.1415926 / 180) * 145;;
			vecArray[A].z = PlayerPoint.z;

			if (Controller->WorldToScreen(vecArray[A], ScreenPoint))
			{
				if (ScreenPoint.x != 0 && ScreenPoint.y != 0 && BottomPoint.x != 0 && BottomPoint.y != 0)
				{
					if (A > 0)
					{
						RendCanvas->K2_StroKeLine({ BottomPoint.x,BottomPoint.y + 10 }, { ScreenPoint.x,ScreenPoint.y + 10 }, PMagicCircle.Color);
					}



				}
			}


			BottomPoint = ScreenPoint;

		}
	}




}

