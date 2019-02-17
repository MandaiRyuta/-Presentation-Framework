#pragma once
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Fade/Fade.h"
#include "../../System/Polygon2D.h"
class Fade;

class SceneTitle : public SceneManager
{
public:
	SceneTitle() {}
	~SceneTitle() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	//@Summary	GetTitleStartBar	:	タイトル画面の下側に点滅させてるポリゴンを取得する関数
	static Polygon2D* GetTitleStartBar();
	//@Summary	GetFade	:	フェード処理を取得する関数
	static Fade* GetFade();
private:
	static Polygon2D* TitleStartBar_;	//タイトル画面の下側に点滅させてるポリゴンの変数
	static Fade* fade_;	//フェード処理変数
};