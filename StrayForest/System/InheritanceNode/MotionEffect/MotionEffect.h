#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

constexpr int MESHEFFECT_X = 4;
constexpr int MESHEFFECT_Y = 2;
constexpr float MESHEFFECT_SIZEX = 5.0f;
constexpr float MESHEFFECT_SIZEY = 5.0f;

class MosionEffect : public GameObjectManager
{
public:
	MosionEffect(int _priority);
	~MosionEffect();

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
	//@Summary	SetDraw	:	モーションエフェクトを描画するときに使う関数
	//@ParamName	=	"_isdraw"	:	描画するかしないかを選択させるフラグ
	static void SetDraw(bool _isdraw);
	//@Summary	CreateMotionEffect	:	モーションエフェクトを作成する
	//@ParamName	=	"_priority"	:	描画優先度
	static MosionEffect* CreateMotionEffect(int _priority);
private:
#define FVF_MESHEFFECT	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//レンダリング情報
	D3DXVECTOR3 position_;	//座標変数
	D3DXVECTOR3 rotation_;	//回転変数
	D3DXVECTOR3 scale_;	//拡大変数

	Entity::MATRIX3D mtx_;	//全ての行列が含まれている変数
	Entity::Dx9Buffer buffer_;	//バッファ
	Entity::VECTOR3D* mpv_;	//レンダリング情報に沿った変数
	
	static bool isdraw_;	//描画フラグ

	int num_of_vertices_;	//頂点数
	int num_of_indices_;	//インデックス数
	int num_of_primites_;	//プリミティブ数
};