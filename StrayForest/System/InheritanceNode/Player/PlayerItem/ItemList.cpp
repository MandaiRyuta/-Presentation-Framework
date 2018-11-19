#include "ItemList.h"
#include "PlayerWeapon.h"
#include "PlayerShiled.h"

void ItemList::Init(LPDIRECT3DDEVICE9 _device)
{
	for (auto itr = sword_.begin(); itr != sword_.end(); ++itr)
	{
		(*itr)->Init(_device);
	}
	for (auto itr = shiled_.begin(); itr != shiled_.end(); ++itr)
	{
		(*itr)->Init(_device);
	}
}

void ItemList::Update()
{
	for (auto itr = sword_.begin(); itr != sword_.end(); ++itr)
	{
		(*itr)->Update();
	}
	for (auto itr = shiled_.begin(); itr != shiled_.end(); ++itr)
	{
		(*itr)->Update();
	}
}

void ItemList::SwordDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone)
{
	for (auto itr = sword_.begin(); itr != sword_.end(); ++itr)
	{
		(*itr)->Draw(_device, targetbone);
	}
}

void ItemList::ShiledDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone)
{
	for (auto itr = shiled_.begin(); itr != shiled_.end(); ++itr)
	{
		(*itr)->Draw(_device, targetbone);
	}
}

void ItemList::Uninit()
{
	SwordClear();
	ShiledClear();
}
