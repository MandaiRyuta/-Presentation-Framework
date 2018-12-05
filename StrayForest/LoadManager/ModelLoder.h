#pragma once
#include "../Entity/Entity.h"

class Models
{
public:
	Models() {}
	virtual ~Models() {}
	virtual Entity::Model* GetModelData() = 0;
	virtual void Relese() = 0;
};
//****************************************************
// class ModelLoder
//****************************************************
class ModelLoder : public Models
{
public:
	ModelLoder(std::string _filename);
	~ModelLoder();
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
	Entity::Model* GetModelData();

	void Relese();
private:
	//****************************************************
	// メンバー変数
	//****************************************************
	/// <summary>
	/// モデル格納変数
	/// </summary>
	Entity::Model* OneModel_;
	/// <summary>
	/// モデルのカウンター
	/// </summary>
};