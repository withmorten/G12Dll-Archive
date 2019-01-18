#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "..\G12Dll\MemoryMgr.h"

#define G12INI_SECTION "G2Barrier"

#include "..\G12Dll\G12.h"

#include "..\G12Dll\G2.hpp"
#include "..\G12Dll\G2.h"
#include "g2barrier.hpp"

FILE *conin, *conout;

#define WORLD_NAME "WORLD"

char worldName[MAX_PATH];

zVEC2 newPointList[38];

float
hMagFrontier::GetDistance(zVEC3 &pos, float &dist, zVEC3 &nearestPoint)
{
	float real_dist;
	zVEC2 playerPos, point2, point1, distToPoints;

	int x;

	dist = 10000000.0;

	playerPos.x = pos.x;
	playerPos.y = pos.z;

	if (playerPos.x == 0.0f && playerPos.y == 0.0f)
	{
		return dist;
	}

	for (x = 1; x < 38; x++)
	{
		point1.x = newPointList[x - 1].x;
		point1.y = newPointList[x - 1].y;

		point2.x = newPointList[x].x;
		point2.y = newPointList[x].y;

		GetDistanceToPoints(point1, point2, playerPos, distToPoints);

		real_dist = sqrtf((distToPoints.y - playerPos.y) * (distToPoints.y - playerPos.y) +
							(distToPoints.x - playerPos.x) * (distToPoints.x - playerPos.x));

		if (real_dist < dist)
		{
			dist = real_dist;
		}
	}

	return dist;
}

void
hMagFrontier::DoCheck(void)
{
	this->oCMagFrontier::DoCheck();

	oCGame *Game = *(oCGame **)0x00AB0884; // ogame

	if (Game && this->npc == *(oCNpc **)0x00AB2684 // oCNpc::player
		&& !(*(zCCamera **)0x008D7F94)->connectedVob->homeWorld->csPlayer->GetPlayingGlobalCutscene()) // zCCamera::activeCam
	{
		oCWorld *World = Game->GetGameWorld();
		if (World)
		{
			if (!_stricmp(World->worldName.ptr, worldName))
			{
				if (this->npc)
				{
					zVEC3 playerProjPos, startPoint;
					playerProjPos.x = this->npc->trafoObjToWorld.row[0].w;
					playerProjPos.y = this->npc->trafoObjToWorld.row[1].w;
					playerProjPos.z = this->npc->trafoObjToWorld.row[2].w;

					float distToBarriere = 60000.0f;
					this->GetDistance(playerProjPos, distToBarriere, startPoint);

					if (distToBarriere > 1200.0f || distToBarriere < 0.0f)
					{
						this->DisposeShootFX();
						this->DisposeWarningFX();
					}
					else
					{
						float f = (1200.0f - distToBarriere) * 0.018181818f;
						int level = (int)f;

						if (!level)
						{
							level = 1;
						}

						this->DoWarningFX(level);

						if (*(int *)0x00AB2660 || (distToBarriere > 650.0f || distToBarriere < 0.0f)) // oCNpc::godmode
						{
							this->DisposeShootFX();
						}
						else
						{
							this->DoShootFX(startPoint);
						}
					}
				}
			}
		}
	}
}

