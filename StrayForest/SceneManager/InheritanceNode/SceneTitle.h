#pragma once
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Fade/Fade.h"
#include "../../System/Polygon2D.h"
class Fade;

class SceneTitle : public SceneManager
{
public:
	SceneTitle() {}
	~SceneTitle() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	//@Summary	GetTitleStartBar	:	�^�C�g����ʂ̉����ɓ_�ł����Ă�|���S�����擾����֐�
	static Polygon2D* GetTitleStartBar();
	//@Summary	GetFade	:	�t�F�[�h�������擾����֐�
	static Fade* GetFade();
private:
	static Polygon2D* TitleStartBar_;	//�^�C�g����ʂ̉����ɓ_�ł����Ă�|���S���̕ϐ�
	static Fade* fade_;	//�t�F�[�h�����ϐ�
};