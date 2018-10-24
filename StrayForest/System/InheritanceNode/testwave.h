#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"
class WAVE : public GameObjectManager
{
private:
	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_pTechnique, m_pTexOffset, m_pSpringPower, m_pAddWavePos, m_pAddWaveHeight;

	//波マップ
	LPDIRECT3DTEXTURE9      m_pWaveMapTexture[2];
	LPDIRECT3DSURFACE9      m_pWaveMapSurface[2];

	//法線マップ
	LPDIRECT3DTEXTURE9      m_pBumpMapTexture;
	LPDIRECT3DSURFACE9      m_pBumpMapSurface;

	LPDIRECT3DDEVICE9 m_pd3dDevice;


	D3DPRESENT_PARAMETERS* Parameter;
	UINT Width_;
	UINT Height_;
	//波マップのインデックス
	int m_RenderTargetIndex;

public:
	WAVE(D3DPRESENT_PARAMETERS* pd3dParameters);
	WAVE(UINT Width, UINT Height);
	~WAVE();
	void Invalidate();
	void Restore();
	HRESULT Load();
	void SetSpringPower(float SpringPower);
	//   void AddWavePos( float X, float Y );
	void AddWave(float Pos_X, float Pos_Y, float Height);
	LPDIRECT3DTEXTURE9 Render();
	BOOL IsOK();
	LPD3DXEFFECT GetEffect() { return m_pEffect; };
};