void
MagicFrontierNewPointListInit(void)
{
	// newPointList from Gothic 1
	newPointList[0].x = 57939.199f;
	newPointList[0].y = 1280.28f;
	newPointList[1].x = 55954.398f;
	newPointList[1].y = 5421.5098f;
	newPointList[2].x = 52856.801f;
	newPointList[2].y = 10047.0f;
	newPointList[3].x = 49451.898f;
	newPointList[3].y = 14908.2f;
	newPointList[4].x = 44199.801f;
	newPointList[4].y = 20513.301f;
	newPointList[5].x = 37684.199f;
	newPointList[5].y = 26271.199f;
	newPointList[6].x = 30434.0f;
	newPointList[6].y = 31462.4f;
	newPointList[7].x = 25573.6f;
	newPointList[7].y = 32692.699f;
	newPointList[8].x = 21248.301f;
	newPointList[8].y = 35176.102f;
	newPointList[9].x = 19450.699f;
	newPointList[9].y = 35205.0f;
	newPointList[10].x = 16263.1f;
	newPointList[10].y = 32799.602f;
	newPointList[11].x = 10755.6f;
	newPointList[11].y = 34744.398f;
	newPointList[12].x = 9736.9004f;
	newPointList[12].y = 37990.5f;
	newPointList[13].x = 8218.5996f;
	newPointList[13].y = 38393.102f;
	newPointList[14].x = 4065.0f;
	newPointList[14].y = 39018.398f;
	newPointList[15].x = 839.90002f;
	newPointList[15].y = 39079.301f;
	newPointList[16].x = -9312.9004f;
	newPointList[16].y = 38694.199f;
	newPointList[17].x = -19258.301f;
	newPointList[17].y = 40991.398f;
	newPointList[18].x = -29684.1f;
	newPointList[18].y = 40535.699f;
	newPointList[19].x = -39313.699f;
	newPointList[19].y = 36558.801f;
	newPointList[20].x = -49319.602f;
	newPointList[20].y = 31970.199f;
	newPointList[21].x = -54137.301f;
	newPointList[21].y = 26761.699f;
	newPointList[22].x = -62089.301f;
	newPointList[22].y = 21598.1f;
	newPointList[23].x = -66193.703f;
	newPointList[23].y = 12999.2f;
	newPointList[24].x = -66132.297f;
	newPointList[24].y = 6204.0f;
	newPointList[25].x = -63855.199f;
	newPointList[25].y = -5700.7998f;
	newPointList[26].x = -59385.102f;
	newPointList[26].y = -10081.5f;
	newPointList[27].x = -56013.801f;
	newPointList[27].y = -22393.4f;
	newPointList[28].x = -47250.301f;
	newPointList[28].y = -28502.0f;
	newPointList[29].x = -37136.5f;
	newPointList[29].y = -38319.199f;
	newPointList[30].x = -24664.699f;
	newPointList[30].y = -46687.898f;
	newPointList[31].x = -7860.6001f;
	newPointList[31].y = -48966.602f;
	newPointList[32].x = 4876.6001f;
	newPointList[32].y = -49691.0f;
	newPointList[33].x = 23147.801f;
	newPointList[33].y = -47875.102f;
	newPointList[34].x = 48722.301f;
	newPointList[34].y = -39488.801f;
	newPointList[35].x = 55902.398f;
	newPointList[35].y = -31909.801f;
	newPointList[36].x = 61238.602f;
	newPointList[36].y = -23412.801f;
	newPointList[37].x = 60230.102f;
	newPointList[37].y = -6641.8999f;
}

void
MagicFrontierNewPointListInitGRM(void)
{
	// newPointList from GRM
	newPointList[17].x = -26219.2f;
	newPointList[17].y = 40844.2f;
	newPointList[18].x = -34576.0f;
	newPointList[18].y = 43032.3f;
	newPointList[19].x = -44458.8f;
	newPointList[19].y = 43099.2f;
	newPointList[20].x = -49763.7f;
	newPointList[20].y = 37384.8f;
}

void
PatchMagicFrontier(void)
{
	if (G12GetPrivateProfileInt("MagicFrontierEnable", 0))
	{
		if (!strlen(worldName))
		{
			G12GetPrivateProfileString("WorldName", WORLD_NAME, worldName, MAX_PATH);
		}

		MagicFrontierNewPointListInit();

		// Use our own oCMagFrontier::DoCheck()
		InjectHook(0x0073E71B, &hMagFrontier::DoCheck, PATCH_CALL);
	}

	if (G12GetPrivateProfileInt("MagicFrontierPointsWorldGRM", 0))
	{
		// GRM fixes has some different points ... just included here for now
		MagicFrontierNewPointListInitGRM();
	}
}

#define BARRIER_ALPHA_MAX 120
#define BARRIER_COLOR 0x00FFFFFF

#define NEW_NUM_MAX_THUNDERS 20

hSkyControler_Barrier *SkyControler_Barrier = NULL;

int Barrier_IgnoreSkyEffectsSetting;
int Barrier_AlwaysVisible;
int Barrier_G1DecalDim;
int Barrier_FadeTimer;
int Barrier_TimeOn, Barrier_TimeOnMin, Barrier_TimeOnMax;
int Barrier_TimeOff, Barrier_TimeOffMin, Barrier_TimeOffMax;

int hBarrier_bThunder1, hBarrier_bThunder2, hBarrier_bThunder3, hBarrier_bThunder4;

zCSoundFX *hBarrier_sfx1, *hBarrier_sfx2, *hBarrier_sfx3, *hBarrier_sfx4;
zTSoundHandle hBarrier_sfxHandle1, hBarrier_sfxHandle2, hBarrier_sfxHandle3, hBarrier_sfxHandle4;

