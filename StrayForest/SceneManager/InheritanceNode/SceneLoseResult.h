#pragma once
#include "../SceneManager.h"

class MeshFiled;
class LosePlayer;
class Fade;
class Polygon2D;
class PolygonColorChanger;

class SceneLoseResult : public SceneManager
{
public:
	SceneLoseResult() {}
	~SceneLoseResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetMeshFiled	:	メッシュフィールドを取得する関数	
	static MeshFiled* GetMeshFiled();
	//@Summary	GetLostPlayer	:	プレイヤーを取得する関数
	static LosePlayer* GetLostPlayer();
	//@Summary	GetFade	:	フェード処理を取得する関数
	static Fade* GetFade();
	//@Summary	GetSepiaPolygon	:	セピア調に設定するポリゴンの取得関数
	static Polygon2D* GetSepiaPolygon();
	//@Summary	GetGameOverPolygon	:	ゲームオーバーを表示するポリゴンの取得関数
	static Polygon2D* GetGameOverPolygon();
	//@Summary	GetPressButtonPolygon	:	スタートボタンを押すを描画するポリゴンの取得関数
	static Polygon2D* GetPressButtonPolygon();
	//@Summary	GetSepiaFlag	:	セピア調になっているか確認するためのフラグ関数
	static bool GetSepiaFlag();
	//@Summary	SetSepiaFlag	:	セピア調に設定するためのフラグ関数
	//@ParamName	=	"_flag"	;	セピア調にするかしないかを指定する
	static void SetSepiaFlag(bool _flag);
	//@Summary	GetGameOverFlag	:	プレイヤーの真上からカメラが移すようになったときに、フラグを切り替えてセピア調にポリゴンを設定するためのフラグ関数
	static bool GetGameOverFlag();
	//@Summary	SetGameOverFlag	:	ゲームオーバーの時に描画する設定に切り替えるフラグ設定関数
	//@ParamName	=	"_flag"	:	切り替えるか切り替えないかを指定するフラグ
	static void SetGameOverFlag(bool _flag);
private:
	static MeshFiled* LostResultMeshFiled_;	//メッシュフィールド変数
	static LosePlayer* LostResultPlayer_;	//プレイヤー変数
	static Fade* fade_;	//フェード処理変数
	static Polygon2D* SepiaPolygon_;	//セピア調に切り替えるポリゴンの変数
	static Polygon2D* GameOverPolygon_;	//ゲームオーバーを表示するポリゴンの変数
	static Polygon2D* PressButtonWord_;	//スタートボタンを押すを描画するポリゴンの変数
	static bool SepiaColorFlag_;	//セピア調に切り替えるためのフラグ変数
	static bool GameOverDrawFlag_;	//ゲームオーバーを描画させるためのフラグ変数
};