#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "..\G12Dll\MemoryMgr.h"


#define G12DLL_NAME "G2Barrier"

#include "..\G12Dll\G12.h"

#include "..\G12Dll\G2.hpp"
#include "..\G12Dll\G2.h"
#include "g2barrier.hpp"

#define WORLD_NAME "WORLD"

static char worldName[MAX_PATH];

static zVEC2 newPointList[38];

float hMagFrontier::GetDistance(zVEC3 &pos, float &dist, zVEC3 &nearestPoint)
{
	float real_dist;
	zVEC2 playerPos, point2, point1, nearest;

	int i;

	dist = 10000000.0f;

	playerPos.n[0] = pos.n[0];
	playerPos.n[1] = pos.n[2];

	if (playerPos.n[0] == 0.0f && playerPos.n[1] == 0.0f)
	{
		return dist;
	}

	for (i = 1; i < 38; i++)
	{
		point1.n[0] = newPointList[i - 1].n[0];
		point1.n[1] = newPointList[i - 1].n[1];

		point2.n[0] = newPointList[i].n[0];
		point2.n[1] = newPointList[i].n[1];

		GetNearestPointFromLineSegment2D(point1, point2, playerPos, nearest);

		real_dist = sqrtf((nearest.n[1] - playerPos.n[1]) * (nearest.n[1] - playerPos.n[1]) +
							(nearest.n[0] - playerPos.n[0]) * (nearest.n[0] - playerPos.n[0]));

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

	if (ogame && this->npc == oCNpc::player
		&& !zCCamera::activeCam->connectedVob->homeWorld->csPlayer->GetPlayingGlobalCutscene())
	{
		oCWorld *world = ogame->GetGameWorld();

		if (world)
		{
			if (!_stricmp(world->worldName._Ptr, worldName))
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
						int level = (int)((1200.0f - distToBarriere) / 55.0f);

						if (!level)
						{
							level = 1;
						}

						this->DoWarningFX(level);

						if (oCNpc::godmode || (distToBarriere > 650.0f || distToBarriere < 0.0f))
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
	newPointList[0].n[0] = 57939.2f;
	newPointList[0].n[1] = 1280.28f;
	newPointList[1].n[0] = 55954.4f;
	newPointList[1].n[1] = 5421.51f;
	newPointList[2].n[0] = 52856.8f;
	newPointList[2].n[1] = 10047.0f;
	newPointList[3].n[0] = 49451.9f;
	newPointList[3].n[1] = 14908.2f;
	newPointList[4].n[0] = 44199.8f;
	newPointList[4].n[1] = 20513.3f;
	newPointList[5].n[0] = 37684.2f;
	newPointList[5].n[1] = 26271.2f;
	newPointList[6].n[0] = 30434.0f;
	newPointList[6].n[1] = 31462.4f;
	newPointList[7].n[0] = 25573.6f;
	newPointList[7].n[1] = 32692.7f;
	newPointList[8].n[0] = 21248.3f;
	newPointList[8].n[1] = 35176.1f;
	newPointList[9].n[0] = 19450.7f;
	newPointList[9].n[1] = 35205.0f;
	newPointList[10].n[0] = 16263.1f;
	newPointList[10].n[1] = 32799.6f;
	newPointList[11].n[0] = 10755.6f;
	newPointList[11].n[1] = 34744.4f;
	newPointList[12].n[0] = 9736.9f;
	newPointList[12].n[1] = 37990.5f;
	newPointList[13].n[0] = 8218.6f;
	newPointList[13].n[1] = 38393.1f;
	newPointList[14].n[0] = 4065.0f;
	newPointList[14].n[1] = 39018.4f;
	newPointList[15].n[0] = 839.9f;
	newPointList[15].n[1] = 39079.3f;
	newPointList[16].n[0] = -9312.9f;
	newPointList[16].n[1] = 38694.2f;
	newPointList[17].n[0] = -19258.3f;
	newPointList[17].n[1] = 40991.4f;
	newPointList[18].n[0] = -29684.1f;
	newPointList[18].n[1] = 40535.7f;
	newPointList[19].n[0] = -39313.7f;
	newPointList[19].n[1] = 36558.8f;
	newPointList[20].n[0] = -49319.6f;
	newPointList[20].n[1] = 31970.2f;
	newPointList[21].n[0] = -54137.3f;
	newPointList[21].n[1] = 26761.7f;
	newPointList[22].n[0] = -62089.3f;
	newPointList[22].n[1] = 21598.1f;
	newPointList[23].n[0] = -66193.7f;
	newPointList[23].n[1] = 12999.2f;
	newPointList[24].n[0] = -66132.3f;
	newPointList[24].n[1] = 6204.0f;
	newPointList[25].n[0] = -63855.2f;
	newPointList[25].n[1] = -5700.8f;
	newPointList[26].n[0] = -59385.1f;
	newPointList[26].n[1] = -10081.5f;
	newPointList[27].n[0] = -56013.8f;
	newPointList[27].n[1] = -22393.4f;
	newPointList[28].n[0] = -47250.3f;
	newPointList[28].n[1] = -28502.0f;
	newPointList[29].n[0] = -37136.5f;
	newPointList[29].n[1] = -38319.2f;
	newPointList[30].n[0] = -24664.7f;
	newPointList[30].n[1] = -46687.9f;
	newPointList[31].n[0] = -7860.6f;
	newPointList[31].n[1] = -48966.6f;
	newPointList[32].n[0] = 4876.6f;
	newPointList[32].n[1] = -49691.0f;
	newPointList[33].n[0] = 23147.8f;
	newPointList[33].n[1] = -47875.1f;
	newPointList[34].n[0] = 48722.3f;
	newPointList[34].n[1] = -39488.8f;
	newPointList[35].n[0] = 55902.4f;
	newPointList[35].n[1] = -31909.8f;
	newPointList[36].n[0] = 61238.6f;
	newPointList[36].n[1] = -23412.8f;
	newPointList[37].n[0] = 60230.1f;
	newPointList[37].n[1] = -6641.9f;
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

		InjectHook(0x0073E71B, &hMagFrontier::DoCheck); // oCNpc::ProcessNpc()
	}

	if (G12GetPrivateProfileInt("MagicFrontierPointsWorldGRM", 0))
	{
		// GRM fixes has some different points ... just included here for now
		MagicFrontierNewPointListInitGRM();
	}
}

#define BARRIER_ALPHA_MAX 120
#define BARRIER_COLOR 0x00FFFFFF

static int meshLoaded = 0;

static int isBarrierRender;

static hSkyControler_Barrier *zsky;

static int earthQuakeInterval;
static int earthQuakeTimer = 0;

static int ignoreSkyEffectsSetting;
static int alwaysVisible;
static int tremorEnable;
static int earthQuakeEnable;

static int activeThunder_Sector1;
static int activeThunder_Sector2;
static int activeThunder_Sector3;
static int activeThunder_Sector4;

static zCSoundFX *sfx1;
static zTSoundHandle sfxHandle1;
static zCSoundFX *sfx2;
static zTSoundHandle sfxHandle2;
static zCSoundFX *sfx3;
static zTSoundHandle sfxHandle3;
static zCSoundFX *sfx4;
static zTSoundHandle sfxHandle4;

static float nextActivation = 8000.0f;

static int showThunders = 0;
static float fadeTime;
static float timeUpdatedFade = 0.0f;
static float timeStepToUpdateFade = 1.0f;
static float timeToStayVisible;
static float timeToStayHidden;

static float delayTimeSector1 = 4000.0f;
static float delayTimeSector2 = 200.0f;
static float delayTimeSector3 = 6000.0f;
static float delayTimeSector4 = 10000.0f;

static myThunder thunderList[20]; // "malloc"
static myThunder *myThunderList;
static int numMyThunders;

void hBarrier::AddTremor(zTRenderContext &renderContext)
{
	zVEC3 amplitude;

	amplitude.n[0] = 0.8f;
	amplitude.n[1] = 1.5f;
	amplitude.n[2] = 0.8f;

	renderContext.cam->AddTremor(renderContext.cam->connectedVob->trafoObjToWorld.GetTranslation(), 4000.0f * 4000.0f, 3000.0f, amplitude);
}

void hBarrier::AddEarthQuake()
{
	oCVisualFX *vfx = oCVisualFX::CreateAndPlay(zSTRING("FX_EarthQuake"), oCNpc::player, oCNpc::player, 0, 0, 0, 0);

	if (vfx)
	{
		vfx->Release();

		vfx = NULL;
	}
}

int hBarrier::Render(zTRenderContext &rndContext, int fadeInOut, int alwaysVisible)
{
	if (this->skySphereMesh)
	{
		zCMaterial *material = this->skySphereMesh->polyList[0]->material;

		int zBufferWriteEnabled = zrenderer->GetZBufferWriteEnabled();
		float farClipZ = zCCamera::activeCam->farClipZ;

		zrenderer->SetZBufferWriteEnabled(0);
		zCCamera::activeCam->SetFarClipZ(2000000.0f);
		rndContext.cam->SetTransform(1, rndContext.cam->connectedVob->trafoObjToWorld.InverseLinTrafo());

		if (fadeInOut)
		{
			this->bFadeInOut = 1;

			if (this->fadeIn)
			{
				if (!alwaysVisible)
				{
					material->color.SetAlphaByte(this->fadeState);
				}

				if (ztimer.totalTimeFloat - timeUpdatedFade > timeStepToUpdateFade)
				{
					this->fadeState++;

					timeUpdatedFade = ztimer.totalTimeFloat;
				}

				if (this->fadeState > BARRIER_ALPHA_MAX)
				{
					this->fadeState = BARRIER_ALPHA_MAX;
					this->fadeIn = 0;
					showThunders = 1;
					fadeTime = ztimer.totalTimeFloat;
				}
			}
			else
			{
				if (ztimer.totalTimeFloat - fadeTime > timeToStayVisible)
				{
					this->fadeOut = 1;
					showThunders = 0;
					fadeTime = ztimer.totalTimeFloat;
				}

				if (this->fadeOut)
				{
					if (!alwaysVisible)
					{
						material->color.SetAlphaByte(this->fadeState);
					}

					if (ztimer.totalTimeFloat - timeUpdatedFade > timeStepToUpdateFade)
					{
						this->fadeState--;

						timeUpdatedFade = ztimer.totalTimeFloat;
					}

					if (this->fadeState < 1)
					{
						this->fadeState = 0;
						this->fadeIn = 1;
						this->fadeOut = 0;

						if (!alwaysVisible)
						{
							this->bFadeInOut = 0;
						}

						if (earthQuakeEnable)
						{
							if (earthQuakeTimer)
							{
								earthQuakeTimer--;
							}
							else
							{
								this->AddEarthQuake();
								earthQuakeTimer = earthQuakeInterval;
							}
						}
					}
				}
			}
		}

		int addNewThunder = 1;

		this->RenderLayer(rndContext, 0, addNewThunder);
		this->RenderLayer(rndContext, 1, addNewThunder);

		if (showThunders)
		{
			zSTRING mfxBarriereAmbient("MFX_Barriere_Ambient");

			zTSound3DParams sound3DParams;
			sound3DParams.obstruction = 0.0f;
			sound3DParams.volume = 1.0f;
			sound3DParams.radius = -1.0f;
			sound3DParams.loopType = 0;
			sound3DParams.coneAngleDeg = 0.0f;
			sound3DParams.reverbLevel = 1.0f;
			sound3DParams.isAmbient3D = 0;
			sound3DParams.pitchOffset = -999999.0f;

			if (!::activeThunder_Sector1 && !zsound->IsSoundActive(::sfxHandle1) &&
				(ztimer.totalTimeFloat - delayTimeSector1) > 8000.f)
			{
				this->AddThunder(this->startPointList1[(this->numStartPoints1 - 1) & _rand()], 11, 0, 1);
				::activeThunder_Sector1 = 1;
				delayTimeSector1 = ztimer.totalTimeFloat;

				if (!::sfx1)
				{
					::sfx1 = zsound->LoadSoundFXScript(mfxBarriereAmbient);
				}

				if (tremorEnable)
				{
					this->AddTremor(rndContext);
				}

				::sfxHandle1 = zsound->PlaySound3D(::sfx1, zCCamera::activeCam->connectedVob, 0, &sound3DParams);
			}

			if (!::activeThunder_Sector2 && !zsound->IsSoundActive(::sfxHandle2) &&
				(ztimer.totalTimeFloat - delayTimeSector2) > 6000.f)
			{
				this->AddThunder(this->startPointList2[(this->numStartPoints2 - 1) & _rand()], 11, 0, 2);
				::activeThunder_Sector2 = 1;
				delayTimeSector2 = ztimer.totalTimeFloat;

				if (!::sfx2)
				{
					::sfx2 = zsound->LoadSoundFXScript(mfxBarriereAmbient);
				}

				if (tremorEnable)
				{
					this->AddTremor(rndContext);
				}

				::sfxHandle2 = zsound->PlaySound3D(::sfx2, zCCamera::activeCam->connectedVob, 0, &sound3DParams);
			}

			if (!::activeThunder_Sector3 && !zsound->IsSoundActive(::sfxHandle3) &&
				(ztimer.totalTimeFloat - delayTimeSector3) > 14000.f)
			{
				this->AddThunder(this->startPointList3[(this->numStartPoints3 - 1) & _rand()], 11, 0, 3);
				::activeThunder_Sector3 = 1;
				delayTimeSector3 = ztimer.totalTimeFloat;

				if (!::sfx3)
				{
					::sfx3 = zsound->LoadSoundFXScript(mfxBarriereAmbient);
				}

				if (tremorEnable)
				{
					this->AddTremor(rndContext);
				}

				::sfxHandle3 = zsound->PlaySound3D(::sfx3, zCCamera::activeCam->connectedVob, 0, &sound3DParams);
			}

			if (!::activeThunder_Sector4 && !zsound->IsSoundActive(::sfxHandle4) &&
				(ztimer.totalTimeFloat - delayTimeSector4) > 2000.f)
			{
				this->AddThunder(this->startPointList4[(this->numStartPoints4 - 1) & _rand()], 11, 0, 4);
				::activeThunder_Sector4 = 1;
				delayTimeSector4 = ztimer.totalTimeFloat;

				if (!::sfx4)
				{
					::sfx4 = zsound->LoadSoundFXScript(mfxBarriereAmbient);
				}

				if (tremorEnable)
				{
					this->AddTremor(rndContext);
				}

				::sfxHandle4 = zsound->PlaySound3D(::sfx4, zCCamera::activeCam->connectedVob, 0, &sound3DParams);
			}

			for (int x = 0; x < this->numMyThunders; x++)
			{
				this->oCBarrier::RenderThunder(&this->myThunderList[x], rndContext);
			}

			zrenderer->FlushPolys();

			if (::sfx1)
			{
				zsound->UpdateSound3D(::sfxHandle1, NULL);
			}

			if (::sfx2)
			{
				zsound->UpdateSound3D(::sfxHandle2, NULL);
			}

			if (::sfx3)
			{
				zsound->UpdateSound3D(::sfxHandle3, NULL);
			}

			if (::sfx4)
			{
				zsound->UpdateSound3D(::sfxHandle4, NULL);
			}
		}

		zrenderer->SetZBufferWriteEnabled(zBufferWriteEnabled);
		zCCamera::activeCam->SetFarClipZ(farClipZ);
	}

	return this->bFadeInOut;
}

int hBarrier::AddThunderSub(myThunder *rootThunder, int startIndex, int startNexIntex, int length, int mumSplits)
{
	int rV = this->oCBarrier::AddThunderSub(rootThunder, startIndex, startNexIntex, length, mumSplits);

	if (isBarrierRender)
	{
		myThunder *thunder = &rootThunder->childs[rootThunder->numChilds];

		thunder->polyStrip->camAlign = 1;
		thunder->polyStrip->alphaFadeSpeed = 0.5;
		thunder->polyStrip->width = 3000.0f;
	}

	return rV;
}

int hBarrier::AddThunder(int startIndex, int length, float random, int sector)
{
	int thunderIndex = this->oCBarrier::AddThunder(startIndex, length, random, sector);

	myThunder *thunder = &this->myThunderList[thunderIndex];

	thunder->polyStrip->camAlign = 1;
	thunder->polyStrip->alphaFadeSpeed = 0.5;
	thunder->polyStrip->width = 3000.0f;

	return thunderIndex;
}

int hBarrier::RenderThunder(myThunder *thunder, zTRenderContext &rndContext)
{
	if (thunder->valid)
	{
		thunder->t1 = ztimer.frameTimeFloat / 200.0f + thunder->t1;

		float f = 0.9f;

		if (thunder->t0 >= f)
		{
			thunder->t0 = f;
		}

		if (thunder->t1 >= f)
		{
			thunder->t1 = f;
		}

		if (thunder->polyStrip->numSeg <= 2)
		{
			thunder->t0 = f;
		}

		if (thunder->t0 >= f
			&& thunder->t1 >= f
			&& thunder->numChilds <= 0)
		{
			if (!thunder->isChild)
			{
				if (thunder->sector == 1)
				{
					::activeThunder_Sector1 = 0;
				}
				if (thunder->sector == 2)
				{
					::activeThunder_Sector2 = 0;
				}
				if (thunder->sector == 3)
				{
					::activeThunder_Sector3 = 0;
				}
				if (thunder->sector == 4)
				{
					::activeThunder_Sector4 = 0;
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
				if (!this->RenderThunder(&thunder->childs[x], rndContext))
				{
					thunder->numChilds--;
				}
			}
		}

		if (!thunder->isChild)
		{
			zMAT4 mat, matTemp, matTemp2;

			matTemp = zMAT4::s_identity;
			mat = zMAT4::s_identity;
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

	return 0;
}

void hBarrier_Init(void)
{
	oCBarrier *barrier = zsky->barrier;

	zCMesh *skySphereMesh = barrier->skySphereMesh;
	zCMaterial *material = skySphereMesh->polyList[0]->material;

	material->SetTexture(zSTRING("BARRIERE.TGA"));
	material->rndAlphaBlendFunc = zRND_ALPHA_FUNC_ADD;
	material->color.SetAlphaByte(barrier->fadeState);

	float maxHeight = skySphereMesh->bbox3D.maxs.n[1];
	float minHeight = maxHeight * 0.925f;

	for (int i = 0; i < skySphereMesh->numPoly; i++)
	{
		zCPolygon *poly = skySphereMesh->polyList[i];

		for (int j = 0; j < poly->polyNumVert; j++)
		{
			int alpha;

			zCVertFeature *feat = poly->features[j];
			zCVertex *vert = poly->vertex[j];

			if (vert->position.n[1] <= minHeight)
			{
				alpha = (int)((vert->position.n[1] / 8000.0f) * 255.0f);
			}
			else
			{
				alpha = (int)((maxHeight - vert->position.n[1]) * 255.0f / (maxHeight - minHeight));
			}

			if (alpha > 255)
			{
				alpha = 255;
			}

			if (alpha < 0)
			{
				alpha = 0;
			}

			feat->lightDyn.dword = BARRIER_COLOR;
			feat->lightDyn.SetAlphaByte(alpha);

			feat->lightStat.dword = BARRIER_COLOR;
			feat->lightStat.SetAlphaByte(alpha);
		}
	}
}

ASM(oCBarrier_Init_Hook)
{
	__asm
	{
		pushad
		call hBarrier_Init
		popad
		mov eax, [eax + 0x34]
		lea ebx, [eax + eax * 2]
		RET(0x006B94FF)
	}
}

void hSkyControler_Barrier::RenderSkyPre(void)
{
	this->zCSkyControler_Outdoor::RenderSkyPre();

	hBarrier *barrier = (hBarrier *)this->barrier;

	if (!meshLoaded)
	{
		meshLoaded = 1;

		::activeThunder_Sector1 = 0;
		::activeThunder_Sector2 = 0;
		::activeThunder_Sector3 = 0;
		::activeThunder_Sector4 = 0;

		::sfx1 = NULL;
		::sfxHandle1 = 0;
		::sfx2 = NULL;
		::sfxHandle2 = 0;
		::sfx3 = NULL;
		::sfxHandle3 = 0;
		::sfx4 = NULL;
		::sfxHandle4 = 0;

		zsky = this;
		barrier->Init();

		// Instead of rewriting AddThunder, AddThunderSub and RemoveThunder just swap whichever thunder is supposed to be worked on
		// Copy it once here, afterwards just switch pointers
		::myThunderList = ::thunderList;
		::numMyThunders = 20;
		memcpy(::myThunderList, barrier->myThunderList, sizeof(myThunder) * 20);

		if (alwaysVisible)
		{
			barrier->skySphereMesh->polyList[0]->material->color.SetAlphaByte(BARRIER_ALPHA_MAX);
		}
	}

	zTRenderContext rndContext;

	if (zCObject::CheckInheritance(&zCSkyControler_Outdoor::classDef, this->_GetClassDef()))
	{
		if (zCSkyControler::s_skyEffectsEnabled
			&& this->rainFX.outdoorRainFXWeight > 0.5f
			&& this->rainFX.renderLightning && this->m_enuWeather)
		{
			memset(&rndContext, 0x00, sizeof(zTRenderContext));
			rndContext.clipFlags = -1;
			rndContext.cam = zCCamera::activeCam;
			rndContext.world = zCCamera::activeCam->connectedVob->homeWorld;
			rndContext.vob = zCCamera::activeCam->connectedVob;

			isBarrierRender = 0;

			barrier->oCBarrier::Render(rndContext, 0, 0);
		}
	}

	if ((zCSkyControler::s_skyEffectsEnabled || ignoreSkyEffectsSetting)
		&& !_stricmp(ogame->GetGameWorld()->worldName._Ptr, worldName))
	{
		nextActivation -= ztimer.frameTimeFloat;

		if (nextActivation < 0)
		{
			nextActivation = timeToStayHidden + ((_rand() / RAND_MAX) * 5.0f * 60.0f * 1000.0f);
			this->bFadeInOut = 1;
		}

		if (this->bFadeInOut)
		{
			memset(&rndContext, 0x00, sizeof(zTRenderContext));
			rndContext.clipFlags = -1;
			rndContext.cam = zCCamera::activeCam;
			rndContext.world = zCCamera::activeCam->connectedVob->homeWorld;
			rndContext.vob = zCCamera::activeCam->connectedVob;

			// Save thunder
			myThunder *myThunderList;
			int numMyThunders;

			// Instead of rewriting AddThunder, AddThunderSub and RemoveThunder just swap whichever thunder is supposed to be worked on
			myThunderList = barrier->myThunderList;
			numMyThunders = barrier->numMyThunders;

			barrier->myThunderList = ::myThunderList;
			barrier->numMyThunders = ::numMyThunders;

			isBarrierRender = 1;

			if (!barrier->Render(rndContext, this->bFadeInOut, alwaysVisible))
			{
				this->bFadeInOut = 0;
			}

			barrier->myThunderList = myThunderList;
			barrier->numMyThunders = numMyThunders;
		}
	}
}

void PatchBarrier(void)
{
	if (G12GetPrivateProfileInt("BarrierEnable", 0))
	{
		G12GetPrivateProfileString("WorldName", WORLD_NAME, worldName, MAX_PATH);

		alwaysVisible = G12GetPrivateProfileInt("BarrierAlwaysOn", 0);
		ignoreSkyEffectsSetting = G12GetPrivateProfileInt("BarrierIgnoreSkyEffectsSetting", 0);

		timeToStayVisible = (float)(G12GetPrivateProfileInt("BarrierTimeOn", 25) * 1000);

		timeToStayHidden = (float)(G12GetPrivateProfileInt("BarrierTimeOff", 1200) * 1000);

		// looks bad when walking, should probably not be enabled at all, creates a small tremor each barrier thunder
		tremorEnable = G12GetPrivateProfileInt("BarrierTremorEnable", 0);

		// creates an earthQuake (eines dieser Beben) each interval times the barrier vanishes
		earthQuakeEnable = G12GetPrivateProfileInt("BarrierEarthQuakeEnable", 0);
		earthQuakeInterval = G12GetPrivateProfileInt("BarrierEarthQuakeInterval", 20);

		// Hook to add barrier texture
		InjectHook(0x006B94F9, oCBarrier_Init_Hook, PATCH_JUMP); // oCBarrier::Init()

		// Use our own RenderSkyPre()
		Patch(0x0083C178, &hSkyControler_Barrier::RenderSkyPre); // oCSkyControler_Barrier::`vftable'

		// Use a slightly moddified AddThunderSub()
		InjectHook(0x006BB376, &hBarrier::AddThunderSub); // oCBarrier::AddThunder()
	}
}

void PatchGothic2(void)
{
	PatchBarrier();
	PatchMagicFrontier();
}

void Init(void)
{
	if (GOTHIC2)
	{
		G12AllocConsole();
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
