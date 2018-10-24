#include "testwave.h"

//SafeRelease�͊֐��ł͂Ȃ��}�N��
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

//�f�o�C�X�����X�g�����Ƃ��ɃR�[������֐�
void WAVE::Invalidate()
{
	if (m_pEffect)
		m_pEffect->OnLostDevice();

	//�g�}�b�v
	for (int i = 0; i<2; i++)
	{
		SafeRelease(m_pWaveMapTexture[i]);
		SafeRelease(m_pWaveMapSurface[i]);
	}

	//�@���}�b�v
	SafeRelease(m_pBumpMapTexture);
	SafeRelease(m_pBumpMapSurface);

	m_RenderTargetIndex = 0;
}

//�f�o�C�X�����X�g�A�����Ƃ��ɃR�[������֐�
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

		//�g�}�b�v�����ŏ�����
		LPDIRECT3DSURFACE9 OldSurface = NULL;
		m_pd3dDevice->GetRenderTarget(0, &OldSurface);

		LPDIRECT3DSURFACE9 OldDepthStencilSurface = NULL;
		m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

		//�f�v�X�o�b�t�@�͎g�p���Ȃ��̂Ŗ����ɂ���(���ӂQ)
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
		//�l�p���|���S���쐬

		//�V�F�[�_�[�̏�����
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

//�g�̍�����ݒ�ł���悤�ɂ���
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
		//�g��ǉ�����ʒu��ݒ�
		D3DXVECTOR2 AddWavePos = D3DXVECTOR2(Pos_X, Pos_Y);
		m_pEffect->SetValue(m_pAddWavePos, &AddWavePos, sizeof(D3DXVECTOR2));

		//�ǉ�����g�̍�����ݒ肷��
		m_pEffect->SetFloat(m_pAddWaveHeight, Height);
	}
}

LPDIRECT3DTEXTURE9 WAVE::Render()
{
	if (m_pEffect)
	{
		D3DVIEWPORT9 OldViewport, NewViewport;

		//�r���[�|�[�g��g�}�b�v�̃T�C�Y�ɍ��킹��
		m_pd3dDevice->GetViewport(&OldViewport);
		CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
		NewViewport.Width = (DWORD)Width_;
		NewViewport.Height = (DWORD)Height_;
		m_pd3dDevice->SetViewport(&NewViewport);

		//���݂̃����_�[�^�[�Q�b�g�T�[�t�F�C�X���擾
		LPDIRECT3DSURFACE9 OldSurface = NULL;
		m_pd3dDevice->GetRenderTarget(0, &OldSurface);

		m_RenderTargetIndex = 1 - m_RenderTargetIndex;

		//�����_�[�^�[�Q�b�g���Z�b�g����
		m_pd3dDevice->SetRenderTarget(0, m_pWaveMapSurface[1 - m_RenderTargetIndex]);

		LPDIRECT3DSURFACE9 OldDepthStencilSurface = NULL;
		m_pd3dDevice->GetDepthStencilSurface(&OldDepthStencilSurface);

		//�f�v�X�o�b�t�@���g�p���Ȃ��̂Ŗ����ɂ���(���ӂQ)
		m_pd3dDevice->SetDepthStencilSurface(NULL);

		//�g�}�b�v���e�N�X�`���[�X�e�[�W�O�ɃZ�b�g����
		m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[m_RenderTargetIndex]);

		//�g�}�b�v�̍X�V
		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//�l�p�`�̕`��P
	
		m_pEffect->EndPass();

		//�X�V�����g�}�b�v���Q�Ƃ����ʂ�ʉ��ɂ��ă����_�����O����
		m_pd3dDevice->SetRenderTarget(0, m_pBumpMapSurface);

		m_pd3dDevice->SetTexture(0, m_pWaveMapTexture[1 - m_RenderTargetIndex]);

		m_pEffect->BeginPass(1);

		//�l�p�`�̕`��Q

		m_pEffect->EndPass();
		m_pEffect->End();

		//�߂�
		m_pd3dDevice->SetRenderTarget(0, OldSurface);
		SafeRelease(OldSurface);

		m_pd3dDevice->SetDepthStencilSurface(OldDepthStencilSurface);
		SafeRelease(OldDepthStencilSurface);

		m_pd3dDevice->SetViewport(&OldViewport);
	}

	return m_pBumpMapTexture;
}