class hMagFrontier : public oCMagFrontier
{
public:
	void DoCheck(void);
	float GetDistance(zVEC3 *pos, float *dist, zVEC3 *nearestPoint);
};

class hBarrier : public oCBarrier
{
public:
	int Render(zTRenderContext *rndContext, int fadeInOut, int alwaysVisible);
	int RenderThunder(myThunder *thunder, zTRenderContext *rndContext);
};

class hSkyControler_Barrier : public oCSkyControler_Barrier
{
public:
	void RenderSkyPre(void);
};
