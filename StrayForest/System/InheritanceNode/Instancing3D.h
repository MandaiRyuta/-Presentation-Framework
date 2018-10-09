#pragma once
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../Entity/Entity.h"

constexpr int INSTANCINGMODEL_MAX = 200;

class Instancing3D : public GameObjectManager
{
public:
	Instancing3D() 
		: GameObjectManager(OBJ_3D_MODEL) 
	{}
	~Instancing3D() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static Instancing3D* Create();
private:
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	D3DXVECTOR3 scale_;
	Entity::MATRIX3D matrix_;
	Entity::Dx9Buffer buffer_;
	Entity::INSTANCINGWORLD world_;
	Entity::INSTANCINGBUFFER insbuffer_;
};