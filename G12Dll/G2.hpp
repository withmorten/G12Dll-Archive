#undef PlaySound

#define zRND_ALPHA_FUNC_ADD 3

typedef unsigned int zCOLOR;
typedef int zTSoundHandle;
class zCLightMap;
class zCMaterial;
class zCTexture;
class zCBspSector;
class zCSoundFX;
class zCDecal;
class zCViewBase;
class zCWorld;
class zCTree;
class zCBspLeaf;
class zCAIBase;
class zCRigidBody;
class zCEventManager;
class zCCollisionObjectDef;
class zCCollisionObject;
class zCOutdoorRainFX;
class zCCSManager;
class oCNpc;
class zCWaypoint;
class oTDirectionInfo;
class oCNpcTalent;
class zCCSCutsceneContext;
class zCSession;
class zCWayNet;
class zCViewProgressBar;
class zCWorldPerFrameCallback;
class zCZone;
class zCCBspTree;
class zCBspNode;
class zCBspBase;
class zCVobLight;
class oTVobList;
class oTVobListNpcs;
class oTVobListItems;
class oCVisualFX;
class zCCSPlayer;
class zTNode;
class zCBBox3DSorterBase;
class zCPolyStrip;
class zCParser;

template<class T> class zCArray
{
public:
	T *pArray;
	int numAlloc;
	int numInArray;
};

template<class T> class zCArraySort : public zCArray<T>
{
public:
	int(*Compare)(T *ele1, T *ele2);
};

template<class T> class zCList
{
public:
	T *data;
	zCList *next;
};

class zSTRING
{
public:
	int _vftable;
	int _allocator;
	char *ptr;
	int len;
	int res;

public:
	zSTRING(const char *)
	{
		XCALL(0x004010C0);
	}
};

class zCObject
{
public:
	int _vftable;
	int _refCtr;
	int _hashIndex;
	int _hashNext;
	zSTRING _objectName;

public:
	int Release(void)
	{
		XCALL(0x0040C310);
	}

	zSTRING *GetObjectName(void)
	{
		XCALL(0x005A9CD0);
	}
};

class zCVisual : public zCObject
{
public:
	zCVisual *nextLODVisual;
	zCVisual *prevLODVisual;
	float lodFarDistance;
	float lodNearFadeOutDistance;
};

class zVEC2
{
public:
	float x;
	float y;
};

class zVEC3
{
public:
	float x;
	float y;
	float z;
};

class zVEC4
{
public:
	float x;
	float y;
	float z;
	float w;
};

class zMAT4
{
public:
	zVEC4 row[4];

public:
	zMAT4 *operator=(zMAT4 *)
	{
		XCALL(0x00514D80);
	}
};

class zTPlane
{
public:
	float m_fD;
	zVEC3 m_vNormal;
};

class zCVertex
{
public:
	zVEC3 position;

	union
	{
		struct
		{
			int mytransforminedIndex;
			int myIndex;
		};

		unsigned int hackData;
	};
};

class zCVertFeature
{
public:
	zVEC3 vertNormal;
	zCOLOR lightStat;
	zCOLOR lightDyn;
	float texu;
	float texv;
};

class zCPolygon
{
public:
	zCVertex **Vertices;

	int LastTimeDrawn;
	zTPlane PolyPlane;
	zCMaterial *Material;
	zCLightMap *Lightmap;

	zCVertex **ClipVertices;
	zCVertFeature **ClipFeatures;
	int NumClipVert;

	zCVertFeature **Features;
	unsigned char PolyNumVert;
};

class zTBBox3D
{
public:
	zVEC3 mins;
	zVEC3 maxs;
};

class zCOBBox3D
{
public:
	zVEC3 m_vCenter;
	zVEC3 m_vAxisX;
	zVEC3 m_vAxisY;
	zVEC3 m_vAxisZ;
	zVEC3 m_vExtent;
	zCList<zCOBBox3D> m_lstHierarchy;
};

class zTBSphere3D
{
public:
	zVEC3 center;
	float radius;
};

class zCMesh : public zCVisual
{
public:
	int numPoly;
	int numVert;
	int numFeat;

	zCVertex **vertList;
	zCPolygon **polyList;
	zCVertFeature **featList;

