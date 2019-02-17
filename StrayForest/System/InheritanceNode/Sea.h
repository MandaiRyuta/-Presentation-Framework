#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

//****************************************************
// constexpr
//****************************************************
constexpr int WAVE_X = 100;
constexpr int WAVE_Z = 100;
constexpr float WAVE_XSize = 20.0f;
constexpr float WAVE_ZSize = 20.0f;
//****************************************************
// define
//****************************************************
#define FVF_WAVE ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Sea : public GameObjectManager
{
public:
	Sea() : GameObjectManager(0) {}
	~Sea() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
	//@Summary	Create	:	�C���쐬����
	static Sea* Create();
private:
	Entity::MeshFiledSize meshinfo_;	//���b�V���t�B�[���h���
	Entity::Dx9Buffer buffer_;	//�o�b�t�@
	Entity::VECTOR3D* mpv_;	//�`����
	Entity::MATRIX3D matrix_;	//�S�Ă̍s����

	LPDIRECT3DTEXTURE9 texture;	//�e�N�X�`���[���
	LPDIRECT3DTEXTURE9 bumptexture;	//�o���v�}�b�v
	LPDIRECT3DVERTEXDECLARATION9 pDecl_;	//�f�J�[��
	
	int number_of_vertices_;	//���_���
	int number_of_indices_;	//�C���f�b�N�X���
	int number_of_primities_;	//�v���~�e�B�u���

	int SetnX;	//X
	int SetnZ;	//Z

	DWORD	m_gtime;	//����

	float Kx[2];	//�g�̕���(X�����j
	float Kz[2];	//�g�̕���(Z����)
	float wlen[2];	//�g�̒���
	float k[2];	//�g�̒������v���v�Z
	float amp[2];	//�g�̑傫���E���˂�
	float w[2];	//�g�̂��˂�̂͂₳
	float freq;	//�g�̎���
};