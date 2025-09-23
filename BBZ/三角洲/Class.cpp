#include"Class.h"
#include"Engine.h"
#include"Spoofcall.h"
#include"Utils.h"

void UObject::ProcessEvent(void* Function, void* Args)
{

	void** Vtable = *reinterpret_cast<void***>(this);


	using T_ProcessEvent = void (*)(UObject*, void*, void*);


	T_ProcessEvent ProcessEventFunc = reinterpret_cast<T_ProcessEvent>(Vtable[68]);


	ProcessEventFunc(this, Function, Args);
}


UObject* UObject::StaticFindObject(void* ObjectClass, UObject* InObjectPackage, const TCHAR* OrigInName, bool ExactClass)
{
	//类型
	using T_FindObject = UObject * (*)(void*, UObject*, const TCHAR*, bool);

	static T_FindObject FindObjectFunc = nullptr;

	if (!FindObjectFunc)
	{
		// v8 = sub_147F63F10(v7, 0LL, v6, 0LL);
		ULONG64 StaticFindObjectAddr = Utils::Pattern::FindPattern(
			"48 89 5C 24 08 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC 60 80 3D 85 20 2A 08 00"
		).get();

		FindObjectFunc = reinterpret_cast<T_FindObject>(StaticFindObjectAddr);
		printf("StaticFindObject: %p\n", FindObjectFunc);
	}

	// 直接调用函数（x64 下无需显式指定 __fastcall）
	return FindObjectFunc(ObjectClass, InObjectPackage, OrigInName, ExactClass);
}

FString UKismetStringLibrary::Conv_NameToString(uint64_t InName)
{
	// 定义函数指针类型（匹配目标函数签名）
	using FuncType = FString * (__fastcall*)(void*, FString*);

	// 静态变量存储函数地址
	static FuncType Function = nullptr;

	// 如果函数地址未初始化，则通过特征码查找
	if (!Function) {
		ULONG64 Nametostring = Utils::Pattern::FindPattern(
			"40 55 57 41 56 48 8D AC 24 ?? ?? FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 83 79 04 00"
		).get();

		if (!Nametostring) {
			// 如果特征码未找到，返回空 FString
			return FString();
		}

		// 将地址转换为函数指针
		Function = reinterpret_cast<FuncType>(Nametostring);
	}

	// 定义 FString 用于存储结果
	FString Str;

	// 直接调用函数
	Function(reinterpret_cast<void*>(&InName), &Str);

	// 返回结果
	return Str;
}

FVector UKismetStringLibrary::GetForwardVector(const FRotator* InRo)
{
	const float PitchNoWinding = Utils::Fmod(InRo->pitch, 360.0f);
	const float YawNoWinding = Utils::Fmod(InRo->yaw, 360.0f);
	float SP, CP, SY, CY;
	Utils::SinCos(&SP, &CP, DegreesToRadians(PitchNoWinding));
	Utils::SinCos(&SY, &CY, DegreesToRadians(YawNoWinding));
	FVector V = { CP * CY,CP * SY,SP};
	if (Utils::ContainsNaN(V))
	{
		return FVector();
	}

	return V;
}

void* UObject::GetIteamClass()
{
	static void* PlayerClass = NULL;

	if (!PlayerClass) {
		PlayerClass = UObject::StaticFindObject(NULL, NULL, L"DFMGameplay.InventoryPickup", false);
	}

	return PlayerClass;

}

void UObject::Free(void* Addr)
{

}

void* UObject::GetPlayerClass()
{
	static void* PlayerClass = NULL;

	if (!PlayerClass) {
		PlayerClass = UObject::StaticFindObject(NULL, NULL, L"GPGameplay.IntCharacter", false);
	}

	return PlayerClass;

}

APlayerController* UObject::GetLocalPlayerController(UWorld* WorldContextObject)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPNetModeUtils.GetLocalPlayerController", false);
	}

	struct {
		APlayerController* ReturnValue;
	} Params = {};

	WorldContextObject->ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}