	zCVertex *vertArray;
	zCPolygon *polyArray;
	zCVertFeature *featArray;

	zTBBox3D bbox3D;
	zCOBBox3D obbox3D;

	zCMesh *next;
	zCMesh *prev;

	int masterFrameCtr;

	zSTRING meshName;
	int hasLightmaps;
	int m_bUsesAlphaTesting;

	int numVertAlloc;
	int numPolyAlloc;
};

class zCTexAniCtrl
{
public:
	int m_nTexAnimatedChannel;
	float m_fCurrentFrame;
	float m_fTexAniFPS;
	int m_mFrameCtr;
	int m_bNoLoopTexAni;
};

class zCMaterial : public zCObject
{
public:
	zCArray<zCPolygon *> polyList;
	int polyListTimeStamp;

	zCTexture *texture;
	zCOLOR color;
	int smoothAngle;
	int matGroup;
	zCBspSector *bspSectorFront;
	zCBspSector *bspSectorBack;
	zCTexAniCtrl texAniCtrl;
	zSTRING *detailObjectVisualName;

	int kambient;
	int kdiffuse;

	int m_bEnvironmentalMappingStrength;

	struct
	{
		unsigned char smooth : 1;
		unsigned char dontUseLightmaps : 1;
		unsigned char texAniMap : 1;
		unsigned char lodDontCollapse : 1;
		unsigned char noCollDet : 1;
		unsigned char forceOccluder : 1;
		unsigned char m_bEnvironmentalMapping : 1;
		unsigned char polyListNeedsSort : 1;
		unsigned char matUsage : 8;
		unsigned char libFlag : 8;
		int rndAlphaBlendFunc : 8;
		unsigned char m_bIgnoreSun : 1;
	};

	int m_enuWaveMode;
	int m_enuWaveSpeed;
	int m_fWaveMaxAmplitude;
	int m_fWaveGridSize;

	int detailTexture;
	int detailTextureScale;
	int texAniMapDelta[2];

	int default_mapping[2];
	int texScale[2];

public:
	zSTRING *GetName(void)
	{
		XCALL(0x0055FF10);
	}

	void SetTexture(zSTRING *)
	{
		XCALL(0x005649E0);
	}
};

class zTViewPortData
{
public:
	int xmin;
	int ymin;
	int xdim;
	int ydim;
	float xminFloat;
	float yminFloat;
	float xmaxFloat;
	float ymaxFloat;
	float xdimFloat;
	float ydimFloat;
	float xdimFloatMinus1;
	float ydimFloatMinus1;
	float xcenter;
	float ycenter;
};

class zTCamVertSimple
{
public:
	float x;
	float y;
	float z;
	zVEC2 texuv;
	zCOLOR color;
};

class zCVob : public zCObject
{
public:
	zCTree *globalVobTreeNode;
	int lastTimeDrawn;
	int lastTimeCollected;

	zCArray<zCBspLeaf *> vobLeafList;

	zMAT4 trafoObjToWorld;
	zTBBox3D bbox3D;
	zTBSphere3D bsphere3D;

	zCArray<zCVob *> touchVobList;

	int type;
	int groundShadowSizePacked;
	zCWorld *homeWorld;
	zCPolygon *groundPoly;
	zCAIBase *callback_ai;
	zMAT4 *trafo;

	zCVisual *visual;
	float visualAlpha;
	float m_fVobFarClipZScale;
	int m_AniMode;
	float m_aniModeStrength;
	int m_zBias;

	zCRigidBody *rigidBody;

	zCOLOR lightColorStat;
	zCOLOR lightColorDyn;
	zVEC3 lightDirectioNStat;
	zSTRING *vobPresetName;

	zCEventManager *eventManager;
	float nextOnTimer;

	struct
	{
		unsigned char showVisual : 1;
		unsigned char drawBBox3D : 1;
		unsigned char visualAlphaEnabled : 1;
		unsigned char physicsEnabled : 1;

		unsigned char staticVob : 1;
		unsigned char ignoredByTraceRay : 1;
		unsigned char collDetectionStatic : 1;
		unsigned char collDetectionDynamic : 1;

		unsigned char castDynShadow : 2;
		unsigned char lightColorStatDirty : 1;
		unsigned char lightColorDynDirty : 1;

