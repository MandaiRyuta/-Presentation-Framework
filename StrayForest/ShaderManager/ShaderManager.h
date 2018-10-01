//****************************************************
// @file : ShaderManager.h
// @brief: Shader�̊Ǘ��N���X�̍쐬
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
	// �����o�[�֐�
	//****************************************************
public:
	/// <summary>
	/// �R���X�g���N�^ new �����Ƃ��ɌĂяo�����
	/// </summary>
	ShaderManager() {}
	/// <summary>
	/// �f�X�g���N�^ delete �����Ƃ��ɌĂяo����J�������
	/// </summary>
	~ShaderManager() {}

public:
	//****************************************************
	//�@������
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
	// �Q�b�^�[
	//****************************************************
	/// <summary>
	/// VS�e�[�u���̃Q�b�^�[
	/// </summary>
	static LPD3DXCONSTANTTABLE GetVSTable(std::string _Arrayname);
	/// <summary>
	/// PS�e�[�u���̃Q�b�^�[
	/// </summary>
	static LPD3DXCONSTANTTABLE GetPSTable(std::string _ArrayName);
	/// <summary>
	/// ���_�V�F�[�_�[�̃Q�b�^�[
	/// </summary>
	static LPDIRECT3DVERTEXSHADER9 GetVertexShader(std::string _Arrayname);
	/// <summary>
	/// �s�N�Z���V�F�[�_�[�̃Q�b�^�[
	/// </summary>
	static LPDIRECT3DPIXELSHADER9 GetPixelShader(std::string _Arrayname);
private:
	//****************************************************
	// �ϐ�
	//****************************************************
	static Entity::Dx9Shader shader_;
};