float delayTimeSector1 = 4000.0f;
float delayTimeSector2 = 200.0f;
float delayTimeSector3 = 6000.0f;
float delayTimeSector4 = 10000.0f;

zCSoundSystem *SoundSystem;

myThunder oCBarrier_myThunderTemp[NEW_NUM_MAX_THUNDERS], hBarrier_myThunderTemp[NEW_NUM_MAX_THUNDERS];
int oCBarrier_numMyThundersTemp, hBarrier_numMyThundersTemp;

int
hBarrier::Render(zTRenderContext &rndContext, int fadeInOut, int alwaysVisible)
{
	zCRnd_D3D *Renderer = *(zCRnd_D3D **)0x00982F08; // zrenderer
	zCCamera *Camera = *(zCCamera **)0x008D7F94; // zCCamera::activeCam
	zCMaterial *FrontierMat = this->skySphereMesh->polyList[0]->Material;

	int zBufferWriteEnabled = Renderer->GetZBufferWriteEnabled();
	float farClipZ = Camera->farClipZ;

	Renderer->SetZBufferWriteEnabled(0);
	Camera->SetFarClipZ(2000000.0f);

	if (!Barrier_AlwaysVisible)
	{
		if (this->fadeIn)
		{
			if (this->fadeState != BARRIER_ALPHA_MAX)
			{
				this->fadeState++;
				FrontierMat->color.SetAlphaByte((BYTE)this->fadeState);
			}
			else
			{
				this->fadeIn = 0;
				this->bFadeInOut = 0;
				Barrier_FadeTimer = Barrier_TimeOnMin + _rand() % ((Barrier_TimeOnMax + 1) - Barrier_TimeOnMin);
			}
		}
		else if (this->fadeOut)
		{
			if (this->fadeState)
			{
				this->fadeState--;
				FrontierMat->color.SetAlphaByte((BYTE)this->fadeState);
			}
			else
			{
				this->fadeOut = 0;
				this->bFadeInOut = 0;
				Barrier_FadeTimer = Barrier_TimeOffMin + _rand() % ((Barrier_TimeOffMax + 1) - Barrier_TimeOffMin);
			}
		}
		else if (!this->bFadeInOut)
		{
			if (Barrier_FadeTimer)
			{
				Barrier_FadeTimer--;
			}
			else
			{
				if (this->fadeState == BARRIER_ALPHA_MAX)
				{
					this->bFadeInOut = 1;
					this->fadeOut = 1;
				}
				else
				{
					this->bFadeInOut = 1;
					this->fadeIn = 1;
				}
			}
		}
	}

	int unused;

	this->RenderLayer(rndContext, 0, &unused);
	this->RenderLayer(rndContext, 1, &unused);

	if (this->fadeState == BARRIER_ALPHA_MAX) // showThunders
	{
		zSTRING MfxBarriereAmbient("MFX_Barriere_Ambient");

		zTSound3DParams sound3DParams;
		sound3DParams.obstruction = 0.0f;
		sound3DParams.volume = 1.0f;
		sound3DParams.radius = -1.0f;
		sound3DParams.loopType = 0;
		sound3DParams.coneAngleDeg = 0.0f;
		sound3DParams.reverbLevel = 1.0f;
		sound3DParams.isAmbient3D = 0;
		sound3DParams.pitchOffset = -999999.0f;

		if (!hBarrier_bThunder1 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle1) &&
			*(float *)0x0099B3DC - delayTimeSector1 > 8000.f) // actualTime
		{
			this->AddThunder(this->startPointList1[(this->numStartPoints1 - 1) & _rand()], 11, 0, 1);
			hBarrier_bThunder1 = 1;
			delayTimeSector1 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx1)
			{
				hBarrier_sfx1 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle1 = SoundSystem->PlaySound3D(hBarrier_sfx1, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_bThunder2 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle2) &&
			*(float *)0x0099B3DC - delayTimeSector2 > 6000.f) // actualTime
		{
			this->AddThunder(this->startPointList2[(this->numStartPoints2 - 1) & _rand()], 11, 0, 2);
			hBarrier_bThunder2 = 1;
			delayTimeSector2 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx2)
			{
				hBarrier_sfx2 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle2 = SoundSystem->PlaySound3D(hBarrier_sfx2, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_bThunder3 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle3) &&
			*(float *)0x0099B3DC - delayTimeSector3 > 14000.f) // actualTime
		{
			this->AddThunder(this->startPointList3[(this->numStartPoints3 - 1) & _rand()], 11, 0, 3);
			hBarrier_bThunder3 = 1;
			delayTimeSector3 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx3)
			{
				hBarrier_sfx3 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle3 = SoundSystem->PlaySound3D(hBarrier_sfx3, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_bThunder4 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle4) &&
			*(float *)0x0099B3DC - delayTimeSector4 > 2000.f) // actualTime
		{
			this->AddThunder(this->startPointList4[(this->numStartPoints4 - 1) & _rand()], 11, 0, 4);
			hBarrier_bThunder4 = 1;
			delayTimeSector4 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx4)
			{
				hBarrier_sfx4 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle4 = SoundSystem->PlaySound3D(hBarrier_sfx4, Camera->connectedVob, 0, &sound3DParams);
		}

		for (int x = 0; x < this->numMyThunders; x++)
		{
			this->RenderThunder(&this->myThunderList[x], rndContext);
		}

		Renderer->FlushPolys();

		if (hBarrier_sfx1)
		{
			SoundSystem->UpdateSound3D(hBarrier_sfxHandle1, NULL);
		}

		if (hBarrier_sfx2)
		{
			SoundSystem->UpdateSound3D(hBarrier_sfxHandle2, NULL);
		}

		if (hBarrier_sfx3)
		{
			SoundSystem->UpdateSound3D(hBarrier_sfxHandle3, NULL);
		}

		if (hBarrier_sfx4)
		{
			SoundSystem->UpdateSound3D(hBarrier_sfxHandle4, NULL);
		}
	}

	Renderer->SetZBufferWriteEnabled(zBufferWriteEnabled);
	Camera->SetFarClipZ(farClipZ);

	return fadeInOut;
}

