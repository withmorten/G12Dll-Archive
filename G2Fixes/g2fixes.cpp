#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdint.h>
#include "..\G12Dll\MemoryMgr.h"

#define G12INI_SECTION "G2Fixes"

#include "..\G12Dll\G12.h"

#include "..\G12Dll\G2.hpp"
#include "..\G12Dll\G2.h"
#include "g2fixes.hpp"

FILE *conin, *conout;

void hNpc::CreateVobList(float max_dist)
{
	zCVob *vob;
	oCMobInter *mob;
	oCNpc *npc;
	zVEC3 trafo_vec;
	zTBBox3D bbox;
	zCClassDef *classDef;

	int delete_vob;
	int x;

	if (this->homeWorld)
	{
		for (x = 0; x < this->vobList.numInArray; x++)
		{
			vob = this->vobList.array[x];

			if (vob)
			{
				vob->Release();

				this->vobList.array[x] = NULL;
			}
		}

		this->vobList.DeleteList();

		this->trafoObjToWorld.GetTranslation(trafo_vec);

		bbox.maxs.n[0] = trafo_vec.n[0] + max_dist;
		bbox.maxs.n[1] = trafo_vec.n[1] + max_dist;
		bbox.maxs.n[2] = trafo_vec.n[2] + max_dist;

		bbox.mins.n[0] = trafo_vec.n[0] - max_dist;
		bbox.mins.n[1] = trafo_vec.n[1] - max_dist;
		bbox.mins.n[2] = trafo_vec.n[2] - max_dist;

		this->homeWorld->bspTree.bspRoot->CollectVobsInBBox3D(this->vobList, bbox);

		for (x = 0; x < this->vobList.numInArray; x++)
		{
			delete_vob = 0;

			vob = this->vobList.array[x];

			if (vob)
			{
				if (vob == this)
				{
					delete_vob = 1;
				}
				else
				{
					classDef = vob->_GetClassDef();

					while (classDef)
					{
						if (classDef == (zCClassDef *)0x00AB19A0) // oCMobInter::classDef
						{
							mob = (oCMobInter *)vob;

							if (mob->IsOccupied())
							{
								delete_vob = 1;
							}

							break;
						}
						else if (classDef == (zCClassDef *)0x00AB1E20) // oCNpc::classDef
						{
							npc = (oCNpc *)vob;

							if (npc->attribute[0] <= 0 && npc->inventory2.IsEmpty(1, 1))
							{
								delete_vob = 1;
							}

							break;
						}
						else
						{
							classDef = classDef->baseClassDef;
						}
					}
				}

				if (delete_vob)
				{
					this->vobList.Remove(this->vobList.array[x]);

					x--;
				}
				else
				{
					vob->refCtr++;
				}
			}
		}
	}
}

void PatchFocus(void)
{
	InjectHook(0x0073369B, &hNpc::CreateVobList, PATCH_CALL);
	InjectHook(0x00733BE9, &hNpc::CreateVobList, PATCH_CALL);
	InjectHook(0x0075DC54, &hNpc::CreateVobList, PATCH_CALL);
	InjectHook(0x0075DE95, &hNpc::CreateVobList, PATCH_CALL);
}

const char *Gothic1AppName = "Gothic - 2.6 (fix)";
const char *Gothic1WorldZen = "WORLD.ZEN";
const char *NoSound = "NEWGAME";

void PatchGothic2(void)
{
	if (G12GetPrivateProfileInt("Gothic1Mode", 0))
	{
		// Fix App Title
		Patch(0x0089D9AC, Gothic1AppName);

		// New game starts WORLD.ZEN
		Patch(0x00429A23 + 1, Gothic1WorldZen);
		Patch(0x00429A52 + 1, Gothic1WorldZen);

		// No GAMESTART menu "music"
		Patch(0x004DB7EE + 1, NoSound);
		Patch(0x004DB815 + 1, NoSound);
	}

	if (G12GetPrivateProfileInt("NoGamestartMusic", 0))
	{
		// No GAMESTART menu "music"
		Patch(0x004DB7EE + 1, NoSound);
		Patch(0x004DB815 + 1, NoSound);
	}

	if (G12GetPrivateProfileInt("HideFocus", 0))
	{
		PatchFocus();
	}
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