#pragma once
#include "../../../Entity/Entity.h"
#include "../../../InputManager/input.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"

class ChutorialBoss : public GameObjectManager
{
public:
	ChutorialBoss();
	~ChutorialBoss();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	�`���[�g���A���p�̃{�X���쐬����֐�
	static ChutorialBoss* Create();
	//@Summary	GetPosition	:	�ʒu���
	D3DXVECTOR3 GetPosition();
private:
	Entity::MATRIX3D matrix_;	//�S�Ă̍s����܂Ƃ߂��ϐ�
	D3DXVECTOR3 position_;	//���W�ϐ�
	float rotation_;	//Y���̉�]�ϐ�
	int framecount_;	//�A�j���[�V�����p�t���[���J�E���g
	CSkinMesh* skinmesh_;	//�X�L�����b�V�����
};