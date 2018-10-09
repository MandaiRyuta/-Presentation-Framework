//****************************************************
// @file : meshfiled.h
// @brief: メッシュフィールドの作成
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include
//****************************************************
#include "meshfiled.h"
#include "../../Renderer/Renderer.h"
#include "../../LoadManager/CsvLoder.h"
#include "../../LoadManager/TextureLoder.h"
#include "../../ShaderManager/EffectShaderManager.h"
#include "Camera.h"
//****************************************************
// 初期化
//****************************************************
void MeshFiled::Init()
{
	/// <summary>
	/// デバイスを受け取る
	/// </summary>
	LPDIRECT3DDEVICE9 device = GetDevice();

	VertexBufferCreate(device);
	IndexBufferCreate(device);

	/// <summary>
	/// マテリアルの初期化を行った後に設定を行う
	/// </summary>
	ZeroMemory(&meshmaterial_, sizeof(meshmaterial_));

	//****************************************************
	// @ Diffuse : 拡散光の設定
	// @ Ambient : 環境光の設定
	// @ Specular: 反射光の設定
	//****************************************************
	meshmaterial_.Diffuse = { 0.8f, 0.7f, 0.8f, 1.0f };
	meshmaterial_.Ambient = { 0.7f, 0.7f, 0.7f, 1.0f };

	/// <summary>
	/// ワールド行列を単位行列にする
	/// </summary>
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixTranslation(&matrix_.position, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&matrix_.scale, 1.1f, 1.0f, 1.1f);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, 0.0f, 0.0f, 0.0f);
}

//****************************************************
// 更新
//****************************************************
void MeshFiled::Update()
{
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

//****************************************************
// 描画 ※Shader通すので一時作業停止
//****************************************************
void MeshFiled::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->SetFVF(FVF_FILED);
	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR3D));
	device->SetIndices(buffer_.index_buffer);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

	device->SetMaterial(&meshmaterial_);
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	device->SetTransform(D3DTS_WORLD, &matrix_.world);

	device->SetTexture(0, TextureLoder::GetTextureData(FLOOR01));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);

	device->SetTexture(0, TextureLoder::GetTextureData(FLOOR02));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);

	/*なぜかエラー吐かれる*/
	//LPDIRECT3DDEVICE9 device = GetDevice();
	//D3DXVECTOR4 v;
	//D3DXMATRIX mWVP = matrix_.world * CCamera::GetView() * CCamera::GetProj();
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTechnique("TShader");
	//EffectShaderManager::GetEffect(BUMPMAP)->Begin(NULL, 0);
	//EffectShaderManager::GetEffect(BUMPMAP)->BeginPass(0);
	//EffectShaderManager::GetEffect(BUMPMAP)->SetMatrix("mWVP", &mWVP);
	//D3DXVECTOR4 LightPos = D3DXVECTOR4(Light::GetLightPos().x, Light::GetLightPos().y, Light::GetLightPos().z, 0);
	//D3DXMatrixInverse(&mWVP, NULL, &matrix_.world);
	//D3DXVec4Transform(&v, &LightPos, &mWVP);
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//v.w = -0.7f;
	//EffectShaderManager::GetEffect(BUMPMAP)->SetVector("vLightDir", &v);
	//D3DXMATRIX viewworld = matrix_.world * CCamera::GetView();
	//D3DXMatrixInverse(&viewworld, NULL, &viewworld);
	//v = D3DXVECTOR4(0, 0, 0, 1);
	//D3DXVec4Transform(&v, &v, &viewworld);
	//EffectShaderManager::GetEffect(BUMPMAP)->SetVector("vEyePos", &v);
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("NormalMap", TextureLoder::GetTextureData(FLOOR01NORMAL));
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("DecaleTex", TextureLoder::GetTextureData(FLOOR01));
	//device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("NormalMap", TextureLoder::GetTextureData(FLOOR02NORMAL));
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("DecaleTex", TextureLoder::GetTextureData(FLOOR02));
	//
	//device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);
	//EffectShaderManager::GetEffect(BUMPMAP)->EndPass();
	//EffectShaderManager::GetEffect(BUMPMAP)->End();
}

