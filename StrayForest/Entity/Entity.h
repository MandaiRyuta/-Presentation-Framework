#pragma once
#include <map>
#include <vector>
#include <string>
#include "../Scene/Scene.h"

struct CharactorStatus
{
	int charaHP;
	int charaMP;
	int charaSP;
	float charaSTAMINA;
};

struct Model
{
	LPD3DXMESH p_mesh_;
	D3DMATERIAL9* p_meshmaterial_;
	LPDIRECT3DTEXTURE9* p_meshtexture_;
	DWORD dw_material_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scall_;
	D3DXCOLOR color_;
	float rotatiion_;
	bool isscall_;
	int  index_;
	D3DXMATRIX world_;
};

enum TEXTURENUMBER
{
	NONE,
};

enum ACTIONPATTERN
{
	WALK,
	RUN,
	ATTACK,
	DEFFENCE,
	SKILL,
	MAGIC,
};
class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}
};