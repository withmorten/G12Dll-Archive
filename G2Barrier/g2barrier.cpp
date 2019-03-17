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

float hMagFrontier::GetDistance(zVEC3 &pos, float &dist, zVEC3 &nearestPoint)
{
	float real_dist;
	zVEC2 playerPos, point2, point1, distToPoints;

	int x;

	dist = 10000000.0f;

	playerPos.n[0] = pos.n[0];
	playerPos.n[1] = pos.n[2];

	if (playerPos.n[0] == 0.0f && playerPos.n[1] == 0.0f)
	{
		return dist;
	}

	for (x = 1; x < 38; x++)
	{
		point1.n[0] = newPointList[x - 1].n[0];
		point1.n[1] = newPointList[x - 1].n[1];

		point2.n[0] = newPointList[x].n[0];
		point2.n[1] = newPointList[x].n[1];

		GetNearestPointFromLineSegment2D(point1, point2, playerPos, distToPoints);

		real_dist = sqrtf((distToPoints.n[1] - playerPos.n[1]) * (distToPoints.n[1] - playerPos.n[1]) +
							(distToPoints.n[0] - playerPos.n[0]) * (distToPoints.n[0] - playerPos.n[0]));

		if (real_dist < dist)
		{
			dist = real_dist;
		}
	}

	return dist;
}

