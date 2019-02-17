#pragma once
#include "../SceneManager.h"

class MeshFiled;
class LosePlayer;
class Fade;
class Polygon2D;
class PolygonColorChanger;

class SceneLoseResult : public SceneManager
{
public:
	SceneLoseResult() {}
	~SceneLoseResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetMeshFiled	:	���b�V���t�B�[���h���擾����֐�	
	static MeshFiled* GetMeshFiled();
	//@Summary	GetLostPlayer	:	�v���C���[���擾����֐�
	static LosePlayer* GetLostPlayer();
	//@Summary	GetFade	:	�t�F�[�h�������擾����֐�
	static Fade* GetFade();
	//@Summary	GetSepiaPolygon	:	�Z�s�A���ɐݒ肷��|���S���̎擾�֐�
	static Polygon2D* GetSepiaPolygon();
	//@Summary	GetGameOverPolygon	:	�Q�[���I�[�o�[��\������|���S���̎擾�֐�
	static Polygon2D* GetGameOverPolygon();
	//@Summary	GetPressButtonPolygon	:	�X�^�[�g�{�^����������`�悷��|���S���̎擾�֐�
	static Polygon2D* GetPressButtonPolygon();
	//@Summary	GetSepiaFlag	:	�Z�s�A���ɂȂ��Ă��邩�m�F���邽�߂̃t���O�֐�
	static bool GetSepiaFlag();
	//@Summary	SetSepiaFlag	:	�Z�s�A���ɐݒ肷�邽�߂̃t���O�֐�
	//@ParamName	=	"_flag"	;	�Z�s�A���ɂ��邩���Ȃ������w�肷��
	static void SetSepiaFlag(bool _flag);
	//@Summary	GetGameOverFlag	:	�v���C���[�̐^�ォ��J�������ڂ��悤�ɂȂ����Ƃ��ɁA�t���O��؂�ւ��ăZ�s�A���Ƀ|���S����ݒ肷�邽�߂̃t���O�֐�
	static bool GetGameOverFlag();
	//@Summary	SetGameOverFlag	:	�Q�[���I�[�o�[�̎��ɕ`�悷��ݒ�ɐ؂�ւ���t���O�ݒ�֐�
	//@ParamName	=	"_flag"	:	�؂�ւ��邩�؂�ւ��Ȃ������w�肷��t���O
	static void SetGameOverFlag(bool _flag);
private:
	static MeshFiled* LostResultMeshFiled_;	//���b�V���t�B�[���h�ϐ�
	static LosePlayer* LostResultPlayer_;	//�v���C���[�ϐ�
	static Fade* fade_;	//�t�F�[�h�����ϐ�
	static Polygon2D* SepiaPolygon_;	//�Z�s�A���ɐ؂�ւ���|���S���̕ϐ�
	static Polygon2D* GameOverPolygon_;	//�Q�[���I�[�o�[��\������|���S���̕ϐ�
	static Polygon2D* PressButtonWord_;	//�X�^�[�g�{�^����������`�悷��|���S���̕ϐ�
	static bool SepiaColorFlag_;	//�Z�s�A���ɐ؂�ւ��邽�߂̃t���O�ϐ�
	static bool GameOverDrawFlag_;	//�Q�[���I�[�o�[��`�悳���邽�߂̃t���O�ϐ�
};