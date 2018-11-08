#include "EffectShaderManager.h"

std::vector<LPD3DXEFFECT> EffectShaderManager::effects_;
int	EffectShaderManager::effectcount_ = 0;

void EffectShaderManager::EffectLoad(std::string _filepath)
{
	LPD3DXEFFECT effect;
	if (FAILED(D3DXCreateEffectFromFile(GetDevice(), _filepath.c_str(), NULL, NULL, 0, NULL, &effect, NULL)))
	{
		MessageBox(NULL, "シェーダーファイル読み込み失敗", "ERROR_SHADERFILE", MB_OK);
		PostQuitMessage(0);
	}
	effects_.push_back(effect);
	effectcount_++;
}

LPD3DXEFFECT EffectShaderManager::GetEffect(EFFECTINFO _effectnumber)
{
	if (_effectnumber > effectcount_)
	{
		MessageBox(NULL, "ロードされているエフェクトの数を超えています", NULL, MB_OK);
		PostQuitMessage(0);
	}

	return effects_[_effectnumber];
}

void EffectShaderManager::ReleaseAll()
{
	for (unsigned int i = 0; i < effects_.size(); i++)
	{
		effects_[i]->Release();
		effects_[i] = nullptr;
	}
}
