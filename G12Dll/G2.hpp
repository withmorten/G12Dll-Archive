#ifdef PlaySound
#undef PlaySound
#endif

#define zRND_ALPHA_FUNC_ADD 3

typedef int zTSoundHandle;
typedef int zTVobCharClass;
typedef int zTVobSleepingMode;
typedef int zTSndManMedium;

typedef int oTSndMaterial;

struct oTDirectionInfo;
struct oTVobList;
struct oTVobListNpcs;
struct oTVobListItems;

struct myPoly;
struct myVert;

struct zTNode;

class zCLightMap;
class zCMaterial;
class zCTexture;
class zCBspSector;
class zCSoundFX;
class zCDecal;
class zCViewBase;
class zCWorld;
class zCBspLeaf;
class zCAIBase;
class zCRigidBody;
class zCEventManager;
class zCCollisionObjectDef;
class zCCollisionObject;
class zCOutdoorRainFX;
class zCCSManager;
class zCWaypoint;
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
class zCCSPlayer;
class zCBBox3DSorterBase;
class zCPolyStrip;
class zCParser;
class zCClassDef;
class zCArchiver;
class zCVob;
class zCCamera;
class zCPolygon;
class zCVertex;
class zCEventMessage;
class zCRoute;
class zCView;
class zCPlayerGroup;
class zCObject;

class oCNpc;
class oCNpcTalent;
class oCVisualFX;
class oCAIVobMove;
class oCRtnEntry;
class oCItem;
class oCMag_Book;
class oCSpell;
class oCAskBox;
class oCInfo;
class oCNews;
class oCMission;
class oCMobInter;
class oCAIHuman;
class oCAniCtrl_Human;
class oCNpcMessage;
class oCVob;

template<class T> class zCArray
{
public:
	T *array;
	int numAlloc;
	int numInArray;

public:
	void DeleteList();
	void Remove(zCVob *&);
};

template<class T> class zCArraySort : public zCArray<T>
{
public:
	int (*Compare) (T *ele1, T *ele2);
};

template<class T> class zCList
{
public:
	T *data;
	zCList *next;
};

template<class T> class zCListSort
{
public:
	int (*Compare) (T *ele1, T *ele2);
	T *data;
	zCListSort *next;
};

template<class T> class zCTree
{
	zCTree *parent;
	zCTree *firstChild;
	zCTree *next;
	zCTree *prev;
	T *data;
};

template<class T, int SIZE> class zCMatrixStack
{
public:
	int pos;
	T stack[SIZE];
};

template<class _Ty> class _A {};

class std_string
{
public:
	_A<char *> allocator;
	char *_Ptr;
	int _Len;
	int _Res;
};

class zSTRING : public std_string
{
public:
	virtual void *vector_deleting_destructor(unsigned int) { XCALL(0x0041C760); }

public:
	zSTRING() { XCALL(0x00402AF0); }
	zSTRING(char *) { XCALL(0x004010C0); }
};

class zCOLOR
{
public:
	union
	{
		struct
		{
			BYTE b;
			BYTE g;
			BYTE r;
			BYTE alpha;
		};

		DWORD dword;
	};

public:
	void SetAlphaByte(BYTE);
	BYTE GetAlphaByte();
};

class zVEC2
{
public:
	float n[2];
};

class zVEC3
{
public:
	float n[3];
};

class zVEC4
{
public:
	float n[4];
};

class zMAT4
{
public:
	zVEC4 v[4];

public:
	zMAT4 &operator=(zMAT4 &) { XCALL(0x00514D80); }
	void GetTranslation(zVEC3 &) { XCALL(0x00487C70); }
};

struct zTPlane
{
	float distance;
	zVEC3 normal;
};

struct zTBBox3D
{
	zVEC3 mins;
	zVEC3 maxs;
};

struct zTBSphere3D
{
	zVEC3 center;
	float radius;
};