//****************************************************
// 開放
//****************************************************
void MeshFiled::Uninit()
{
	/// <summary>
	/// バーテックスバッファの解放処理
	/// </summary>
	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
	}
	/// <summary>
	/// インデックスバッファの解放処理
	/// </summary>
	if (buffer_.index_buffer != nullptr)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = nullptr;
	}
}

//****************************************************
// 生成関数
//****************************************************
MeshFiled * MeshFiled::Create(Entity::MeshFiledSize _meshinfo)
{
	MeshFiled* pMeshfiled = new MeshFiled(_meshinfo);
	pMeshfiled->Init();
	return pMeshfiled;
}

//****************************************************
// バーテックスバッファの生成
//****************************************************
void MeshFiled::VertexBufferCreate(LPDIRECT3DDEVICE9 _device)
{
	/// <summary>
	/// Vectorの二次元配列
	/// </summary>
	std::vector<std::vector<std::string>> filedtable;

	/// <summary>
	/// Csv読み込み
	/// </summary>
	CsvLoder::CsvRead("Resource/CSVFile/meshfiled.csv", filedtable);
	
	/// <summary>
	/// 頂点の開始地点
	/// </summary>
	float fStartX = -meshinfo_.size_x * (meshinfo_.filed_x / 2);
	float fStartZ = meshinfo_.size_x * (meshinfo_.filed_z / 2);

	/// <summary>
	/// Xの個数とZの個数
	/// </summary>
	int nCx = meshinfo_.filed_x + 1;
	int nCz = meshinfo_.filed_z + 1;

	/// <summary>
	/// バーテックス＆インデックス＆プリミティブ数の計算
	/// </summary>
	number_of_vertices_ = nCx * nCz;
	number_of_indices_ = (nCx * 2 + 1) * (nCz - 2) + (nCx - 2);
	number_of_primities_ = this->number_of_indices_ - 2;

	/// <summary>
	/// バッファ―の生成
	/// </summary>
	if (FAILED(_device->CreateVertexBuffer(
		sizeof(Entity::VECTOR3D) * number_of_vertices_,
		D3DUSAGE_WRITEONLY,
		FVF_FILED,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		NULL)))
	{
		MessageBox(NULL, "VertexBufferの生成に失敗しました。", "MeshFiled", MB_OK);
		PostQuitMessage(0);
	}

	/// <summary>
	/// vertexbufferをロックして書き込み、そしてアンロックする
	/// </summary>
	buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv_, D3DLOCK_DISCARD);

	/// <summary>
	/// 外積計算するために必要な変数
	/// </summary>
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 normal;

	/// <summary>
	/// csvファイルの最後の情報で止まるようにする。
	/// </summary>
	char *end[1] = { "\n" };

	/// <summary>
	/// フィールドの高さをcsvから取得し、X座標とZ座標が求められているメッシュフィールドの情報格納変数へ代入する
	/// </summary>
	for (int nZ = 0; nZ < nCz - 1; nZ++)
	{
		for (int nX = 0; nX < nCx - 1; nX++)
		{
			FiledHeight[nZ][nX] = strtof(filedtable[nZ][nX].c_str(), &end[0]);
		}
	}
	
	/*
		@nCount : メッシュフィールドの頂点の数を数える変数
	*/
	for (int z = 0, nCount = 0; z < nCz; z++)
	{
		for (int x = 0; x < nCx; x++)
		{
			/// <summary>
			/// 3個分の座標を取得
			/// </summary>
			mpv_[nCount].position = D3DXVECTOR3(fStartX + (meshinfo_.size_x * x), FiledHeight[z][x], fStartZ - (meshinfo_.size_z * z));

			nCount++;
		}
	}

	for (int nZ = 0, nCount = 0; nZ < nCz; nZ++)
	{
		for (int nX = 0; nX < nCx; nX++)
		{
			/// <summary>
			/// 外積に必要なベクトルの計算
			/// </summary>
			vx = mpv_[(nZ * nCz) + (nX + 2)].position - mpv_[nZ * nCz + nX].position;
			vz = mpv_[(nZ * nCz) + (nX + 1)].position - mpv_[nZ * nCx + nX].position;
			/// <summary>
			/// 外積の計算
			/// </summary>
			//****************************************************
			// normal.x = vx.y * vz.z - vx.z * vz.y
			// normal.y = vx.z * vz.x - vx.x * vz.z
			// normal.z = vx.x * vz.y - vx.y * vz.x
			//****************************************************
			D3DXVec3Cross(&normal, &vx, &vz);
			/// <summary>
			/// ベクトルの正規化
			/// </summary>
			D3DXVec3Normalize(&normal, &normal);
			/// <summary>
			/// メッシュ配置情報の法線へ外積して求めた法線を代入
			/// </summary>
			mpv_[(nZ * nCx) + nX].normal = normal;

			/// <summary>
			/// カラー情報
			/// </summary>
			mpv_[nCount].color = D3DCOLOR_RGBA(255, 255, 255, 255);

			/// <summary>
			/// テクスチャuv値
			/// </summary>
			mpv_[nCount].texcoord = D3DXVECTOR2((meshinfo_.size_x * nX) / (meshinfo_.size_x * nCx), (meshinfo_.size_z * nZ) / (meshinfo_.size_z * nCz));

			/// <summary>
			/// メッシュ配置カウンターに１追加
			/// </summary>
			nCount++;
		}
	}

	buffer_.vertex_buffer->Unlock();
}

