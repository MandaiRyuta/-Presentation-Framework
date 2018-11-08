#pragma once
#include "../Entity/Entity.h"

//****************************************************
// 列挙型
//****************************************************
enum LOADMODEL
{
	SKYDOME,
	TREE,
	TESTMODEL,
	SHADOW,
	MODEL_MAX,	//モデルの最大個数
};

//****************************************************
// class ModelLoder
//****************************************************
class ModelLoder
{
private:
	ModelLoder() {}
	~ModelLoder() {}
public:
	/// <summary>
	/// ロードデータ
	/// </summary>
	//****************************************************
	// @ _filename : ファイルパス
	// @ _LoadType : 取り込む形式　0番：テクスチャ　1番: モデル
	//****************************************************
	static void LoadData(std::string _filename);
public:
	//****************************************************
	// ゲッター
	//****************************************************
	/// <summary>
	/// モデルデーターのゲッター
	/// </summary>
	//****************************************************
	// @ number : モデルナンバー
	//****************************************************
	static Entity::Model* GetModelData(LOADMODEL _targetmodel);

	static void ReleseAll();
private:
	//****************************************************
	// メンバー変数
	//****************************************************
	/// <summary>
	/// モデル格納変数
	/// </summary>
	static std::vector<Entity::Model*> model_;
	static Entity::Model InitModel[100];
	Entity::Model* OneModel_;
	/// <summary>
	/// モデルのカウンター
	/// </summary>
	static int ModelCounter_;
};