struct zTViewPortData
{
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

struct zTCamVertSimple
{
	float x;
	float y;
	float z;
	zVEC2 texuv;
	zCOLOR color;
};

struct zTRenderContext
{
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

struct zTRainFX
{
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

struct zTTraceRayReport
{
	int foundHit;
	zCVob *foundVob;
	zCPolygon *foundPoly;
	zVEC3 foundIntersection;
	zVEC3 foundPolyNormal;
	zCVertex *foundVertex;
};

struct zTSound3DParams
{
	float obstruction;
	float volume;
	float radius;
	int loopType;
	float coneAngleDeg;
	float reverbLevel;
	int isAmbient3D;
	float pitchOffset;
};

struct myThunder
{
	zVEC3 originVec;
	myThunder *childs;
	int numChilds;
	float startTime[5];
	zCPolyStrip *polyStrip;
	int numSegs;
	int valid;
	float t0;
	float t1;
	int numSplits;
	int dead;
	int isChild;
	int sector;
};

class zCClassDef
{
public:
	zSTRING className;
	zSTRING baseClassName;
	zSTRING scriptClassName;
	zCClassDef *baseClassDef;
	zCObject (*createNewInstance) (void);
	zCObject (*createNewInstanceBackup) (void);
	unsigned int classFlags;
	unsigned int classSize;
	int numLivingObjects;
	int numCtorCalled;
	zCObject **hashtable;
	zCArray<zCObject *> objectList;
	unsigned short archiveVersion;
	unsigned short archiveVersionSum;
};

class zCObject
{
public:
	int refCtr;
	int hashIndex;
	zCObject *hashNext;
	zSTRING objectName;

public:
	virtual zCClassDef *_GetClassDef() { XCALL(0x00401EC0); }

public:
	int Release() { XCALL(0x0040C310); }
};

class zTBoxSortHandle
{
public:
	zCBBox3DSorterBase *mySorter;
	zTBBox3D bbox3D;

	int indexBegin[3];
	int indexEnd[3];

	zCArray<zCVob *> activeList;

public:
	virtual void *scalar_deleting_destructor(unsigned int) { XCALL(0x0083A610); }
};

class zCVisual : public zCObject
{
public:
	zCVisual *nextLODVisual;
	zCVisual *prevLODVisual;
	float lodFarDistance;
	float lodNearFadeOutDistance;

public:
	zCVisual() { XCALL(0x00606660); }
};

class zCVertex
{
public:
	zVEC3 position;

	union
	{
		struct
		{
			int transformedIndex;
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
	zCVertex **vertex;

	int lastTimeDrawn;
	zTPlane polyPlane;
	zCMaterial *material;
	zCLightMap *lightmap;

	zCVertex **clipVert;
	zCVertFeature **clipFeat;
	int numClipVert;

	zCVertFeature **features;
	unsigned char polyNumVert;
};

class zCOBBox3D
{
public:
	zVEC3 center;
	zVEC3 axis[3];
	zVEC3 extent;
	zCList<zCOBBox3D> childs;
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
	int aniChannel;
	float actFrame;
	float aniFPS;
	int frameCtr;
	int bOneShotAni;
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
	float m_fWaveMaxAmplitude;
	float m_fWaveGridSize;

	zCTexture *detailTexture;
	float detailTextureScale;
	zVEC2 texAniMapDelta;

	zVEC2 default_mapping;
	zVEC2 texScale;

public:
	void SetTexture(zSTRING &) { XCALL(0x005649E0); }
};

class zCVob : public zCObject
{
public:
	zCTree<zCVob> *globalVobTreeNode;
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

public:
	zCClassDef *_GetClassDef() { XCALL(0x0043CCB0); }
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

	zCMatrixStack<zMAT4, 8> trafoViewStack;
	zCMatrixStack<zMAT4, 8> trafoWorldStack;
	zCMatrixStack<zMAT4, 8> trafoWorldViewStack;
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
	void SetTransform(int, zMAT4 &) { XCALL(0x0054A540); }
	zMAT4 &GetTransform(int) { XCALL(0x0054A6A0); }
	void SetFarClipZ(float) { XCALL(0x0054B200); }
};

class zCDecal : public zCVisual
{
public:
	void SetDecalDim(float, float) { XCALL(0x00556970); }
	int Render(zTRenderContext &) { XCALL(0x00556990); }
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
	zCPolyStrip() { XCALL(0x005BD300); }
	void SetVisibleSegments(float, float) { XCALL(0x005BDB90); }
	int Render(zTRenderContext &) { XCALL(0x005BDC70); }
};

class oCBarrier
{
public:
	zCMesh *skySphereMesh;

