#pragma once
#include "../../System/InheritanceNode/MyEffekseer/MyEffekseer.h"
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Player/Player.h"
#include "../../System/InheritanceNode/BossMonster/BossMonster.h"

class MagicObject;
class MeshFiled;
class Polygon2D;
class MosionEffect;
class Sword;
class Shiled;
class Fade;
class SceneGame : public SceneManager
{
public:
	SceneGame() {}
	~SceneGame() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetPlayer	:	�v���C���[���擾�֐�
	static Player* GetPlayer();
	//@Summary	GetHitExplosion	:	���@�������������ɕ`�悷��G�t�F�N�g�擾�֐�
	static MyEffekseer* GetHitExplosion();
	//@Summary	GetPlayerMagicEfk	:	���@�G�t�F�N�g�擾�֐�
	static MyEffekseer* GetPlayerMagicEfk();
	//@Summary	GetPlayerAttack01Efk	:	�v���C���[�ʏ�U�����̃G�t�F�N�g�擾�֐�
	static MyEffekseer* GetPlayerAttack01Efk();
	//@Summary	GetMagicObjects	:	�r�����ɔ�яo���Ă閂�@�G�t�F�N�g�̏����擾����֐�
	//@ParamName	=	"i"	:	�r�����ɔ�яo���Ă閂�@�̔ԍ�
	static MyEffekseer* GetMagicObjects(int i);
	//@Summary	GetBossMagicAEfk	:	�{�X�̖��@�G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossMagicAEfk();
	//@Summary	GetBossMagicB_1Efk	:	�{�X�̖��@�G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossMagicB_1Efk();
	//@Summary	GetBossMagicCEfk	:	�{�X�̖��@�G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossMagicCEfk();
	//@Summary	GetBossBuffEfk	:	�w���X�������ɓG�ɕ`�悳���I�[���G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossBuffEfk();
	//@Summary	GetDamegeEffectOnEfk	:	�G�̃_���[�W�G�t�F�N�g�擾�֐�
	static MyEffekseer* GetDamegeEffectONEfk();
	//@Summary	GetBossBuff2Efk	:	�w���X�������ɓG�ɕ`�悳���I�[���G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossBuff2Efk();
	//@Summary	GetBossAttackEfk	:	�{�X�̒ʏ�U���G�t�F�N�g�擾�֐�
	static MyEffekseer* GetBossAttackEfk();
	//@Summary	GetMeshFiled	:	���b�V���t�B�[���h�擾�֐�
	static MeshFiled* GetMeshFiled();
	//@Summary	GetHealthBar	:	�v���C���[HP�o�[���擾�֐�
	static Polygon2D* GetHealthBar();
	//@Summary	GetManaBar	:	�v���C���[SP�o�[���擾�֐�
	static Polygon2D* GetManaBar();
	//@Summary	GetMotionEffect	:	�v���C���[�̌��̃��[�V�����G�t�F�N�g�擾�֐�
	static MosionEffect* GetMotionEffect();
	//@Summary	GetBossMonster	:	�{�X�����擾����֐�
	static BossMonster* GetBossMonster();
	//@Summary	GetPlayerShiled	:	���̏��擾�֐�
	static Shiled* GetPlayerShiled();
	//@Summary	GetPlayerSword	:	���̏��擾�֐�
	static Sword* GetPlayerSword();
	//@Summary	GetPuaseScreen	:	�|�[�Y���ɕ`�悷���ʏ����擾����֐�
	static Polygon2D* GetPauseScreen();
	//@Summary	GetPauseButton01ON	:	�|�[�Y���̕`�悷��|���S�������擾����֐�
	static Polygon2D* GetPauseButton01ON();
	//@Summary	GetPauseButton02ON	:	�|�[�Y���̕`�悷��|���S�������擾����֐�
	static Polygon2D* GetPauseButton02ON();
	//@Summary	GetPauseButton01OFF	:	�|�[�Y���̕`�悷��|���S�������擾����֐�
	static Polygon2D* GetPauseButton01OFF();
	//@Summary	GetPauseButton02OFF	:	�|�[�Y���̕`�悷��|���S�������擾����֐�
	static Polygon2D* GetPauseButton02OFF();
	//@Summary	GetDamegeEffect	:	�v���C���[�̃_���[�W�G�t�F�N�g�擾�֐�
	static Polygon2D* GetDamegeEffect();
	//@Summary	GetGameStartPolygon01	:	�Q�[�����J�n���ɕ`�悳���|���S�������擾����֐�
	static Polygon2D* GetGameStartPolygon01();
	//@Summary	GetGameStartPolygon02	:	�Q�[�����J�n���ɕ`�悳���|���S�������擾����֐�
	static Polygon2D* GetGameStartpolygon02();
	//@Summary	GetFade	:	�t�F�[�h���擾�֐�
	static Fade* GetFade();
	//@Summary	GetMagicEffect	:	�v���C���[�̖��@�G�t�F�N�g�����擾����֐�
	static MagicObject* GetMagicEffect();
private:
	static MagicObject* magic_;	//�v���C���[�̖��@�ϐ�
	static Player* player_;	//�v���C���[�ϐ�
	static BossMonster* boss_;	//�{�X�ϐ�
	static MeshFiled* meshfiled_;	//���b�V���t�B�[���h�ϐ�
	static MosionEffect* motioneffect_;	//���[�V�����G�t�F�N�g�ϐ��i���ɑΉ�)
	static MyEffekseer* HitExplosion_;	//�v���C���[�̖��@���G�ɓ����������ɕ`�悳���G�t�F�N�g�ϐ�
	static MyEffekseer* MagicObjects[10];	//�v���C���[�̖��@�I�u�W�F�N�g�ϐ�
	static MyEffekseer* PlayerMagicEfk_;	//�v���C���[�̖��@�r�����ɕ`�悳���G�t�F�N�g�̕ϐ�
	static MyEffekseer* PlayerAttack01Efk_;	//�v���C���[�̒ʏ�U���̃G�t�F�N�g�ϐ�
	static MyEffekseer* BossMonsterMagicAEfk_;	//�{�X�̖��@�G�t�F�N�g
	static MyEffekseer* BossMonsterMagicB_1Efk_;	//�{�X�̖��@�G�t�F�N�g
	static MyEffekseer* BossMonsterMagicCEfk_;	//�{�X�̖��@�G�t�F�N�g
	static MyEffekseer* BossMonsterBuffEfk_;	//�{�X�̏�Ԃɂ���ĕ`�悳���I�[���G�t�F�N�g�ϐ�
	static MyEffekseer* GetDamegeEffectONEfk_;	//�{�X���U���󂯂��ۂɕ`�悳���G�t�F�N�g�ϐ�
	static MyEffekseer* BossMonsterBuff2Efk_;	//�{�X�̏�Ԃɂ���ĕ`�悳���I�[���G�t�F�N�g�ϐ�
	static MyEffekseer* BossAttackEfk_;	//�{�X�̍U�������������ۂɕ`�悳���G�t�F�N�g�ϐ�
	static Polygon2D* DamegeEffect_;	//�v���C���[��������ȉ��̃w���X�ɂȂ�Ɖ�ʑS�̂ɕ`�悳���G�t�F�N�g�ϐ�
	static Polygon2D* HealthBar_;	//�v���C���[��HP�o�[�ϐ�
	static Polygon2D* ManaBar_;	//�v���C���[��SP�o�[�ϐ�
	static Polygon2D* PauseScreen_;	//�|�[�Y�`��ϐ�
	static Polygon2D* PauseButtonOn01_;	//�|�[�Y���ɑI������|���S���̕ϐ�
	static Polygon2D* PauseButtonOn02_;	//�|�[�Y���ɑI������|���S���̕ϐ�
	static Polygon2D* PauseButtonOff01_;	//�|�[�Y���ɑI������|���S���̕ϐ�
	static Polygon2D* PauseButtonOff02_;	//�|�[�Y���ɑI������|���S���̕ϐ�
	static Polygon2D* GameStartPolygon01_;	//�Q�[���J�n�O�ɕ`�悳���|���S���̕ϐ�
	static Polygon2D* GameStartPolygon02_;	//�Q�[���J�n�O�ɕ`�悳���|���S���̕ϐ�
	static Sword* sword_;	//�����f���̕ϐ�
	static Shiled* shiled_;	//�����f���̕ϐ�
	static Fade* fade_;	//�t�F�[�h�ϐ�
};