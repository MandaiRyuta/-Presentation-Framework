#include "Instancing3D.h"
#include "../../LoadManager/ModelLoder.h"
#include "../../ShaderManager/EffectShaderManager.h"
#include "Camera.h"
/*
	Instancingを導入してからFPSが下がった
*/
void Instancing3D::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	ModelLoder::GetModelData(TREE)->p_mesh->GetVertexBuffer(&buffer_.vertex_buffer);
	ModelLoder::GetModelData(TREE)->p_mesh->GetIndexBuffer(&buffer_.index_buffer);

	device->CreateVertexBuffer(
		sizeof(Entity::MODEL_WORLD1),
		0,
		0,
		D3DPOOL_MANAGED,
		&insbuffer_.pWorld1Buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::MODEL_WORLD2),
		0,
		0,
		D3DPOOL_MANAGED,
		&insbuffer_.pWorld2Buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::MODEL_WORLD3),
		0,
		0,
		D3DPOOL_MANAGED,
		&insbuffer_.pWorld3Buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::MODEL_WORLD4),
		0,
		0,
		D3DPOOL_MANAGED,
		&insbuffer_.pWorld4Buffer,
		0
	);

	world_.pWorld1 = new Entity::MODEL_WORLD1[INSTANCINGMODEL_MAX];
	world_.pWorld2 = new Entity::MODEL_WORLD2[INSTANCINGMODEL_MAX];
	world_.pWorld3 = new Entity::MODEL_WORLD3[INSTANCINGMODEL_MAX];
	world_.pWorld4 = new Entity::MODEL_WORLD4[INSTANCINGMODEL_MAX];

	for (DWORD dw = 0; dw < INSTANCINGMODEL_MAX; dw++)
	{
		D3DXMatrixIdentity(&matrix_.world);
		world_.pWorld1[dw].m11 = matrix_.world._11;
		world_.pWorld1[dw].m12 = matrix_.world._12;
		world_.pWorld1[dw].m13 = matrix_.world._13;
		world_.pWorld1[dw].m14 = matrix_.world._14;

		world_.pWorld2[dw].m21 = matrix_.world._21;
		world_.pWorld2[dw].m22 = matrix_.world._22;
		world_.pWorld2[dw].m23 = matrix_.world._23;
		world_.pWorld2[dw].m24 = matrix_.world._24;

		world_.pWorld3[dw].m31 = matrix_.world._31;
		world_.pWorld3[dw].m32 = matrix_.world._32;
		world_.pWorld3[dw].m33 = matrix_.world._33;
		world_.pWorld3[dw].m34 = matrix_.world._34;

		world_.pWorld4[dw].m41 = matrix_.world._41;
		world_.pWorld4[dw].m42 = matrix_.world._42;
		world_.pWorld4[dw].m43 = matrix_.world._43;
		world_.pWorld4[dw].m44 = matrix_.world._44;
	}

	D3DVERTEXELEMENT9 declelement[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// Local coord
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	// 法線
		//以下行列データ
		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	// ワールド行列1
		{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	// ワールド行列2
		{ 3, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	// ワールド行列3
		{ 4, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	// ワールド行列4

		D3DDECL_END()
	};

	device->CreateVertexDeclaration(declelement, &insbuffer_.pDecl);

	/*後でメッシュフィールドの高さを適応させる*/
	position_ = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	scale_ = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixTranslation(&matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, rotation_.y, rotation_.x, rotation_.z);
	D3DXMatrixScaling(&matrix_.scale, scale_.x, scale_.y, scale_.z);
}

void Instancing3D::Update()
{
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

void Instancing3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (UINT)INSTANCINGMODEL_MAX); //ここだけ板ポリゴンの枚数
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)1);
	pDevice->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)1);
	pDevice->SetStreamSourceFreq(4, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)1);

	pDevice->SetVertexDeclaration(insbuffer_.pDecl);

	pDevice->SetStreamSource(0, buffer_.vertex_buffer, 0, ModelLoder::GetModelData(TREE)->p_mesh->GetNumBytesPerVertex());
	pDevice->SetStreamSource(1, insbuffer_.pWorld1Buffer, 0, sizeof(Entity::MODEL_WORLD1));
	pDevice->SetStreamSource(2, insbuffer_.pWorld2Buffer, 0, sizeof(Entity::MODEL_WORLD2));
	pDevice->SetStreamSource(3, insbuffer_.pWorld3Buffer, 0, sizeof(Entity::MODEL_WORLD3));
	pDevice->SetStreamSource(4, insbuffer_.pWorld4Buffer, 0, sizeof(Entity::MODEL_WORLD4));
	pDevice->SetIndices(buffer_.index_buffer);

	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	pDevice->SetRenderState(D3DRS_CLIPPING, TRUE);
	//ライトON
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

	////αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 64);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//*シェーダーの関数名*/
	EffectShaderManager::GetEffect(INSTANCING3D)->SetTechnique("tecMinimum");
	D3DXMATRIX mtxall[INSTANCINGMODEL_MAX] = {};
	//D3DXMATRIX mtxall = 　/*ワールド * ビュー * プロジェクション*/
	EffectShaderManager::GetEffect(INSTANCING3D)->Begin(NULL, 0);
	EffectShaderManager::GetEffect(INSTANCING3D)->BeginPass(0);
	for (int a = 0; a < INSTANCINGMODEL_MAX; a++)
	{	
		mtxall[a] = matrix_.world * CCamera::GetView() * CCamera::GetProj();
		D3DXVECTOR4 color = { ModelLoder::GetModelData(TREE)->color.r,ModelLoder::GetModelData(TREE)->color.g,ModelLoder::GetModelData(TREE)->color.b,ModelLoder::GetModelData(TREE)->color.a };
		EffectShaderManager::GetEffect(INSTANCING3D)->SetMatrix("mWVP", (D3DXMATRIX*)&mtxall[a]);
		EffectShaderManager::GetEffect(INSTANCING3D)->SetVector("mColor", &color);
		for (DWORD i = 0; i < ModelLoder::GetModelData(TREE)->dw_material; i++)
		{
			//pDevice->SetTexture(0, this->model_->p_meshtexture_[i]);
			EffectShaderManager::GetEffect(INSTANCING3D)->SetTexture("texDecal", ModelLoder::GetModelData(TREE)->p_meshtexture[i]);
			ModelLoder::GetModelData(TREE)->p_mesh->DrawSubset(i);
			//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,mesh[a]->GetNumVertices(), 0, mesh[a]->GetNumFaces());
		}
	}
	EffectShaderManager::GetEffect(INSTANCING3D)->EndPass();
	EffectShaderManager::GetEffect(INSTANCING3D)->End();
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	pDevice->SetStreamSourceFreq(3, 1);
	pDevice->SetStreamSourceFreq(4, 1);
	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
}

