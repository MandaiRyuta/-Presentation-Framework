#include "TPolygon2D.h"

Polygon2D::Polygon2D(
	int _priority,
	float _dx,
	float _dy,
	float _dw,
	float _dh,
	unsigned int _tcx, 
	unsigned int _tcy,
	unsigned int _tcw,
	unsigned int _tch, 
	D3DCOLOR _color,
	bool _affine,
	float _angle,
	float _rot_offsetx,
	float _rot_offsety,
	float _scale_offsetX,
	float _scale_offsetY,
	float _scaleX,
	float _scaleY,
	LPDIRECT3DTEXTURE9 _texture)
	: GameObjectManager(_priority)
	, angle_(_angle)
	, rot_offsetX_(_rot_offsetx)
	, rot_offsetY_(_rot_offsety)
	, scale_offsetX_(_scale_offsetX)
	, scale_offsetY_(_scale_offsetY)
	, scaleX_(_scaleX)
	, scaleY_(_scaleY)
{
	infomation_.dx_ = _dx;
	infomation_.dy_ = _dy;
	infomation_.dw_ = _dw;
	infomation_.dh_ = _dh;
	infomation_.tcx_ = _tcx;
	infomation_.tcy_ = _tcy;
	infomation_.tcw_ = _tcw;
	infomation_.tch_ = _tch;
	infomation_.color_ = _color;
	infomation_.affine_ = _affine;
}

Polygon2D::~Polygon2D()
{
}

void Polygon2D::CreateVertex(D3DCOLOR _color, float _dx, float _dy, float _dw, float _dh, int _tcx, int _tcy, int _tcw, int _tch)
{
	Entity::VECTOR2D* pv;
	buffer_.vertex_buffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	
	pv[0].position = D3DXVECTOR4(_dx, _dy - _dh / 2, 0.0f, 1.0f);
	pv[1].position = D3DXVECTOR4(_dx + _dw / 2, _dy - _dh / 2, 0.0f, 1.0f);
	pv[2].position = D3DXVECTOR4(_dx + _dw / 2, _dy + _dh / 2, 0.0f, 1.0f);
	pv[3].position = D3DXVECTOR4(_dx, _dy + _dh / 2, 0.0f, 1.0f);

	pv[0].color = _color;
	pv[1].color = _color;
	pv[2].color = _color;
	pv[3].color = _color;

	float u0 = (float)_tcx / _tcw;
	float v0 = (float)_tcy / _tch;
	float u1 = (float)(_tcx + _tcw) / _tcw;
	float v1 = (float)(_tcy + _tch) / _tch;

	pv[0].texcoord = D3DXVECTOR2(u0, v0);
	pv[1].texcoord = D3DXVECTOR2(u1, v0);
	pv[2].texcoord = D3DXVECTOR2(u1, v1);
	pv[3].texcoord = D3DXVECTOR2(u0, v1);
}

void Polygon2D::CreateVertexAffine(D3DCOLOR _color, float _dx, float _dy, float _dw, float _dh, int _tcx, int _tcy, int _tcw, int _tch)
{
	Entity::VECTOR2D* pv;
	
	buffer_.vertex_buffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);

	float x0 = (0.0f - scale_offsetX_) * scaleX_ + scaleX_;
	float x1 = (_dw - scale_offsetX_) * scaleX_ + scaleX_;
	float y0 = (0.0f - scale_offsetY_) * scaleY_ + scaleY_;
	float y1 = (_dh - scale_offsetY_) * scaleY_ + scaleY_;

	float VX0 = _dx + x0 * cosf(angle_) - y0 * sinf(angle_);
	float VY0 = _dy + x0 * sinf(angle_) + y0 * cosf(angle_);
	float VX1 = _dx + x1 * cosf(angle_) - y0 * sinf(angle_);
	float VY1 = _dy + x1 * sinf(angle_) + y0 * cosf(angle_);
	float VX2 = _dx + x1 * cosf(angle_) - y1 * sinf(angle_);
	float VY2 = _dy + x1 * sinf(angle_) + y1 * cosf(angle_);
	float VX3 = _dx + x0 * cosf(angle_) - y1 * sinf(angle_);
	float VY3 = _dx + x0 * sinf(angle_) + y1 * cosf(angle_);

	pv[0].position = D3DXVECTOR4(_dx + VX0, _dy + VY0, 0.0f, 1.0f);
	pv[1].position = D3DXVECTOR4(_dx + VX1, _dy + VY1, 0.0f, 1.0f);
	pv[2].position = D3DXVECTOR4(_dx + VX2, _dy + VY2, 0.0f, 1.0f);
	pv[3].position = D3DXVECTOR4(_dx + VX3, _dy + VY3, 0.0f, 1.0f);

	pv[0].color = _color;
	pv[1].color = _color;
	pv[2].color = _color;
	pv[3].color = _color;

	float u0 = (float)_tcx / _tcw;
	float v0 = (float)_tcy / _tch;
	float u1 = (float)(_tcx + _tcw) / _tcw;
	float v1 = (float)(_tcy + _tch) / _tch;

	pv[0].texcoord = D3DXVECTOR2(u0, v0);
	pv[1].texcoord = D3DXVECTOR2(u1, v0);
	pv[2].texcoord = D3DXVECTOR2(u1, v1);
	pv[3].texcoord = D3DXVECTOR2(u0, v1);

	buffer_.vertex_buffer->Unlock();
}

void Polygon2D::Init()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	
	HRESULT hr = device->CreateVertexBuffer(sizeof(Entity::VECTOR2D) * 4, D3DUSAGE_WRITEONLY, FVF_POLYGON2D, D3DPOOL_MANAGED, &buffer_.vertex_buffer, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファの作成失敗", "ERROR", MB_OK);
	}
}

void Polygon2D::Update()
{
}

void Polygon2D::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	if (infomation_.affine_)
	{
		CreateVertexAffine(infomation_.color_, infomation_.dx_, infomation_.dy_, infomation_.dw_, infomation_.dh_, infomation_.tcx_, infomation_.tcy_, infomation_.tcw_, infomation_.tch_);
	}
	else
	{
		CreateVertex(infomation_.color_, infomation_.dx_, infomation_.dy_, infomation_.dw_, infomation_.dh_, infomation_.tcx_, infomation_.tcy_, infomation_.tcw_, infomation_.tch_);
	}

	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR2D));

	device->SetFVF(FVF_POLYGON2D);

	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	device->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	device->SetTexture(0, NULL);

	device->DrawPrimitive(
		D3DPT_TRIANGLEFAN, 0, 2
	);

	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

void Polygon2D::Uninit()
{
	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
		delete buffer_.vertex_buffer;
	}
}

void Polygon2D::SetColor(D3DCOLOR _color)
{
	infomation_.color_ = _color;
}

void Polygon2D::SetPolygonScale(float _x, float _y)
{
	scaleX_ = _x;
	scaleY_ = _y;
}

Polygon2D * Polygon2D::Create(int _priority, float _dx, float _dy, float _dw, float _dh, unsigned int _tcx, unsigned int _tcy, unsigned int _tcw, unsigned int _tch, D3DCOLOR _color, bool _affine, float _angle, float _rot_offsetx, float _rot_offsety, LPDIRECT3DTEXTURE9 _texture)
{
	return nullptr;
}
