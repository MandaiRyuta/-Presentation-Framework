#pragma once
//�I�u�W�F�N�g�̏��̍ő�擾��
constexpr int OBJ_MAX = 400;
//�`����
constexpr int SORT_MAX = 3;

class GameObjectManager
{
public:
	//@Summary	GameObjectManager	:	�`���ނ����߂ĕ`�������荞��
	GameObjectManager(int _Priority);
	virtual ~GameObjectManager() {}
public:
	virtual void Init(){}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	void Release();
	//@Summary	UpdateAll	:	�`�����S�čX�V
	static void UpdateAll();
	//@Summary	DrawAll	:	�`��������ׂĕ`�悳����
	static void DrawAll();
	//@Summary	ReleaseAll	:	�`�悵�����̂��ׂĂ����
	static void ReleaseAll();
	//@Summary SetPause	:	�|�[�Y�t���O��ݒ肷��֐�
	//@ParamName	=	"_pause"	:	�|�[�Y�t���O
	static void SetPause(bool _pause);
	//@Summary	GetPause	:	���݂̃|�[�Y�̃t���O���擾����
	static bool GetPause();
private:
	static bool RestartFlag_;	//���X�^�[�g�t���O�ϐ�
	static bool NonRestartFlag_;	//���X�^�[�g���Ȃ��t���O�ϐ�
	static bool pause_;	//�|�[�Y�t���O�ϐ�
	static GameObjectManager* object_[SORT_MAX][OBJ_MAX];	//�I�u�W�F�N�g����荞�ޕϐ�
	static int PauseState_;	//�|�[�Y���I������Ƃ��Ɏg���ϐ�
};