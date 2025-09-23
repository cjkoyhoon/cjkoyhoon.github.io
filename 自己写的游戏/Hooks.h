#pragma once
#include"base.h"
#include "engine.h"
#include"Utils.h"
#include <unordered_map>
#include <chrono>
namespace Hooks
{
	void Initialize();
	void hkPostRender(void* GameViewport, UCanvas* Canvas);
	namespace Menu
	{

		inline bool Box2D = false;
		inline bool 烽火模式 = true;
		inline bool 战场模式 = false;
		inline bool DrawIteam = false;
		inline bool 盒子容器 = false;
		inline bool 容器 = false;
		inline bool 物资 = false;
		inline bool OpenAimbot = true;
		inline bool DrawBone = true;
		inline bool DrawTeamId = true;
		inline bool DrawName = true;
		inline bool LosLine = true;
		inline bool ShowMagicCircle = false;
		inline bool DrawRadar = false;
		inline bool DrawTriangle = true;
		inline bool Playerdistance = false;
		inline int AimMod = 0;
		inline int AimBith = 0;
		static inline bool DrawBlood = true;
		static inline bool DrawBox3D = false;
		inline int AimBotKey = 1;
		inline float SilentRange = 150;
		 inline float 价值 = 1500;
		 inline float 容器距离 = 100;
		 inline float 物资距离 = 100;
		 inline float 盒子距离 = 100;
		static FLinearColor test_color{ 1.0f, 1.0f, 1.0f, 1.0f };
		static FLinearColor Triangle_color{ 0,255,0 };
		static FLinearColor ColorLosLine{ 1.0f, 1.0f, 1.0f, 1.0f };
		static FLinearColor BoneColor{ 0.0f, 1.0f, 0.0f, 1.0f };
		static FVector2D posSize = { 10,10 };
		static float AimSpee = 0.4f;
		static std::unordered_map<int, string> KeyStrings = { {0, "None"}, {1, "左键"}, {2, "邮件"}, {3, "BRK"}, {4, "M3"}, {5, "M4"}, {6, "M5"}, {8, "BCK"}, {9, "TAB"}, {13, "ENT"}, {16, "SFT"}, {17, "CTL"}, {18, "ALT"}, {19, "PUS"}, {20, "CAP"}, {27, "ESC"}, {32, "SPC"}, {33, "PGU"}, {34, "PGD"}, {35, "END"}, {36, "HOM"}, {37, "LFT"}, {38, "UP"}, {39, "RGT"}, {40, "Down"}, {44, "PRN"}, {45, "INS"}, {46, "DEL"}, {48, "0"}, {49, "1"}, {50, "2"}, {51, "3"}, {52, "4"}, {53, "5"}, {54, "6"}, {55, "7"}, {56, "8"}, {57, "9"}, {65, "A"}, {66, "B"}, {67, "C"}, {68, "D"}, {69, "E"}, {70, "F"}, {71, "G"}, {72, "H"}, {73, "I"}, {74, "J"}, {75, "K"}, {76, "L"}, {77, "M"}, {78, "N"}, {79, "O"}, {80, "P"}, {81, "Q"}, {82, "R"}, {83, "S"}, {84, "T"}, {85, "U"}, {86, "V"}, {87, "W"}, {88, "X"}, {89, "Y"}, {90, "Z"}, {91, "WIN"}, {96, "NU0"}, {97, "NU1"}, {98, "NU2"}, {99, "NU3"}, {100, "NU4"}, {101, "NU5"}, {102, "NU6"}, {103, "NU7"}, {104, "NU8"}, {105, "NU9"}, {106, "*"}, {107, "+"}, {109, "-"}, {110, "."}, {111, "/"}, {112, "F1"}, {113, "F2"}, {114, "F3"}, {115, "F4"}, {116, "F5"}, {117, "F6"}, {118, "F7"}, {119, "F8"}, {120, "F9"}, {121, "F10"}, {122, "F11"}, {123, "F12"}, {124, "F13"}, {125, "F14"}, {126, "F15"}, {127, "F16"}, {128, "F17"}, {129, "F18"}, {130, "F19"}, {131, "F20"}, {132, "F21"}, {133, "F22"}, {134, "F23"}, {135, "F24"}, {144, "NLK"}, {145, "SCL"}, {186, ";"}, {187, "="}, {188, ","}, {189, "-"}, {190, "."}, {191, "/?"}, {192, "~"}, {219, "["}, {220, "\\"}, {221, "]"}, {222, "'\""}
		};
		static vector<string> AimBotMod = { "内存自瞄", "静默自瞄" };
		static vector<string> AimBotPos = { "头部", "胸部", "脚部" };

	/*	bool Tab(const string name, FVector2D pos, FVector2D size, bool active);

		bool GroupBox(const string name, float x, float y, float w, float h, bool tab_enable, int* tab, int maxtab = 1);

		void Slider(float min, float max, const string name, float* item, float step = 0.1f);

		void Slider(int min, int max, const string name, int* item, int step = 1);

		void CheckBox(const string& name, bool* item, bool sameLine = false);

		bool IsKeyPressed(int key);

		bool Window();

		void ComboBox(const string name, vector<string> itemname, int* item);
		void MultiComboBox(const string name, vector<string> itemname, bool* item, float scrollStep = 20.0f);


		void Keybinds(const std::string& name, int* item);

		bool IsAsyncKeyPressed(int key);*/

	}

	namespace Draw
	{
		void DrawMenuText(float x, float y, uint32_t Size, bool bCentreX, bool bCentreY, FColor Color, const wchar_t* text, ...);


		void DrawEspText(UCanvas* Canvas, float x, float y, uint32_t Size, bool bCentreX, bool bCentreY, FLinearColor Color, const wchar_t* text, ...);

		inline FVector2D MousePosition = { 0.0f, 0.0f };

		void DrawCursor(FColor Color);
	}



}