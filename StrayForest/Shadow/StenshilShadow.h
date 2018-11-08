#pragma once
#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"

class StenshilShadow : public GameObjectManager
{
public:
	StenshilShadow() 
		: GameObjectManager(0)
	{}
	~StenshilShadow() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static StenshilShadow* Create();
private:
	Entity::MATRIX3D matrix_;
	Entity::Dx9Buffer buffer_;
};