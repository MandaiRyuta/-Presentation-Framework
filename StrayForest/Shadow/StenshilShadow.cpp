#include "StenshilShadow.h"
#include "../LoadManager/ModelLoder.h"
#include "../ShaderManager/EffectShaderManager.h"

void StenshilShadow::Init()
{
	//ModelLoder::GetModelData(SHADOW)->position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//ModelLoder::GetModelData(SHADOW)->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//ModelLoder::GetModelData(SHADOW)->scall = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
}

void StenshilShadow::Update()
{
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

void StenshilShadow::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	//device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR); 		//-1
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);					//裏面描画 クロックワーク（時計回り）　CCW（カウンタークロックワーク）（反時計回り）
	//
	//EffectShaderManager::GetEffect(MODEL3D)->SetTechnique("tecMinimum");
	//EffectShaderManager::GetEffect(MODEL3D)->SetMatrix("mWVP", &matrix_.world);
	//EffectShaderManager::GetEffect(MODEL3D)->Begin(NULL, 0);
	//EffectShaderManager::GetEffect(MODEL3D)->BeginPass(0);
	//
	//for (DWORD i = 0; i < ModelLoder::GetModelData(SHADOW)->dw_material; i++)
	//{
	//	EffectShaderManager::GetEffect(MODEL3D)->SetTexture("texDecal",ModelLoder::GetModelData(SHADOW)->p_meshtexture[i]);
	//	ModelLoder::GetModelData(SHADOW)->p_mesh->DrawSubset(i);
	//};
	//
	//EffectShaderManager::GetEffect(MODEL3D)->EndPass();
	//EffectShaderManager::GetEffect(MODEL3D)->End();

	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				//色情報有効
	//device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);				//ステンシル値 == 1の時
	
	//EffectShaderManager::GetEffect(MODEL3D)->SetTechnique("tecMinimum");
	//EffectShaderManager::GetEffect(MODEL3D)->SetMatrix("mWVP", &matrix_.world);
	//EffectShaderManager::GetEffect(MODEL3D)->Begin(NULL, 0);
	//EffectShaderManager::GetEffect(MODEL3D)->BeginPass(0);
	//
	//for (DWORD i = 0; i < ModelLoder::GetModelData(SHADOW)->dw_material; i++)
	//{
	//	EffectShaderManager::GetEffect(MODEL3D)->SetTexture("texDecal", ModelLoder::GetModelData(SHADOW)->p_meshtexture[i]);
	//	ModelLoder::GetModelData(SHADOW)->p_mesh->DrawSubset(i);
	//};
	//
	//EffectShaderManager::GetEffect(MODEL3D)->EndPass();
	//EffectShaderManager::GetEffect(MODEL3D)->End();
}

void StenshilShadow::Uninit()
{
	if (ModelLoder::GetModelData(SHADOW)->p_mesh != nullptr)
	{
		ModelLoder::GetModelData(SHADOW)->p_mesh->Release();
		ModelLoder::GetModelData(SHADOW)->p_mesh = nullptr;
	}
	if (ModelLoder::GetModelData(SHADOW)->p_meshmaterial != nullptr)
	{
		delete[] ModelLoder::GetModelData(SHADOW)->p_meshmaterial;
	}
	if (ModelLoder::GetModelData(SHADOW)->p_meshtexture != nullptr)
	{
		delete[] ModelLoder::GetModelData(SHADOW)->p_meshtexture;
	}
}

StenshilShadow * StenshilShadow::Create()
{
	StenshilShadow* create_stenshilshadow = new StenshilShadow();
	create_stenshilshadow->Init();

	return create_stenshilshadow;
}
