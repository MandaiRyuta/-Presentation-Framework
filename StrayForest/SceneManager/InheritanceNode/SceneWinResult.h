#pragma once

#include "../SceneManager.h"
class Fade;
class MeshFiled;
class WinPlayer;
class Polygon2D;
class SceneWinResult : public SceneManager
{
public:
	SceneWinResult() {}
	~SceneWinResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//@Summary	GetMeshFiled	:	���b�V���t�B�[���h���擾����֐�
	static MeshFiled* GetMeshFiled();
	//@Summary	GetWinPlayer	:	�v���C���[�擾����֐�
	static WinPlayer* GetWinPlayer();
	//@Summary	GetWinWord	:	�X�^�[�g�{�^����������`�悷��|���S�����擾����ϐ�
	static Polygon2D* GetWinWord();
	//@Summary	GetFade	:	�t�F�[�h�������擾����֐�
	static Fade* GetFade();
private:
	static MeshFiled* WinResultMeshFiled_;	//���b�V���t�B�[���h�ϐ�
	static WinPlayer* WinResultPlayer_;	//�v���C���[�ϐ�
	static Fade* fade_;	//�t�F�[�h�����ϐ�
	static Polygon2D* WinWord_;	//�X�^�[�g�{�^����������`�悷��|���S���̕ϐ�
};