//****************************************************
// インデックスバッファの生成
//****************************************************
void MeshFiled::IndexBufferCreate(LPDIRECT3DDEVICE9 _device)
{
	/// <summary>
	/// Xの個数とZの個数
	/// </summary>
	int nCx = meshinfo_.filed_x + 1;

	/// <summary>
	/// インデックス番号格納変数（ポインター）
	/// </summary>
	LPWORD ppIndex;

	/// <summary>
	/// インデックスの数を奇数と偶数で分けて処理させるために必要な変数
	/// </summary>
	int nS = 0, nF = 0;
	int nC = 2 * nCx, nD = 2 * nCx + 1;

	if (FAILED(_device->CreateIndexBuffer(
		sizeof(WORD) * number_of_indices_,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL)))
	{
		MessageBox(NULL, "インデックスバッファの生成に失敗しました", "MeshFiled", MB_OK);
		PostQuitMessage(0);
	}

	buffer_.index_buffer->Lock(0, 0, (void**)&ppIndex, D3DLOCK_DISCARD);

	for (int nCount = 0; nCount < this->number_of_indices_; nCount++)
	{
		//インデックス偶数番の縮退
		if (nCount == nC)
		{
			ppIndex[nCount] = ppIndex[nCount - 1];
			nC += (2 * (nCx + 1));
			continue;
		}
		//インデックス偶数番
		if (nCount % 2 == 0)
		{
			ppIndex[nCount] = (WORD)(nCx + nS);
			nS++;
		}
		//インデックス奇数番の縮退
		if (nCount == nD)
		{
			ppIndex[nCount] = (WORD)(nCx + nS);
			nD += (2 * (nCx + 1));
			continue;
		}
		//インデックス奇数番
		if (nCount % 2 == 1)
		{
			ppIndex[nCount] = (WORD)(nF);
			if (nCount == ((nC * nCx) - 1))
			{
				ppIndex[nCount] = (WORD)(nF);
				continue;
			}
			else
			{
				nF++;
			}
		}
	}

	buffer_.index_buffer->Unlock();

}

