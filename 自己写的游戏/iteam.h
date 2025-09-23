#pragma once
#include "base.h"
#include "class.h"
#include"Hooks.h"
class IteamRender
{
public:
	IteamRender(AActor* Enemy, APlayerController* LocalPlayer, UCanvas* Canvas);

	void DrawAInventoryPickup_OpenBox();

	void DrawInventory_DeadBody();

	void DrawBP_InventoryPickup_();


private:

	UCanvas* RenderCanvas = nullptr;
	AActor* PActor = nullptr;
	APlayerController* Controller = nullptr;

	wstring IteamClassName = L"";
	float jul = 0;

	FVector ITeamsPoint = {};

	FVector2D ScreenPont = {};

	wstring Inventory_DeadBody;
	wstring AInventoryPickup_OpenBox;
	wstring AInventoryPickup;
};