	myPoly *myPolyList;
	myVert *myVertList;

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

	int hBarrier_activeThunder_Sector1;
	int activeThunder_Sector2;
	int activeThunder_Sector3;
	int activeThunder_Sector4;

	zVEC2 *originalTexUVList;

public:
	void Init() { XCALL(0x006B9440); }
	void AddTremor(zTRenderContext &) { XCALL(0x006B9CE0); }
	int RenderLayer(zTRenderContext &, int, int *) { XCALL(0x006B9CF0); }
	int Render(zTRenderContext &, int, int) { XCALL(0x006B9F30); }
	void RemoveThunder(myThunder *) { XCALL(0x006BA9F0); }
	int AddThunder(int, int, float, int) { XCALL(0x006BADE0); }
	int RenderThunder(myThunder *, zTRenderContext &) { XCALL(0x006BB4B0) }
};

class zCRnd_D3D
{
public:
	void FlushPolys() { XCALL(0x0064DD10); }
	void SetZBufferWriteEnabled(int) { XCALL(0x006524E0); }
	int GetZBufferWriteEnabled() { XCALL(0x00652520); }
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
	void RenderSkyPre() { XCALL(0x005EA850); }
};

class oCSkyControler_Barrier : public zCSkyControler_Outdoor
{
public:
	oCBarrier *barrier;
	int bFadeInOut;

public:
	void RenderSkyPre() { XCALL(0x006BB8D0); }
};

class zCBspTree
{
public:
	zCBspNode *actNodePtr;
	zCBspLeaf *actLeafPtr;

