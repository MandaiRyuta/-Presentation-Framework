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
	bool Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision& colision);
	void NecessaryLengthCalculation_Sphere_Sphere();
	bool Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection();
	void AmountOfSqueezingVectorCalculation_Sphere_Sphere();
private:
	D3DXVECTOR3 center_to_center_;
	D3DXVECTOR3 hit_vector_;
	D3DXVECTOR3 pos01_;
	D3DXVECTOR3 pos02_;
	float radius01_;
	float radius02_;
	float two_radius_;
};
