#include "Guardian.h"
#include "GuardianManager.h"
#include "../../../LoadManager/ModelLoder.h"
#include "../../../ShaderManager/EffectShaderManager.h"
#include "../Camera.h"
#include "../../../System/InheritanceNode/Player/Player.h"

void Guardian::Init()
{
	for (int i = 0; i < 10; i++)
	{
		D3DXMatrixIdentity(&matrix_[i].position);
		D3DXMatrixIdentity(&matrix_[i].scale);
		D3DXMatrixIdentity(&matrix_[i].rotation);
	}

	vecRot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void Guardian::Update()
{
	//プレイヤーの位置情報、回転情報のmtx
	//玉の位置を計算する　プレイヤーのローカル座標
	//マトリックスで、玉の座標を変換する。
	D3DXMATRIX RotVec;
	D3DXMatrixTranslation(&RotVec, Player::GetPlayerMatrix()._43 + 10.0f, Player::GetPlayerMatrix()._42 + 15.0f, Player::GetPlayerMatrix()._41 + 10.0f);

	D3DXMatrixTranslation(&matrix_[0].position, Player::GetPlayerMatrix()._41, Player::GetPlayerMatrix()._42 + 15.0f, Player::GetPlayerMatrix()._43);
	float x = RotVec._41 - matrix_[0].position._41;
	float y = RotVec._42 - matrix_[0].position._42;
	float z = RotVec._43 - matrix_[0].position._43;
	float fx = x * cosf(FrameCount_) - z * sinf(FrameCount_) + matrix_[0].position._41;
	float fy = x * cosf(FrameCount_) - y * sinf(FrameCount_) + matrix_[0].position._42;
	float fz = x * sinf(FrameCount_) + z * cosf(FrameCount_) + matrix_[0].position._43;
	D3DXMatrixTranslation(&matrix_[0].position, fx, fy, fz);
	D3DXMatrixScaling(&matrix_[0].scale, 2.0f, 2.0f, 2.0f);
	D3DXMatrixRotationYawPitchRoll(&matrix_[0].rotation, fx, fy, fz);

	matrix_[0].world = matrix_[0].scale * matrix_[0].rotation * matrix_[0].position;
	FrameCount_ -= 0.1f;
}

void Guardian::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();


		D3DXMATRIX mWVP = matrix_[0].world * CCamera::GetView() * CCamera::GetProj();
		// レンダリング

		device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
		device->SetRenderState(D3DRS_ZENABLE, true);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		EffectShaderManager::GetEffect(GUARDIAN)->SetTechnique("tecMinimum");
		EffectShaderManager::GetEffect(GUARDIAN)->SetMatrix("mWVP", &mWVP);
		EffectShaderManager::GetEffect(GUARDIAN)->Begin(NULL, 0);
		EffectShaderManager::GetEffect(GUARDIAN)->BeginPass(0);

		for (DWORD i = 0; i < ModelLoder::GetModelData(LOADMODEL::TESTMODEL)->dw_material; i++)
		{
			EffectShaderManager::GetEffect(GUARDIAN)->SetTexture("texDecal", ModelLoder::GetModelData(LOADMODEL::TESTMODEL)->p_meshtexture[i]);
			ModelLoder::GetModelData(LOADMODEL::TESTMODEL)->p_mesh->DrawSubset(i);
		}

		EffectShaderManager::GetEffect(GUARDIAN)->EndPass();
		EffectShaderManager::GetEffect(GUARDIAN)->End();
		device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
}

void Guardian::Uninit()
{
	if (ModelLoder::GetModelData(TESTMODEL)->p_mesh != nullptr)
	{
		ModelLoder::GetModelData(TESTMODEL)->p_mesh->Release();
		ModelLoder::GetModelData(TESTMODEL)->p_mesh = nullptr;
	}
	if (ModelLoder::GetModelData(TESTMODEL)->p_meshmaterial != nullptr)
	{
		delete[] ModelLoder::GetModelData(TESTMODEL)->p_meshmaterial;
	}
	if (ModelLoder::GetModelData(TESTMODEL)->p_meshtexture != nullptr)
	{
		delete[] ModelLoder::GetModelData(TESTMODEL)->p_meshtexture;
	}
}

Guardian * Guardian::Create()
{
	Guardian* ret = new Guardian();
	ret->Init();
	return ret;
}