	zCBspBase *bspRoot;
	zCMesh *mesh;
	zCPolygon **treePolyList;
	zCBspNode *nodeList;
	zCBspLeaf *leafList;
	int numNodes;
	int numLeafs;
	int numPolys;

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

class zCVobBBox3DSorter
{
public:
	zCArray<zTBoxSortHandle *> handles;
	zCArraySort<zTNode *> nodeList[3];
	int sorted;

public:
	virtual void *vector_deleting_destructor(unsigned int) { XCALL(0x0083A624); }
};

class zCWorld : public zCObject
{
public:
	zCTree<zCVob> globalVobTree;

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

class zCCSPlayer
{
public:
	zCCSCutsceneContext *GetPlayingGlobalCutscene() { XCALL(0x00420770); }
};

class zCSoundSystem
{
public:
	virtual void *scalar_deleting_destructor(unsigned int) { XCALL(0x004EB4D0); }
	virtual zCSoundFX *LoadSoundFX(zSTRING &) { XCALL(0x004EB360); }
	virtual zCSoundFX *LoadSoundFXScript(zSTRING &) { XCALL(0x004EB370); }
	virtual zCParser *GetSFXParser() { XCALL(0x004EB380); }
	virtual float GetPlayingTimeMSEC(zSTRING &) { XCALL(0x004EB390); }
	virtual void SetSound3DDefaultRadius(float) { XCALL(0x004EB3A0); }
	virtual float GetSound3DDefaultRadius() { XCALL(0x004EB3B0); }
	virtual void SetMasterVolume(float) { XCALL(0x004EB3C0); }
	virtual float GetMasterVolume() { XCALL(0x004EB3D0); }
	virtual zTSoundHandle PlaySound(zCSoundFX *, int) = 0;
	virtual zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float) = 0;
	virtual zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *) = 0;
	virtual zTSoundHandle PlaySound3D(zSTRING &, zCVob *, int, zTSound3DParams *) = 0;
	virtual void StopSound(zTSoundHandle &) { XCALL(0x004EB3E0); }
	virtual void StopAllSounds() { XCALL(0x004EB3F0); }
	virtual int GetSound3DProps(zTSoundHandle &, zTSound3DParams &) = 0;
	virtual int UpdateSound3D(zTSoundHandle &, zTSound3DParams *) = 0;
	virtual void GetSoundProps(zTSoundHandle &, int &, float &, float &) { XCALL(0x004EB400); }
	virtual void UpdateSoundProps(zTSoundHandle &, int, float, float) { XCALL(0x004EB410); }
	virtual int IsSoundActive(zTSoundHandle &) { XCALL(0x004EB420); }
};

class zCSndSys_MSS : public zCSoundSystem
{
public:
	void *scalar_deleting_destructor(unsigned int) { XCALL(0x004EB550); }
	zCSoundFX *LoadSoundFX(zSTRING &) { XCALL(0x004ED960); }
	zCSoundFX *LoadSoundFXScript(zSTRING &) { XCALL(0x004EE120); }
	zCParser *GetSFXParser() { XCALL(0x004F4270); }
	float GetPlayingTimeMSEC(zSTRING &) { XCALL(0x004F40E0); }
	void SetMasterVolume(float) { XCALL(0x004ED8E0); }
	float GetMasterVolume() { XCALL(0x004ED730); }
	zTSoundHandle PlaySound(zCSoundFX *, int) { XCALL(0x004EF7B0); }
	zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float) { XCALL(0x004F0B70); }
	zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *) { XCALL(0x004F10F0); }
	zTSoundHandle PlaySound3D(zSTRING &, zCVob *, int, zTSound3DParams *) { XCALL(0x004F1060); }
	void StopSound(zTSoundHandle &) { XCALL(0x004F2300); }
	void StopAllSounds() { XCALL(0x004F23C0); }
	int GetSound3DProps(zTSoundHandle &, zTSound3DParams &) { XCALL(0x004F3780); }
	int UpdateSound3D(zTSoundHandle &, zTSound3DParams *) { XCALL(0x004F2410); }
	void GetSoundProps(zTSoundHandle &, int &, float &, float &) { XCALL(0x004F3580); }
	void UpdateSoundProps(zTSoundHandle &, int, float, float) { XCALL(0x004F3970); }
	int IsSoundActive(zTSoundHandle &) { XCALL(0x004F3FD0); }
};

class zCSoundSystemDummy : public zCSoundSystem
{
public:
	void *scalar_deleting_destructor(unsigned int) { XCALL(0x00639000); }
	zCSoundFX *LoadSoundFX(zSTRING &) { XCALL(0x00632AC0); }
	zTSoundHandle PlaySound(zCSoundFX *, int) { XCALL(0x00632B80); }
	zTSoundHandle PlaySound(zCSoundFX *, int, int, float, float) { XCALL(0x00632B70); }
	zTSoundHandle PlaySound3D(zCSoundFX *, zCVob *, int, zTSound3DParams *) { XCALL(0x00632BA0); }
	zTSoundHandle PlaySound3D(zSTRING &, zCVob *, int, zTSound3DParams *) { XCALL(0x00632B90); }
	int GetSound3DProps(zTSoundHandle &, zTSound3DParams &) { XCALL(0x00632BB0); }
	int UpdateSound3D(zTSoundHandle &, zTSound3DParams *) { XCALL(0x00632BC0); }
};

class zCOption
{
public:
	int ReadBool(zSTRING &, char *, int) { XCALL(0x00462160); }
};

class zCInputCallback
{
public:
	virtual int HandleEvent(int) { XCALL(0x0043D4E0); }
};

class zCBspBase
{
public:
	void __fastcall CollectVobsInBBox3D(zCArray<zCVob *> &, zTBBox3D &) { XCALL(0x00531110); }
};

struct oTRobustTrace
{
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

struct TNpcAIState
{
	int index;
	int loop;
	int end;
	int timeBehaviour;
	float restTime;
	int phase;
	int valid;
	zSTRING name;
	float stateTime;
	int prgIndex;
	int isRtnState;
};

struct TNpcPerc
{
	int percID;
	int percFunc;
};

struct TNpcSlot
{
	zSTRING name;
	int inInventory;
	int tmpLevel;
	zSTRING itemName;

