#include "PlayerMove.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../MeshFiled.h"
#include "../Camera.h"

void PlayerMove::Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation)
{
	keyboard_ = GameManager::GetKeyboard();
	position_ = CCamera::GetAt();
	position_.y = SceneGame::GetMeshFiled()->GetHeight(position_);

	int X = -keyboard_->GetKeyPress(DIK_A) + keyboard_->GetKeyPress(DIK_D);
	int Z = -keyboard_->GetKeyPress(DIK_S) + keyboard_->GetKeyPress(DIK_W);

	move_ = D3DXVECTOR3((float)X, 0.0f, (float)Z);

	frontvec_ = (position_)-CCamera::GetEye();
	D3DXVec3Normalize(&frontvec_, &frontvec_);
	D3DXVec3Cross(&rightvec_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &frontvec_);
	D3DXVec3Normalize(&rightvec_, &rightvec_);
	D3DXVec3Cross(&upvec_, &frontvec_, &rightvec_);

	D3DXMATRIX setrot;
	D3DXMatrixRotationAxis(&setrot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rotation_);
	D3DXVec3TransformNormal(&move_, &move_, &setrot);

	position_ -= move_ * 1.2f;

	//入力でアニメーションを切り替える

	rotation_ = D3DXToRadian(D3DXToDegree(atan2(frontvec_.x, frontvec_.z))) + D3DXToRadian(180.0f);		
	
	D3DXMatrixRotationY(&_mtx_rotation, rotation_);

	D3DXMatrixTranslation(&_mtx_position, position_.x, position_.y, position_.z);
}