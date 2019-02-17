#pragma once
#include "../../Entity/Entity.h"
#include "../../GameObjectManager/GameObjectManager.h"

class Skydome : public GameObjectManager
{
public:
	Skydome() : GameObjectManager(0)
	{

	}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	�X�J�C�h�[���쐬
	static Skydome* Create();
private:
	Entity::MATRIX3D matrix_;	//�S�Ă̍s����

	D3DXVECTOR3 position_;	//���W
	D3DXVECTOR3 rotation_;	//��]
	D3DXVECTOR3 scale_;	//�g��
};