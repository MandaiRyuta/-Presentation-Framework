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
	CsvLoder();
	~CsvLoder();

public:
	//@Summary	CsvRoad	:	�ǂݍ��ݐ�p�֐�
	//@ParamName	=	_filename	:	�t�@�C���p�X
	//@ParamName	=	_table	:	Vector��2�����z��i���b�V���t�B�[���h�̍����i�[����
	//@ParamName	=	delimiter	:	�}�X�̋�؂�_
	static bool CsvRead(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
	//@Summary	CsvWrite	:	�������ݐ�p�֐�
	//@ParamName	=	_filename	: �t�@�C���p�X
	//@ParamName	=	_table		: Vector�̓񎟌��z��	(���b�V���t�B�[���h�̍����i�[����)
	//@ParamName	=	delimiter	: �}�X�̋�؂�_
	//static bool CsvWrite(const std::string& _filename, std::vector<std::vector<std::string>>& _table, const char delimiter = ',');
};