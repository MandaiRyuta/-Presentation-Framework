//****************************************************
// @file : ShaderManager.cpp
// @brief: Shaderの管理クラスの作成
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include
//****************************************************
#include "ShaderManager.h"

Entity::Dx9Shader ShaderManager::shader_;
//****************************************************
// シェーダーコンパイル
//****************************************************
//****************************************************
// @ _device : デバイス
// @ _filepath : ファイルパス
// @ _VSfunction : 頂点シェーダー関数
// @ _VSversion : 頂点シェーダーバージョン
// @ _PSfunction : ピクセルシェーダー関数
// @ _PSversion : ピクセルシェーダーバージョン
// @ _Arrayname : 配列の名前　(map用)
//****************************************************
bool ShaderManager::ShaderCompile(LPDIRECT3DDEVICE9 _device, std::string _filepath, std::string _VSfunction, std::string _VSversion, std::string _PSfunction, std::string _PSversion, std::string _Arrayname)
{
	/// <summary>
	/// エラーコード
	/// </summary>
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code;

	/// <summary>
	/// エラーチェック
	/// </summary>
	HRESULT hr;
	/// <summary>
	/// 頂点シェーダをコンパイル
	/// </summary>
	//****************************************************
	// @ _filepath.c_str() : ファイルパス
	// @ _VSFunction._c_str() : 頂点シェーダーの関数名
	// @ _VSversion.c_str() : 頂点シェーダーのバージョン
	// @ code : コンパイル済みのシェーダーコード(OUT)
	// @ err : コンパイルエラー情報が格納される(OUT)
	// @ VSConstantTable_ : シェーダー内のコンスタントテーブル
	//****************************************************
	hr = D3DXCompileShaderFromFile(
		_filepath.c_str(),
		nullptr,
		nullptr,
		_VSfunction.c_str(),
		_VSversion.c_str(),
		0,
		&code,
		&err,
		&shader_.VSConstantTable_[_Arrayname.c_str()]
	);

	/// <summary>
	/// シェーダーコンパイルエラー確認処理
	/// </summary>
	if (FAILED(hr))
	{
		if (err)
		{
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else
		{
			MessageBox(NULL, "シェーダーファイルが読み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	/// <summary>
	/// 頂点シェーダーオブジェクトを作成する
	/// </summary>
	//****************************************************
	// @ code : コンパイル済みシェーダーコード(IN)
	// @ vertexshader_ : 頂点シェーダー変数
	//****************************************************
	hr = _device->CreateVertexShader(
		(DWORD*)code->GetBufferPointer(),
		&shader_.vertexshader_[_Arrayname.c_str()]
	);
	/// <summary>
	/// エラー処理
	/// </summary>
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreateVertexShader", MB_OK);
	}

	/// <summary>
	/// コンパイル済みコードからピクセルシェーダをコンパイル
	/// </summary>
	//****************************************************
	// @ _filepath : ファイルパス
	// @ _PSfunction.c : ピクセルシェーダー関数名
	// @ _PSversion :
	//****************************************************
	hr = D3DXCompileShaderFromFile(
		_filepath.c_str(),
		nullptr,
		nullptr,
		_PSfunction.c_str(),
		_PSversion.c_str(),
		0,
		&code,
		&err,
		&shader_.PSConstantTable_[_Arrayname.c_str()]
	);

	/// <summary>
	/// エラー発生確認処理
	/// </summary>
	if (FAILED(hr))
	{
		/// <summary>
		/// コンパイルエラーあり
		/// </summary>
		if (err)
		{
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		/// <summary>
		/// その他のエラー
		/// </summary>
		else
		{
			MessageBox(NULL, "シェーダーファイルが読み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}

		return false;
	}

	/// <summary>
	/// コンパイル済みコードからピクセルシェーダーオブジェクトを作成する
	/// </summary>
	//****************************************************
	// @ code : コンパイル済みシェーダーコード
	// @ pixelshader_ : ピクセルシェーダー (OUT)
	//****************************************************
	hr = _device->CreatePixelShader(
		(DWORD*)code->GetBufferPointer(),
		&shader_.pixelshader_[_Arrayname.c_str()]
	);

	return true;
}

//****************************************************
// 頂点シェーダーテーブルのゲッター
//****************************************************
//****************************************************
// @ _Arrayname : mapの配列名
//****************************************************
LPD3DXCONSTANTTABLE ShaderManager::GetVSTable(std::string _Arrayname)
{
	/// <summary>
	/// 頂点シェーダーコンスタントテーブルを呼び出し先に渡す
	/// </summary>
	return shader_.VSConstantTable_[_Arrayname.c_str()];
}

//****************************************************
// ピクセルシェーダーテーブルのゲッター
//****************************************************
//****************************************************
// @ _Arrayname : mapの配列名
//****************************************************
LPD3DXCONSTANTTABLE ShaderManager::GetPSTable(std::string _ArrayName)
{
	/// <summary>
	/// ピクセルシェーダーコンスタントテーブルを呼び出し先に渡す
	/// </summary>
	return shader_.PSConstantTable_[_ArrayName.c_str()];
}

//****************************************************
// 頂点シェーダーのゲッター
//****************************************************
//****************************************************
// @ _Arrayname : mapの配列名
//****************************************************
LPDIRECT3DVERTEXSHADER9 ShaderManager::GetVertexShader(std::string _Arrayname)
{
	/// <summary>
	/// 頂点シェーダーを呼び出し先に渡す
	/// </summary>
	return shader_.vertexshader_[_Arrayname.c_str()];
}

//****************************************************
// ピクセルシェーダーのゲッター
//****************************************************
//****************************************************
// @ _Arrayname : mapの配列名
//****************************************************
LPDIRECT3DPIXELSHADER9 ShaderManager::GetPixelShader(std::string _Arrayname)
{
	/// <summary>
	/// ピクセルシェーダーを呼び出し先に渡す
	/// </summary>
	return shader_.pixelshader_[_Arrayname.c_str()];
}
