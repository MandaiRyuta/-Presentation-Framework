#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

struct FADE_VERTEX
{
	float x, y, z;
	DWORD color;
};

class Fade : public GameObjectManager
{
public:
	Fade() : GameObjectManager(2) {}
	~Fade() {}
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;
	void Update() override;

	//@Summary	BlackFadeIn	:	�w�i�F�����F�̃t�F�[�h�C���֐�
	void BlackFadeIn();
	//@Summary	BlackFadeOut	:	�w�i�F�����F�̃t�F�[�h�A�E�g�֐�
	void BlackFadeOut();
	//@Summary	WhiteFadeIn	:	�w�i�F�����F�̃t�F�[�h�C���֐�
	void WhiteFadeIn();
	//@Summary	WhiteFadeOut	:	�w�i�F�����F�̃t�F�[�h�A�E�g�֐�
	void WhiteFadeOut();
	//@Summary	GetFadeFlag	:	�t�F�[�h�����������ǂ�����m�点��֐�
	bool GetFadeFlag();
	//@Summary	FadeSetNumber	:	�ǂ̃t�F�[�h�ɑΉ������邩��ݒ肷��֐�
	void FadeSetNumber(int fade);
public:
	//@Summary	Create	=	"�t�F�[�h�쐬�֐�"
	static Fade* Create();
private:
	int FadeIn;	//�t�F�[�h�C���̃��l
	int FadeOut;	//�t�F�[�h�A�E�g�̃��l
	int FadeSet_;	//�Ή�������t�F�[�h�̔ԍ�
	bool BlackFadeInFlag_;	//�w�i�F�����F�̃t�F�[�h�C���������������ǂ����m�点��
	bool BlackFadeOutFlag_;	//�w�i�F�����F�̃t�F�[�h�A�E�g�������������ǂ����m�点��
	bool WhiteFadeInFlag_;	//�w�i�F�����F�̃t�F�[�h�C���������������m�点��
	bool WhiteFadeOutFlag_;	//�w�i�F�����F�̃t�F�[�h�A�E�g�������������m�点��
};