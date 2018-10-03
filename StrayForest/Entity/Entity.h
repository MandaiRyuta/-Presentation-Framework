#pragma once
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
	struct Dx9Buffer
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer;
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	};

	struct EnemyStatePattern
	{
		ACTIONPATTERN action_;
		D3DXVECTOR3 position;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rotation;
	};

	struct CameraInfo
	{
		D3DXVECTOR3 at;
		D3DXVECTOR3 eye;
		D3DXVECTOR3 up;
		D3DXMATRIX view;
		D3DXMATRIX proj;
	};

	struct Model
	{
		LPD3DXMESH p_mesh;
		D3DMATERIAL9* p_meshmaterial;
		LPDIRECT3DTEXTURE9* p_meshtexture;
		DWORD dw_material;
		D3DXVECTOR3 position;
		D3DXVECTOR3 scall;
		D3DXCOLOR color;
		D3DXVECTOR3 rotation;
		D3DXMATRIX world;
	};

	struct FilePathData
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

	struct MeshFiledSize
	{
		int filed_x;
		int filed_z;
		float size_x;
		float size_z;
	};

	struct Dx9Shader
	{
		/// <summary>
		/// 定数テーブル
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> VSConstantTable_;
		/// <summary>
		/// 定数テーブル
		/// </summary>
		std::unordered_map<std::string, LPD3DXCONSTANTTABLE> PSConstantTable_;
		/// <summary>
		/// 頂点シェーダー
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DVERTEXSHADER9> vertexshader_;
		/// <summary>
		/// ピクセルシェーダー
		/// </summary>
		std::unordered_map<std::string, LPDIRECT3DPIXELSHADER9> pixelshader_;
	};
}
