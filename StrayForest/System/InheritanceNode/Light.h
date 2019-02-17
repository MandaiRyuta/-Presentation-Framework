#pragma once

#include "../../Entity/Entity.h"

class Light
{
public:
	Light() {}
	~Light() {}

public:
	void Init();
	void Update() {}
	void Draw() {}
	void Uninit() {}

	//@Summary	CreateMaterialLight	:	�}�e���A�������쐬
	void CreateMaterialLight(D3DMATERIAL9 _mat);
	//@Summary	CreateLight	:	���C�g�����쐬
	void CreateLight(Entity::LightInfo _light);
	//@Summary	GetLightPos	:	���C�g�̍��W���擾����֐�
	static D3DXVECTOR3 GetLightPos();
	//@Summary	SetLightPos	:	���C�g�̍��W��ݒ肷��
	static void SetLightPos(D3DXVECTOR3 _pos);
private:
	static D3DXVECTOR3 lightpos_;	//���C�g�̍��W
	Entity::LightInfo lightinfo_;	//���C�g���
};