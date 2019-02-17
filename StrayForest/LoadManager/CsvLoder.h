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
	CsvLoder();
	~CsvLoder();

public:
	//@Summary	CsvRoad	:	読み込み専用関数
	//@ParamName	=	_filename	:	ファイルパス
	//@ParamName	=	_table	:	Vectorの2次元配列（メッシュフィールドの高さ格納引数
	//@ParamName	=	delimiter	:	マスの区切り点
	static bool CsvRead(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
	//@Summary	CsvWrite	:	書き込み専用関数
	//@ParamName	=	_filename	: ファイルパス
	//@ParamName	=	_table		: Vectorの二次元配列	(メッシュフィールドの高さ格納引数)
	//@ParamName	=	delimiter	: マスの区切り点
	//static bool CsvWrite(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
};