	oCVob *vob;

	int wasVobTreeWhenInserted : 1;
};

class oCVob : public zCVob
{
public:
	zCClassDef *_GetClassDef() { XCALL(0x0077B6C0); }
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
	oCWorld *GetGameWorld() { XCALL(0x006C2C30); }
};

class oCMagFrontier
{
public:
	oCVisualFX *warningFX;
	oCVisualFX *shootFX;
	oCNpc *npc;

	unsigned char isWarning : 1;
	unsigned char isShooting : 1;

public:
	void DoCheck() { XCALL(0x00473740); }
	void DoWarningFX(int) { XCALL(0x00474CB0); }
	void DisposeWarningFX() { XCALL(0x00474E70); }
	void DoShootFX(zVEC3 &) { XCALL(0x00474EB0); }
	void DisposeShootFX() { XCALL(0x004751A0); }
};

class oCNpcTimedOverlay
{
public:
	zSTRING mdsOverlayName;
	float timer;
};

class oCNpc_States
{
public:
	zSTRING name;

	oCNpc *npc;
	TNpcAIState curState;
	TNpcAIState nextState;
	int lastAIState;

	int hasRoutine;
	int rtnChanged;
	oCRtnEntry *rtnBefore;
	oCRtnEntry *rtnNow;
	zCRoute *rtnRoute;
	int rtnOverlay;
	int rtnOverlayCount;
	int walkmode_routine;
	int weaponmode_routine;
	int startNewRoutine;

	int aiStateDriven;
	zVEC3 aiStatePosition;

	oCNpc *parOther;
	oCNpc *parVictim;
	oCItem *parItem;

	int rtnChangeCount;

public:
	virtual void Archive(zCArchiver &) { XCALL(0x0076EE70); }
};

class oCItemContainer : public zCInputCallback
{
public:
	zCListSort<oCItem> *contents;
	oCNpc *npc;
	zSTRING titleText;
	int invMode;
	int selectedItem;
	int offset;
	int maxSlotsCol;
	int maxSlotsColScr;
	int maxSlotsRow;
	int maxSlotsRowScr;
	int maxSlots;
	int marginTop;
	int marginLeft;
	int frame;
	int right;
	int ownList;
	int prepared;
	int passive;
	int TransferCount;

	zCView *viewTitle;
	zCView *viewBack;
	zCView *viewItem;
	zCView *viewItemActive;
	zCView *viewItemHightlighted;
	zCView *viewItemActiveHighlighted;
	zCView *viewItemInfo;
	zCView *viewItemInfoItem;
	zCView *textView;
	zCView *viewArrowAtTop;
	zCView *viewArrowAtBottom;

	zCWorld *rndWorld;
	int posx;
	int posy;
	int m_bManipulateItemsDisabled;
	int m_bCanTransferMoreThanOneItem;
};

class oCNpcInventory : public oCItemContainer
{
public:
	oCNpc *owner;
	int packAbility;

	zCListSort<oCItem> inventory;

	zSTRING packString;
	int maxSlots;

public:
	int IsEmpty(int, int) { XCALL(0x0070D1A0); }
};

class oCNewsMemory
{
public:
	zCList<oCNews> iknow;

public:
	virtual void Archive(zCArchiver &) { XCALL(0x0072A140); }
};

class oCNpc : public oCVob
{
public:
	int idx;
	zSTRING name[5];
	zSTRING slot;
	zSTRING effect;

	int npcType;
	int variousFlags;
	int attribute[8];
	int hitChance[5];
	int protection[8];
	int damage[8];
	int damagetype;
	int guild;
	int level;
	int mission[5];
	int fighttactic;
	int fmode;
	int voice;
	int voicePitch;
	int mass;
	int daily_routine;
	int startAIState;
	zSTRING spawnPoint;
	int spawnDelay;
	int senses;
	int senses_range;
	int aiscriptvars[100];
	zSTRING wpname;
	int experience_points;
	int experience_points_next_level;
	int learn_points;
	int bodyStateInterruptableOverride;
	int noFocus;
	int parserEnd;

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
	oCNpc_States state;
	oCNpcInventory inventory2;
	oCItemContainer *trader;
	oCNpc *tradeNpc;

