#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

constexpr int MESHEFFECT_X = 4;
constexpr int MESHEFFECT_Y = 2;
constexpr float MESHEFFECT_SIZEX = 5.0f;
constexpr float MESHEFFECT_SIZEY = 5.0f;

class MosionEffect : public GameObjectManager
{
public:
	MosionEffect(int _priority);
	~MosionEffect();

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
	static void SetDraw(bool _isdraw);
	static MosionEffect* CreateMotionEffect(int _priority);
private:
#define FVF_MESHEFFECT	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	D3DXVECTOR3 scale_;

	Entity::MATRIX3D mtx_;
	Entity::Dx9Buffer buffer_;
	Entity::VECTOR3D* mpv_;
	
	static bool isdraw_;

	int num_of_vertices_;
	int num_of_indices_;
	int num_of_primites_;
};