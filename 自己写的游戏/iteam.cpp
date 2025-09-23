#include "iteam.h"

IteamRender::IteamRender(AActor* Enemy, APlayerController* LocalPlayer, UCanvas* Canvas)
{
	PActor = Enemy;
	RenderCanvas = Canvas;
	Controller = LocalPlayer;
	if (SAFE_PTR(Enemy->RootComponent))
	{
		ITeamsPoint = Enemy->RootComponent->Pos;
		jul = FVector::Distance(ITeamsPoint, Controller->PlayerCameraManager->GetCameraLocation()) / 100;

		if (Controller->WorldToScreen(ITeamsPoint, ScreenPont))
		{
			IteamClassName = PActor->GetName();
		}
	}
	
}

void IteamRender::DrawAInventoryPickup_OpenBox()
{
	if (IteamClassName.find(L"BP_Interactor") != std::string::npos
		&& IteamClassName.find(L"false") != std::string::npos)
	{
		wchar_t StrName[1024];
		FString PicKupStr;
		if (SAFE_PTR(PActor->GetItemName().TextData->DisplayString.Data) && SAFE_PTR(PActor->GetItemName().TextData))
		{
			if (swprintf(StrName, _countof(StrName), L"%ws [%0.2fm]\n", PActor->GetItemName().TextData->DisplayString.Data, jul) > 0)
			{
				wstring strtemp = StrName;
				PicKupStr.Data = (wchar_t*)(strtemp.c_str());
				PicKupStr.Count = static_cast<int32_t>(wcslen(strtemp.c_str())) + 1;
				PicKupStr.Max = PicKupStr.Count;
				if (Hooks::Menu::容器距离 > jul)
				{
					RenderCanvas->K2_StrokeText(PicKupStr, { 1.0f, 1.0f, 0.0f, 1.0f }, ScreenPont);
				}
			}
			
		}

	}

}

void IteamRender::DrawInventory_DeadBody()
{
	if (IteamClassName.find(L"Inventory_DeadBody") != std::string::npos)
	{
		wchar_t StrName[1024];
		FString PicKupStr;
		if (swprintf(StrName, _countof(StrName), L"%ws [%0.2fm]\n", L"盒子", jul) > 0)
		{
			wstring strtemp = StrName;
			PicKupStr.Data = (wchar_t*)(strtemp.c_str());
			PicKupStr.Count = static_cast<int32_t>(wcslen(strtemp.c_str())) + 1;
			PicKupStr.Max = PicKupStr.Count;
			if (Hooks::Menu::盒子距离 > jul)
			{
				RenderCanvas->K2_StrokeText(PicKupStr, { 1.0f, 1.0f, 1.0f, 1.0 }, ScreenPont);
			}
		}
	

		
	}

}

FLinearColor GetQualityColor(uint32_t Quality)
{
	FLinearColor TextColor;
	switch (Quality) {
	case 1: // 白色（普通）
		TextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 2: // 绿色（良好）
		TextColor = FLinearColor(0.1f, 0.9f, 0.2f, 1.0f);
		break;
	case 3: // 蓝色（优质）
		TextColor = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);
		break;
	case 4: // 紫色（稀有）
		TextColor = FLinearColor(0.7f, 0.2f, 1.0f, 1.0f);
		break;
	case 5: // 金色（史诗）
		TextColor = FLinearColor(1.0f, 0.8f, 0.1f, 1.0f);
		break;
	case 6: // 红色（传说）
	default: 
		TextColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	return TextColor;
}

void IteamRender::DrawBP_InventoryPickup_()
{
	if (IteamClassName.find(L"BP_InventoryPickup_") != std::string::npos)
	{
		wchar_t Value[256];
		wchar_t StrName[256];
		FString PicKupStr;
		FString ValueStr;
		if (SAFE_PTR(PActor->GetItemName().TextData->DisplayString.Data) && SAFE_PTR(PActor->GetItemName().TextData))
		{
			if (swprintf(StrName, _countof(StrName), L"%ws [%0.2fm]\n", PActor->GetItemName().TextData->DisplayString.Data, jul) > 0)
			{
				wstring strtemp = StrName;
				PicKupStr.Data = (wchar_t*)(strtemp.c_str());
				PicKupStr.Count = static_cast<int32_t>(wcslen(strtemp.c_str())) + 1;
				PicKupStr.Max = PicKupStr.Count;
				if (SAFE_PTR(PActor->ItemData))
				{
					if (swprintf(Value, _countof(Value), L"￥%d \n", PActor->ItemData->ItemValue) > 0)
					{
						wstring Valuestrtemp = Value;
						ValueStr.Data = (wchar_t*)(Valuestrtemp.c_str());
						ValueStr.Count = static_cast<int32_t>(wcslen(Valuestrtemp.c_str())) + 1;
						ValueStr.Max = ValueStr.Count;

						uint32_t Quality = PActor->ItemData->Quality;
						if (PActor->ItemData->ItemValue >(uint32_t)Hooks::Menu::价值 && Hooks::Menu::物资距离>jul)
						{			
							RenderCanvas->K2_StrokeText(ValueStr, GetQualityColor(Quality), { ScreenPont.x, ScreenPont.y - 15 });
							RenderCanvas->K2_StrokeText(PicKupStr, GetQualityColor(Quality), ScreenPont);

						}
						

						
					}
				

				}



			}
					

		
		}
		
		
	}
}