UFont* UObject::GetRoboto()
{
	static UFont* Roboto = NULL;

	if (!Roboto) {
		Roboto = (UFont*)StaticFindObject(NULL, NULL, L"/Game/UI/Fonts/FZLTZHJW_ZH_Font.FZLTZHJW_ZH_Font", false);
	}

	return Roboto;
}




wstring UObject::GetName()
{
	FString Name = UKismetStringLibrary::Conv_NameToString(*(uint64_t*)((uint8_t*)this + 0x24));
	wstring NamesPtr = Name.Data;
	size_t Pos = NamesPtr.rfind(L"/");
	if (Pos != std::string::npos)
	{
		NamesPtr = NamesPtr.substr(Pos + 1);
	}
	return NamesPtr;
}

void UGameplayStatics::GetAllActorsOfClass(UWorld* WorldContextObject, void* ActorClass, TArray<ASolarCharacter*>* OutActors)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GameplayStatics.GetAllActorsOfClass", NULL);
	}

	struct
	{
		UWorld* WorldContextObject;
		void* ActorClass;
		TArray<ASolarCharacter*> OutActors;
	}Params{ WorldContextObject,ActorClass,TArray<ASolarCharacter*>() };

	WorldContextObject->ProcessEvent(Function, &Params);

	*OutActors = Params.OutActors;
}

void UGameplayStatics::GetAllIteamsOfClass(UWorld* WorldContextObject, void* ActorClass, TArray<AActor*>* OutActors)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GameplayStatics.GetAllActorsOfClass", NULL);
	}

	struct
	{
		UWorld* WorldContextObject;
		void* ActorClass;
		TArray<AActor*> OutActors;
	}Params{ WorldContextObject,ActorClass,TArray<AActor*>() };

	WorldContextObject->ProcessEvent(Function, &Params);

	*OutActors = Params.OutActors;
}



void UCanvas::K2_DrawBox(FVector2D ScreenPosition, FVector2D ScreenSize, float Thickness, FLinearColor RenderColor)
{
	static void* Function = NULL; // UFuntion

	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Canvas.K2_DrawBox", false);
	}

	struct {
		FVector2D ScreenPosition;
		FVector2D ScreenSize;
		float Thickness;
		FLinearColor RenderColor;
	}Params{ ScreenPosition,ScreenSize,Thickness,RenderColor };

	ProcessEvent(Function, &Params);
}

void UCanvas::K2_DrawLine(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor)
{
	static void* Function = NULL; // UFuntion

	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Engine.Canvas.K2_DrawLine", false);
	}
	struct {
		FVector2D ScreenPositionA;
		FVector2D ScreenPositionB;
		float Thickness;
		FLinearColor RenderColor;
	}Params{ ScreenPositionA,ScreenPositionB,Thickness,RenderColor };

	ProcessEvent(Function, &Params);
}

void UCanvas::K2_DrawText(void* RenderFont, FString RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor RenderColor, float Kerning, FLinearColor ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor OutlineColor)
{
	static void* Function = NULL; // UFuntion

	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Canvas.K2_DrawText", false);
	}

	struct {
		void* RenderFont;
		FString RenderText;
		FVector2D ScreenPosition;
		FVector2D Scale;
		FLinearColor RenderColor;
		float Kerning;
		FLinearColor ShadowColor;
		FVector2D ShadowOffset;
		bool bCentreX;
		bool bCentreY;
		bool bOutlined;
		FLinearColor OutlineColor;
	}Params{ RenderFont,RenderText,ScreenPosition,Scale,RenderColor,Kerning,ShadowColor,ShadowOffset,bCentreX,bCentreY,bOutlined,OutlineColor };

	ProcessEvent(Function, &Params);
}

