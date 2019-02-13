#pragma once
#include "../Entity/Entity.h"
//****************************************************
// 列挙型
//****************************************************
enum LOADTEXTURE
{
	FLOOR01,
	FLOOR02,
	FLOOR01NORMAL,
	FLOOR02NORMAL,
	SEA,
	TEX_PARTICLE,
	MOTIONEFFECT,
	STATUS,
	HP,
	MANA,
	PAUSEWAKU,
	PAUSESTART,
	PAUSEEND,
	STATUS_EMPTY,
	PAUSE,
	PAUSEBUTTON01_ON,
	PAUSEBUTTON02_ON,
	PAUSEBUTTON01_OFF,
	PAUSEBUTTON02_OFF,
	DAMEGEEFFECT01,
	ABUTTON,
	BBUTTON,
	XBUTTON,
	YBUTTON,
	ROLL,
	ATTACK,
	MAGIC,
	DEF,
	CONTROLBUTTON01,
	CONTROLBUTTON02,
	SIDEBUTTON,
	PLAYERRUN,
	TITLE_BACKGROUND,
	TITLE_BATTLEEDITION,
	TITLE_STARTBUTTON,
	TITLE_LOGO,
	CHUTORIALWORD,
	CHUTORIALDESCRIPTION,
	RESULTWINWORD,
	RESULTLOSEWORD,
	WINPOLYGONWORD,
	LOSEPOLYGONWORD,
	GAMESTARTPOLYGON,
	CHUTORIALWORD02,
	TEXTUREMAX,	//テクスチャの最大個数
};

//****************************************************
// class TextureLoder
//****************************************************
class TextureLoder
{
private:
	TextureLoder() {}
	~TextureLoder() {}
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
	/// テクスチャーデーターのゲッター
	/// </summary>
	//****************************************************
	// @ number : テクスチャナンバー
	//****************************************************
	static LPDIRECT3DTEXTURE9 GetTextureData(int _targettexture);
	static void RelaseAll();
private:
	//****************************************************
	// メンバー変数
	//****************************************************
	/// <summary>
	/// テクスチャー格納変数
	/// </summary>
	static std::vector<LPDIRECT3DTEXTURE9> texture_;
	/// <summary>
	/// テクスチャーのカウンター
	/// </summary>
	static int TextureCounter_;
};