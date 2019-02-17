#pragma once
#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"

class StenshilShadow : public GameObjectManager
{
public:
	StenshilShadow(int _type) 
		: GameObjectManager(0)
		, type_(_type)
	{}
	~StenshilShadow() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	ステンシルシャドウを作る為の関数
	//@ParamName	=	"_type"	:	1番目の描画か2番目の描画か（※重ねた部分を黒色に指定して丸影にさせる為）
	static StenshilShadow* Create(int _type);
private:
	int type_;	//1番目か2番目かを指定する変数
	Entity::MATRIX3D matrix_;	//全ての行列情報を持っている変数
	Entity::Dx9Buffer buffer_;	//バッファ―
};