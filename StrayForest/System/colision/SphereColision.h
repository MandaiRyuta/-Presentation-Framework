#pragma once
#include "../../Entity/Entity.h"

class SphereColision
{
public:
	SphereColision() 
	{
		center_to_center_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		hit_vector_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		two_radius_ = 0.0f;
		pos01_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pos02_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		radius01_ = 0.0f;
		radius02_ = 0.0f;
	}
	~SphereColision() {}
public:
	//@Summary	Collision_detection_of_Sphere_and_Sphere	:	球と球の衝突判定を確認する関数
	//@ParamName	=	"colision"	:	1個目の球情報と2個目の球情報が入る
	bool Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision& colision);
	//@Summary	NecessaryLengthCalculation_Sphere_Sphere	:	二つの中心点の距離と、距離を調べる関数
	void NecessaryLengthCalculation_Sphere_Sphere();
	//@Summary	Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection	:	ベクトルの長さを調べる関数
	bool Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection();
	//@Summary	AmountOfSqueezingVectorCalculation_Sphere_Sphere	:	めりこみ量を調べる関数
	void AmountOfSqueezingVectorCalculation_Sphere_Sphere();
private:
	D3DXVECTOR3 center_to_center_;	//二つの中心点の距離
	D3DXVECTOR3 hit_vector_;	//めり込み量
	D3DXVECTOR3 pos01_;	//1番目の球情報
	D3DXVECTOR3 pos02_;	//2番目の球情報
	float radius01_;	//1番目の球の半径
	float radius02_;	//2番目の球の半径
	float two_radius_;	//二つの半径を合わせた物
};