		int isInMovementMode : 2;
		unsigned char sleepingMode : 2;

		unsigned char mbHintTrafoLocalConst : 1;
		unsigned char mbInsideEndMovementMethod : 1;
		int visualCamAlign : 2;

		unsigned char collButNoMove : 4;

		unsigned char dontWriteIntoArchive : 1;
		unsigned char bIsInWater : 1;
		unsigned char bIsAmbientVob : 1;
	};

	zCCollisionObjectDef *m_poCollisionObjectClass;
	zCCollisionObject *m_poCollisionObject;
};

class oCVob : public zCVob
{
};

class zCCamera
{
public:
	zTPlane frustumplanes[6];
	BYTE signbits[6];

	zTViewPortData vpdata;
	zCViewBase *targetView;

	zMAT4 camMatrix;
	zMAT4 camMatrixInv;

	int tremorToggle;
	float tremorScale;
	zVEC3 tremorAmplitude;
	zVEC3 tremorOrigin;
	float tremorVelo;

	zMAT4 trafoView;
	zMAT4 trafoViewInv;
	zMAT4 trafoWOrld;

	int trafoViewStackPos;
	zMAT4 trafoViewStack[8];
	int trafoWorldStackPos;
	zMAT4 trafoWorldStack[8];
	int trafoWorldViewStackPos;
	zMAT4 trafoWorldViewStack[8];
	zMAT4 trafoProjection;

	zTCamVertSimple polyCamVerts[4];
	zCPolygon *poly;
	zCMesh *polyMesh;
	zCMaterial *polyMaterial;

	int screenFadeEnabled;
	zCOLOR screenFadeColor;
	zSTRING screenFadeTexture;
	float screenFadeTextureAniFps;
	int screenFadeTextureBlendFunc;
	int cinemaScopeEnabled;
	zCOLOR cinemaScopeColor;

	int projection;
	int drawMode;
	int shadeMode;
	int drawWire;

	float farClipZ;
	float nearClipZ;
	float viewDistanceX;
	float viewDistanceY;
	float viewDistanceXInv;
	float viewDistanceYInv;
	int vobFarClipZ;
	float fovH;
	float fovV;
	zCVob *connectedVob;

	float topBottomSin;
	float topBottomCos;
	float leftRightSin;
	float leftRightCos;

public:
	void SetTransform(int, zMAT4 *)
	{
		XCALL(0x0054A540);
	}

	zMAT4 *GetTransform(int)
	{
		XCALL(0x0054A6A0);
	}

	void SetFarClipZ(float z)
	{
		XCALL(0x0054B200);
	}
};

class zTRenderContext
{
public:
	int clipFlags;
	zCVob *vob;
	zCWorld *world;
	zCCamera *cam;
	float distVobToCam;
	int visualCamAlign;
	int m_AniMode;
	float m_aniModeStrength;
	zCOLOR hintLightingHighlightColor;

	struct
	{
		unsigned char hintLightingFullbright : 1;
		unsigned char hintLightingSwell : 1;
		unsigned char hintLightingHighlight : 1;
	};
};

class zCDecal : public zCVisual
{
public:
	void SetDecalDim(float, float)
	{
		XCALL(0x00556970);
	}

	int Render(zTRenderContext *)
	{
		XCALL(0x00556990);
	}
};

class zCPolyStrip : public zCVisual
{
public:
	zCMaterial *material;

	zCVertex *vertList;
	zCPolygon *polyList;

	int numPoly;
	int numVert;

	zVEC3 *centerPointList;
	float *alphaList;
	float width;
	zCVob *connectedVob;
	zTBBox3D bbox3D;
	int camAlign;
	int heightCheck;
	int everyFrameUpdate;
	float heightBound;

	int firstSeg;
	int lastSeg;
	int numSeg;

	float visLastFrac;
	float visFirstFrac;

	float alphaFadeSpeed;
	float newAlphaFadeSpeed;
	float newAlpha;
	int lastDirSeg;
	zVEC3 lastDirNormal;

	struct
	{
		unsigned char localFOR : 1;
	};

public:
	void SetVisibleSegments(float, float)
	{
		XCALL(0x005BDB90);
	}

	int Render(zTRenderContext *)
	{
		XCALL(0x005BDC70);
	}
};

