#pragma once
#include "../Entity/Entity.h"

//使う種類ごとにシェーダーをわけているので番号を振っている
enum EFFECTINFO
{
	MODEL3D,
	//INSTANCING3D,
	SKINMESH,
	STENSHILSHADOW,
	SHILED,
	SWORD,
	//PARTICLE,
	EFFECT_MAX,
};

//シェーダーマネージャークラス
class EffectShaderManager
{
private:
	EffectShaderManager() {}
	~EffectShaderManager() {}
public:
	//@Summary	EffectLoad	:	シェーダーのファイルパスを読み込んで、データーを読み込む
	//@ParamName	=	"_filepath"		:	ファイルパス
	static void EffectLoad(std::string _filepath);
	//@Summary	GetEffect	:	指定したシェーダーを呼び出す関数
	//@ParamName	=	"_effectnumber"	:	EFFECTINFOの番号
	static LPD3DXEFFECT GetEffect(EFFECTINFO _effectnumber);
	//@Summary	ReleaseAll	:	全てのシェーダーのデータ開放
	static void ReleaseAll();
private:
	static std::vector<LPD3DXEFFECT> effects_;	//シェーダー情報を取り込む変数
	static int effectcount_;	//シェーダーの番号
};