void UCanvas::K2_DrawTexture(void* RenderTexture, FVector2D ScreenPosition, FVector2D ScreenSize, FLinearColor RenderColor)
{
	static void* Function = NULL; // UFuntion

	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Canvas.K2_DrawTexture", false);
	}

	struct {
		void* RenderTexture;
		FVector2D ScreenPosition;
		FVector2D ScreenSize;
		FVector2D CoordinatePosition;
		FVector2D CoordinateSize;
		FLinearColor RenderColor;
		int BlendMode;
		float Rotation;
		FVector2D PivotPoint;
	}Params{ RenderTexture,ScreenPosition,ScreenSize,{0,0},{0,0},RenderColor,0,0,{0,0} };

	ProcessEvent(Function, &Params);
}

void UCanvas::K2_DrawPolygon(FVector2D ScreenPosition, FVector2D Radius, int32_t NumberOfSides, FLinearColor RenderColor, float Thickness)
{
	float TwoPI = 2.f * 3.1415926f;

	for (int32_t i = 0; i < NumberOfSides; i++)
	{
		float AngleA = (float)i / (float)NumberOfSides * TwoPI; // 求出开始绘制的点A弧度
		float AngleB = (float)(i + 1) / (float)NumberOfSides * TwoPI; //  求出绘制的点B弧度

		FVector2D PointA = FVector2D(cos(AngleA) * Radius.x, sin(AngleA) * Radius.y);
		FVector2D PointB = FVector2D(cos(AngleB) * Radius.x, sin(AngleB) * Radius.y);

		PointA.x += ScreenPosition.x;
		PointA.y += ScreenPosition.y;
		PointB.x += ScreenPosition.x;
		PointB.y += ScreenPosition.y;

		K2_DrawLine(PointA, PointB, Thickness, RenderColor);
	}
}

FVector2D UCanvas::K2_TextSize(void* RenderFont, FString RenderText, FVector2D Scale)
{
	static void* Function = NULL; // UFuntion

	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Canvas.K2_TextSize", false);
	}

	struct {
		void* RenderFont;
		FString RenderText;
		FVector2D Scale;
		FVector2D ReturnValue;
	}Params{ RenderFont,RenderText,Scale };

	ProcessEvent(Function, &Params);
	return Params.ReturnValue;
}

APlayerController* UGameInstance::GetPlayerController()
{
	uint8_t* Player = **(uint8_t***)((uint8_t*)this + 0x48);
	if (!IsBadReadPtr(Player, 8))
		return *(APlayerController**)(Player + 0x38);

	return NULL;
}

ASolarCharacter* UGameInstance::GetPlayer()
{
	uint8_t* PlayerController = (uint8_t*)GetPlayerController();
	if (!IsBadReadPtr(PlayerController, 8))
		return *(ASolarCharacter**)(PlayerController + 0x400);
	return NULL;

}