class myThunder
{
public:
	zVEC3 m_vPosition;
	myThunder *m_pSubThunders;
	int m_nNumSubThunders;
	float m_fSubStartSeg[3];
	int hackData8;
	int hackData9;
	zCPolyStrip *m_pPolyStrip;
	int m_nNumSegments;
	int m_bActive;
	float m_nStartVisSeg;
	float m_nEndVisSeg;
	int m_nIndex;
	int hackData16;
	int m_bIsSubThunder;
	int m_Sector;
};

class oCBarrier
{
public:
	zCMesh *skySphereMesh;

	void *myPolyList;
	void *myVertList;

	int numMyVerts;
	int numMyPolys;

	myThunder *myThunderList;
	int numMaxThunders;
	int numMyThunders;

	int actualIndex;
	int rootBoltIndex;

	int startPointList1[10];
	int numStartPoints1;
	int startPointList2[10];
	int numStartPoints2;
	int startPointList3[10];
	int numStartPoints3;
	int startPointList4[10];
	int numStartPoints4;

	int topestPoint;

	int bFadeInOut;
	int fadeState;

	int fadeIn;
	int fadeOut;
	int bFlashing;
	int fFlashTime;

	zCSoundFX *sfx1;
	zTSoundHandle sfxHandle1;
	zCSoundFX *sfx2;
	zTSoundHandle sfxHandle2;
	zCSoundFX *sfx3;
	zTSoundHandle sfxHandle3;
	zCSoundFX *sfx4;
	zTSoundHandle sfxHandle4;

	zCDecal *thunderStartDecal;

	int bThunder1;
	int bThunder2;
	int bThunder3;
	int bThunder4;

	zVEC2 *originalTexUVList;

public:
	void Init(void)
	{
		XCALL(0x006B9440);
	}

	int RenderLayer(zTRenderContext *, int, int *)
	{
		XCALL(0x006B9CF0);
	}

	int Render(zTRenderContext *, int, int)
	{
		XCALL(0x006B9F30);
	}

	void RemoveThunder(myThunder *)
	{
		XCALL(0x006BA9F0);
	}

	int AddThunder(int, int, float, int)
	{
		XCALL(0x006BADE0);
	}
};

class zCRnd_D3D
{
public:
	void FlushPolys(void)
	{
		XCALL(0x0064DD10);
	}

	void SetZBufferWriteEnabled(int zBufferWriteEnabled)
	{
		XCALL(0x006524E0);
	}

	int GetZBufferWriteEnabled(void)
	{
		XCALL(0x00652520);
	}
};

class zTRainFX
{
public:
	zCOutdoorRainFX *outdoorRainFX;
	int camLocationHint;
	float outdoorRainFXWeight;
	float soundVolume;
	float timerInsideSectorCantSeeOutside;
	float timeStartRain;
	float timeStopRain;
	int renderLightning;
	int m_bRaining;
	int m_iRainCtr;
};

class zCSkyPlanet
{
public:
	zCMesh *mesh;
	zVEC4 color0;
	zVEC4 color1;
	float size;
	zVEC3 pos;
	zVEC3 rotAxis;
};

class zCSkyLayer
{
public:
	zCMesh *skyPolyMesh;
	zCPolygon *skyPoly;
	zVEC2 skyTexOffs;
	zCMesh *skyDomeMesh;
	int skyMode;
};

class zCSkyLayerData
{
public:
	int skyMode;
	zCTexture *tex;
	zSTRING texName;
	float texAlpha;
	float texScale;
	zVEC2 texSpeed;
};

class zCSkyState
{
public:
	float time;
	zVEC3 polyColor;
	zVEC3 fogColor;
	zVEC3 domeColor1;
	zVEC3 domeColor0;
	float fogDist;
	int sunOn;
	int cloudShadowOn;

	zCSkyLayerData layer[2];
};

class zCSkyControler : public zCObject
{
public:
	zCOLOR *polyLightCLUTPtr;
	float cloudShadowScale;
	int m_bColorChanged;
	int m_enuWeather;

	zCOLOR backgroundColor;
	int fillBackground;
	zCTexture *backgroundTexture;
	int relightCtr;
	float lastRelightTime;
	float m_fRelightTime;

public:
	int GetWeatherType(void)
	{
		XCALL(0x005DF510);
	}
};

