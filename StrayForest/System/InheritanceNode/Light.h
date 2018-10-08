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

	void CreateMaterialLight(D3DMATERIAL9 _mat);
	void CreateLight(Entity::LightInfo _light);

	static D3DXVECTOR3 GetLightPos();
	static void SetLightPos(D3DXVECTOR3 _pos);
private:
	static D3DXVECTOR3 lightpos_;
	Entity::LightInfo lightinfo_;
};