#pragma once
#include "../main.h"
#include "../Renderer/Renderer.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <vector>

class SceneManager;
class CCamera;
class Light;
class CInputKeyboard;
class CInputMouse;
class Models;
class GamePadXbox;
class EffectSound;
//�v���C���[�̕����X�s�[�h
constexpr float WALKSPEED = 1.0f;
//�v���C���[�̑���X�s�[�h
constexpr float RUNSPEED = 3.0f;
//�v���C���[�̃��[�����O�X�s�[�h
constexpr float ROLLSPEED = 4.0f;

//****************************************************
// �񋓌^
//****************************************************
enum LOADMODEL
{
	MODEL_SKYDOME,
	//MODEL_TREE,
	MODEL_SHADOW,
	MODEL_SHILED,
	MODEL_SWORD,
	MODEL_MAX,	//���f���̍ő��
};

enum SCENE_NUM
{
	SCENE_TITLE,
	SCENE_CHUTORIAL,
	SCENE_GAME,
	SCENE_WINRESULT,
	SCENE_LOSERESULT,
	SCENE_MAX
};

class GameManager
{
public:
	//@Summary	GameManager	:�@DirectX9�̏�����
	GameManager(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight);
	~GameManager() {}
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
public:
	//@Summary	SetSceneMode	:	�V�[���̐؂�ւ����V�[���ԍ��U��
	//@Param Name	=	"_Mode"	:	�V�[�����
	//@Param Name	=	"_scene_num"	:	�V�[���ԍ�
	static void SetSceneMode(SceneManager* _Mode, SCENE_NUM _scene_num);
public:
	//@Summary	GetSceneNumber	:	���݂̃V�[���ԍ�
	static SCENE_NUM GetSceneNumber();
	//@Summary	GetKeyboard	:	�L�[�{�[�h���擾�֐�
	static CInputKeyboard* GetKeyboard();
	//@Summary	GetMouse	:	�}�E�X���擾�֐�
	static CInputMouse* GetMouse();
	//@Summary	GetModel	:	���f�����擾�֐�
	//@Param Name	=	"_modelnum"	:	���f���ԍ�
	static Models* GetModel(LOADMODEL _modelnum);
	//@Summary	GetCamera	:	�J�������擾�֐�
	static CCamera* GetCamera();
	//@Summary	GetGamePad	:	�Q�[���p�b�g���擾�֐�
	static GamePadXbox* GetGamePad();
	//@Summary	GetEffectSound	:	�G�t�F�N�g�T�E���h���擾�֐�
	static EffectSound* GetEffectSound();
private:
	static GamePadXbox* GamePad_;	//�Q�[���p�b�g
	static SCENE_NUM SceneNum_;	//�V�[���ԍ�
	static CInputMouse* mouse_;	//�}�E�X���
	static CInputKeyboard* keyboard_;	//�L�[�{�[�h���
	CDX9Renderer* renderer_;	//�`��N���X
	static CCamera* camera_;	//�J�������
	Light* light_;	//���C�g���
	static SceneManager* mode_;	//�V�[�����
	static std::vector<Models*> modelinfo_;	//���f�����
	static EffectSound* sound_;	//�G�t�F�N�g�T�E���h���
};