class zCSkyControler_Mid : public zCSkyControler
{
public:
	int underwaterFX;
	zCOLOR underwaterColor;
	float underwaterFarZ;

	float underwaterStartTime;
	float oldFovX;
	float oldFovY;

	zCVob *underwaterPFX;

	zCPolygon *scrPoly;
	zCMesh *scrPolyMesh;
	int scrPolyAlpha;
	zCOLOR scrPolyColor;
	int scrPolyAlphaFunc;
};

class zCSkyControler_Outdoor : public zCSkyControler_Mid
{
public:
	int initDone;
	float masterTime;
	float masterTimeLast;

	zCSkyState masterState;
	zCSkyState *state0;
	zCSkyState *state1;

	zCArray<zCSkyState *> stateList;

	zCOLOR polyLightClut[256];

	float dayCounter;

	zCArray<zVEC3> fogColorDayVariations;
	zCArray<zVEC3> fogColorDayVariations2;

	float m_fSkyScale;
	int m_bSkyScaleChanged;
	zVEC3 m_overrideColor;
	int m_bOverrideColorFlag;
	int m_bDontRain;
	int m_bLevelChanged;
	int m_bDarkSky;

	float resultFogScale;
	float heightFogMinY;
	float heightFogMaxY;
	float userFogFar;
	float resultFogNear;
	float resultFogFar;
	float resultFogSkyNear;
	float resultFogSkyFar;
	zCOLOR resultFogColor;
	zCOLOR resultFogColorOverride;
	float userFarZScalability;

	zCSkyState *skyLaterState[2];
	zCSkyLayer skyLayer[2];
	zCSkyLayer skyLayerRainClouds;
	zCTexture *skyCloudLayerTex;

	zCSkyPlanet planets[2];
	int m_bSunVisible;
	float m_fFadeScale;

	zCVob *vobSkyPfx;
	float skyPFXTimer;

	int m_bIsMainControler;
	zVEC3 m_bWindVec;

	zTRainFX rainFX;
public:
	int GetRenderLightning(void)
	{
		XCALL(0x005E6780);
	}

	void RenderSkyPre(void)
	{
		XCALL(0x005EA850);
	}
};

class oCSkyControler_Barrier : public zCSkyControler_Outdoor
{
public:
	oCBarrier *barrier;
	int bFadeInOut;
public:
	void RenderSkyPre(void)
	{
		XCALL(0x006BB8D0);
	}
};

class zTTraceRayReport
{
public:
	int m_BIntersect;
	zCVob *m_pVob;
	zCPolygon *m_pPolygon;
	zVEC3 m_vIntersect;
	zVEC3 m_vNormal;
	zCVertex *m_pVertex;
};

class zCBspTree
{
public:
	zCBspNode *actNodePtr;
	zCBspLeaf *actLeafPtr;

	zCBspBase *bspRoot;
	zCMesh *m_pMesh;
	zCPolygon **m_ppTreePolyList;
	zCBspNode *nodeList;
	zCBspLeaf *m_pLeafList;
	int numNodes;
	int m_nLeafSize;
	int m_nNumPolys;

	zCArray<zCVob *> renderVobList;
	zCArray<zCVobLight *> renderLightList;
	zCArray<zCBspSector *> sectorList;
	zCArray<zCPolygon *> portalList;

	int bspTreeMode;
	int worldRenderMode;
	float vobFarClipZ;

	zTPlane vobFarPlane;
	int vobFarPlaneSignbits;
	int drawVobBBox3D;
	int leafsRendered;
	int vobsRendered;
	int m_bRenderedFirstTime;
	int masterFrameCtr;
	zCPolygon **actPolyPtr;
	int compiled;
};

class zTBoxSortHandle
{
public:
	int _vftable;
	zCBBox3DSorterBase *mySorter;
	zTBBox3D bbox3D;

	int indexBegin[3];
	int indexEnd[3];

	zCArray<zCVob *> activeList;
};

class zCVobBBox3DSorter
{
public:
	int _vftable;
	zCArray<zTBoxSortHandle *> handles;
	zCArraySort<zTNode *> nodeList[3];
	int sorted;
};