int
hBarrier::RenderThunder(myThunder *thunder, zTRenderContext &rndContext)
{
	if (!thunder->m_bActive)
	{
		return 0;
	}

	thunder->m_nEndVisSeg = *(float *)0x0099B3D8 * 0.0049999999f + thunder->m_nEndVisSeg; // frameTimeF

	if (thunder->m_nStartVisSeg >= 0.89999998f)
	{
		thunder->m_nStartVisSeg = 0.89999998f;
	}

	if (thunder->m_nEndVisSeg >= 0.89999998f)
	{
		thunder->m_nEndVisSeg = 0.89999998f;
	}

	if (thunder->m_pPolyStrip->numSeg <= 2)
	{
		thunder->m_nStartVisSeg = 0.89999998f;
	}

	if (thunder->m_nStartVisSeg >= 0.89999998f
		&& thunder->m_nEndVisSeg >= 0.89999998f
		&& thunder->m_nNumSubThunders <= 0)
	{
		if (!thunder->m_bIsSubThunder)
		{
			if (thunder->m_Sector == 1)
			{
				hBarrier_bThunder1 = 0;
			}
			if (thunder->m_Sector == 2)
			{
				hBarrier_bThunder2 = 0;
			}
			if (thunder->m_Sector == 3)
			{
				hBarrier_bThunder3 = 0;
			}
			if (thunder->m_Sector == 4)
			{
				hBarrier_bThunder4 = 0;
			}

			this->numMyThunders--;
		}

		this->RemoveThunder(thunder);
		thunder->m_bActive = 0;

		return 0;
	}

	if (thunder->m_nStartVisSeg != thunder->m_nEndVisSeg)
	{
		thunder->m_pPolyStrip->SetVisibleSegments(thunder->m_nStartVisSeg, thunder->m_nEndVisSeg);
		thunder->m_pPolyStrip->Render(rndContext);
	}

	for (int x = 0; x < thunder->m_nNumSubThunders; x++)
	{
		if (thunder->m_nEndVisSeg >= thunder->m_fSubStartSeg[x])
		{
			if (!this->RenderThunder(&thunder->m_pSubThunders[x], rndContext))
			{
				thunder->m_nNumSubThunders--;
			}
		}
	}

	if (!thunder->m_bIsSubThunder)
	{
		zMAT4 mat, matTemp, matTemp2;

		matTemp = *(zMAT4 *)0x008D45E8; // zMAT4::s_identity
		mat = *(zMAT4 *)0x008D45E8; // zMAT4::s_identity
		mat = rndContext.cam->GetTransform(1);

		mat.row[0].z = mat.row[0].z * -1.0f;
		mat.row[1].z = mat.row[1].z * -1.0f;
		mat.row[2].z = mat.row[2].z * -1.0f;

		mat.row[0].w = thunder->m_vPosition.x;
		mat.row[1].w = thunder->m_vPosition.y;
		mat.row[2].w = thunder->m_vPosition.z;

		matTemp2 = rndContext.cam->GetTransform(0);

		rndContext.cam->SetTransform(0, mat);
		this->thunderStartDecal->Render(rndContext);
		rndContext.cam->SetTransform(0, matTemp2);
	}

	return 1;
}

