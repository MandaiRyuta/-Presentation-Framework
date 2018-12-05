#pragma once
#include "../../../../Entity/Entity.h"
#include "PlayerWeapon.h"
#include "PlayerShiled.h"
#include <vector>

class ItemList
{
public:
	void add(PlayerSword* _sword, PlayerShiled* _shiled);
	void SwordClear();
	void ShiledClear();
	void Init();
	void Update();
	void SwordDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone);
	void ShiledDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone);
	void Uninit();
private:
	PlayerSword* sword_;
	PlayerShiled* shiled_;
};