class zCWorld : public zCObject
{
public:
	zCTree *parent;
	zCTree *firstChild;
	zCTree *next;
	zCTree *prev;
	zCVob *data;

	zTTraceRayReport traceRayReport;

	zCSession *ownerSession;
	zCCSPlayer *csPlayer;

	zSTRING m_strlevelName;
	int compiled;
	int compiledEditorMode;
	int traceRayIgnoreVobFlag;
	int m_bIsInventoryWorld;
	int worldRenderMode;
	zCWayNet *wayNet;
	int masterFrameCtr;
	float vobFarClipZ;
	float vobFarClipZScalability;

	zCArray<zCVob *> traceRayVobList;
	zCArray<zCVob *> traceRayTempIgnoreVobList;

	int renderingFirstTime;
	int showWaynet;
	int showTraceRayLines;

	zCViewProgressBar *progressBar;
	int unarchiveFileLen;
	int unarchiveStartPosVobtree;
	int numVobsInWorld;

	zCArray<zCWorldPerFrameCallback *> perFrameCallbackList;

	zCSkyControler *skyControlerIndoor;
	zCSkyControler *skyControlerOutdoor;
	zCSkyControler *activeSkyControler;

	zCArray<zCZone *> zoneGlobalList;
	zCArraySort<zCZone *> zoneActiveList;
	zCArraySort<zCZone *> zoneLastClassList;

	zCVobBBox3DSorter zoneBoxSorter;
	zTBoxSortHandle zoneActiveHandle;

	int addZonesToWorld;
	int showZonesDebugInfo;

	zCCBspTree *cbspTree;
	zCBspTree bspTree;

	zCArray<zCVob *> activeVobList;
	zCArray<zCVob *> walkList;

	zCArray<zCVob *> vobHashTable[2048];
};

class oCWorld : public zCWorld
{
public:
	zSTRING worldFilename;
	zSTRING worldName;

	oTVobList *voblist;
	oTVobListNpcs *voblist_npcs;
	oTVobListItems *voblist_items;
};

class oCGame
{
public:
	oCWorld *GetGameWorld(void)
	{
		XCALL(0x006C2C30);
	}
};

class zCCSPlayer
{
public:
	zCCSCutsceneContext *GetPlayingGlobalCutscene(void)
	{
		XCALL(0x00420770);
	}
};

class oCMagFrontier
{
public:
	oCVisualFX *warningFX;
	oCVisualFX *shootFX;
	oCNpc *npc;
	unsigned char statusBit;

public:
	void DoCheck(void)
	{
		XCALL(0x00473740);
	}

	void DoWarningFX(int)
	{
		XCALL(0x00474CB0);
	}

	void DisposeWarningFX(void)
	{
		XCALL(0x00474E70);
	}

	void DoShootFX(zVEC3 *)
	{
		XCALL(0x00474EB0);
	}

	void DisposeShootFX(void)
	{
		XCALL(0x004751A0);
	}
};

class oTRobustTrace
{
public:
	struct
	{
		unsigned char stand : 1;
		unsigned char dirChoosed : 1;
		unsigned char exactPosition : 1;
		unsigned char targetReached : 1;
		unsigned char standIfTargetReached : 1;
		unsigned char waiting : 1;
		unsigned char isObstVobSmall : 1;
		unsigned char targetVisible : 1;
		unsigned char useChasmChecks : 1;
	};

	zVEC3 targetPos;
	zCVob *targetVob;
	zCVob *obstVob;
	float targetDist;
	float lastTargetDist;
	float maxTargetDist;
	float dirTurn;
	float timer;
	zVEC3 dirFirst;
	float dirLastAngle;

	zCArray<oTDirectionInfo *> lastDirections;

	int frameCtr;

	zVEC3 targetPostArray[5];
	int targetPosCounter;
	int targetPosIndex;
	float checkVisibilityTime;
	float positionUpdateTime;
	float failurePossibility;
};

class oCNpcTimedOverlay
{
public:
	zSTRING mdsOverlayName;
	float timer;
};

class oCNpc : public oCVob
{
public:
	int m_nID;
	zSTRING m_sNameNpc[5];
	zSTRING m_sSlot;
	zSTRING m_sEffect;