void Instancing3D::Uninit()
{
	delete world_.pWorld1;
	delete world_.pWorld2;
	delete world_.pWorld3;
	delete world_.pWorld4;

	if (ModelLoder::GetModelData(TREE)->p_mesh != nullptr)
	{
		ModelLoder::GetModelData(TREE)->p_mesh->Release();
		ModelLoder::GetModelData(TREE)->p_mesh = nullptr;
	}
	if (ModelLoder::GetModelData(TREE)->p_meshmaterial != nullptr)
	{
		delete[] ModelLoder::GetModelData(TREE)->p_meshmaterial;
	}
	if (ModelLoder::GetModelData(TREE)->p_meshtexture != nullptr)
	{
		delete[] ModelLoder::GetModelData(TREE)->p_meshtexture;
	}
	if (insbuffer_.pDecl != nullptr)
	{
		insbuffer_.pDecl->Release();
		insbuffer_.pDecl = nullptr;
	}
	if (insbuffer_.pWorld1Buffer != nullptr)
	{
		insbuffer_.pWorld1Buffer->Release();
		insbuffer_.pWorld1Buffer = nullptr;
	}
	if (insbuffer_.pWorld2Buffer != nullptr)
	{
		insbuffer_.pWorld2Buffer->Release();
		insbuffer_.pWorld2Buffer = nullptr;
	}
	if (insbuffer_.pWorld3Buffer != nullptr)
	{
		insbuffer_.pWorld3Buffer->Release();
		insbuffer_.pWorld3Buffer = nullptr;
	}
	if (insbuffer_.pWorld4Buffer != nullptr)
	{
		insbuffer_.pWorld4Buffer->Release();
		insbuffer_.pWorld4Buffer = nullptr;
	}

	if (buffer_.index_buffer != nullptr)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = nullptr;
	}

	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
	}
}

Instancing3D * Instancing3D::Create()
{
	Instancing3D* Instancing = new Instancing3D();
	Instancing->Init();
	return Instancing;
}
