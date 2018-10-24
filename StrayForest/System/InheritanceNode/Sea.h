#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

constexpr int FRAME_TIME = 20;
constexpr int WAVE_PITCH = 10;
constexpr int WAVE_QTY = (40 + 1);
constexpr float WAVE_AMPLITUDE = 20.0f;
constexpr float WAVE_LENGTH = 100.0f;
constexpr float WAVE_CYCLE = 1.0f;


//****************************************************
// constexpr
//****************************************************
constexpr int WAVE_X = 100;
constexpr int WAVE_Z = 100;
constexpr float WAVE_XSize = 20.0f;
constexpr float WAVE_ZSize = 20.0f;
//****************************************************
// define
//****************************************************
#define FVF_WAVE ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Sea : public GameObjectManager
{
public:
	Sea() : GameObjectManager(0) {}
	~Sea() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	static Sea* Create();
private:
	Entity::WAVE wave_[WAVE_QTY][WAVE_QTY];
	Entity::MeshFiledSize meshinfo_;
	Entity::Dx9Buffer buffer_;
	Entity::VECTOR3D* mpv;
	Entity::MATRIX3D matrix_;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 bumptexture;
	LPDIRECT3DVERTEXDECLARATION9 pDecl_;
	
	int number_of_vertices_;
	int number_of_indices_;
	int number_of_primities_;

	int SetnX;
	int SetnZ;
};