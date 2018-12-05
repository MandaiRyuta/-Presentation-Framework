#include "MotionEffect.h"
#include "../LoadManager/TextureLoder.h"

void MeshEffect::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	int nX, nY, nY2;
	Entity::VECTOR3D* mpv_;
	if (FAILED(device->CreateVertexBuffer(
		sizeof(Entity::VECTOR3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_MESHEFFECT,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		NULL))) {
		PostQuitMessage(0);
	}

	buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv_, D3DLOCK_DISCARD);

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
	for (int i = 0; i < 8; i += 2)
	{
		nX = 5 * i;
		nY = 40;
		nY2 = 0;
		mpv_[i].position = D3DXVECTOR3((float)nX, (float)nY, 0.0f);
		mpv_[i + 1].position = D3DXVECTOR3((float)nX, (float)nY2, 0.0f);
	}

	buffer_.vertex_buffer->Unlock();

	LPWORD ppIndex;

	if (FAILED(device->CreateIndexBuffer(
		sizeof(WORD)* 27,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL))) {
		PostQuitMessage(0);
	}

	buffer_.index_buffer->Lock(0, 0, (void**)&ppIndex, D3DLOCK_DISCARD);

	ppIndex[0] = 1;
	ppIndex[1] = 0;
	ppIndex[2] = 2;
	ppIndex[3] = 1;
	ppIndex[4] = 2;
	ppIndex[5] = 3;
	//
	ppIndex[6] = 1;
	ppIndex[7] = 2;
	ppIndex[8] = 3;

	ppIndex[9] = 3;
	ppIndex[10] = 2;
	ppIndex[11] = 4;
	ppIndex[12] = 3;
	ppIndex[13] = 4;
	ppIndex[14] = 5;
	//
	ppIndex[15] = 3;
	ppIndex[16] = 4;
	ppIndex[17] = 5;

	ppIndex[18] = 5;
	ppIndex[19] = 4;
	ppIndex[20] = 6;
	ppIndex[21] = 5;
	ppIndex[22] = 6;
	ppIndex[23] = 7;
	//
	ppIndex[24] = 5;
	ppIndex[25] = 6;
	ppIndex[26] = 7;


	buffer_.index_buffer->Unlock();

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.world);
}

void MeshEffect::Update()
{
	//for (int i = 0; i < 8; i++)
	//{
	//	MeshPosition_[i * 2] = MeshPosition_[i * 2 + 2];
	//	MeshPosition_[i * 2 + 1] = MeshPosition_[i * 2 + 3];
	//}
	//D3DXVec3TransformCoord();
	//MeshPosition_[6] = ;
	//MeshPosition_[7] = ;
	D3DXMatrixTranslation(&matrix_.position, 100.0f, 80.0f, 0.0f);
	D3DXMatrixScaling(&matrix_.scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, 0.0f, 0.0f, 0.0f);
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

void MeshEffect::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetFVF(FVF_MESHEFFECT);
	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR3D));
	device->SetIndices(buffer_.index_buffer);
	device->SetTexture(0, TextureLoder::GetTextureData(SEA));
	//device->SetMaterial(&this->MeshMaterial_);
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetTransform(D3DTS_WORLD, &matrix_.world);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 8, 0, 28);
}

void MeshEffect::Uninit()
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

void MeshEffect::VertexBufferCreate(LPDIRECT3DDEVICE9 _device)
{
	
}

void MeshEffect::IndexBufferCreate(LPDIRECT3DDEVICE9 _device)
{

}

MeshEffect * MeshEffect::Create()
{
	MeshEffect* create_mesheffect = new MeshEffect;
	create_mesheffect->Init();

	return create_mesheffect;
}
