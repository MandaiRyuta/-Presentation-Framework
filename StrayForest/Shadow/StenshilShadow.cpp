#include "StenshilShadow.h"
#include "../LoadManager/ModelLoder.h"
#include "../ShaderManager/EffectShaderManager.h"
#include "../System/InheritanceNode/Camera.h"
#include "../../StrayForest/System/InheritanceNode/Player/Player.h"
#include "../../StrayForest/System/InheritanceNode/BossMonster/BossMonster.h"

void StenshilShadow::Init()
{
	//ModelLoder::GetModelData(SHADOW)->position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//ModelLoder::GetModelData(SHADOW)->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//ModelLoder::GetModelData(SHADOW)->scall = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);

	D3DXMatrixTranslation(&matrix_.position, 0.0f, 5.0f, 80.0f);

	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, 0.0f, 0.0f, 0.0f);
}

void StenshilShadow::Update()
{
	if (type_ == 0)
	{
		D3DXMatrixScaling(&matrix_.scale, 10.0f, 60.0f, 10.0f);
		D3DXMatrixTranslation(&matrix_.position, Player::GetPlayerPosMatrix()._41, 5.0f, Player::GetPlayerPosMatrix()._43);
	}
	else if (type_ == 1)
	{
		D3DXMatrixScaling(&matrix_.scale, 30.0f, 60.0f, 30.0f);
		D3DXMatrixTranslation(&matrix_.position, BossMonster::GetPosition().x, BossMonster::GetPosition().y, BossMonster::GetPosition().z);
	}
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
	matrix_.world = matrix_.world * CCamera::GetView() * CCamera::GetProj();
}

void StenshilShadow::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	/*ステンシルシャドウ実装の為追加*/
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);					//ステンシル有効
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					//カラー無効

	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		//+1の計算をする
	device->SetRenderState(D3DRS_STENCILREF, 1);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングの設定　モデルの表面だけ描画

	EffectShaderManager::GetEffect(STENSHILSHADOW)->SetTechnique("tecMinimum");
	EffectShaderManager::GetEffect(STENSHILSHADOW)->SetMatrix("mWVP", &matrix_.world);
	EffectShaderManager::GetEffect(STENSHILSHADOW)->Begin(NULL, 0);
	EffectShaderManager::GetEffect(STENSHILSHADOW)->BeginPass(0);
	
	for (DWORD i = 0; i < ModelLoder::GetModelData(SHADOW)->dw_material; i++)
	{
		EffectShaderManager::GetEffect(STENSHILSHADOW)->SetTexture("texDecal",ModelLoder::GetModelData(SHADOW)->p_meshtexture[i]);
		ModelLoder::GetModelData(SHADOW)->p_mesh->DrawSubset(i);
	};
	
	EffectShaderManager::GetEffect(STENSHILSHADOW)->EndPass();
	EffectShaderManager::GetEffect(STENSHILSHADOW)->End();

	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR); 		//-1
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);					//裏面描画 クロックワーク（時計回り）　CCW（カウンタークロックワーク）（反時計回り）

	EffectShaderManager::GetEffect(STENSHILSHADOW)->SetTechnique("tecMinimum");
	EffectShaderManager::GetEffect(STENSHILSHADOW)->SetMatrix("mWVP", &matrix_.world);
	EffectShaderManager::GetEffect(STENSHILSHADOW)->Begin(NULL, 0);
	EffectShaderManager::GetEffect(STENSHILSHADOW)->BeginPass(0);
	
	for (DWORD i = 0; i < ModelLoder::GetModelData(SHADOW)->dw_material; i++)
	{
		EffectShaderManager::GetEffect(STENSHILSHADOW)->SetTexture("texDecal", ModelLoder::GetModelData(SHADOW)->p_meshtexture[i]);
		ModelLoder::GetModelData(SHADOW)->p_mesh->DrawSubset(i);
	};

	EffectShaderManager::GetEffect(STENSHILSHADOW)->EndPass();
	EffectShaderManager::GetEffect(STENSHILSHADOW)->End();

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				//色情報有効
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);				//ステンシル値 == 1の時
}

void StenshilShadow::Uninit()
{
	if (type_ == 1)
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
}

StenshilShadow * StenshilShadow::Create(int _type)
{
	StenshilShadow* create_stenshilshadow = new StenshilShadow(_type);
	create_stenshilshadow->Init();

	return create_stenshilshadow;
}
