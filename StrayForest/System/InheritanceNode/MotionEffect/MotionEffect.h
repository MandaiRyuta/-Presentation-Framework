#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

constexpr int MESHEFFECT_X = 4;
constexpr int MESHEFFECT_Y = 2;
constexpr float MESHEFFECT_SIZEX = 5.0f;
constexpr float MESHEFFECT_SIZEY = 5.0f;

class MosionEffect : public GameObjectManager
{
public:
	MosionEffect(int _priority);
	~MosionEffect();

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
	//@Summary	SetDraw	:	���[�V�����G�t�F�N�g��`�悷��Ƃ��Ɏg���֐�
	//@ParamName	=	"_isdraw"	:	�`�悷�邩���Ȃ�����I��������t���O
	static void SetDraw(bool _isdraw);
	//@Summary	CreateMotionEffect	:	���[�V�����G�t�F�N�g���쐬����
	//@ParamName	=	"_priority"	:	�`��D��x
	static MosionEffect* CreateMotionEffect(int _priority);
private:
#define FVF_MESHEFFECT	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//�����_�����O���
	D3DXVECTOR3 position_;	//���W�ϐ�
	D3DXVECTOR3 rotation_;	//��]�ϐ�
	D3DXVECTOR3 scale_;	//�g��ϐ�

	Entity::MATRIX3D mtx_;	//�S�Ă̍s�񂪊܂܂�Ă���ϐ�
	Entity::Dx9Buffer buffer_;	//�o�b�t�@
	Entity::VECTOR3D* mpv_;	//�����_�����O���ɉ������ϐ�
	
	static bool isdraw_;	//�`��t���O

	int num_of_vertices_;	//���_��
	int num_of_indices_;	//�C���f�b�N�X��
	int num_of_primites_;	//�v���~�e�B�u��
};