#include "MotionEffect.h"
#include "../Player/PlayerItem/PlayerWeapon.h"
#include "../../../LoadManager/TextureLoder.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"

bool MosionEffect::isdraw_ = false;

MosionEffect::MosionEffect(int _priority) 
	: GameObjectManager(_priority)
{
}

MosionEffect::~MosionEffect()
{
}
/*頂点バッファを作成時の領域確保に対し、実際いに作られていた頂点の数がオーバーしていた為、今まで更新がいってても終了時にバグがおきてた*/
void MosionEffect::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	if (FAILED(device->CreateVertexBuffer(
		sizeof(Entity::VECTOR3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_MESHEFFECT,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		NULL
	)))
	{
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "ERROR", MB_OK);
		PostQuitMessage(0);
	}

	buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv_, D3DLOCK_DISCARD);

	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int nX, nY, nY2;
	for (int i = 0; i < 4; i ++)
	{
		nX = 20 * i;
		nY = 40;
		nY2 = 0;
		mpv_[i * 2].position = D3DXVECTOR3((float)nX, (float)nY, 0.0f);
		mpv_[i * 2 + 1].position = D3DXVECTOR3((float)nX, (float)nY2, 0.0f);
		mpv_[i * 2].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		mpv_[i * 2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		mpv_[i * 2].texcoord = D3DXVECTOR2(1.0f, 1.0f);

		mpv_[i * 2 + 1].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		mpv_[i * 2 + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		mpv_[i * 2 + 1].texcoord = D3DXVECTOR2(1.0f, 1.0f);
	}

	buffer_.vertex_buffer->Unlock();

	LPWORD ppIndex;

	if (FAILED(device->CreateIndexBuffer(
		sizeof(WORD) * 8,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL
	)))
	{
		MessageBox(NULL, "インデックスバッファの作成に失敗しました", "ERROR", MB_OK);
		PostQuitMessage(0);
	}

	buffer_.index_buffer->Lock(0, 0, (void**)&ppIndex, D3DLOCK_DISCARD);

	ppIndex[0] = 1;
	ppIndex[1] = 0;
	ppIndex[2] = 2;

	//ppIndex[3] = 1;
	//ppIndex[4] = 2;
	ppIndex[3] = 3;
	//
	//ppIndex[6] = 1;
	//ppIndex[7] = 2;
	//ppIndex[8] = 3;

	//ppIndex[9] = 3;
	//ppIndex[10] = 2;
	ppIndex[4] = 4;

	//ppIndex[12] = 3;
	//ppIndex[13] = 4;
	ppIndex[5] = 5;
	//
	//ppIndex[15] = 3;
	//ppIndex[16] = 4;
	//ppIndex[17] = 5;

	//ppIndex[18] = 5;
	//ppIndex[19] = 4;
	ppIndex[6] = 6;

	//ppIndex[21] = 5;
	//ppIndex[22] = 6;
	ppIndex[7] = 7;
	//
	//ppIndex[24] = 5;
	//ppIndex[25] = 6;
	//ppIndex[26] = 7;

	buffer_.index_buffer->Unlock();

	D3DXMatrixIdentity(&mtx_.position);
	D3DXMatrixIdentity(&mtx_.rotation);
	D3DXMatrixIdentity(&mtx_.scale);
	D3DXMatrixIdentity(&mtx_.world);

	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void MosionEffect::Update()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXVECTOR3 weponPosTop;
	D3DXVECTOR3 weponPosBottom;

	if (isdraw_)
	{
		D3DXVec3TransformCoord(&weponPosTop, &D3DXVECTOR3(0.0f, 3.0f, 0.0f), &SceneGame::GetPlayerSword()->GetMtxWorld());
		D3DXVec3TransformCoord(&weponPosBottom, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &SceneGame::GetPlayerSword()->GetMtxWorld());

		buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv_, D3DLOCK_DISCARD);

		for (int i = 0; i < 4; i++)
		{
			mpv_[i * 2] = mpv_[i * 2 + 2];
			mpv_[i * 2 + 1] = mpv_[i * 2 + 3];
			mpv_[i * 2].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			mpv_[i * 2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			mpv_[i * 2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
			mpv_[i * 2 + 1].normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			mpv_[i * 2 + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			mpv_[i * 2 + 1].texcoord = D3DXVECTOR2(1.0f, 1.0f);
		}

		mpv_[6].position = weponPosTop;
		mpv_[7].position = weponPosBottom;

		buffer_.vertex_buffer->Unlock();

		D3DXMatrixTranslation(&mtx_.position, position_.x, position_.y, position_.z);
		D3DXMatrixRotationYawPitchRoll(&mtx_.rotation, rotation_.x, rotation_.y, rotation_.z);
		D3DXMatrixScaling(&mtx_.scale, scale_.x, scale_.y, scale_.z);
		mtx_.world = mtx_.scale * mtx_.rotation * mtx_.world;
	}
}

void MosionEffect::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	if(isdraw_)
	{
		device->SetFVF(FVF_MESHEFFECT);
		device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR3D));
		device->SetIndices(buffer_.index_buffer);
		device->SetTexture(0, TextureLoder::GetTextureData(MOTIONEFFECT));
		device->SetRenderState(D3DRS_LIGHTING, TRUE);
		device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		device->SetTransform(D3DTS_WORLD, &mtx_.world);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 8, 0, 8);

		device->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
}

void MosionEffect::Uninit()
{
	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
	}
	if (buffer_.index_buffer != nullptr)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = nullptr;
	}
}

void MosionEffect::SetDraw(bool _isdraw)
{
	isdraw_ = _isdraw;
}

MosionEffect * MosionEffect::CreateMotionEffect(int _priority)
{
	MosionEffect* motioneffct = new MosionEffect(_priority);
	motioneffct->Init();
	return motioneffct;
}