//****************************************************
// 対象となる位置の高さを求める
//****************************************************
float MeshFiled::GetHeight(D3DXVECTOR3 _position)
{
	/// <summary>
	/// 頂点を結んだベクトルの算出用変数
	/// </summary>
	D3DXVECTOR3 V01, V12, V20;

	/// <summary>
	/// プレイヤーと各ベクトルを比較する変数
	/// </summary>
	D3DXVECTOR3 V0p, V1p, V2p;

	/// <summary>
	/// 2次元の外積値
	/// </summary>
	float C0, C1, C2;
	float C3, C4, C5;

	/// <summary>
	/// 法線ベクトル用　変数
	/// </summary>
	D3DXVECTOR3 normal;

	/// <summary>
	/// フィールドの最大個数
	/// </summary>
	//int MaxFiledX = (MeshFiledX)+1;
	int MaxFiledZ = (MeshFiledZ)+1;

	for (int nZ = 0; nZ < MeshFiledZ; nZ++)
	{
		for (int nX = 0; nX < MeshFiledX; nX++)
		{
			/// <summary>
			/// 方向ベクトルを求める
			/// </summary>
			V01 = mpv_[(nZ + 1)* MaxFiledZ + nX].position - mpv_[nZ * MaxFiledZ + nX].position;
			V12 = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position - mpv_[(nZ + 1) * MaxFiledZ + nX].position;
			V20 = mpv_[nZ * MaxFiledZ + nX].position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// 位置ベクトルを求める
			/// </summary>
			V0p = _position - mpv_[nZ * MaxFiledZ + nX].position;
			V1p = _position - mpv_[(nZ + 1) * MaxFiledZ + nX].position;
			V2p = _position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// 向きを求める
			/// </summary>
			C0 = V01.x * V0p.z - V01.z * V0p.x;
			C1 = V12.x * V1p.z - V12.z * V1p.x;
			C2 = V20.x * V2p.z - V20.z * V2p.x;

			/// <summary>
			/// D3DXVec3Cross() : 衝突判定用の法線を求め, 法線を含んだ計算をし,_position.yに返す
			/// </summary>
			if (C0 >= 0.0f && C1 >= 0.0f && C2 >= 0.0f)
			{
				D3DXVec3Cross(&normal, &V01, &V12);
				_position.y = mpv_[nZ * MaxFiledZ + nX].position.y - (normal.x * (_position.x - mpv_[nZ * MaxFiledZ + nX].position.x) + normal.z * (_position.z - mpv_[nZ * MaxFiledZ + nX].position.z)) / normal.y;
				break;
			}
			/// <summary>
			/// 方向ベクトルを求める
			/// </summary>
			V01 = mpv_[nZ * MaxFiledZ + nX].position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;
			V12 = mpv_[nZ * MaxFiledZ + (nX + 1)].position - mpv_[nZ * MaxFiledZ + nX].position;
			V20 = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position - mpv_[nZ * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// 位置ベクトルを求める
			/// </summary>
			V0p = _position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;
			V1p = _position - mpv_[nZ * MaxFiledZ + nX].position;
			V2p = _position - mpv_[nZ * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// 向きを求める
			/// </summary>
			C3 = V01.x * V0p.z - V01.z * V0p.x;
			C4 = V12.x * V1p.z - V12.z * V1p.x;
			C5 = V20.x * V2p.z - V20.z * V2p.x;

			/// <summary>
			/// D3DXVec3Cross() : 衝突判定用の法線を求め, 法線を含んだ計算をし,_position.yに返す
			/// </summary>
			if (C3 <= 0.0f && C4 <= 0.0f && C5 <= 0.0f)
			{
				D3DXVec3Cross(&normal, &V01, &V12);
				_position.y = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.y - (normal.x * (_position.x - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.x) + normal.z * (_position.z - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.z)) / normal.y;
				break;
			}
		}
	}
	return _position.y;
}

//----------------------------------------------------
// EOF
//----------------------------------------------------