#include "testwave.h"

//SafeReleaseは関数ではなくマクロ
#define SafeRelease(x) { if(x) { (x)->Release(); (x)=NULL; } }

WAVE::WAVE(D3DPRESENT_PARAMETERS* pd3dParameters) : GameObjectManager(0)
{
	m_pd3dDevice = GetDevice();
	Parameter = pd3dParameters;
	m_pEffect = NULL;

	for (int i = 0; i<2; i++)
	{
		m_pWaveMapTexture[i] = NULL;
		m_pWaveMapSurface[i] = NULL;
	}

	m_pBumpMapTexture = NULL;
	m_pBumpMapSurface = NULL;
	
	m_RenderTargetIndex = 0;
}

WAVE::WAVE(UINT Width, UINT Height) : GameObjectManager(0)
{
	m_pd3dDevice = GetDevice();

	m_pEffect = NULL;

	Width_ = Width;
	Height_ = Height;

	for (int i = 0; i<2; i++)
	{
		m_pWaveMapTexture[i] = NULL;
		m_pWaveMapSurface[i] = NULL;
	}

	m_pBumpMapTexture = NULL;
	m_pBumpMapSurface = NULL;

	m_RenderTargetIndex = 0;
}

WAVE::~WAVE()
{
	Invalidate();
	SafeRelease(m_pEffect);
}

//デバイスがロストしたときにコールする関数
void WAVE::Invalidate()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();

	//波マップ
	for (int i = 0; i<2; i++)
	{
		SafeRelease(m_pWaveMapTexture[i]);
		SafeRelease(m_pWaveMapSurface[i]);
	}

	//法線マップ
	SafeRelease(m_pBumpMapTexture);
	SafeRelease(m_pBumpMapSurface);

	m_RenderTargetIndex = 0;
}

//デバイスがリストアしたときにコールする関数
void WAVE::Restore()
{
	if (m_pEffect)
	{
		m_pEffect->OnResetDevice();

		for (int i = 0; i<2; i++)
		{
			D3DXCreateTexture(m_pd3dDevice,
				(DWORD)Width_,
				(DWORD)Height_,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_G16R16F,
				D3DPOOL_DEFAULT,
				&m_pWaveMapTexture[i]);
			m_pWaveMapTexture[i]->GetSurfaceLevel(0, &m_pWaveMapSurface[i]);
		}

		//波マップを黒で初期化
		LPDIRECT3DSURFACE9 OldSurface = NULL;
		m_pd3dDevice->GetRenderTarget(0, &OldSurface);

		LPDIRECT3DSURFACE9 OldDepthStencilSurface = NULL;
		m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

		//デプスバッファは使用しないので無効にする(注意２)
		m_pd3dDevice->SetDepthStencilSurface(NULL);

		for (int i = 0; i<2; i++)
		{
			m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[i]);
			m_pd3dDevice->Clear(0L,
				NULL,
				D3DCLEAR_TARGET,
				0x0,
				1.0f,
				0L
			);
		}
		m_pd3dDevice->SetRenderTarget(0, OldSurface);
		SafeRelease(OldSurface);

		m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
		SafeRelease(OldDepthStencilSurface);

		D3DXCreateTexture(m_pd3dDevice,
			(DWORD)Width_,
			(DWORD)Height_,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pBumpMapTexture);
		m_pBumpMapTexture->GetSurfaceLevel(0, &m_pBumpMapSurface);
	}
}

HRESULT WAVE::Load()
{
	D3DCAPS9 caps;
	HRESULT hr;

	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 48, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	m_pd3dDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
	{
		//四角いポリゴン作成

		//シェーダーの初期化
		LPD3DXBUFFER pErr = NULL;
		hr = D3DXCreateEffectFromFile(m_pd3dDevice, "Wave.fx", NULL, NULL, 0, NULL, &m_pEffect, &pErr);
		if (FAILED(hr))
			return -2;

		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pTexOffset = m_pEffect->GetParameterByName(NULL, "TexOffset");
		m_pSpringPower = m_pEffect->GetParameterByName(NULL, "SpringPower");
		m_pAddWavePos = m_pEffect->GetParameterByName(NULL, "AddWavePos");
		m_pAddWaveHeight = m_pEffect->GetParameterByName(NULL, "AddWaveHeight");

		m_pEffect->SetTechnique(m_pTechnique);

		D3DXVECTOR2 Size;
		Size.x = 1.0f / Width_;
		Size.y = 1.0f / Height_;
		m_pEffect->SetFloatArray(m_pTexOffset, (float*)&Size, sizeof(D3DXVECTOR2));
	}

	else
	{
		return -3;
	}

	return S_OK;
}

void WAVE::SetSpringPower(float SpringPower)
{
	if (m_pEffect)
	{
		m_pEffect->SetFloat(m_pSpringPower, SpringPower);
	}
}

//波の高さを設定できるようにする
/*
void WAVE::AddWavePos( float X, float Y )
{
if( m_pEffect )
{
D3DXVECTOR2 AddWavePos = D3DXVECTOR2( X, Y );
m_pEffect->SetValue( m_pAddWavePos, &AddWavePos, sizeof( D3DXVECTOR2 ) );
}
}
*/
void WAVE::AddWave(float Pos_X, float Pos_Y, float Height)
{
	if (m_pEffect)
	{
		//波を追加する位置を設定
		D3DXVECTOR2 AddWavePos = D3DXVECTOR2(Pos_X, Pos_Y);
		m_pEffect->SetValue(m_pAddWavePos, &AddWavePos, sizeof(D3DXVECTOR2));

		//追加する波の高さを設定する
		m_pEffect->SetFloat(m_pAddWaveHeight, Height);
	}
}

LPDIRECT3DTEXTURE9 WAVE::Render()
{
	if (m_pEffect)
	{
		D3DVIEWPORT9 OldViewport, NewViewport;

		//ビューポートを波マップのサイズに合わせる
		m_pd3dDevice->GetViewport(&OldViewport);
		CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
		NewViewport.Width = (DWORD)Width_;
		NewViewport.Height = (DWORD)Height_;
		m_pd3dDevice->SetViewport(&NewViewport);

		//現在のレンダーターゲットサーフェイスを取得
		LPDIRECT3DSURFACE9 OldSurface = NULL;
		m_pd3dDevice->GetRenderTarget(0, &OldSurface);

		m_RenderTargetIndex = 1 - m_RenderTargetIndex;

		//レンダーターゲットをセットする
		m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[1 - m_RenderTargetIndex]);

		LPDIRECT3DSURFACE9 OldDepthStencilSurface = NULL;
		m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

		//デプスバッファを使用しないので無効にする(注意２)
		m_pd3dDevice->SetDepthStencilSurface(NULL);

		//波マップをテクスチャーステージ０にセットする
		m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[m_RenderTargetIndex]);

		//波マップの更新
		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//四角形の描画１
	
		m_pEffect->EndPass();

		//更新した波マップを参照し水面を凸凹にしてレンダリングする
		m_pd3dDevice->SetRenderTarget(0, m_pBumpMapSurface);

		m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[1 - m_RenderTargetIndex]);

		m_pEffect->BeginPass(1);

		//四角形の描画２

		m_pEffect->EndPass();
		m_pEffect->End();

		//戻す
		m_pd3dDevice->SetRenderTarget(0, OldSurface);
		SafeRelease(OldSurface);

		m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
		SafeRelease(OldDepthStencilSurface);

		m_pd3dDevice->SetViewport(&OldViewport);
	}

	return m_pBumpMapTexture;
}