	float rangeToPlayer;

	zCArray<zTSoundHandle> listOfVoiceHandles;
	int voiceIndex;
	zCArray<oCVisualFX *> effectList;

	int showaidebug : 1;
	int showNews : 1;
	int csAllowedAsRole : 1;

	int isSummoned : 1;
	int respawnOn : 1;
	int movlock : 1;
	int drunk : 1;
	int mad : 1;
	int overlay_wounded : 1;
	int inOnDamage : 1;
	int autoremoveweapon : 1;
	int openinventory : 1;
	int askroutine : 1;
	int spawnInRange : 1;

	int body_TexVarNr : 16;
	int body_TexColorNr : 16;
	int head_TexVarNr : 16;
	int teeth_TexVarNr : 16;
	int guildTrue : 8;
	int drunk_heal : 8;
	int mad_heal : 8;
	int spells : 8;
	int bodyState : 19;
	int m_bAniMessageRunning : 1;

	int instanz;

	zSTRING mds_name;
	zSTRING body_visualName;
	zSTRING head_visualName;

	zVEC3 model_scale;
	float model_fatness;

	int namenr;
	float hpHeal;
	float manaHeal;
	float swimtime;
	float divetime;
	float divectr;
	zCVob *fireVob;
	int fireDamage;
	float fireDamageTimer;

	int attitude;
	int tmp_attitude;
	float attTimer;
	int knowsPlayer;

	TNpcPerc percList[33];
	int percActive;
	float percActiveTime;
	float percActiveDelta;

	int overrideFallDownHeight;
	float fallDownHeight;
	int fallDownDamage;

	oCMag_Book *mag_book;
	zCList<oCSpell> activeSpells;
	int lastHitSpellID;
	int lastHitSpellCat;

	zCArray<zSTRING> activeOverlays;

	oCAskBox *askbox;
	int askYes;
	int askNo;
	float canTalk;
	oCNpc *talkOther;

	oCInfo *info;
	oCNews *news;
	oCMission *curMission;

	oCNewsMemory knownNews;

	zCVob *carry_vob;
	oCMobInter *interactMob;
	oCItem *interactItem;
	int interactItemCurrentState;
	int interactItemTargetState;

	int script_aiprio;
	int old_script_state;
	oCAIHuman *human_ai;
	oCAniCtrl_Human *anictrl;
	zCRoute *route;
	float damageMul;

	oCNpcMessage *csg;
	oCNpcMessage *lastLookMsg;
	oCNpcMessage *lastPointMsg;

	zCArray<zCVob *> vobList;
	float vobcheck_time;
	float pickvobdelay;
	zCVob *focus_vob;

	zCArray<TNpcSlot *> invSlot;
	zCArray<TNpcSlot *> tmpSlotList;

	float fadeAwayTime;
	float respawnTime;

	float selfDist;
	int fightRangeBase;
	int fightRangeFist;
	int fightRangeG;

	float fight_waitTime;
	int fight_waitForAniEnd;
	float fight_lastStrafeFrame;

	int soundType;
	zCVob *soundVob;
	zVEC3 soundPosition;

	zCPlayerGroup *playerGroup;

public:
	zCClassDef *_GetClassDef() { XCALL(0x0072E370); }
	void CreateVobList(float) { XCALL(0x0075DA40); }
};

class oCMOB : public oCVob
{
public:
	zCClassDef *_GetClassDef() { XCALL(0x0071BA20); }
};

class oCMobInter : public oCMOB
{
public:
	zCClassDef *_GetClassDef() { XCALL(0x0071D190); }

public:
	int IsOccupied() { XCALL(0x00718CC0); }
};

class oCVisualFX : public zCObject
{
public:
	static oCVisualFX *__cdecl CreateAndPlay(zSTRING &, zCVob *, zCVob *, int, float, int, int) { XCALL(0x0048E760); }
};
