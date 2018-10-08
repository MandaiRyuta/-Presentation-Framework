#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

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
private:
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