void
Barrier_Init(void)
{
	oCBarrier *Barrier = SkyControler_Barrier->barrier;
	Barrier->bFadeInOut = 1;

	zCMesh *FrontierMesh = Barrier->skySphereMesh;
	zCMaterial *FrontierMat = FrontierMesh->polyList[0]->Material;

	zSTRING BarrierTexture("BARRIERE.TGA");
	FrontierMat->SetTexture(BarrierTexture);
	FrontierMat->rndAlphaBlendFunc = zRND_ALPHA_FUNC_ADD;
	FrontierMat->color.SetAlphaByte((BYTE)Barrier->fadeState);

	int numPolys = FrontierMesh->numPoly;
	float maxHeight = FrontierMesh->bbox3D.maxs.y;
	float minHeight = maxHeight * 0.925000011920929f;

	for (int i = 0; i < numPolys; i++)
	{
		zCPolygon *Poly = FrontierMesh->polyList[i];
		int numVerts = Poly->PolyNumVert;

		for (int j = 0; j < numVerts; j++)
		{
			int alpha;

			zCVertFeature *Feat = Poly->Features[j];
			zCVertex *Vert = Poly->Vertices[j];

			if (Vert->position.y <= minHeight)
			{
				alpha = (int)(Vert->position.y * 0.0001250000059371814f * 255.0f);
			}
			else
			{
				alpha = (int)((maxHeight - Vert->position.y) * 255.0f / (maxHeight - minHeight));
			}

			if (alpha > 255) alpha = 255;
			if (alpha < 0) alpha = 0;

			Feat->lightDyn.color = BARRIER_COLOR;
			Feat->lightDyn.SetAlphaByte((BYTE)alpha);

			Feat->lightStat.color = BARRIER_COLOR;
			Feat->lightStat.SetAlphaByte((BYTE)alpha);
		}
	}
}

ASM(Barrier_Init_Hook)
{
	__asm
	{
		pushad
		call Barrier_Init
		popad
		mov eax, [eax + 0x34]
		lea ebx, [eax + eax * 2]
		RET(0x006B94FF)
	}
}

