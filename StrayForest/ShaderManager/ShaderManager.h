//****************************************************
// @file : ShaderManager.h
// @brief: Shaderの管理クラスの作成
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
#pragma once
//****************************************************
// include
//****************************************************
#include "../Entity/Entity.h"
#include <map>

//****************************************************
// class
//****************************************************
class ShaderManager
{
	//****************************************************
	// メンバー関数
	//****************************************************
public:
	/// <summary>
	/// コンストラクタ new したときに呼び出される
	/// </summary>
	ShaderManager() {}
	/// <summary>
	/// デストラクタ delete したときに呼び出され開放される
	/// </summary>
	~ShaderManager() {}

public:
	//****************************************************
	//　初期化
	//****************************************************
	static bool ShaderCompile(
		LPDIRECT3DDEVICE9 _device,
		std::string _filepath,
		std::string _VSfunction,
		std::string _VSversion,
		std::string _PSfunction,
		std::string _PSversion,
		std::string _Arrayname
	);
public:
	//****************************************************
	// ゲッター
	//****************************************************
	/// <summary>
	/// VSテーブルのゲッター
	/// </summary>
	static LPD3DXCONSTANTTABLE GetVSTable(std::string _Arrayname);
	/// <summary>
	/// PSテーブルのゲッター
	/// </summary>
	static LPD3DXCONSTANTTABLE GetPSTable(std::string _ArrayName);
	/// <summary>
	/// 頂点シェーダーのゲッター
	/// </summary>
	static LPDIRECT3DVERTEXSHADER9 GetVertexShader(std::string _Arrayname);
	/// <summary>
	/// ピクセルシェーダーのゲッター
	/// </summary>
	static LPDIRECT3DPIXELSHADER9 GetPixelShader(std::string _Arrayname);
private:
	//****************************************************
	// 変数
	//****************************************************
	static Entity::Dx9Shader shader_;
};