#pragma once
#include "../../../Entity/Entity.h"
#include "../../../InputManager/input.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"
#include "../../../InputManager/XBoxController.h"

class ChutorialPlayer : public GameObjectManager
{
public:
	ChutorialPlayer();
	~ChutorialPlayer();
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static ChutorialPlayer* Create();
	D3DXVECTOR3 GetPosition();
private:
	void Move();
	void Attack();
	void Magic();
	void Diffence();
private:
	enum CHUTORIAL_MOVE_PATTERN
	{
		STATE,
		WALK,
		RUN,
		ROLL,
		NONE
	};
	GamePadXbox* gamepad_;
	CSkinMesh* skinmesh_;
	CInputKeyboard* keyboard_;
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	D3DXVECTOR3 frontvec_;
	D3DXVECTOR3 rightvec_;
	D3DXVECTOR3 upvec_;
	D3DXVECTOR3 move_;
	CHUTORIAL_MOVE_PATTERN animpattern_;
	ACTIONPATTERN attackpattern_;
	float movespeed_;
	int counttime_;
	int diffencetime_;
	int magictime_;
	int sleeptime_;
	int keyframe_;
	bool rollflag_;
};