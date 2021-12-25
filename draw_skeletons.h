#pragma once

#include "Misc.h"
#include "engine_render.h"
#include "world_rendering.h"

inline void PostRender(UCanvas* pCanvas) {

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


	if (!pCanvas) return;
	if (!World()) return;

	if (!hk_renderbasics::MathLib) hk_renderbasics::MathLib = (SDK::UKismetMathLibrary*)SDK::UKismetMathLibrary::StaticClass();

	if (hk_renderbasics::LocalController->WasInputKeyJustPressed(KeyName::ToggleKey) & 1)
	{
		framework::show_menu = !framework::show_menu;
	}
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

		FVector2D vPos[100];
		std::vector<int> nBoneIDS = { 66 ,65 ,36 ,2 ,9 ,62,10,38,11,39,67,74,73,80,68,75,71,78,72,79 }; // when drawing bones
		std::vector<int> nBoneIDSSimple = { 66, 9, 62, 11, 39, 72, 79 };                                // when not drawing bones.
		std::vector<std::vector<int>> nBonePairs =
		{
		{99, 1},
		{1, 3},
		{2, 4},
		{-+2, 5},
		{4, 6},
		{5, 7},
		{6, 8},
		{7, 9},
		{3, 10},
		{3, 11},
		{10, 12},
		{11, 13},
		{12, 14},
		{13, 15},
		{14, 16},
		{15, 17},
		{16, 18},
		{17, 19}
		};

		size_t nIndex = 0;

		float minX = FLT_MAX;
		float maxX = -FLT_MAX;
		float minY = FLT_MAX;
		float maxY = -FLT_MAX;

		if (bDrawBones)
		{
			for (auto ID : nBoneIDS)
			{
				bool bResult = false;
				if (ID == 66)
				{
					FVector vWorldPos;
					if (hkfunctions::GetBoneWorld((ACharacter*)Actor, 66, &vWorldPos))
					{
						hk_renderbasics::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[99]);

						vWorldPos.Z += 15.5f;
						bResult = hk_renderbasics::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[nIndex]);
					}
				}
				else
				{
					nIndex++;
					bResult = hkfunctions::GetBoneScreen((ACharacter*)Actor, ID, &vPos[nIndex]);
				}

				if (bResult)
				{
					minX = min(vPos[nIndex].X, minX);
					maxX = max(vPos[nIndex].X, maxX);
					minY = min(vPos[nIndex].Y, minY);
					maxY = max(vPos[nIndex].Y, maxY);
				}
			}
		}
		else
		{
			for (auto ID : nBoneIDSSimple)
			{
				bool bResult = false;
				if (ID == 66)
				{
					FVector vWorldPos;
					if (hkfunctions::GetBoneWorld((ACharacter*)Actor, 66, &vWorldPos))
					{
						bResult = hk_renderbasics::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[99]);

						vWorldPos.Z += 15.5f;
						bResult = hk_renderbasics::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[nIndex]);
					}
				}
				else
				{
					nIndex++;
					bResult = hkfunctions::GetBoneScreen((ACharacter*)Actor, ID, &vPos[nIndex]);
				}

				if (bResult)
				{
					minX = min(vPos[nIndex].X, minX);
					maxX = max(vPos[nIndex].X, maxX);
					minY = min(vPos[nIndex].Y, minY);
					maxY = max(vPos[nIndex].Y, maxY);
				}
			}
		}

		RECT hk_result;
		hk_result.top = minY;
		hk_result.bottom = maxY - minY;
		hk_result.left = minX;
		hk_result.right = maxX - minX;
		rDraw = hk_result;
		auto topLeft = FVector2D(minX - 3.0f, minY - 3.0f);
		auto bottomRight = FVector2D(maxX + 3.0f, maxY + 3.0f);
		auto centerTop = FVector2D((topLeft.X + bottomRight.X) / 2.0f + +10 + 1.65, topLeft.Y);
		auto theAdditionY = (bottomRight.Y - topLeft.Y) / 5;
		auto theAdditionX = (bottomRight.X - topLeft.X) / 3;
		auto topRight = FVector2D(bottomRight.X, topLeft.Y);
		auto bottomLeft = FVector2D(topLeft.X, bottomRight.Y);
		float th2 = 2.f;
		float DummyThic = 1.f;
		SDK::AFortPlayerPawn* mypawn = (SDK::AFortPlayerPawn*)hk_renderbasics::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn;
		auto mapawn = (SDK::AFortPlayerPawnAthena*)hk_renderbasics::LocalController->K2_GetPawn();
		auto BoxColor = visible ? SDK::FLinearColor(0.f, 255.f, 0.f, 1.0f) : SDK::FLinearColor(255.f, 0.f, 0.f, 1.0f);

		

		if (mesh)
		{
			auto playerstate = Actor->PlayerState;
			auto Statics = hk_renderbasics::gGameplayStatics;


			if (playerstate)
			{

				FVector Mainhead = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_HEAD), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector head = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_NECK), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector chest = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_CHEST), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lshoulder = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_SHOULDER_2), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rshoulder = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_SHOULDER), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lelbow = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_ELBOW), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector relbow = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_ELBOW), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lhand = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_HAND_ROOT_1), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rhand = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_HAND_ROOT_1), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector pelvis = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_PELVIS_1), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lleg = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_LEG_ROOT), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rleg = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_LEG_ROOT), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lknee = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_KNEE), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rknee = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_KNEE), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lfoot = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FOOT_MID), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rfoot = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FOOT_MID), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lfootroot = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FOOT_ROOT), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rfootroot = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FOOT_ROOT), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());

				FVector lfinger1 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FINGER_1), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lfinger2 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FINGER_2), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lfinger3 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FINGER_3), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lfinger4 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_FINGER_4_), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());

				FVector rfinger1 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FINGER_1), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rfinger2 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FINGER_2), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rfinger3 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FINGER_3), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rfinger4 = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_FINGER_4_), hk_renderbasics::LocalController->PlayerCameraManager->GetCameraRotation());
				auto centerTop = FVector2D((topLeft.X + bottomRight.X) / 2.0f + +10 + 1.65, topLeft.Y);
				auto namePosX = centerTop.X;
				auto namePosY = centerTop.Y;
				auto centerBottom = FVector2D((bottomLeft.X + topRight.X) / 2.0f + +10 + 1.65, bottomLeft.Y);
				auto DistanceX = centerBottom.X;
				auto DistanceY = centerBottom.Y;

				if (options::Visuals::skeleton)
				{
					pCanvas->K2_DrawLine(FVector2D(Mainhead.X, Mainhead.Y), FVector2D(head.X, head.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(head.X, head.Y), FVector2D(chest.X, chest.Y), 1, White);

					pCanvas->K2_DrawLine(FVector2D(head.X, head.Y), FVector2D(rshoulder.X, rshoulder.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(head.X, head.Y), FVector2D(lshoulder.X, lshoulder.Y), 1, White);

					pCanvas->K2_DrawLine(FVector2D(lshoulder.X, lshoulder.Y), FVector2D(lelbow.X, lelbow.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(lelbow.X, lelbow.Y), FVector2D(lhand.X, lhand.Y), 1, White);

					pCanvas->K2_DrawLine(FVector2D(rshoulder.X, rshoulder.Y), FVector2D(relbow.X, relbow.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(relbow.X, relbow.Y), FVector2D(rhand.X, rhand.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(head.X, head.Y), FVector2D(chest.X, chest.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(chest.X, chest.Y), FVector2D(pelvis.X, pelvis.Y), 1, White);

					pCanvas->K2_DrawLine(FVector2D(pelvis.X, pelvis.Y), FVector2D(lleg.X, lleg.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(lleg.X, lleg.Y), FVector2D(lknee.X, lknee.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(lknee.X, lknee.Y), FVector2D(lfoot.X, lfoot.Y), 1, White);

					pCanvas->K2_DrawLine(FVector2D(pelvis.X, pelvis.Y), FVector2D(rleg.X, rleg.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(rleg.X, rleg.Y), FVector2D(rknee.X, rknee.Y), 1, White);
					pCanvas->K2_DrawLine(FVector2D(rknee.X, rknee.Y), FVector2D(rfoot.X, rfoot.Y), 1, White);

				

				}
			}
		}
	}
}





inline void engine__rendering(UObject* pObject, UCanvas* pCanvas, SDK::APlayerCameraManager* CamManager, float MaxDist = 250) {

	if (pCanvas) {

		width = pCanvas->SizeX;
		height = pCanvas->SizeY;

		PostRender(pCanvas);
	}

	return RetRendering(pObject, pCanvas, CamManager, MaxDist);

}

inline void render::RenderCanvas() {

	engine_render_t* pr_ptr;
	pr_ptr = (engine_render_t*)((DWORD64)GetModuleHandleW(NULL) + 0x761AB01); // HERE IS THE POST RENDER VTABLE.
	RetRendering = (engine_render_t)*pr_ptr;
	*pr_ptr = RetRendering;
}
