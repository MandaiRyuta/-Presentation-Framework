#pragma once
#include "../Entity/Entity.h"

//�g����ނ��ƂɃV�F�[�_�[���킯�Ă���̂Ŕԍ���U���Ă���
enum EFFECTINFO
{
	MODEL3D,
	//INSTANCING3D,
	SKINMESH,
	STENSHILSHADOW,
	SHILED,
	SWORD,
	//PARTICLE,
	EFFECT_MAX,
};

//�V�F�[�_�[�}�l�[�W���[�N���X
class EffectShaderManager
{
private:
	EffectShaderManager() {}
	~EffectShaderManager() {}
public:
	//@Summary	EffectLoad	:	�V�F�[�_�[�̃t�@�C���p�X��ǂݍ���ŁA�f�[�^�[��ǂݍ���
	//@ParamName	=	"_filepath"		:	�t�@�C���p�X
	static void EffectLoad(std::string _filepath);
	//@Summary	GetEffect	:	�w�肵���V�F�[�_�[���Ăяo���֐�
	//@ParamName	=	"_effectnumber"	:	EFFECTINFO�̔ԍ�
	static LPD3DXEFFECT GetEffect(EFFECTINFO _effectnumber);
	//@Summary	ReleaseAll	:	�S�ẴV�F�[�_�[�̃f�[�^�J��
	static void ReleaseAll();
private:
	static std::vector<LPD3DXEFFECT> effects_;	//�V�F�[�_�[������荞�ޕϐ�
	static int effectcount_;	//�V�F�[�_�[�̔ԍ�
};