	int m_NpcType;
	int m_dwFlags;
	int m_nAttribute[8];
	int m_nHitChance[5];
	int m_nProtection[8];
	int m_nDamages[8];
	int m_nDamageTypes;
	int m_nGuild;
	int m_nLevel;
	int m_pfnMission[5];
	int m_nFightTactic;
	int fmode;
	int m_nVoice;
	int m_nVoicePitch;
	int m_nBodymass;
	int m_pfnDailyRoutine;
	int m_pfnStartAiState;
	zSTRING m_sRespawnPoint;
	int m_nRespawnTime;
	int m_nSenses;
	int m_nSensesRange;
	int m_nAivar[100];
	zSTRING m_sWp;
	int m_nExpPoints;
	int m_nExpNext;
	int m_nLearnPoints;
	int bodyStateInterruptableOverride;
	int m_bNoFocus;
	int *m_pAIVAR;

	int bloodEnabled;
	int bloodDistance;
	int bloodAmount;
	int bloodFlow;
	zSTRING bloodEmitter;
	zSTRING bloodTexture;
	int didHit;
	int didParade;
	int didShoot;
	int hasLockedEnemy;
	int isDefending;
	int wasAming;
	int lastAction;
	oCNpc *enemy;

	float speedTurn;
	int foundFleePoint;
	int reachedFleePoint;
	zVEC3 vecFlee;
	zVEC3 posFlee;
	zCWaypoint *waypointFlee;
	oTRobustTrace rbt;
	zCList<oCNpcTimedOverlay> timedOverlays;
	zCArray<oCNpcTalent *> talents;
	int spellMana;
	oCMagFrontier magFrontier;
};

class zTSound3DParams
{
public:
	float obstruction;
	float volume;
	float radius;
	int loopType;
	float coneAngleDeg;
	float reverbLevel;
	int isAmbient3D;
	float pitchOffset;
};

class zCSoundFX : public zCObject
{
};

class zCSoundSystem
{
public:
	virtual ~zCSoundSystem()
	{
		XCALL(0x004EB4D0);
	}

	virtual zCSoundFX *LoadSoundFX(zSTRING *)
	{
		XCALL(0x004EB360);
	}

	virtual zCSoundFX *LoadSoundFXScript(zSTRING *)
	{
		XCALL(0x004EB370);
	}

	virtual zCParser *GetSFXParser(void)
	{
		XCALL(0x004EB380);
	}

	virtual float GetPlayingTimeMSEC(zSTRING *)
	{
		XCALL(0x004EB390);
	}

	virtual void SetSound3DDefaultRadius(float)
	{
		XCALL(0x004EB3A0);
	}

	virtual float GetSound3DDefaultRadius(void)
	{
		XCALL(0x004EB3B0);
	}

	virtual void SetMasterVolume(float)
	{
		XCALL(0x004EB3C0);
	}

	virtual float GetMasterVolume(void)
	{
		XCALL(0x004EB3D0);
	}

	virtual zTSoundHandle PlaySound(zCSoundFX *, int) = 0;

	virtual zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float) = 0;

	virtual zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *) = 0;

	virtual zTSoundHandle PlaySound3D(zSTRING *, zCVob *, int, zTSound3DParams *) = 0;

	virtual void StopSound(zTSoundHandle *)
	{
		XCALL(0x004EB3E0);
	}

	virtual void StopAllSounds(void)
	{
		XCALL(0x004EB3F0);
	}

	virtual int GetSound3DProps(zTSoundHandle *, zTSound3DParams *) = 0;

	virtual int UpdateSound3D(zTSoundHandle *, zTSound3DParams *) = 0;

	virtual void GetSoundProps(zTSoundHandle *, int *, float *, float *)
	{
		XCALL(0x004EB400);
	}

	virtual void UpdateSoundProps(zTSoundHandle *, int, float, float)
	{
		XCALL(0x004EB410);
	}

	virtual int IsSoundActive(zTSoundHandle *)
	{
		XCALL(0x004EB420);
	}
};

class zCSndSys_MSS : public zCSoundSystem
{
public:
	~zCSndSys_MSS()
	{
		XCALL(0x004EB550);
	}

	zCSoundFX *LoadSoundFX(zSTRING *)
	{
		XCALL(0x004ED960);
	}

