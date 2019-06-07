class hNpc : public oCNpc
{
public:
	void OnDamage_Events(oSDamageDescriptor &descDamage);
	void CreateVobList(float max_dist);
};

class hSpell : public oCSpell
{
public:
	void StopTargetEffects(zCVob *vob);
	int IsValidTarget(zCVob *v);
	int IsInvestSpell();
	void DoLogicInvestEffect();
	int CastSpecificSpell();
	void EndTimedEffect();
	void DoTimedEffect();
};

class hSkyControler_Outdoor : public zCSkyControler_Outdoor
{
public:
	void ReadFogColorsFromINI();
};

class hActiveSnd : public zCActiveSnd
{
public:
	void AutoCalcObstruction(int immediate) { return; }
};
