#pragma once
#include "../../../Entity/Entity.h"

class Particle
{
	enum EMMITTERTYPE
	{
		EMT_BILLBOARDPARTICLE,
		EMT_POINTPARTICLE,
		EMT_NONE,
	};
public:
	Particle();
	~Particle();
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
private:
	void InitBillBoardParticle();
	void DrawBillBoardParticle();
	void InitPointParticle();
	void DrawPointParticle();
public:
	/*InitÇÃëOÇ≈ê›íËÇ∑ÇÈÇ±Ç∆*/
	void SetEmmitterType(EMMITTERTYPE _emmittertype);
	void SetTexture(LPDIRECT3DTEXTURE9 _texture);
	void SetNumParticle(int _num);
	void SetPosition(D3DXVECTOR3 _pos);
	void SetScale(D3DXVECTOR3 _scale);
	void SetRotation(D3DXVECTOR3 _rotation);
public:
	void AddMove(D3DXVECTOR3 _move);
	void AddScale(D3DXVECTOR3 _scale);
	void AddRotation(D3DXVECTOR3 _rotation);
private:
	int particlenum_;
	EMMITTERTYPE emmittertype_;
	LPDIRECT3DTEXTURE9 texture_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 rotation_;

	Entity::MODEL_WORLD1* pWorld1;
	Entity::MODEL_WORLD2* pWorld2;
	Entity::MODEL_WORLD3* pWorld3;
	Entity::MODEL_WORLD4* pWorld4;
	Entity::INSTANCINGBUFFER worldbuffer_;
	Entity::MATRIX3D matrix_;
	Entity::Dx9Buffer buffer_;
};