#include "Renderer.h"
//�o�b�N�o�b�t�@�̐ݒ�p
D3DPRESENT_PARAMETERS d3dpp_ = CDX9Parameter::getInstance();
//DirectX9 �f�o�C�X
LPDIRECT3DDEVICE9 device_ = CDX9Device::getInstance();

bool CDX9Renderer::Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	DX9Init(hWnd, bWindow, nWindowWidth, nWindowHeight);
	//camera_ = new CCamera({ 0.0f,0.0f,0.0f }, { 0.0f, 5.0f,-20.0f }, { 0.0f,1.0f,0.0f });
	//light_ = new CLight()
	return true;
}

void CDX9Renderer::Uninit()
{
	if (pD3D_ != NULL)
	{
		pD3D_->Release();
		pD3D_ = NULL;
	}
	if (device_ != NULL)
	{
		device_->Release();
		device_ = NULL;
	}
}

bool CDX9Renderer::DX9Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight)
{
	pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D_ == NULL)
	{
		MessageBox(hWnd, "Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂����B", NULL, MB_OK);
		return false;
	}

	D3DDISPLAYMODE d3ddm;

	if (FAILED(pD3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(hWnd, "�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂����B", NULL, MB_OK);
		return false;
	}


	ZeroMemory(&d3dpp_, sizeof(d3dpp_));							//�@���̂��̂�S�Ă�����������(����������擪�A�h���X, ����������T�C�Y)
	d3dpp_.BackBufferWidth = nWindowWidth;				//�@�����(�o�b�N�o�b�t�@)�̕�
	d3dpp_.BackBufferHeight = nWindowHeight;				//	�����(�o�b�N�o�b�t�@)�̍���
	d3dpp_.BackBufferFormat = d3ddm.Format;				//	�F��
	d3dpp_.BackBufferCount = 1;							//	�o�b�N�o�b�t�@�̐�
	d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;		//	�f���M���̓���(DISCARD�͐����������C�ɂ���)
	d3dpp_.EnableAutoDepthStencil = TRUE;						//	TRUE�ŗǂ�
	d3dpp_.AutoDepthStencilFormat = D3DFMT_D24S8;					//	���͂���ŗǂ���̃t�H�[�}�b�g ���X�e���V���V���h�E�̎����̂��߂ɐݒ�
	d3dpp_.Windowed = bWindow;						//	TRUE�ŃE�B���h�E���[�h,FALSE�Ńt���X�N���[�����[�h
	d3dpp_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//	�t���X�N���[�����[�h�̎��̃��t���b�V�����[�g��Hz����ύX
	d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//	���j�^�[��Hz���ɍ��킹�ĕ`�悳���(IMMEDIATE���Ɛ���������҂����ɕ`�悷��)

	if (FAILED(pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp_,
		&device_
	)))
	{
		MessageBox(hWnd, "Direct3DDevice�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// Setup ImGui binding
	ImGui_ImplDX9_Init(hWnd, device_);
	return true;
}

D3DPRESENT_PARAMETERS GetParameter()
{
	return d3dpp_;
}

LPDIRECT3DDEVICE9 GetDevice()
{
	return device_;
}
