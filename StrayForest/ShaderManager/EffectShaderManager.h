#pragma once
#include "../Entity/Entity.h"

enum EFFECTINFO
{
	MODEL3D,
	INSTANCING3D,
	SKINMESH,
	GUARDIAN,
	STENSHILSHADOW,
	SHILED,
	SWORD,
	EFFECT_MAX,
};

class EffectShaderManager
{
private:
	EffectShaderManager() {}
	~EffectShaderManager() {}
public:
	static void EffectLoad(std::string _filepath);
	static LPD3DXEFFECT GetEffect(EFFECTINFO _effectnumber);
	static void ReleaseAll();
private:
	static std::vector<LPD3DXEFFECT> effects_;
	static int effectcount_;
};