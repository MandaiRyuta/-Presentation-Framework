//****************************************************
// @file : CsvLoder.cpp
// @brief: Csv�t�@�C���̓ǂݍ��݁��������݃N���X���쐬
// @Date : 2018/09/25
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include 
//****************************************************
#include "CsvLoder.h"
#include "../main.h"

//****************************************************
// CSV�ǂݍ��݊֐�
//****************************************************
bool CsvLoder::CsvRead(const std::string & _filename, std::vector<std::vector<std::string>>& _table, const char delimiter)
{
	/// <summary>
	/// �t�@�C�����J��
	/// </summary>
	std::fstream filestream(_filename);
	/// <summary>
	/// �w�肵���t�@�C�����T���Ȃ��Ƃ��̃G���[����
	/// </summary>
	if (!filestream.is_open())
	{
		MessageBox(NULL, "�ΏۂƂȂ�CSV�t�@�C�����J���܂���ł���", "CsvFile is not found", MB_OK);
		PostQuitMessage(0);
		return false;
	}

	/// <summary>
	/// �t�@�C����ǂݍ���
	/// </summary>
	while (!filestream.eof())
	{
		/// <summary>
		/// Csv�t�@�C�����̈�s�ǂݍ���
		/// </summary>
		//****************************************************
		// @ buffer : ��������i�[����ϐ�
		//****************************************************
		std::string buffer;
		filestream >> buffer;

		/// <summary>
		/// �t�@�C������ǂݍ��񂾍s�̕��������؂蕶����
		/// </summary>
		//****************************************************
		// @ record : ��s���̕�����̃��X�g
		// @ streambuffer(buffer) : ������X�g���[��
		// @ token : 1�Z�����̕�����
		//****************************************************
		std::vector<std::string> record;
		std::istringstream streambuffer(buffer);
		std::string token;

		while (getline(streambuffer, token, delimiter))
		{
			/// <summary>
			/// 1�Z�����̕���������X�g�ɒǉ�����
			/// </summary>
			record.push_back(token);
		}
		/// <summary>
		/// 1�s���̕�������o�͈����̃��X�g�ɒǉ�����
		/// </summary>
		_table.push_back(record);
	}

	return true;
}

//****************************************************
// Csv�������݊֐�
//****************************************************
bool CsvLoder::CsvWrite(const std::string & _filename, std::vector<std::vector<std::string>>& _table, const char delimiter)
{
	/// <summary>
	/// ����g�p���Ȃ��ז�����
	/// </summary>
	return true;
}
