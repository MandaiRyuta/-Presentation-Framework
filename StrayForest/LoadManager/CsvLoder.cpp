//****************************************************
// @file : CsvLoder.cpp
// @brief: Csvファイルの読み込み＆書き込みクラスを作成
// @Date : 2018/09/25
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include 
//****************************************************
#include "CsvLoder.h"
#include "../main.h"

//****************************************************
// CSV読み込み関数
//****************************************************
bool CsvLoder::CsvRead(const std::string & _filename, std::vector<std::vector<std::string>>& _table, const char delimiter)
{
	/// <summary>
	/// ファイルを開く
	/// </summary>
	std::fstream filestream(_filename);
	/// <summary>
	/// 指定したファイルが探せないときのエラー処理
	/// </summary>
	if (!filestream.is_open())
	{
		MessageBox(NULL, "対象となるCSVファイルを開けませんでした", "CsvFile is not found", MB_OK);
		PostQuitMessage(0);
		return false;
	}

	/// <summary>
	/// ファイルを読み込む
	/// </summary>
	while (!filestream.eof())
	{
		/// <summary>
		/// Csvファイル内の一行読み込み
		/// </summary>
		//****************************************************
		// @ buffer : 文字列を格納する変数
		//****************************************************
		std::string buffer;
		filestream >> buffer;

		/// <summary>
		/// ファイルから読み込んだ行の文字列を区切り文字で
		/// </summary>
		//****************************************************
		// @ record : 一行分の文字列のリスト
		// @ streambuffer(buffer) : 文字列ストリーム
		// @ token : 1セル分の文字列
		//****************************************************
		std::vector<std::string> record;
		std::istringstream streambuffer(buffer);
		std::string token;

		while (getline(streambuffer, token, delimiter))
		{
			/// <summary>
			/// 1セル分の文字列をリストに追加する
			/// </summary>
			record.push_back(token);
		}
		/// <summary>
		/// 1行分の文字列を出力引数のリストに追加する
		/// </summary>
		_table.push_back(record);
	}

	return true;
}

//****************************************************
// Csv書き込み関数
//****************************************************
bool CsvLoder::CsvWrite(const std::string & _filename, std::vector<std::vector<std::string>>& _table, const char delimiter)
{
	/// <summary>
	/// 今回使用しない為未実装
	/// </summary>
	return true;
}