BoneIndex* USkeletalMeshComponent::GetBoneIndex(uint32_t NumBones)
{
	static vector<BoneIndex*> BoneIdxArray;

	for (size_t i = 0; i < BoneIdxArray.size(); i++)
	{
		if (BoneIdxArray[i]->NumBones == NumBones)
			return BoneIdxArray[i]; 
	}

	BoneIndex* NewBoneIdx = new BoneIndex;
	NewBoneIdx->NumBones = NumBones;
	BoneIdxArray.push_back(NewBoneIdx);

	TArray<uint64_t> BoneNames = GetAllSocketNames();
	for (uint32_t i = 0; i < NumBones; i++)
	{  
		FString BonePtr = UKismetStringLibrary::Conv_NameToString(BoneNames.Data[i]);
		wstring BoneName = BonePtr.Data;
		transform(BoneName.begin(), BoneName.end(), BoneName.begin(), ::tolower); 

		if (BoneName == L"head") { NewBoneIdx->head = i; }
		else if (BoneName == L"lefthand") { NewBoneIdx->hand_l = i; }
		else if (BoneName == L"righthand") { NewBoneIdx->hand_r = i; }

		else if (BoneName == L"leftshoulder") { NewBoneIdx->clavicle_l = i; }  
		else if (BoneName == L"rightshoulder") { NewBoneIdx->clavicle_r = i; } 

		else if (BoneName == L"leftfoot") { NewBoneIdx->foot_l = i; }
		else if (BoneName == L"leftleg") { NewBoneIdx->calf_l = i; }

		else if (BoneName == L"rightleg") { NewBoneIdx->calf_r = i; }
		else if (BoneName == L"rightfoot") { NewBoneIdx->foot_r = i; }

		else if (BoneName == L"hips") { NewBoneIdx->pelvis = i; }
		else if (BoneName == L"neck") { NewBoneIdx->neck_01 = i; }

		else if (BoneName == L"leftupleg") { NewBoneIdx->thigh_l = i; }
		else if (BoneName == L"rightupleg") { NewBoneIdx->thigh_r = i; }

		else if (BoneName == L"spine2") { NewBoneIdx->spine_03 = i; }
		else if (BoneName == L"spine1") { NewBoneIdx->spine_02 = i; }

		else if (BoneName == L"spine") { NewBoneIdx->spine_01 = i; }
		else if (BoneName == L"leftforearm") { NewBoneIdx->lowerarm_l = i; }

		else if (BoneName == L"rightforearm") { NewBoneIdx->lowerarm_r = i; }
		else if (BoneName == L"leftarm") { NewBoneIdx->upperarm_l = i; }

		else if (BoneName == L"rightarm") { NewBoneIdx->upperarm_r = i; }

	}

	return NewBoneIdx;
}

TArray<uint64_t> USkeletalMeshComponent::GetAllSocketNames()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"SceneComponent.GetAllSocketNames", false);
	}

	struct
	{
		TArray<uint64_t> ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

FVector USkeletalMeshComponent::GetSocketTransform(uint64_t InSocketName)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"SceneComponent.GetSocketTransform", false);
	}

	struct
	{
		uint64_t InSocketName;
		uint32_t TransformSpace;
		bool bDoParallel;
		FTransform ReturnValue;
	}Params{ InSocketName,0,false };

	ProcessEvent(Function, &Params);

	return Params.ReturnValue.Translation;
}

FRotator ASolarCharacter::GetBaseAimRotation()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Pawn.GetBaseAimRotation", false);
	}

	struct {
		FRotator ReturnValue;
	} Params = {};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}
APlayerController* ASolarCharacter::GetController()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Pawn.GetController", false);
	}

	struct {
		APlayerController* ReturnValue;
	} Params = {};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

FRotator APlayerCameraManager::GetCameraRotation()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"PlayerCameraManager.GetCameraRotation", false);
	}

	struct
	{
		FRotator ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

FVector APlayerCameraManager::GetCameraLocation()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"PlayerCameraManager.GetCameraLocation", false);
	}

	struct
	{
		FVector ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

bool APlayerController::WorldToScreen(FVector WorldLocation, FVector2D& ScreenLocation)
{
	static void* Function = NULL;

	if (!Function)
	{
		Function = StaticFindObject(NULL, NULL, L"PlayerController.ProjectWorldLocationToScreen", false);
	}

	struct
	{
		FVector WorldLocation;
		FVector2D ScreenLocation;
		bool bPlayerViewportRelative;
		bool ReturnValue;
	}Params{ WorldLocation,FVector2D(),false };

	ProcessEvent(Function, &Params);

	ScreenLocation = Params.ScreenLocation;
	return Params.ReturnValue;
}
char APlayerController::LineOfSightTo(ASolarCharacter* Other, FVector ViewPoint)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Controller.LineOfSightTo", false);
	}

	struct
	{
		ASolarCharacter* Other;
		FVector ViewPoint;
		char bAlternateChecks;
		char ReturnValue;
	}Params{ Other,ViewPoint,0 };

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

