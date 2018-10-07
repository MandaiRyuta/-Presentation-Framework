#pragma once

#include "../../Entity/Entity.h"

class Light
{
public:
	Light() {}
	~Light() {}

public:
	void Init();
	void Update() {}
	void Draw() {}
	void Uninit() {}

	void CreateMaterialLight(D3DMATERIAL9 mat);
	void CreateLight(Entity::LightInfo _light);
private:
	Entity::LightInfo lightinfo_;
};