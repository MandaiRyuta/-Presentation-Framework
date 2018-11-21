#include "Particle.h"

Particle::Particle()
	: pWorld1(new Entity::MODEL_WORLD1)
	, pWorld2(new Entity::MODEL_WORLD2)
	, pWorld3(new Entity::MODEL_WORLD3)
	, pWorld4(new Entity::MODEL_WORLD4)
	, position_(0.0f,0.0f,0.0f)
	, scale_(1.0f,1.0f,1.0f)
	, rotation_(0.0f,0.0f,0.0f)
	, particlenum_(0)
	, emmittertype_(EMT_NONE)
	, texture_(nullptr)
{
}

Particle::~Particle()
{
}

void Particle::Init()
{
	switch (emmittertype_)
	{
	case EMT_BILLBOARDPARTICLE:
		InitBillBoardParticle();
		break;
	case EMT_POINTPARTICLE:
		InitPointParticle();
		break;
	default:
		break;
	}
}

void Particle::Update()
{

}

void Particle::Draw()
{
	switch (emmittertype_)
	{
	case EMT_BILLBOARDPARTICLE:
		DrawBillBoardParticle();
		break;
	case EMT_POINTPARTICLE:
		DrawPointParticle();
		break;
	default:
		break;
	}
}

void Particle::Uninit()
{
	delete pWorld1;
	delete pWorld2;
	delete pWorld3;
	delete pWorld4;

	if (worldbuffer_.pWorld1Buffer != nullptr)
	{
		worldbuffer_.pWorld1Buffer->Release();
		worldbuffer_.pWorld1Buffer = nullptr;
		delete worldbuffer_.pWorld1Buffer;
	}

	if (worldbuffer_.pWorld2Buffer != nullptr)
	{
		worldbuffer_.pWorld2Buffer->Release();
		worldbuffer_.pWorld2Buffer = nullptr;
		delete worldbuffer_.pWorld2Buffer;
	}

	if (worldbuffer_.pWorld3Buffer != nullptr)
	{
		worldbuffer_.pWorld3Buffer->Release();
		worldbuffer_.pWorld3Buffer = nullptr;
		delete worldbuffer_.pWorld3Buffer;
	}

	if (worldbuffer_.pWorld4Buffer != nullptr)
	{
		worldbuffer_.pWorld4Buffer->Release();
		worldbuffer_.pWorld4Buffer = nullptr;
		delete worldbuffer_.pWorld4Buffer;
	}

	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
		delete buffer_.vertex_buffer;
	}

	if (buffer_.index_buffer != nullptr)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = nullptr;
		delete buffer_.index_buffer;
	}

	if (texture_ != nullptr)
	{
		texture_->Release();
		texture_ = nullptr;
		delete texture_;
	}
}

