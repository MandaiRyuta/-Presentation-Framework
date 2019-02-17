#pragma once

#include "../SceneManager.h"
class Fade;
class MeshFiled;
class WinPlayer;
class Polygon2D;
class SceneWinResult : public SceneManager
{
public:
	SceneWinResult() {}
	~SceneWinResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetMeshFiled	:	メッシュフィールドを取得する関数
	static MeshFiled* GetMeshFiled();
	//@Summary	GetWinPlayer	:	プレイヤー取得する関数
	static WinPlayer* GetWinPlayer();
	//@Summary	GetWinWord	:	スタートボタンを押すを描画するポリゴンを取得する変数
	static Polygon2D* GetWinWord();
	//@Summary	GetFade	:	フェード処理を取得する関数
	static Fade* GetFade();
private:
	static MeshFiled* WinResultMeshFiled_;	//メッシュフィールド変数
	static WinPlayer* WinResultPlayer_;	//プレイヤー変数
	static Fade* fade_;	//フェード処理変数
	static Polygon2D* WinWord_;	//スタートボタンを押すを描画するポリゴンの変数
};