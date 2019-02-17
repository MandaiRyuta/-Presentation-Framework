#pragma once
#include "../SceneManager.h"
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../../System/InheritanceNode/Player/ChutorialPlayer.h"
#include "../../System/InheritanceNode/BossMonster/ChutorialBoss.h"
#include "../../System/InheritanceNode/MagicObject/MagicObject.h"

class MeshFiled;
class Polygon2D;
class Sword;
class Shiled;
class Fade;

class SceneChutorial : public SceneManager
{
public:
	SceneChutorial() {}
	~SceneChutorial() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary GetMeshFiled	:	���b�V���t�B�[���h�̏����擾����֐�
	static MeshFiled* GetMeshFiled();
	//@Summary	GetChutorialPlayer	:	�`���[�g���A���̃v���C���[���擾�֐�
	static ChutorialPlayer* GetChutorialPlayer();
	//@Summary	GetChutorialBoss	:	�`���[�g���A���̃{�X���擾�֐�
	static ChutorialBoss* GetChutorialBoss();
	//@Summary	GetExplosion	:	�����G�t�F�N�g���̎擾�֐�
	static MyEffekseer* GetExplosion();
	//@Summary	GetMagicObject	:	���@�I�u�W�F�N�g���擾����֐�
	//@ParamName	=	"num"	:	���ڂ̖��@�I�u�W�F�N�g�����w��
	static MyEffekseer* GetMagicObject(int num);
	//@Summary	GetPlayerMagicEfk	:	���@�w�G�t�F�N�g�̏��擾�֐�
	static MyEffekseer* GetPlayerMagicEfk();
	//@Summary	GetPlayerAttackEfk	:	�U���G�t�F�N�g�̏��擾�֐�
	static MyEffekseer* GetPlayerAttackEfk();
	//@Summary	GetLeftcontroller	:	�|���S���ō�������X�e�B�b�N���������������擾����֐�
	static Polygon2D* GetLeftController();
	//@Summary	GetRightcontroller	:	�|���S���ō�����E�X�e�B�b�N���������������擾����֐�
	static Polygon2D* GetRightController();
	//@Summary	GetSwordModel	:	���̃��f�������擾����֐�
	static Sword* GetSwordModel();
	//@Summary	GetShiledModel	:	���̃��f�������擾����֐�
	static Shiled* GetShiledModel();
	//@Summary	GetFade	:	�t�F�[�h�����擾����֐�
	static Fade* GetFade();
	//@Summary	GetMagic	:	�S�Ă̖��@�����擾����֐�
	static MagicObject* GetMagic();
private:
	static ChutorialBoss* chutorialboss_;	//�{�X�̕ϐ�
	static ChutorialPlayer* chutorialplayer_;	//�v���C���[�̕ϐ�
	static MeshFiled* meshfiled_;	//���b�V���t�B�[���h�̕ϐ�
	static MyEffekseer* ChutorialHitExplosion_;	//���@���G�ɓ����������̃G�t�F�N�g�ϐ�
	static MyEffekseer* ChutorialMagicObjects[10];	//���@�I�u�W�F�N�g�ϐ�
	static MyEffekseer* ChutorialPlayerMagicEfk_;	//���@�G�t�F�N�g�ϐ�
	static MyEffekseer* ChutorialPlayerAttack01Efk_;	//�U���G�t�F�N�g�ϐ�
	static MagicObject* magic_;	//�S�Ă̖��@�I�u�W�F�N�g���Ǘ����Ă���ϐ�
	static Polygon2D* LeftController_;	//���X�e�B�b�N�p�̃|���S���ϐ�
	static Polygon2D* RightController_;	//�E�X�e�B�b�N�p�̃|���S���ϐ�

	static Sword* chutorialsword_;	//�����f���̕ϐ�
	static Shiled* chutorialshiled_;	//�����f���̕ϐ�
	static Fade* fade_;	//�t�F�[�h�����ϐ�
};