void Particle::InitBillBoardParticle()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->CreateVertexBuffer(
		sizeof(Entity::POLYGON3D) * 4,
		0,
		0,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::POLYGON3D) * 4,
		0,
		0,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::POLYGON3D) * 4,
		0,
		0,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		0
	);

	device->CreateVertexBuffer(
		sizeof(Entity::POLYGON3D) * 4,
		0,
		0,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		0
	);
	for (DWORD dw = 0; dw < particlenum_; dw++)
	{
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		D3DXMatrixTranslation(&world, 0.0f, 0.0f, 0.0f);

		pWorld1[dw].m11 = world._11;
		pWorld1[dw].m12 = world._12;
		pWorld1[dw].m13 = world._13;
		pWorld1[dw].m14 = world._14;

		pWorld2[dw].m21 = world._21;
		pWorld2[dw].m22 = world._22;
		pWorld2[dw].m23 = world._23;
		pWorld2[dw].m24 = world._24;

		pWorld3[dw].m31 = world._31;
		pWorld3[dw].m32 = world._32;
		pWorld3[dw].m33 = world._33;
		pWorld3[dw].m34 = world._34;

		pWorld4[dw].m41 = world._41;
		pWorld4[dw].m42 = world._42;
		pWorld4[dw].m43 = world._43;
		pWorld4[dw].m44 = world._44;
	}

	Entity::POLYGON3D* pv;

	buffer_.vertex_buffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);

	Entity::POLYGON3D v[4] =
	{
		{ D3DXVECTOR3(2.5f, -2.5f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
		{ D3DXVECTOR3(2.5f,  2.5f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
		{ D3DXVECTOR3(-2.5f,  2.5f, 0.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
		{ D3DXVECTOR3(-2.5f, -2.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
	};

	memcpy(&pv[0], &v[0], sizeof(Entity::POLYGON3D) * 4);

	buffer_.vertex_buffer->Unlock();

	void* p = 0;

	worldbuffer_.pWorld1Buffer->Lock(0, 0, &p, 0);
	memcpy(p, pWorld1, sizeof(Entity::MODEL_WORLD1) * particlenum_);
	p = 0;

	worldbuffer_.pWorld2Buffer->Lock(0, 0, &p, 0);
	memcpy(p, pWorld2, sizeof(Entity::MODEL_WORLD2) * particlenum_);
	p = 0;

	worldbuffer_.pWorld3Buffer->Lock(0, 0, &p, 0);
	memcpy(p, pWorld3, sizeof(Entity::MODEL_WORLD3) * particlenum_);
	p = 0;

	worldbuffer_.pWorld4Buffer->Lock(0, 0, &p, 0);
	memcpy(p, pWorld4, sizeof(Entity::MODEL_WORLD4) * particlenum_);
	p = 0;

	device->CreateIndexBuffer(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL
	);

	LPWORD pIndex;
	buffer_.index_buffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	WORD index[] =
	{
		0, 3, 2,
		2, 1, 0,
	};

	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);
	buffer_.index_buffer->Unlock();

	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0,12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0,20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },

		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
		{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
		{ 3, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },
		{ 4, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },

		D3DDECL_END()
	};

	device->CreateVertexDeclaration(declElems, &worldbuffer_.pDecl);

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.world);
}

void Particle::DrawBillBoardParticle()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (UINT)particlenum_);
	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)1);
	device->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)2);
	device->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)3);
	device->SetStreamSourceFreq(4, D3DSTREAMSOURCE_INSTANCEDATA | (UINT)4);

	device->SetVertexDeclaration(worldbuffer_.pDecl);

	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::POLYGON3D));
	device->SetStreamSource(1, worldbuffer_.pWorld1Buffer, 0, sizeof(Entity::MODEL_WORLD1));
	device->SetStreamSource(2, worldbuffer_.pWorld2Buffer, 0, sizeof(Entity::MODEL_WORLD2));
	device->SetStreamSource(3, worldbuffer_.pWorld3Buffer, 0, sizeof(Entity::MODEL_WORLD3));
	device->SetStreamSource(4, worldbuffer_.pWorld4Buffer, 0, sizeof(Entity::MODEL_WORLD4));
	device->SetIndices(buffer_.index_buffer);
	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, false);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	for (int i = 0; i < particlenum_; i++)
	{

	}

	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void Particle::InitPointParticle()
{
}

void Particle::DrawPointParticle()
{
}

void Particle::SetEmmitterType(EMMITTERTYPE _emmittertype)
{
	emmittertype_ = _emmittertype;
}

void Particle::SetTexture(LPDIRECT3DTEXTURE9 _texture)
{
	texture_ = _texture;
}

void Particle::SetNumParticle(int _num)
{
	particlenum_ = _num;
}

void Particle::SetPosition(D3DXVECTOR3 _pos)
{
	position_ = _pos;
}

void Particle::SetScale(D3DXVECTOR3 _scale)
{
	scale_ = _scale;
}

void Particle::SetRotation(D3DXVECTOR3 _rotation)
{
	rotation_ = _rotation;
}

void Particle::AddMove(D3DXVECTOR3 _move)
{
	position_ += _move;
}

void Particle::AddScale(D3DXVECTOR3 _scale)
{
	scale_ += _scale;
}

void Particle::AddRotation(D3DXVECTOR3 _rotation)
{
	rotation_ += _rotation;
}