	zCSoundFX *LoadSoundFXScript(zSTRING *)
	{
		XCALL(0x004EE120);
	}

	zCParser *GetSFXParser(void)
	{
		XCALL(0x004F4270);
	}

	float GetPlayingTimeMSEC(zSTRING *)
	{
		XCALL(0x004F40E0);
	}

	void SetSound3DDefaultRadius(float)
	{
		XCALL(0x004EB3A0);
	}

	float GetSound3DDefaultRadius(void)
	{
		XCALL(0x004EB3B0);
	}

	void SetMasterVolume(float)
	{
		XCALL(0x004ED8E0);
	}

	float GetMasterVolume(void)
	{
		XCALL(0x004ED730);
	}

	zTSoundHandle PlaySound(zCSoundFX *, int)
	{
		XCALL(0x004EF7B0);
	}

	zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float)
	{
		XCALL(0x004F0B70);
	}

	zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *)
	{
		XCALL(0x004F10F0);
	}

	zTSoundHandle PlaySound3D(zSTRING *, zCVob *, int, zTSound3DParams *)
	{
		XCALL(0x004F1060);
	}

	void StopSound(zTSoundHandle *)
	{
		XCALL(0x004F2300);
	}

	void StopAllSounds(void)
	{
		XCALL(0x004F23C0);
	}

	int GetSound3DProps(zTSoundHandle *, zTSound3DParams *)
	{
		XCALL(0x004F3780);
	}

	int UpdateSound3D(zTSoundHandle *, zTSound3DParams *)
	{
		XCALL(0x004F2410);
	}

	void GetSoundProps(zTSoundHandle *, int *, float *, float *)
	{
		XCALL(0x004F3580);
	}

	void UpdateSoundProps(zTSoundHandle *, int, float, float)
	{
		XCALL(0x004F3970);
	}

	int IsSoundActive(zTSoundHandle *)
	{
		XCALL(0x004F3FD0);
	}
};

class zCSoundSystemDummy : public zCSoundSystem
{
public:
	~zCSoundSystemDummy()
	{
		XCALL(0x00639000);
	}

	zCSoundFX *LoadSoundFX(zSTRING *)
	{
		XCALL(0x00632AC0);
	}

	zCSoundFX *LoadSoundFXScript(zSTRING *)
	{
		XCALL(0x004EB370);
	}

	zCParser *GetSFXParser(void)
	{
		XCALL(0x004EB380);
	}

	float GetPlayingTimeMSEC(zSTRING *)
	{
		XCALL(0x004EB390);
	}

	void SetSound3DDefaultRadius(float)
	{
		XCALL(0x004EB3A0);
	}

	float GetSound3DDefaultRadius(void)
	{
		XCALL(0x004EB3B0);
	}

	void SetMasterVolume(float)
	{
		XCALL(0x004EB3C0);
	}

	float GetMasterVolume(void)
	{
		XCALL(0x004EB3D0);
	}

	zTSoundHandle PlaySound(zCSoundFX *, int)
	{
		XCALL(0x00632B80);
	}

	zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float)
	{
		XCALL(0x00632B70);
	}

	zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *)
	{
		XCALL(0x00632BA0);
	}

	zTSoundHandle PlaySound3D(zSTRING *, zCVob *, int, zTSound3DParams *)
	{
		XCALL(0x00632B90);
	}

	void StopSound(zTSoundHandle *)
	{
		XCALL(0x004EB3E0);
	}

	void StopAllSounds(void)
	{
		XCALL(0x004EB3F0);
	}

	int GetSound3DProps(zTSoundHandle *, zTSound3DParams *)
	{
		XCALL(0x00632BB0);
	}

	int UpdateSound3D(zTSoundHandle *, zTSound3DParams *)
	{
		XCALL(0x00632BC0);
	}

	void GetSoundProps(zTSoundHandle *, int *, float *, float *)
	{
		XCALL(0x004EB400);
	}

	void UpdateSoundProps(zTSoundHandle *, int, float, float)
	{
		XCALL(0x004EB410);
	}

	int IsSoundActive(zTSoundHandle *)
	{
		XCALL(0x004EB420);
	}
};

class zCOption
{
public:
	int ReadBool(zSTRING *, char *, int)
	{
		XCALL(0x00462160);
	}
};
