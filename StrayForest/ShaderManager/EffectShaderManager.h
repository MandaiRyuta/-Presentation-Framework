#pragma once
#include "../Entity/Entity.h"

enum EFFECTINFO
{
	MODEL3D,
	BUMPMAP,
	EFFECT_MAX,
};

class EffectShaderManager
{
public:
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