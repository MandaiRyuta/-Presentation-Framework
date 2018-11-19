#pragma once
#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"

class StenshilShadow : public GameObjectManager
{
public:
	StenshilShadow(int _type) 
		: GameObjectManager(0)
		, type_(_type)
	{}
	~StenshilShadow() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static StenshilShadow* Create(int _type);
private:
	int type_;
	Entity::MATRIX3D matrix_;
	Entity::Dx9Buffer buffer_;
};