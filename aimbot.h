#pragma once

#include "multitask.h"
#include "Misc.h"
#include "world_rendering.h"
#include "engine_render.h"

// AS YOU CAN SEE THEY USE AN INTERNAL AIMBOT USING SDKS AND WITHOUT ANY SIGS.
// FOR THE PSILENT YOU JUST NEED TO FIX THE PROCESS EVENT



inline BOOL(*LOS)(SDK::APlayerController* controller, SDK::AFortPlayerPawn* pawn, SDK::FVector* vp, bool alt) = nullptr;
inline BOOLEAN LineOFSightTo(SDK::APlayerController* controller, SDK::AFortPlayerPawn* pawn, SDK::FVector* vp) {
	return LOS(controller, pawn, vp, false);
}
inline void rendering(UCanvas* pCanvas) {
	KeyNames();
	SDK::AFortPlayerPawn* Target;
	AFortPawn* closest_player = 0;
	float closest_distance = FLT_MAX;
	SDK::USkeletalMeshComponent* mesh = Target->Mesh;
	static SDK::UKismetSystemLibrary* KismetSystemLibrary = NULL;
	static SDK::UFortKismetLibrary* FortKismetLib = NULL;
	static SDK::UGameplayStatics* GameplayStatics = NULL;
	if (!KismetSystemLibrary) KismetSystemLibrary = (SDK::UKismetSystemLibrary*)SDK::UKismetSystemLibrary::StaticClass();
	if (!FortKismetLib) FortKismetLib = (SDK::UFortKismetLibrary*)SDK::UFortKismetLibrary::StaticClass();
	if (!GameplayStatics) GameplayStatics = (SDK::UGameplayStatics*)SDK::UGameplayStatics::StaticClass();
	framework::render_menu(pCanvas);

	auto AllPlayers = FortKismetLib->STATIC_GetFortPlayerPawns(hk_renderbasics::gWorld = (UWorld*)(*(uintptr_t*)hk_renderbasics::UWorld_Offset));
	for (int i = 0; i < AllPlayers.Num(); i++)
	{
		float max = 999.f;
		SDK::AFortPlayerPawn* Actor = (AFortPlayerPawn*)AllPlayers[i];
		if (Actor == (AFortPlayerPawnAthena*)hk_renderbasics::LocalController->K2_GetPawn())  continue;
		if (FortKismetLib->STATIC_OnSameTeam(hk_renderbasics::LocalController->AcknowledgedPawn, Actor)) continue;
		if (Actor->IsDead()) continue;
		if (Actor->IsDBNO())continue;
		SDK::FVector viewPoint = { 0, 0, 0 };
		bool visible = LineOFSightTo(hk_renderbasics::LocalController, Actor, &viewPoint) && (options::Aim::visible_check);
		auto OutlineColor = SDK::FLinearColor(0.f, 0.f, 0.f, 1.0f);
		auto CrosshairColor = SDK::FLinearColor(255.f, 255.f, 255.f, 1.0f);
		auto White = SDK::FLinearColor(255.f, 255.f, 255.f, 255.f);
		SDK::USkeletalMeshComponent* mesh = Actor->Mesh;
		RECT rDraw;
		bool bDrawBones = true;
		if (visible || !options::Aim::visible_check)
		{
			SDK::FVector2D wnd_size = SDK::FVector2D(width, height);
			FVector target = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, (int)options::Aim::head && (int)options::Aim::neck && (int)options::Aim::chest && (int)options::Aim::pelvis), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
			auto dist = GetDistance2D(wnd_size / 2, target);

			if (dist < options::Aim::fov_range && dist < closest_distance)
			{

				closest_distance = dist;
				closest_player = Actor;
			}
			SDK::AFortWeapon* FortWeapon = (SDK::AFortWeapon*)hk_renderbasics::FortWeapon;
			SDK::AFortPlayerPawn* MyPawn = (SDK::AFortPlayerPawn*)hk_renderbasics::LocalController->AcknowledgedPawn;
			SDK::AFortPlayerPawn* mypawn = (SDK::AFortPlayerPawn*)hk_renderbasics::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn;
			auto mapawn = (SDK::AFortPlayerPawnAthena*)hk_renderbasics::LocalController->K2_GetPawn();
			auto Camera = hk_renderbasics::LocalController->PlayerCameraManager;
				if (bAimingLock)
					bAimingLock = false;

				if (closest_player && hk_renderbasics::LocalController->IsInputKeyDown(KeyName::Right) && hk_renderbasics::LocalController->AcknowledgedPawn->CurrentWeapon)
				{
					if (hk_renderbasics::LocalController->AcknowledgedPawn->CurrentWeapon->GetWeaponDataItemType() == SDK::EFortItemType::WeaponRanged)
					{

						hkfunctions::SetAim(Camera, (SDK::AFortPlayerPawn*)closest_player);

					}
				}
			}
		}
	}