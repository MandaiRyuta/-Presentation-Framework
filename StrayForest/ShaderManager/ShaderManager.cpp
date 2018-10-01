//****************************************************
// @file : ShaderManager.cpp
// @brief: Shader�̊Ǘ��N���X�̍쐬
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include
//****************************************************
#include "ShaderManager.h"

Entity::Dx9Shader ShaderManager::shader_;
//****************************************************
// �V�F�[�_�[�R���p�C��
//****************************************************
//****************************************************
// @ _device : �f�o�C�X
// @ _filepath : �t�@�C���p�X
// @ _VSfunction : ���_�V�F�[�_�[�֐�
// @ _VSversion : ���_�V�F�[�_�[�o�[�W����
// @ _PSfunction : �s�N�Z���V�F�[�_�[�֐�
// @ _PSversion : �s�N�Z���V�F�[�_�[�o�[�W����
// @ _Arrayname : �z��̖��O�@(map�p)
//****************************************************
bool ShaderManager::ShaderCompile(LPDIRECT3DDEVICE9 _device, std::string _filepath, std::string _VSfunction, std::string _VSversion, std::string _PSfunction, std::string _PSversion, std::string _Arrayname)
{
	/// <summary>
	/// �G���[�R�[�h
	/// </summary>
	LPD3DXBUFFER err = NULL;
	LPD3DXBUFFER code;

	/// <summary>
	/// �G���[�`�F�b�N
	/// </summary>
	HRESULT hr;
	/// <summary>
	/// ���_�V�F�[�_���R���p�C��
	/// </summary>
	//****************************************************
	// @ _filepath.c_str() : �t�@�C���p�X
	// @ _VSFunction._c_str() : ���_�V�F�[�_�[�̊֐���
	// @ _VSversion.c_str() : ���_�V�F�[�_�[�̃o�[�W����
	// @ code : �R���p�C���ς݂̃V�F�[�_�[�R�[�h(OUT)
	// @ err : �R���p�C���G���[��񂪊i�[�����(OUT)
	// @ VSConstantTable_ : �V�F�[�_�[���̃R���X�^���g�e�[�u��
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
	/// �V�F�[�_�[�R���p�C���G���[�m�F����
	/// </summary>
	if (FAILED(hr))
	{
		if (err)
		{
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else
		{
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǂݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}
	/// <summary>
	/// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	/// </summary>
	//****************************************************
	// @ code : �R���p�C���ς݃V�F�[�_�[�R�[�h(IN)
	// @ vertexshader_ : ���_�V�F�[�_�[�ϐ�
	//****************************************************
	hr = _device->CreateVertexShader(
		(DWORD*)code->GetBufferPointer(),
		&shader_.vertexshader_[_Arrayname.c_str()]
	);
	/// <summary>
	/// �G���[����
	/// </summary>
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "CreateVertexShader", MB_OK);
	}

	/// <summary>
	/// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_���R���p�C��
	/// </summary>
	//****************************************************
	// @ _filepath : �t�@�C���p�X
	// @ _PSfunction.c : �s�N�Z���V�F�[�_�[�֐���
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
	/// �G���[�����m�F����
	/// </summary>
	if (FAILED(hr))
	{
		/// <summary>
		/// �R���p�C���G���[����
		/// </summary>
		if (err)
		{
			MessageBox(NULL, (LPSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		/// <summary>
		/// ���̑��̃G���[
		/// </summary>
		else
		{
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǂݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}

		return false;
	}

	/// <summary>
	/// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	/// </summary>
	//****************************************************
	// @ code : �R���p�C���ς݃V�F�[�_�[�R�[�h
	// @ pixelshader_ : �s�N�Z���V�F�[�_�[ (OUT)
	//****************************************************
	hr = _device->CreatePixelShader(
		(DWORD*)code->GetBufferPointer(),
		&shader_.pixelshader_[_Arrayname.c_str()]
	);

	return true;
}

//****************************************************
// ���_�V�F�[�_�[�e�[�u���̃Q�b�^�[
//****************************************************
//****************************************************
// @ _Arrayname : map�̔z��
//****************************************************
LPD3DXCONSTANTTABLE ShaderManager::GetVSTable(std::string _Arrayname)
{
	/// <summary>
	/// ���_�V�F�[�_�[�R���X�^���g�e�[�u�����Ăяo����ɓn��
	/// </summary>
	return shader_.VSConstantTable_[_Arrayname.c_str()];
}

//****************************************************
// �s�N�Z���V�F�[�_�[�e�[�u���̃Q�b�^�[
//****************************************************
//****************************************************
// @ _Arrayname : map�̔z��
//****************************************************
LPD3DXCONSTANTTABLE ShaderManager::GetPSTable(std::string _ArrayName)
{
	/// <summary>
	/// �s�N�Z���V�F�[�_�[�R���X�^���g�e�[�u�����Ăяo����ɓn��
	/// </summary>
	return shader_.PSConstantTable_[_ArrayName.c_str()];
}

//****************************************************
// ���_�V�F�[�_�[�̃Q�b�^�[
//****************************************************
//****************************************************
// @ _Arrayname : map�̔z��
//****************************************************
LPDIRECT3DVERTEXSHADER9 ShaderManager::GetVertexShader(std::string _Arrayname)
{
	/// <summary>
	/// ���_�V�F�[�_�[���Ăяo����ɓn��
	/// </summary>
	return shader_.vertexshader_[_Arrayname.c_str()];
}

//****************************************************
// �s�N�Z���V�F�[�_�[�̃Q�b�^�[
//****************************************************
//****************************************************
// @ _Arrayname : map�̔z��
//****************************************************
LPDIRECT3DPIXELSHADER9 ShaderManager::GetPixelShader(std::string _Arrayname)
{
	/// <summary>
	/// �s�N�Z���V�F�[�_�[���Ăяo����ɓn��
	/// </summary>
	return shader_.pixelshader_[_Arrayname.c_str()];
}
