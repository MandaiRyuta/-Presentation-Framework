#pragma once
#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"

constexpr int MESHEFFECT_X = 4;
constexpr int MESHEFFECT_Y = 2;
constexpr float MESHEFFECT_SIZEX = 5.0f;
constexpr float MESHEFFECT_SIZEY = 5.0f;
class MeshEffect : public GameObjectManager
{
public:
	MeshEffect() : GameObjectManager(1) {}
	~MeshEffect() {}

public: 
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	void VertexBufferCreate(LPDIRECT3DDEVICE9 _device);
	void IndexBufferCreate(LPDIRECT3DDEVICE9 _device);
	static MeshEffect* Create();
private:
	#define FVF_MESHEFFECT ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
	D3DXVECTOR3 MeshPosition_[8];
	Entity::Dx9Buffer buffer_;

	Entity::MATRIX3D matrix_;

	int number_of_vertices_;
	int number_of_indices_;
	int number_of_primities_;
};
