//****************************************************
// @file : CsvLoder.h
// @brief: Csvファイルの読み込み＆書き込みクラスを作成
// @Date : 2018/09/25
// @author:Mandai Ryuta
//****************************************************
#pragma once
//****************************************************
// include
//****************************************************
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
//****************************************************
// class
//****************************************************
class CsvLoder
{
	//****************************************************
	// メンバー関数
	//****************************************************s
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CsvLoder();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CsvLoder();

public:
	/// <summary>
	/// 読み込み専用関数
	/// </summary>
	//****************************************************
	// @ _filename	: ファイルパス
	// @ _table		: Vectorの二次元配列	(メッシュフィールドの高さ格納引数)
	// @ delimiter	: マスの区切り点
	//****************************************************
	static bool CsvRead(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
	/// <summary>
	/// 書き込み専用関数
	/// </summary>
	//****************************************************
	// @ _filename	: ファイルパス
	// @ _table		: Vectorの二次元配列	(メッシュフィールドの高さ格納引数)
	// @ delimiter	: マスの区切り点
	//****************************************************
	//static bool CsvWrite(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
};