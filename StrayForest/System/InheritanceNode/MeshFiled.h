//****************************************************
// @file : meshfiled.cpp
// @brief: メッシュフィールドの作成
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
#pragma once
//****************************************************
// include
//****************************************************
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../Entity/Entity.h"

//****************************************************
// define
//****************************************************
#define FVF_FILED ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//****************************************************
// constexpr
//****************************************************
constexpr int MeshFiledX = 100;
constexpr int MeshFiledZ = 100;
constexpr float MeshFiledXSize = 20.0f;
constexpr float MeshFiledZSize = 20.0f;

//****************************************************
// class
//****************************************************
class MeshFiled : public GameObjectManager
{
	//****************************************************
	// メンバー関数
	//****************************************************
public:
	/// <summary>
	/// MeshFiledクラスのコンストラクタ
	/// </summary>
	//****************************************************
	//* @ _Priority  : 描画優先順位指定
	//* @ _filename  : ファイルパス
	//* @ _mesh_info : メッシュ情報
	//****************************************************
	MeshFiled(Entity::MeshFiledSize _mesh_info)
		: meshinfo_(_mesh_info), GameObjectManager(0)
	{

	}

	/// <summary>
	/// MeshFiledクラスのデストラクタ
	/// </summary>
	~MeshFiled() {}

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 開放
	/// </summary>
	void Uninit() override;

	/// <summary>
	/// Create関数
	/// </summary>
	//****************************************************
	// @ _meshinfo : メッシュ情報
	// @ _filename : ファイルパス
	//****************************************************
	static MeshFiled* Create(Entity::MeshFiledSize _meshinfo);

private:
	/// <summary>
	/// バーテックスバッファの生成
	/// </summary>
	//****************************************************
	// @ _device : DirectX device
	//****************************************************
	void VertexBufferCreate(LPDIRECT3DDEVICE9 _device);
	/// <summary>
	/// インデックスバッファの生成
	/// </summary>
	//****************************************************
	// @ _device : DirectX device
	//****************************************************
	void IndexBufferCreate(LPDIRECT3DDEVICE9 _device);
public:
	//****************************************************
	// ゲッター
	//****************************************************

	/// <summary>
	/// メッシュフィールドの高さ取得
	/// </summary>
	//****************************************************
	// @ _position : 対象の座標
	//****************************************************
	float GetHeight(D3DXVECTOR3 _position);
public:
	//****************************************************
	// セッター
	//****************************************************
private:
	/// <summary>
	/// csvファイルから読み込みフィールドの高さ設定
	/// </summary>
	float FiledHeight[MeshFiledX][MeshFiledZ];

	/// <summary>
	/// バッファ
	/// </summary>
	Entity::Dx9Buffer buffer_;

	/// <summary>
	/// テクスチャー
	/// </summary>
	Entity::Textureinfomation texture_[2];

	/// <summary>
	/// マテリアル情報
	/// </summary>
	D3DMATERIAL9 meshmaterial_;

	/// <summary>
	/// 行列の集まり
	/// </summary>
	Entity::MATRIX3D matrix_;

	/// <summary>
	/// 位置ベクトル
	/// </summary>
	D3DXVECTOR3 position_;

	/// <summary>
	/// 拡大ベクトル
	/// </summary>
	D3DXVECTOR3 scale_;

	/// <summary>
	/// 回転ベクトル
	/// </summary>
	D3DXVECTOR3 rotation_;
	
	/// <summary>
	/// メッシュフィールドの情報
	/// </summary>
	Entity::VECTOR3D* mpv_;

	/// <summary>
	/// メッシュフィールド情報を格納する構造体
	/// </summary>
	Entity::MeshFiledSize meshinfo_;

	/// <summary>
	/// バーテックス数
	/// </summary>
	int number_of_vertices_;

	/// <summary>
	/// インデックス数
	/// </summary>
	int number_of_indices_;

	/// <summary>
	/// プリミティブ数
	/// </summary>
	int number_of_primities_;

	/// <summary>
	/// X座標の配列数
	/// </summary>
	int SetnX_;

	/// <summary>
	/// Z座標の配列数
	/// </summary>
	int SetnZ_;
};

//----------------------------------------------------
// EOF
//----------------------------------------------------