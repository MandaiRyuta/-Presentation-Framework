#include "Sea.h"
#include "../../LoadManager/TextureLoder.h"

void Sea::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	int nCount = 0;
	float fStartX = -WAVE_XSize * (WAVE_X / 2), fStartY = 0.0f, fStartZ = WAVE_ZSize * (WAVE_Z / 2);

	int nCx = WAVE_X + 1, nCy = WAVE_Z + 1;

	this->number_of_vertices_ = nCx * nCy;														//頂点数
	this->number_of_indices_ = (nCx * 2 + 1) * (nCy - 1) + ((nCy - 2) * 1);				//インデックス数
	this->number_of_primities_ = this->number_of_indices_ - 2;								//Primitive数


	if (FAILED(device->CreateVertexBuffer(
		sizeof(Entity::VECTOR3D) * this->number_of_vertices_,
		D3DUSAGE_WRITEONLY,
		FVF_WAVE,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		NULL))) {
		PostQuitMessage(0);
	}

	buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv, D3DLOCK_DISCARD);

	/*
	VX = (P+1) - (P-1);
	*/
	/*
	NX.x = -VX.y;
	NX.y = VX.x;
	NX.z = 0.0;
	*/
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	/*
	フィールドの端は見せない、もし見る場合があるなら、最後の法線を１にセットしておく
	*/

	for (int nZ = 0; nZ < nCy; nZ++) {
		for (int nX = 0; nX < nCx; nX++) {

			mpv[nCount].position = D3DXVECTOR3(fStartX + (WAVE_XSize * nX), 0.0f, fStartZ - (WAVE_ZSize * nZ));

			vx = mpv[(nZ * nCy) + (nX + 2)].position - mpv[nZ * nCy + nX].position;
			vz = mpv[(nZ * nCy) + (nX + 1)].position - mpv[nZ * nCx + (nX)].position;

			D3DXVec3Cross(&n, &vx, &vz);
			D3DXVec3Normalize(&n, &n);
			mpv[nZ * nCx + nX].normal = n;

			mpv[nCount].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			mpv[nCount].texcoord = D3DXVECTOR2((WAVE_XSize * nX) / (WAVE_ZSize * nCx), (WAVE_ZSize * nZ) / (WAVE_ZSize * nCy));

			nCount++;
		}
	}

	buffer_.vertex_buffer->Unlock();

	LPWORD ppIndex;
	int nS = 0, nF = 0, nC = 2 * nCx, nD = 2 * nCx + 1;

	if (FAILED(device->CreateIndexBuffer(
		sizeof(WORD)* this->number_of_indices_,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL))) {
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
			ppIndex[nCount] = nCx + nS;
			nS++;
		}
		//インデックス奇数番の縮退
		if (nCount == nD)
		{
			ppIndex[nCount] = nCx + nS;
			nD += (2 * (nCx + 1));
			continue;
		}
		//インデックス奇数番
		if (nCount % 2 == 1)
		{
			ppIndex[nCount] = nF;
			if (nCount == ((nC * nCx) - 1))
			{
				ppIndex[nCount] = nF;
				continue;
			}
			else
			{
				nF++;
			}
		}
	}

	buffer_.index_buffer->Unlock();

	//HRESULT hr;

	//LPD3DXBUFFER errBuf = 0;
	//
	//if (FAILED(hr = D3DXCreateEffectFromFile(device_, "meshfiled.fx", NULL, NULL, 0, NULL, &seffect_, &errBuf)))
	//{
	//	MessageBox(NULL, (LPCSTR)errBuf->GetBufferPointer(), "ERROR", MB_OK);
	//}
	//else
	//{
	//	technique_ = seffect_->GetTechniqueByName("tech");
	//}
	//LPDIRECT3DTEXTURE9 pHeightTexture;

	//D3DSURFACE_DESC desc;

	//if (FAILED(D3DXCreateTextureFromFile(device_, "resource/texture/Stage.bmp", &pHeightTexture)))
	//{
	//	MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
	//}
	//pHeightTexture->GetLevelDesc(0, &desc);
	//if (FAILED(D3DXCreateTexture(device_, desc.Width, desc.Height, 0, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &hightmap_)))
	//{
	//	MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
	//}
	//if (FAILED(D3DXComputeNormalMap(hightmap_, pHeightTexture, NULL, 0, D3DX_CHANNEL_RED, 1.0f)))
	//{
	//	MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
	//}
	//pHeightTexture->Release();
	//pHeightTexture = NULL;
	//if (errBuf)
	//	errBuf->Release();

	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	D3DXVECTOR3 scale = D3DXVECTOR3(2.0f, 1.0f, 2.0f);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixTranslation(&matrix_.position, position.x, position.y, position.z);
	D3DXMatrixScaling(&matrix_.scale, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, rotation.y, rotation.x, rotation.z);
}

void Sea::Update()
{
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

void Sea::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetFVF(FVF_WAVE);
	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR3D));
	device->SetIndices(buffer_.index_buffer);
	device->SetTexture(0, TextureLoder::GetTextureData(SEA));
	//device->SetMaterial(&this->MeshMaterial_);
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetTransform(D3DTS_WORLD, &matrix_.world);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);
}

void Sea::Uninit()
{
	if (buffer_.vertex_buffer != NULL)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = NULL;
	}
	if (buffer_.index_buffer != NULL)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = NULL;
	}
}

Sea * Sea::Create()
{
	Sea* sea = new Sea;
	sea->Init();
	return sea;
}
