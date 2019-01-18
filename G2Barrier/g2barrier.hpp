class hMagFrontier : public oCMagFrontier
{
public:
	void DoCheck();
	float GetDistance(zVEC3 &, float &, zVEC3 &);
};

class hBarrier : public oCBarrier
{
public:
	int Render(zTRenderContext &, int, int);
	int RenderThunder(myThunder *, zTRenderContext &);
};

class hSkyControler_Barrier : public oCSkyControler_Barrier
{
public:
	void RenderSkyPre();
};
