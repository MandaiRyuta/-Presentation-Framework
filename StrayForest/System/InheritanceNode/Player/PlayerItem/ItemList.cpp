#include "ItemList.h"

void ItemList::add(PlayerSword* _sword, PlayerShiled* _shiled)
{
	sword_ = _sword;
	shiled_ = _shiled;
}

void ItemList::SwordClear()
{
	delete sword_;
}

void ItemList::ShiledClear()
{
	delete shiled_;
}

void ItemList::Init()
{
	shiled_->Init();
	sword_->Init();
}

void ItemList::Update()
{
	shiled_->Update();
	sword_->Update();
}

void ItemList::SwordDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone)
{
	sword_->Draw(_device, targetbone);
}

void ItemList::ShiledDraw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX targetbone)
{
	shiled_->Draw(_device, targetbone);
}

void ItemList::Uninit()
{
	SwordClear();
	ShiledClear();
}