void
hSkyControler_Barrier::RenderSkyPre(void)
{
	this->zCSkyControler_Outdoor::RenderSkyPre();

	hBarrier *Barrier = (hBarrier *)this->barrier;

	if (!*(int *)0x00AB040C) // barrierInited
	{
		*(int *)0x00AB040C = 1; // barrierInited

		zCOption *Options = *(zCOption **)0x008CD988; // zoptions

		if (Options->ReadBool(*(zSTRING *)0x008CD380, "soundEnabled", 1)) // zOPT_SEC_SOUND
		{
			SoundSystem = *(zCSndSys_MSS **)0x0099B03C; // zsound
		}
		else
		{
			SoundSystem = *(zCSoundSystemDummy **)0x0099B03C; // zsound
		}

		SkyControler_Barrier = this;

		if (Barrier_AlwaysVisible)
		{
			Barrier->fadeState = BARRIER_ALPHA_MAX;
		}

		hBarrier_bThunder1 = 0;
		hBarrier_bThunder2 = 0;
		hBarrier_bThunder3 = 0;
		hBarrier_bThunder4 = 0;

		hBarrier_sfx1 = NULL;
		hBarrier_sfxHandle1 = 0;
		hBarrier_sfx2 = NULL;
		hBarrier_sfxHandle2 = 0;
		hBarrier_sfx3 = NULL;
		hBarrier_sfxHandle3 = 0;
		hBarrier_sfx4 = NULL;
		hBarrier_sfxHandle4 = 0;

		Barrier_FadeTimer = 0;

		if (Barrier_G1DecalDim)
		{
			Barrier->thunderStartDecal->SetDecalDim(5000.0f, 5000.0f);
		}

		Barrier->Init();

		// Instead of rewriting AddThunder, AddThunderSub and RemoveThunder just swap whichever thunder is supposed to be worked on
		_memcpy(&oCBarrier_myThunderTemp, this->barrier->myThunderList, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		oCBarrier_numMyThundersTemp = this->barrier->numMyThunders;

		_memcpy(&hBarrier_myThunderTemp, this->barrier->myThunderList, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		hBarrier_numMyThundersTemp = this->barrier->numMyThunders;
	}

	zCCamera *Camera = *(zCCamera **)0x008D7F94; // zCCamera::activeCam

	zTRenderContext rndContext;

	if (*(int *)0x008A5DB0 // zCSkyControler::s_skyEffectsEnabled
		&& this->rainFX.outdoorRainFXWeight > 0.5f
		&& this->rainFX.renderLightning && this->m_enuWeather)
	{
		_memset(&rndContext, 0x00, sizeof(zTRenderContext));
		rndContext.clipFlags = -1;
		rndContext.cam = Camera;
		rndContext.world = Camera->connectedVob->homeWorld;
		rndContext.vob = Camera->connectedVob;

		_memcpy(this->barrier->myThunderList, &oCBarrier_myThunderTemp, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		this->barrier->numMyThunders = oCBarrier_numMyThundersTemp;

		Barrier->oCBarrier::Render(rndContext, 0, 0);

		_memcpy(&oCBarrier_myThunderTemp, this->barrier->myThunderList, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		oCBarrier_numMyThundersTemp = this->barrier->numMyThunders;
	}

	oCGame *Game = *(oCGame **)0x00AB0884; // ogame

	if ((*(int *)0x008A5DB0 // zCSkyControler::s_skyEffectsEnabled
		|| Barrier_IgnoreSkyEffectsSetting)
		&& !_stricmp(Game->GetGameWorld()->worldName.ptr, worldName))
	{
		_memset(&rndContext, 0x00, sizeof(zTRenderContext));
		rndContext.clipFlags = -1;
		rndContext.cam = Camera;
		rndContext.world = Camera->connectedVob->homeWorld;
		rndContext.vob = Camera->connectedVob;

		_memcpy(this->barrier->myThunderList, &hBarrier_myThunderTemp, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		this->barrier->numMyThunders = hBarrier_numMyThundersTemp;

		Barrier->Render(rndContext, 0, 0);

		_memcpy(&hBarrier_myThunderTemp, this->barrier->myThunderList, sizeof(myThunder) * NEW_NUM_MAX_THUNDERS);
		hBarrier_numMyThundersTemp = this->barrier->numMyThunders;
	}
}

void
PatchBarrier(void)
{
	if (G12GetPrivateProfileInt("BarrierEnable", 0))
	{
		G12GetPrivateProfileString("WorldName", WORLD_NAME, worldName, MAX_PATH);

		Barrier_AlwaysVisible = G12GetPrivateProfileInt("BarrierAlwaysOn", 0);
		Barrier_IgnoreSkyEffectsSetting = G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", 0);
		Barrier_G1DecalDim = G12GetPrivateProfileInt("Barrier_G1DecalDim", 0);

		Barrier_TimeOn = G12GetPrivateProfileInt("BarrierTimeOn", 4000);
		Barrier_TimeOnMin = Barrier_TimeOn - (Barrier_TimeOn / 10);
		Barrier_TimeOnMax = Barrier_TimeOn + (Barrier_TimeOn / 10);

		Barrier_TimeOff = G12GetPrivateProfileInt("BarrierTimeOff", 8000);
		Barrier_TimeOffMin = Barrier_TimeOff - (Barrier_TimeOff / 10);
		Barrier_TimeOffMax = Barrier_TimeOff + (Barrier_TimeOff / 10);

		// Hook in oCBarrier::Init() to add barrier texture
		InjectHook(0x006B94F9, Barrier_Init_Hook, PATCH_JUMP);

		// Use our own RenderSkyPre()
		Patch(0x0083C178, &hSkyControler_Barrier::RenderSkyPre);
	}
}

void
PatchGothic2(void)
{
	PatchBarrier();
	PatchMagicFrontier();
}

void
Init(void)
{
	if (G12GetPrivateProfileInt("AllocConsole", 0))
	{
		AllocConsole();
		freopen_s(&conin, "conin$", "r", stdin);
		freopen_s(&conout, "conout$", "w", stdout);
		freopen_s(&conout, "conout$", "w", stderr);
	}

	if (*(int *)0x00502D70 == 0x5614EC83) // Gothic2.exe
	{
		PatchGothic2();
	}
}

BOOL WINAPI
DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}
