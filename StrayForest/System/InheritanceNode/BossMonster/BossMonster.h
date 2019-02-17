#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../Entity/Entity.h"
#include "../../colision/SphereColision.h"

class BossStatusManager;
class BossMonsterAttackPattern;
class BossMonsterMagicPattern;
class BossMonsterPattern;
class SphereColision;

//@Summary : �Q�[���I�u�W�F�N�g�}�l�[�W���[���p�������{�X�����X�^�[�N���X
class BossMonster : public GameObjectManager
{
public:
	//@ParamName ="_Max_Life" : �ő�HP
	//@ParamName ="_Max_Mana" : �ő�SP
	BossMonster(float _Max_Life, float _Max_Mana);
	~BossMonster() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	//@Summary	Damage	:	�_���[�W�ƃm�b�N�o�b�N�ʂ�ݒ肷��֐�
	//@ParamName ="_damage" : �_���[�W��
	//@ParamName ="knockback" : �m�b�N�o�b�N��
	void Damage(float _damage, D3DXVECTOR3 _knockback);
	//@Summary	SetPosition	:	�ʒu��ݒ肷��֐�	
	//@ParamName ="_pos" : �ʒu�ݒ�l
	void SetPosition(D3DXVECTOR3 _pos);
	//@Summary	SetRotation	:	��]��ݒ肷��ׂ̊֐�
	//@ParamName = "_rotation" : ��]�ݒ�l
	void SetRotation(float _rotation);
	//@Summary	SetMoveFlagOn : �ړ��t���O��ON�ɂ��Ė��@�𔭓������Ȃ����߂̊֐�
	void SetMoveFlagON();
	//@Summary	SetMagicCoolTime	:	���@�̃N�[���^�C����ݒ肷��֐�
	//@ParamName = "_MagicCoolTime"	:	���@�̃N�[���^�C���l
	void SetMagicCoolTime(int _MagicCoolTime);
	//@Summary	SetMagicPositionFlag	:	���@�r�����ɍ��W����荞�ވׂ̃t���O
	//@ParamName	=	"_SetMagicPositionFlag"	:	�r�������Ă��邩���ĂȂ���
	void SetMagicPositionFlag(bool _SetMagicPositionFlag);
	//@Summary SetCameraMoveFlag	:	�Q�[���V�[���̊J�n���ɃJ�����Ɖ��o�����邪�A���o�܂ŏI��������Ƀt���O��؂�ւ���֐�
	//@ParamName = "_cameraflag"	:	�J�����≉�o���I��邱�Ƃ�m�点��t���O
	void SetCameraMoveFlag(bool _cameraflag);
	//@Summary	SetKnockBackFlag	:	�m�b�N�o�b�N�������邽�߂̊֐�
	//@ParamName = "_knockbackflag"		:	�m�b�N�o�b�N�����邩�����Ȃ���
	void SetKnockBackFlag(bool _knockbackflag);
	//@Summary	SstAxisMove	:	���ݒ�֐�
	//@ParamName	=	"_AxisMove"	:	XYZ���ݒ萔�l
	void SetAxisMove(D3DXVECTOR3 _AxisMove);
public:
	//@Summary	ChangeBossMonsterMovePattern	:	�ړ��p�^�[�����������N���X���Z�b�g����֐�
	//@ParamName	=	"_pattern"	:	�p�^�[���ԍ�
	//@ParamName	=	"_bossmonsterpattern"	:	���̃{�X�̈ړ��p�^�[���N���X
	void ChangeBossMonsterMovePattern(int _pattern, BossMonsterPattern* _bossmonsterpattern);
	//@Summary	ChangeBossMonsterMagicPattern	:	���@�p�^�[�����������N���X���Z�b�g����֐�
	//@ParamName	=	"_bossmonstermagicpattern"	:	���̖��@�p�^�[���N���X	
	void ChangeBossMonsterMagicPattern(BossMonsterMagicPattern* _bossmonstermagicpattern);
	//@Summary	ChangeBossMonsterAttackPattern	:	�U���p�^�[�����������N���X���Z�b�g����֐�
	//@ParamName	=	"_bossmonsterattackpattern"	:	���̍U���p�^�[���N���X
	void ChangeBossMonsterAttackPattern(BossMonsterAttackPattern* _bossmonsterattackpattern);
public:
	//@Summary	GetAxisMove	:	�ړ����̃Q�b�^�[
	D3DXVECTOR3 GetAxisMove();
	//@Summary	GetMagicPositionFlag	:	�ł����ވʒu���擾�������m�F����t���O���擾�֐�
	bool GetMagicPositionFlag();
	//@Summary	GetMagicFlag	:	���@�̎g�p�t���O���擾����֐�
	bool GetMagicFlag();
	//@Summary	GetMoveFlag		:	�ړ��t���O���擾����֐�
	bool GetMoveFlag();
	//@Summary	GetCameraMoveFlag	:	�J�������o�̏�ԃt���O���擾����֐�
	bool GetCameraMoveFlag();
	//@Summary	GetknockbackFlag	:	�m�b�N�o�b�N�̃t���O���擾����֐�
	bool GetknockbackFlag();
	//@Summary	Getknockback	:	�m�b�N�o�b�N�ʂ��擾����֐�
	D3DXVECTOR3 Getknockback();
	//@Summary	GetMagicCoolTime	:	���@�N�[���^�C�����擾����֐�
	int GetMagicCoolTime();
	//@Summary	GetLife		:	HP�̒l���擾����֐�
	const float GetLife() const { return life_; }
	//@Summary	GetMana		:	SP�̒l���擾����֐�
	const float GetMana() const { return mana_; }
	//@Summary	GetMaxLife	:	�ő�HP���擾����֐�
	const float GetMaxLife() const { return max_life_; }
	//@Summary	GetMaxMana	:	�ő�SP���擾����֐�
	const float GetMaxMana() const { return max_mana_; }
	//@Summary	GetPosition	:	�ʒu�擾�֐�
	static D3DXVECTOR3 GetPosition();
	//@Summary	GetRotation	:	��]�擾�֐�
	static D3DXMATRIX GetRotation() { return GetRotation_; }
	//@Summary	GetPositionMatrix	:	��]�s��擾�֐�
	D3DXMATRIX& GetPositionMatrix();
	//@Summary	GetSkinMesh	:	�X�L�����b�V���擾�֐�
	CSkinMesh* GetSkinMesh();
	//@Summary	GetMoveLowSpeed	:	���擾�֐�
	float& GetMoveLowSpeed();
	//@Summary	GetMoveHighSpeed	:	���x�擾�֐�
	float& GetMoveHighSpeed();
	//@Summary	GetMoveMiddleSpeed	:	���x�擾�֐�
	float& GetMoveMiddleSpeed();
	//@Summary	GetMoveVariableSpeed	:	���x�擾�֐�
	float& GetMoveVariableSpeed();
	//@Summary	GetMoveColisionCheck	:	�Փ˔�����擾����֐�
	bool GetMoveColisionCheck();
	//@Summary	GetStatusNum	:	��Ԃ��擾����֐�
	int GetStateNum();
	//@Summary	GetAttackState	:	�U���̏�ԃt���O���擾����
	bool GetAttackState();
	//@Summary	GetAttackState	:	�U���̏�ԃt���O���Z�b�g����
	//@ParamName	=	"_attack"	:	�U���̏�ԃt���O
	void SetAttackState(bool _attack);
	//@Summary	GetMagicState	:	���@�U���̏�ԃt���O���擾����
	bool GetMagicState();
	//@Summary	GetMagicState	:	���@�U���̏�ԃt���O���Z�b�g����
	//@ParamName	=	"_magicstate"	:	���@�U���̏�ԃt���O
	void SetMagicState(bool _magicstate);
public:
	//@Summary	Position	:	�ʒu���擾�֐��i�Q�ƌ^�j
	D3DXVECTOR3& Position() { return position_; }
public:
	//@Summary	Create	:	�N���G�C�g�֐�
	//@Param Name	=	"_Max_Life"
	//@Param Name	=	"_Max_Mana"
	static BossMonster* Create(float _Max_Life, float _Max_Mana);
private:
	bool magicsetflag_;	//���ݖ��@�U�������m�F����t���O
	int attackframe_;	//�U���I�������ɗ]�C���c�����߂̃t���O
	bool nowattack_;	//���ݍU�������m�F����t���O
	int StateNum_;	//��Ԃ��m�F����ϐ�
	Entity::KNOCKBACKINFO knockback_;	//�m�b�N�o�b�N���
	BossStatusManager* statusmanager_;;	//�X�e�[�^�X�}�l�[�W���[�N���X
	BossMonsterAttackPattern* attack_;	//�U���}�l�[�W���[�N���X
	BossMonsterMagicPattern* magic_;	//���@�}�l�[�W���[�N���X
	BossMonsterPattern* bosspattern_;	//�s���p�^�[���}�l�[�W���[�N���X
	SphereColision* movecolision_;		//�Փ˔���N���X
	Entity::SphereColision movecolisioninfo_;	//�Փ˔���ϐ�
	Entity::BOSSMOVESTATE moveinfomation_;		//�ړ����
	Entity::MATRIX3D matrix_;	//�s��
	static D3DXVECTOR3 GetPos_;	//�ʒu���擾�ϐ�
	static D3DXMATRIX GetRotation_;	//��]���擾�ϐ�

	D3DXVECTOR3 AxisMove_;	//�ړ����ϐ�
	D3DXVECTOR3 scale_;		//�g��ϐ�
	D3DXVECTOR3 position_;	//���W�ϐ�
	D3DXVECTOR3 rotation_;	//��]�ϐ�

	CSkinMesh* skinmesh_;	//�X�L�����b�V��

	bool cameraflag_;	//�Q�[���J�n���̉��o�ؑ֗p�̃t���O
	int camerastartcount_;	//�Q�[���J�n���̉��o�I���܂ł̎���

	Entity::ENEMYMAGICINFO magicuseinfo_;	//���@�g�p�󋵂�c������ϐ�

	float mana_;	//���݂�SP
	float max_mana_;	//MAXSP
	float life_;	//���݂�HP
	float max_life_;	//MAXHP

	bool movestatecheck_;	//�ړ����ړ�����Ȃ�����m�点��t���O
	bool movecheckcolision_;	//�ړ����v���C���[�Ɠ������Ă��邩��m�点��t���O
};