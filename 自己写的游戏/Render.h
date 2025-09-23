#pragma once

#include "base.h"
#include "class.h"

class PlayerRender
{
public:

	// 获取重要的骨骼坐标数据 
	PlayerRender(ASolarCharacter* Enemy, ASolarCharacter* LocalPlayer, UCanvas* Canvas);

	~PlayerRender();

	void DrawBoxFromBase(FVector2D BottomLeft, FVector2D BottomRight, float BoxHeight, FLinearColor Color);

	void DrawBone(FLinearColor Color);

	void DrawBox2D(FLinearColor Color);

	void DrawName();

	void DrawLosLine(FLinearColor Color);

	void DrawBox3D(FLinearColor Color);

	void DrawBlood();

	void ShowMagicCircle();

	void DrawRadar();

	void DrawTriangle(FLinearColor Color);

	void DrawPlayerdistance();


	void DrawPlayerTeamId();
private:

	void DrawPartBone(uint32_t Start, uint32_t End, BoneIndex* IdxArray, FLinearColor Color);

	uint32_t FindLeftPoint();

	uint32_t FindRightPoint();

	uint32_t FindHighestPoint();

	uint32_t FindLowestPoint();

	uint32_t m_BoneNum = 0; // 代表当前人物骨骼的数量 完全可以用骨骼数量来区分使用哪套骨骼

	UCanvas* RendCanvas = NULL;

	uint32_t m_LeftIdx = 0;
	uint32_t m_RightIdx = 0;
	uint32_t m_LowestIdx = 0;
	uint32_t m_HighestIdx = 0;

	bool* m_BoneIs = NULL;
	FVector* m_BonePos = NULL;
	FVector2D* m_BonePoint = NULL;


	ASolarCharacter* m_Enemy = NULL;
	ASolarCharacter* m_LocalPlayer = NULL;
};