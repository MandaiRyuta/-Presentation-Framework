//****************************************************
// @file : CsvLoder.h
// @brief: Csv�t�@�C���̓ǂݍ��݁��������݃N���X���쐬
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
	// �����o�[�֐�
	//****************************************************s
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CsvLoder();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CsvLoder();

public:
	/// <summary>
	/// �ǂݍ��ݐ�p�֐�
	/// </summary>
	//****************************************************
	// @ _filename	: �t�@�C���p�X
	// @ _table		: Vector�̓񎟌��z��	(���b�V���t�B�[���h�̍����i�[����)
	// @ delimiter	: �}�X�̋�؂�_
	//****************************************************
	static bool CsvRead(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
	/// <summary>
	/// �������ݐ�p�֐�
	/// </summary>
	//****************************************************
	// @ _filename	: �t�@�C���p�X
	// @ _table		: Vector�̓񎟌��z��	(���b�V���t�B�[���h�̍����i�[����)
	// @ delimiter	: �}�X�̋�؂�_
	//****************************************************
	//static bool CsvWrite(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
};