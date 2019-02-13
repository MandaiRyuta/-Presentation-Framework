//****************************************************
// @file : meshfiled.cpp
// @brief: ���b�V���t�B�[���h�̍쐬
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
#pragma once
//****************************************************
// include
//****************************************************
#include "../../main.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../Entity/Entity.h"

//****************************************************
// define
//****************************************************
#define FVF_FILED ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//****************************************************
// constexpr
//****************************************************
constexpr int MeshFiledX = 100;
constexpr int MeshFiledZ = 100;
constexpr float MeshFiledXSize = 20.0f;
constexpr float MeshFiledZSize = 20.0f;

//****************************************************
// class
//****************************************************
class MeshFiled : public GameObjectManager
{
	//****************************************************
	// �����o�[�֐�
	//****************************************************
public:
	/// <summary>
	/// MeshFiled�N���X�̃R���X�g���N�^
	/// </summary>
	//****************************************************
	//* @ _Priority  : �`��D�揇�ʎw��
	//* @ _filename  : �t�@�C���p�X
	//* @ _mesh_info : ���b�V�����
	//****************************************************
	MeshFiled(Entity::MeshFiledSize _mesh_info)
		: meshinfo_(_mesh_info), GameObjectManager(0)
	{

	}

	/// <summary>
	/// MeshFiled�N���X�̃f�X�g���N�^
	/// </summary>
	~MeshFiled() {}

	/// <summary>
	/// ������
	/// </summary>
	void Init() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �J��
	/// </summary>
	void Uninit() override;

	/// <summary>
	/// Create�֐�
	/// </summary>
	//****************************************************
	// @ _meshinfo : ���b�V�����
	// @ _filename : �t�@�C���p�X
	//****************************************************
	static MeshFiled* Create(Entity::MeshFiledSize _meshinfo);

private:
	/// <summary>
	/// �o�[�e�b�N�X�o�b�t�@�̐���
	/// </summary>
	//****************************************************
	// @ _device : DirectX device
	//****************************************************
	void VertexBufferCreate(LPDIRECT3DDEVICE9 _device);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̐���
	/// </summary>
	//****************************************************
	// @ _device : DirectX device
	//****************************************************
	void IndexBufferCreate(LPDIRECT3DDEVICE9 _device);
public:
	//****************************************************
	// �Q�b�^�[
	//****************************************************

	/// <summary>
	/// ���b�V���t�B�[���h�̍����擾
	/// </summary>
	//****************************************************
	// @ _position : �Ώۂ̍��W
	//****************************************************
	float GetHeight(D3DXVECTOR3 _position);
public:
	//****************************************************
	// �Z�b�^�[
	//****************************************************
private:
	/// <summary>
	/// csv�t�@�C������ǂݍ��݃t�B�[���h�̍����ݒ�
	/// </summary>
	float FiledHeight[MeshFiledX][MeshFiledZ];

	/// <summary>
	/// �o�b�t�@
	/// </summary>
	Entity::Dx9Buffer buffer_;

	/// <summary>
	/// �e�N�X�`���[
	/// </summary>
	Entity::Textureinfomation texture_[2];

	/// <summary>
	/// �}�e���A�����
	/// </summary>
	D3DMATERIAL9 meshmaterial_;

	/// <summary>
	/// �s��̏W�܂�
	/// </summary>
	Entity::MATRIX3D matrix_;

	/// <summary>
	/// �ʒu�x�N�g��
	/// </summary>
	D3DXVECTOR3 position_;

	/// <summary>
	/// �g��x�N�g��
	/// </summary>
	D3DXVECTOR3 scale_;

	/// <summary>
	/// ��]�x�N�g��
	/// </summary>
	D3DXVECTOR3 rotation_;
	
	/// <summary>
	/// ���b�V���t�B�[���h�̏��
	/// </summary>
	Entity::VECTOR3D* mpv_;

	/// <summary>
	/// ���b�V���t�B�[���h�����i�[����\����
	/// </summary>
	Entity::MeshFiledSize meshinfo_;

	/// <summary>
	/// �o�[�e�b�N�X��
	/// </summary>
	int number_of_vertices_;

	/// <summary>
	/// �C���f�b�N�X��
	/// </summary>
	int number_of_indices_;

	/// <summary>
	/// �v���~�e�B�u��
	/// </summary>
	int number_of_primities_;

	/// <summary>
	/// X���W�̔z��
	/// </summary>
	int SetnX_;

	/// <summary>
	/// Z���W�̔z��
	/// </summary>
	int SetnZ_;
};

//----------------------------------------------------
// EOF
//----------------------------------------------------