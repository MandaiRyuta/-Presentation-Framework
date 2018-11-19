#pragma once
#include "../../../../Entity/Entity.h"
#include <vector>

class PlayerShiled;
class PlayerSword;
class ItemList
{
public:
	void add(PlayerSword* _sword, PlayerShiled* _shiled)
	{
		sword_.push_back(_sword);
		shiled_.push_back(_shiled);
	}
	void SwordClear()
	{
		for (auto itr = sword_.begin(); itr != sword_.end();)
		{
			if (*itr != nullptr)
			{
				itr = sword_.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}
	void ShiledClear()
	{
		for (auto itr = shiled_.begin(); itr != shiled_.end();)
		{
			if (*itr != nullptr)
			{
				itr = shiled_.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}
	void Init(LPDIRECT3DDEVICE9 _device);
	void Update();
	void SwordDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone);
	void ShiledDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone);
	void Uninit();
private:
	std::vector<PlayerSword*> sword_;
	std::vector<PlayerShiled*> shiled_;
};