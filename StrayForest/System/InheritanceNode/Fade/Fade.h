#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

struct FADE_VERTEX
{
	float x, y, z;
	DWORD color;
};

class Fade : public GameObjectManager
{
public:
	Fade() : GameObjectManager(2) {}
	~Fade() {}
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;
	void Update() override;

	//@Summary	BlackFadeIn	:	背景色が黒色のフェードイン関数
	void BlackFadeIn();
	//@Summary	BlackFadeOut	:	背景色が黒色のフェードアウト関数
	void BlackFadeOut();
	//@Summary	WhiteFadeIn	:	背景色が白色のフェードイン関数
	void WhiteFadeIn();
	//@Summary	WhiteFadeOut	:	背景色が白色のフェードアウト関数
	void WhiteFadeOut();
	//@Summary	GetFadeFlag	:	フェード完了したかどうかを知らせる関数
	bool GetFadeFlag();
	//@Summary	FadeSetNumber	:	どのフェードに対応させるかを設定する関数
	void FadeSetNumber(int fade);
public:
	//@Summary	Create	=	"フェード作成関数"
	static Fade* Create();
private:
	int FadeIn;	//フェードインのα値
	int FadeOut;	//フェードアウトのα値
	int FadeSet_;	//対応させるフェードの番号
	bool BlackFadeInFlag_;	//背景色が黒色のフェードインが完了したかどうか知らせる
	bool BlackFadeOutFlag_;	//背景色が黒色のフェードアウトが完了したかどうか知らせる
	bool WhiteFadeInFlag_;	//背景色が白色のフェードインが完了したか知らせる
	bool WhiteFadeOutFlag_;	//背景色が白色のフェードアウトが完了したか知らせる
};