void hMagFrontier::DoCheck(void)
{
	this->oCMagFrontier::DoCheck();

	oCGame *Game = *(oCGame **)0x00AB0884; // ogame

	if (Game && this->npc == *(oCNpc **)0x00AB2684 // oCNpc::player
		&& !(*(zCCamera **)0x008D7F94)->connectedVob->homeWorld->csPlayer->GetPlayingGlobalCutscene()) // zCCamera::activeCam
	{
		oCWorld *World = Game->GetGameWorld();
		if (World)
		{
			if (!_stricmp(World->worldName._Ptr, worldName))
			{
				if (this->npc)
				{
					zVEC3 playerProjPos, startPoint;
					playerProjPos.n[0] = this->npc->trafoObjToWorld.v[0].n[3];
					playerProjPos.n[1] = this->npc->trafoObjToWorld.v[1].n[3];
					playerProjPos.n[2] = this->npc->trafoObjToWorld.v[2].n[3];

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

void MagicFrontierNewPointListInit(void)
{
	// newPointList from Gothic 1
	newPointList[0].n[0] = 57939.199f;
	newPointList[0].n[1] = 1280.28f;
	newPointList[1].n[0] = 55954.398f;
	newPointList[1].n[1] = 5421.5098f;
	newPointList[2].n[0] = 52856.801f;
	newPointList[2].n[1] = 10047.0f;
	newPointList[3].n[0] = 49451.898f;
	newPointList[3].n[1] = 14908.2f;
	newPointList[4].n[0] = 44199.801f;
	newPointList[4].n[1] = 20513.301f;
	newPointList[5].n[0] = 37684.199f;
	newPointList[5].n[1] = 26271.199f;
	newPointList[6].n[0] = 30434.0f;
	newPointList[6].n[1] = 31462.4f;
	newPointList[7].n[0] = 25573.6f;
	newPointList[7].n[1] = 32692.699f;
	newPointList[8].n[0] = 21248.301f;
	newPointList[8].n[1] = 35176.102f;
	newPointList[9].n[0] = 19450.699f;
	newPointList[9].n[1] = 35205.0f;
	newPointList[10].n[0] = 16263.1f;
	newPointList[10].n[1] = 32799.602f;
	newPointList[11].n[0] = 10755.6f;
	newPointList[11].n[1] = 34744.398f;
	newPointList[12].n[0] = 9736.9004f;
	newPointList[12].n[1] = 37990.5f;
	newPointList[13].n[0] = 8218.5996f;
	newPointList[13].n[1] = 38393.102f;
	newPointList[14].n[0] = 4065.0f;
	newPointList[14].n[1] = 39018.398f;
	newPointList[15].n[0] = 839.90002f;
	newPointList[15].n[1] = 39079.301f;
	newPointList[16].n[0] = -9312.9004f;
	newPointList[16].n[1] = 38694.199f;
	newPointList[17].n[0] = -19258.301f;
	newPointList[17].n[1] = 40991.398f;
	newPointList[18].n[0] = -29684.1f;
	newPointList[18].n[1] = 40535.699f;
	newPointList[19].n[0] = -39313.699f;
	newPointList[19].n[1] = 36558.801f;
	newPointList[20].n[0] = -49319.602f;
	newPointList[20].n[1] = 31970.199f;
	newPointList[21].n[0] = -54137.301f;
	newPointList[21].n[1] = 26761.699f;
	newPointList[22].n[0] = -62089.301f;
	newPointList[22].n[1] = 21598.1f;
	newPointList[23].n[0] = -66193.703f;
	newPointList[23].n[1] = 12999.2f;
	newPointList[24].n[0] = -66132.297f;
	newPointList[24].n[1] = 6204.0f;
	newPointList[25].n[0] = -63855.199f;
	newPointList[25].n[1] = -5700.7998f;
	newPointList[26].n[0] = -59385.102f;
	newPointList[26].n[1] = -10081.5f;
	newPointList[27].n[0] = -56013.801f;
	newPointList[27].n[1] = -22393.4f;
	newPointList[28].n[0] = -47250.301f;
	newPointList[28].n[1] = -28502.0f;
	newPointList[29].n[0] = -37136.5f;
	newPointList[29].n[1] = -38319.199f;
	newPointList[30].n[0] = -24664.699f;
	newPointList[30].n[1] = -46687.898f;
	newPointList[31].n[0] = -7860.6001f;
	newPointList[31].n[1] = -48966.602f;
	newPointList[32].n[0] = 4876.6001f;
	newPointList[32].n[1] = -49691.0f;
	newPointList[33].n[0] = 23147.801f;
	newPointList[33].n[1] = -47875.102f;
	newPointList[34].n[0] = 48722.301f;
	newPointList[34].n[1] = -39488.801f;
	newPointList[35].n[0] = 55902.398f;
	newPointList[35].n[1] = -31909.801f;
	newPointList[36].n[0] = 61238.602f;
	newPointList[36].n[1] = -23412.801f;
	newPointList[37].n[0] = 60230.102f;
	newPointList[37].n[1] = -6641.8999f;
}

void MagicFrontierNewPointListInitGRM(void)
{
	// newPointList from GRM
	newPointList[17].n[0] = -26219.2f;
	newPointList[17].n[1] = 40844.2f;
	newPointList[18].n[0] = -34576.0f;
	newPointList[18].n[1] = 43032.3f;
	newPointList[19].n[0] = -44458.8f;
	newPointList[19].n[1] = 43099.2f;
	newPointList[20].n[0] = -49763.7f;
	newPointList[20].n[1] = 37384.8f;
}

void PatchMagicFrontier(void)
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

int Barrier_TremorEnable;
int Barrier_TremorDelayTime, Barrier_TremorDelayTimeMin, Barrier_TremorDelayTimeMax;
int Barrier_TremorTimer = 0;

int hBarrier_activeThunder_Sector1, hBarrier_activeThunder_Sector2, hBarrier_activeThunder_Sector3, hBarrier_activeThunder_Sector4;

zCSoundFX *hBarrier_sfx1, *hBarrier_sfx2, *hBarrier_sfx3, *hBarrier_sfx4;
zTSoundHandle hBarrier_sfxHandle1, hBarrier_sfxHandle2, hBarrier_sfxHandle3, hBarrier_sfxHandle4;

float delayTimeSector1 = 4000.0f;
float delayTimeSector2 = 200.0f;
float delayTimeSector3 = 6000.0f;
float delayTimeSector4 = 10000.0f;

zCSoundSystem *SoundSystem;

myThunder oCBarrier_myThunderTemp[NEW_NUM_MAX_THUNDERS], hBarrier_myThunderTemp[NEW_NUM_MAX_THUNDERS];
int oCBarrier_numMyThundersTemp, hBarrier_numMyThundersTemp;

void hBarrier::AddTremor(zTRenderContext &renderContext)
{
	oCNpc *hero = *(oCNpc **)0x00AB2684; // oCNpc::player

	oCVisualFX *vfx = oCVisualFX::CreateAndPlay(zSTRING("FX_EarthQuake"), hero, hero, 0, 0, 0, 0);

	if (vfx)
	{
		vfx->Release();

		vfx = NULL;
	}
}

int hBarrier::Render(zTRenderContext &rndContext, int fadeInOut, int alwaysVisible)
{
	zCRnd_D3D *Renderer = *(zCRnd_D3D **)0x00982F08; // zrenderer
	zCCamera *Camera = *(zCCamera **)0x008D7F94; // zCCamera::activeCam
	zCMaterial *FrontierMat = this->skySphereMesh->polyList[0]->material;

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

				if (Barrier_TremorEnable)
				{
					if (Barrier_TremorTimer)
					{
						Barrier_TremorTimer--;
					}
					else
					{
						this->AddTremor(rndContext);
						Barrier_TremorTimer = Barrier_TremorDelayTimeMin + _rand() % ((Barrier_TremorDelayTimeMax + 1) - Barrier_TremorDelayTimeMin);
					}
				}
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

		if (!hBarrier_activeThunder_Sector1 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle1) &&
			*(float *)0x0099B3DC - delayTimeSector1 > 8000.f) // actualTime
		{
			this->AddThunder(this->startPointList1[(this->numStartPoints1 - 1) & _rand()], 11, 0, 1);
			hBarrier_activeThunder_Sector1 = 1;
			delayTimeSector1 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx1)
			{
				hBarrier_sfx1 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle1 = SoundSystem->PlaySound3D(hBarrier_sfx1, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_activeThunder_Sector2 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle2) &&
			*(float *)0x0099B3DC - delayTimeSector2 > 6000.f) // actualTime
		{
			this->AddThunder(this->startPointList2[(this->numStartPoints2 - 1) & _rand()], 11, 0, 2);
			hBarrier_activeThunder_Sector2 = 1;
			delayTimeSector2 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx2)
			{
				hBarrier_sfx2 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle2 = SoundSystem->PlaySound3D(hBarrier_sfx2, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_activeThunder_Sector3 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle3) &&
			*(float *)0x0099B3DC - delayTimeSector3 > 14000.f) // actualTime
		{
			this->AddThunder(this->startPointList3[(this->numStartPoints3 - 1) & _rand()], 11, 0, 3);
			hBarrier_activeThunder_Sector3 = 1;
			delayTimeSector3 = *(float *)0x0099B3DC; // actualTime

			if (!hBarrier_sfx3)
			{
				hBarrier_sfx3 = SoundSystem->LoadSoundFXScript(MfxBarriereAmbient);
			}

			hBarrier_sfxHandle3 = SoundSystem->PlaySound3D(hBarrier_sfx3, Camera->connectedVob, 0, &sound3DParams);
		}

		if (!hBarrier_activeThunder_Sector4 && !SoundSystem->IsSoundActive(hBarrier_sfxHandle4) &&
			*(float *)0x0099B3DC - delayTimeSector4 > 2000.f) // actualTime
		{
			this->AddThunder(this->startPointList4[(this->numStartPoints4 - 1) & _rand()], 11, 0, 4);
			hBarrier_activeThunder_Sector4 = 1;
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

int hBarrier::RenderThunder(myThunder *thunder, zTRenderContext &rndContext)
{
	if (!thunder->valid)
	{
		return 0;
	}

	thunder->t1 = *(float *)0x0099B3D8 * 0.0049999999f + thunder->t1; // frameTimeF

	if (thunder->t0 >= 0.89999998f)
	{
		thunder->t0 = 0.89999998f;
	}

	if (thunder->t1 >= 0.89999998f)
	{
		thunder->t1 = 0.89999998f;
	}

	if (thunder->polyStrip->numSeg <= 2)
	{
		thunder->t0 = 0.89999998f;
	}

	if (thunder->t0 >= 0.89999998f
		&& thunder->t1 >= 0.89999998f
		&& thunder->numChilds <= 0)
	{
		if (!thunder->isChild)
		{
			if (thunder->sector == 1)
			{
				hBarrier_activeThunder_Sector1 = 0;
			}
			if (thunder->sector == 2)
			{
				hBarrier_activeThunder_Sector2 = 0;
			}
			if (thunder->sector == 3)
			{
				hBarrier_activeThunder_Sector3 = 0;
			}
			if (thunder->sector == 4)
			{
				hBarrier_activeThunder_Sector4 = 0;
			}

			this->numMyThunders--;
		}

		this->RemoveThunder(thunder);
		thunder->valid = 0;

		return 0;
	}

	if (thunder->t0 != thunder->t1)
	{
		thunder->polyStrip->SetVisibleSegments(thunder->t0, thunder->t1);
		thunder->polyStrip->Render(rndContext);
	}

	for (int x = 0; x < thunder->numChilds; x++)
	{
		if (thunder->t1 >= thunder->startTime[x])
		{
			if (!this->oCBarrier::RenderThunder(&thunder->childs[x], rndContext))
			{
				thunder->numChilds--;
			}
		}
	}

	if (!thunder->isChild)
	{
		zMAT4 mat, matTemp, matTemp2;

		matTemp = *(zMAT4 *)0x008D45E8; // zMAT4::s_identity
		mat = *(zMAT4 *)0x008D45E8; // zMAT4::s_identity
		mat = rndContext.cam->GetTransform(1);

		mat.v[0].n[2] *= -1.0f;
		mat.v[1].n[2] *= -1.0f;
		mat.v[2].n[2] *= -1.0f;

		mat.v[0].n[3] = thunder->originVec.n[0];
		mat.v[1].n[3] = thunder->originVec.n[1];
		mat.v[2].n[3] = thunder->originVec.n[2];

		matTemp2 = rndContext.cam->GetTransform(0);

		rndContext.cam->SetTransform(0, mat);

		this->thunderStartDecal->SetDecalDim(5000.0f, 5000.0f);
		this->thunderStartDecal->Render(rndContext);
		this->thunderStartDecal->SetDecalDim(4000.0f, 4000.0f);

		rndContext.cam->SetTransform(0, matTemp2);
	}

	return 1;
}

void Barrier_Init(void)
{
	oCBarrier *Barrier = SkyControler_Barrier->barrier;
	Barrier->bFadeInOut = 1;

	zCMesh *FrontierMesh = Barrier->skySphereMesh;
	zCMaterial *FrontierMat = FrontierMesh->polyList[0]->material;

	FrontierMat->SetTexture(zSTRING("BARRIERE.TGA"));
	FrontierMat->rndAlphaBlendFunc = zRND_ALPHA_FUNC_ADD;
	FrontierMat->color.SetAlphaByte((BYTE)Barrier->fadeState);

	int numPolys = FrontierMesh->numPoly;
	float maxHeight = FrontierMesh->bbox3D.maxs.n[1];
	float minHeight = maxHeight * 0.925000011920929f;

	for (int i = 0; i < numPolys; i++)
	{
		zCPolygon *Poly = FrontierMesh->polyList[i];
		int numVerts = Poly->polyNumVert;

		for (int j = 0; j < numVerts; j++)
		{
			int alpha;

			zCVertFeature *Feat = Poly->features[j];
			zCVertex *Vert = Poly->vertex[j];

			if (Vert->position.n[1] <= minHeight)
			{
				alpha = (int)(Vert->position.n[1] * 0.0001250000059371814f * 255.0f);
			}
			else
			{
				alpha = (int)((maxHeight - Vert->position.n[1]) * 255.0f / (maxHeight - minHeight));
			}

			if (alpha > 255) alpha = 255;
			if (alpha < 0) alpha = 0;

			Feat->lightDyn.dword = BARRIER_COLOR;
			Feat->lightDyn.SetAlphaByte((BYTE)alpha);

			Feat->lightStat.dword = BARRIER_COLOR;
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

void hSkyControler_Barrier::RenderSkyPre(void)
{
	this->zCSkyControler_Outdoor::RenderSkyPre();

	hBarrier *Barrier = (hBarrier *)this->barrier;

	if (!*(int *)0x00AB040C) // meshLoaded
	{
		*(int *)0x00AB040C = 1; // meshLoaded

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

		hBarrier_activeThunder_Sector1 = 0;
		hBarrier_activeThunder_Sector2 = 0;
		hBarrier_activeThunder_Sector3 = 0;
		hBarrier_activeThunder_Sector4 = 0;

		hBarrier_sfx1 = NULL;
		hBarrier_sfxHandle1 = 0;
		hBarrier_sfx2 = NULL;
		hBarrier_sfxHandle2 = 0;
		hBarrier_sfx3 = NULL;
		hBarrier_sfxHandle3 = 0;
		hBarrier_sfx4 = NULL;
		hBarrier_sfxHandle4 = 0;

		Barrier_FadeTimer = 0;

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

		Barrier->myThunderList = oCBarrier_myThunderTemp;
		Barrier->numMyThunders = oCBarrier_numMyThundersTemp;

		Barrier->oCBarrier::Render(rndContext, 0, 0);

		oCBarrier_numMyThundersTemp = Barrier->numMyThunders;
	}

	oCGame *Game = *(oCGame **)0x00AB0884; // ogame

	if ((*(int *)0x008A5DB0 // zCSkyControler::s_skyEffectsEnabled
		|| Barrier_IgnoreSkyEffectsSetting)
		&& !_stricmp(Game->GetGameWorld()->worldName._Ptr, worldName))
	{
		_memset(&rndContext, 0x00, sizeof(zTRenderContext));
		rndContext.clipFlags = -1;
		rndContext.cam = Camera;
		rndContext.world = Camera->connectedVob->homeWorld;
		rndContext.vob = Camera->connectedVob;

		Barrier->myThunderList = hBarrier_myThunderTemp;
		Barrier->numMyThunders = hBarrier_numMyThundersTemp;

		Barrier->Render(rndContext, 0, 0);

		hBarrier_numMyThundersTemp = Barrier->numMyThunders;
	}
}

void PatchBarrier(void)
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

		Barrier_TremorEnable = G12GetPrivateProfileInt("BarrierTremorEnable", 0);
		Barrier_TremorDelayTime = G12GetPrivateProfileInt("BarrierTremorDelayTime", 20);
		Barrier_TremorDelayTimeMin = Barrier_TremorDelayTime - (Barrier_TremorDelayTime / 10);
		Barrier_TremorDelayTimeMax = Barrier_TremorDelayTime + (Barrier_TremorDelayTime / 10);

		// Hook in oCBarrier::Init() to add barrier texture
		InjectHook(0x006B94F9, Barrier_Init_Hook, PATCH_JUMP);

		// Use our own RenderSkyPre()
		Patch(0x0083C178, &hSkyControler_Barrier::RenderSkyPre);
	}
}

void PatchGothic2(void)
{
	PatchBarrier();
	PatchMagicFrontier();
}

void Init(void)
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

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}
