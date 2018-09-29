#pragma once
#include <map>
#include <vector>
#include <string>
#include "../SceneManager/SceneManager.h"

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

namespace Entity
{
	struct Model
	{
		LPD3DXMESH p_mesh_;
		D3DMATERIAL9* p_meshmaterial_;
		LPDIRECT3DTEXTURE9* p_meshtexture_;
		DWORD dw_material_;
		D3DXVECTOR3 position_;
		D3DXVECTOR3 scall_;
		D3DXCOLOR color_;
		D3DXVECTOR3 rotation_;
		D3DXMATRIX world_;
	};

	struct FILEPATHDATA
	{
		int texturecount_;
		std::vector <std::string> texture_;
	};

	struct Textureinfomation
	{
		LPDIRECT3DTEXTURE9 texture;
	};

	struct CharactorStatus
	{
		int charaLv;
		int charaHP;
		int charaMP;
		int charaSP;
		float charaSTAMINA;
	};

	struct VECTOR3D
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	};

	struct VECTOR2D
	{
		D3DXVECTOR4 position;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	};

	struct MESHINFOMATION
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer;
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	};
}
