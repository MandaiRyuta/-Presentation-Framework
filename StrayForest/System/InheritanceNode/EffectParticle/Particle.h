#pragma once
#include "../../../Entity/Entity.h"
constexpr int MAX_PARTICLE = 200;
class Particle
{
	struct ParticleInfo
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Speed;
		bool bParticle;
		int ParticleLife;
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
public:
	void CreateParticle(D3DXVECTOR3 _position, D3DXVECTOR3 _speed, int _life);
	void DestroyParticle(int _num, D3DXVECTOR3 _position, D3DXVECTOR3 _speed, int _life);
public:
	/*InitÇÃëOÇ≈ê›íËÇ∑ÇÈÇ±Ç∆*/
	void SetLife(int _life);
	void SetTexture(LPDIRECT3DTEXTURE9 _texture);
	void SetPosition(D3DXVECTOR3 _pos);
	void SetScale(D3DXVECTOR3 _scale);
public:
	void AddScale(D3DXVECTOR3 _scale);
private:
	int life_expectancy_;
	ParticleInfo particles_[MAX_PARTICLE];
	LPDIRECT3DTEXTURE9 texture_;
	D3DXVECTOR3 ReferencePoint_;
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