int32_t ASolarPlayerState::GetCamp()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPPlayerState.GetCamp", false);
	}
	struct
	{
		int32_t ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

FString ASolarPlayerState::GetPlayerName()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"PlayerState.GetPlayerName", false);
	}

	struct
	{
		FString ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

int32_t ASolarPlayerState::GetTeamID()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPPlayerState.GetTeamID", false);
	}

	struct
	{
		int32_t ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

float ASolarCharacter::GetHealth()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPCharacterBase.GetHealth", false);
	}
	struct
	{
		float ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}

float ASolarCharacter::GetHealthMax()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPCharacterBase.GetHealthMax", false);
	}

	struct
	{
		float ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;

}

char ASolarCharacter::IsPlayerAI()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"GPCharacterBase.IsAI", false);
	}

	struct
	{
		char ReturnValue;
	}Params{};

	ProcessEvent(Function, &Params);

	return Params.ReturnValue;
}


void UCanvas::K2_StrokeText(FString RenderText, FLinearColor Color, const FVector2D& Pos)
{
	const FLinearColor OutlineColor = FLinearColor(0.12f, 0.12f, 0.12f, 0.5f);  
	const FLinearColor SoftShadowColor = FLinearColor(0.05f, 0.05f, 0.05f, 0.25f); 
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) continue;
			K2_DrawText(UObject::GetRoboto(), RenderText, { Pos.x + x * 0.5f, Pos.y + y * 0.5f }, // X
				{ 1.f,1.f }, OutlineColor, 1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());
		}
	}

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) continue;
			K2_DrawText(UObject::GetRoboto(), RenderText, { Pos.x + x * 0.8f, Pos.y + y * 0.8f }, // X
				{ 1.f,1.f }, SoftShadowColor, 1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());
		}
	}

	FLinearColor AdjustedColor = FLinearColor(std::clamp(Color.r * 1.3f, 0.0f, 1.0f),std::clamp(Color.g * 1.3f, 0.0f, 1.0f),std::clamp(Color.b * 1.3f, 0.0f, 1.0f),	Color.a);

	K2_DrawText(UObject::GetRoboto(), RenderText, Pos, { 1.f,1.f }, AdjustedColor,
		1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());

}

void UCanvas::K2_StroKeLine(const FVector2D& P1, const FVector2D& P2, FLinearColor Color)
{
	const float LineThickness = 1.0f;
	const FLinearColor OutlineColor1(0.1f, 0.1f, 0.1f, 0.3f);
	const FLinearColor OutlineColor2(0.1f, 0.1f, 0.1f, 0.2f);
	K2_DrawLine(P1, P2, LineThickness + 0.8f, OutlineColor1);
	K2_DrawLine(P1, P2, LineThickness + 1.2f, OutlineColor2);
	K2_DrawLine(P1, P2, LineThickness, Color);
}

FString AActor::GetActorsName()
{
	FString Name = UKismetStringLibrary::Conv_NameToString(*(uint64_t*)((uint8_t*)this + 0x24));
	return Name;
}

FText AActor::GetItemName()
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"PickupBase.GetItemName", false);
	}

	struct {
		FText ReturnValue;
	} Params = {};

	ProcessEvent(Function, &Params);

     return Params.ReturnValue;
}

void APlayerController::SetControlRotation(FRotator& NewRotation)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"Controller.SetControlRotation", false);
	}

	struct {
		FRotator ReturnValue;
	} Params = {};

	ProcessEvent(Function, &Params);

	NewRotation = Params.ReturnValue;
}

bool APlayerController::GetMousePosition(FVector2D& MousePosition)
{
	static void* Function = NULL;
	if (!Function) {
		Function = StaticFindObject(NULL, NULL, L"PlayerController.GetMousePosition", false);
	}

	struct {
		float LocationX;
		float LocationY;
		bool ReturnValue;
	} Params = {};

	ProcessEvent(Function, &Params);

	MousePosition = FVector2D(Params.LocationX, Params.LocationY);
	return Params.ReturnValue;
}
