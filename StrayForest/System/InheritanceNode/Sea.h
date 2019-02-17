#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

//****************************************************
// constexpr
//****************************************************
constexpr int WAVE_X = 100;
constexpr int WAVE_Z = 100;
constexpr float WAVE_XSize = 20.0f;
constexpr float WAVE_ZSize = 20.0f;
//****************************************************
// define
//****************************************************
#define FVF_WAVE ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Sea : public GameObjectManager
{
public:
	Sea() : GameObjectManager(0) {}
	~Sea() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
	//@Summary	Create	:	海を作成する
	static Sea* Create();
private:
	Entity::MeshFiledSize meshinfo_;	//メッシュフィールド情報
	Entity::Dx9Buffer buffer_;	//バッファ
	Entity::VECTOR3D* mpv_;	//描画情報
	Entity::MATRIX3D matrix_;	//全ての行列情報

	LPDIRECT3DTEXTURE9 texture;	//テクスチャー情報
	LPDIRECT3DTEXTURE9 bumptexture;	//バンプマップ
	LPDIRECT3DVERTEXDECLARATION9 pDecl_;	//デカール
	
	int number_of_vertices_;	//頂点情報
	int number_of_indices_;	//インデックス情報
	int number_of_primities_;	//プリミティブ情報

	int SetnX;	//X
	int SetnZ;	//Z

	DWORD	m_gtime;	//時間

	float Kx[2];	//波の方向(X成分）
	float Kz[2];	//波の方向(Z成分)
	float wlen[2];	//波の長さ
	float k[2];	//波の長さを計数計算
	float amp[2];	//波の大きさ・うねり
	float w[2];	//波のうねりのはやさ
	float freq;	//波の周期
};