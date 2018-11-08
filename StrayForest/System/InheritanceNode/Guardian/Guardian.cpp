#include "Guardian.h"
#include "GuardianMove\GuardianManager.h"
#include "GuardianMove\Guardian01.h"
#include "GuardianMove\Guardian02.h"
#include "GuardianMove\Guardian03.h"
#include "GuardianMove\Guardian04.h"
#include "GuardianMove\Guardian05.h"
#include "GuardianMove\Guardian06.h"
#include "GuardianMove\Guardian07.h"
#include "GuardianMove\Guardian08.h"
#include "GuardianMove\Guardian09.h"
#include "GuardianMove\Guardian10.h"
#include "../../../LoadManager/ModelLoder.h"
#include "../../../ShaderManager/EffectShaderManager.h"
#include "../Camera.h"
#include "../../../System/InheritanceNode/Player/Player.h"

void Guardian::Init()
{
	animtime_ = 0;

	for (int i = 0; i < 8; i++)
	{
		D3DXMatrixIdentity(&matrix_[i].position);
		D3DXMatrixIdentity(&matrix_[i].scale);
		D3DXMatrixIdentity(&matrix_[i].rotation);
	}

	guardians_[0] = new Guardian01;
	guardians_[1] = new Guardian02;
	guardians_[2] = new Guardian03;
	guardians_[3] = new Guardian04;
	guardians_[4] = new Guardian05;
	guardians_[5] = new Guardian06;
	guardians_[6] = new Guardian07;
	guardians_[7] = new Guardian08;
	guardians_[8] = new Guardian09;
	guardians_[9] = new Guardian10;
	vecRot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void Guardian::Update()
{
	//static float t = 0.0f;
	
	for (int i = 0; i < 10; i++)
	{
		guardians_[i]->Update(matrix_[i]);
		//D3DXMatrixTranslation(&matrix_[i].position, Player::GetPlayerMatrix()._41, Player::GetPlayerMatrix()._42 + 10.0f, Player::GetPlayerMatrix()._43);
		//float x = RotVec._41 - matrix_[i].position._41;
		//float z = RotVec._43 - matrix_[i].position._43;
		//float fx = x * cosf(t) - z * sinf(t) + matrix_[i].position._41;
		//float fz = x * sinf(t) + z * cosf(t) + matrix_[i].position._43;
		//D3DXMatrixTranslation(&matrix_[i].position, fx, Player::GetPlayerMatrix()._42 + 10.0f, fz);
		//D3DXMatrixScaling(&matrix_[i].scale, 2.0f, 2.0f, 2.0f);
		//D3DXMatrixRotationYawPitchRoll(&matrix_[i].rotation, 0.0f, 0.0f, 0.0f);

		//matrix_[i].world = matrix_[i].scale * matrix_[i].rotation * matrix_[i].position;
	}
	//t += 0.1f;
}

void Guardian::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();


	for (int p = 0; p < 8; p++)
	{
		D3DXMATRIX mWVP = matrix_[p].world * CCamera::GetView() * CCamera::GetProj();
		// ƒŒƒ“ƒ_ƒŠƒ“ƒO

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
}

void Guardian::Uninit()
{
	for (int i = 0; i < 10; i++)
	{
		delete guardians_[i];
	}
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
	Guardian* create_guardian = new Guardian;
	create_guardian->Init();

	return create_guardian;
}
