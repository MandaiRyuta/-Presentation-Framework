#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <unordered_map>
#if _DEBUG
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/EffekseerRendererDX9.lib" )
#else
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/EffekseerRendererDX9.lib" )
#endif

#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class MyEffekseer : public GameObjectManager
{
public:
	MyEffekseer(int _priority, wchar_t _filepath[]);
	~MyEffekseer();
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

public:
	static MyEffekseer* CreateMyEffect(int _priority, wchar_t _filepath[]);
public:
	//@Summary	SetMovePosition	:	移動位置を設定する
	void SetMovePosition(D3DXVECTOR3 _addmove);
	//@Summary	SetPosition	:	座標をセットする
	//@ParamName	=	"_targetposition"	:	位置
	void SetPosition(D3DXVECTOR3 _targetposition);
	//@Summary	SetScale	:	拡大値をセットする
	//@ParamName	=	"_scale"	:	設定する拡大値
	void SetScale(D3DXVECTOR3 _scale);
	//@Summary	SetRotation	:	回転をセットする
	//@ParamName	=	"_rotation"	:	回転の値
	void SetRotation(D3DXVECTOR3 _rotation);
	//@Summary	SetWorldMatrix	:	ワールド行列をセットする
	//@ParamName	=	"_location"	:	ワールド行列にセットする値
	void SetWorldMatrix(Entity::EffectInfomation _location);
	//@Summary	SetIsDrawing	:	描画設定
	//@ParamName	=	"_drawing"	:	描画フラグ
	void SetIsDrawing(bool _drawing);
private:
	//@Summary	SetEfkWorldMatrix	:	エフェクシア側にセットするワールド行列
	void SetEfkWorldMatrix(D3DXMATRIX _world);
public:
	//@Summary	PlayEffect	:	エフェクト再生
	void PlayEffect();
	//@Summary	StopEffect	:	エフェクト停止
	void StopEffect();
public:
	//@Summary	GetPosition	:	エフェクト描画時の座標情報を取得する
	const D3DXVECTOR3 GetPosition();
	//@Summary	GetRotation	:	エフェクト描画時の回転情報を取得する
	const D3DXVECTOR3 GetRotation();
	//@Summary	GetWorld	:	エフェクト描画時のワールド情報を取得する
	const D3DXMATRIX GetWorld();
	//@Summary	GetFramecount	:	描画中のフレームカウントを取得する
	const float GetFrameCount();
public:
	//@Summary	SetFramecount	:	フレームカウントを設定する
	//@_deltatime	:	1フレーム毎の増加値を設定
	void SetFrameCount(float _deltatime);
private:
	float deltaframe_;	//1フレームでカウントされる値
	bool IsDrawing_;	//描画フラグ
	bool PlayFlag_;		//再生フラグ
	D3DXMATRIX world_;	//ワールド行列
	Effekseer::Manager* MyEfkManager_;	//エフェクシアマネージャー
	EffekseerRendererDX9::Renderer* MyEfkRenderer_;	//エフェクシアレンダラー
	Effekseer::Effect*	MyEfkEffect_;	//エフェクシア側のパラメーター
	Effekseer::Handle	MyEfkHandle_;	//エフェクシア側のハンドル情報
	Entity::EffectInfomation location_;	//エフェクト描画に必要な情報
};