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
	static ChutorialBoss* Create();
	D3DXVECTOR3 GetPosition();
private:
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 position_;
	float rotation_;
	int framecount_;
	CSkinMesh* skinmesh_;
};