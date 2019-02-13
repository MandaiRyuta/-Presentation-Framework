#include "SphereColision.h"

bool SphereColision::Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision & colision)
{
	pos01_ = colision.colision01.modelpos;
	pos02_ = colision.colision02.modelpos;
	radius01_ = colision.colision01.r;
	radius02_ = colision.colision02.r;

	//’†SŠÔ‹——£‚Æ”¼Œa‚Ì‡Œv‚É‚æ‚éÕ“Ë”»’è(2æ)
	NecessaryLengthCalculation_Sphere_Sphere();
	
	if (Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection())
	{
		AmountOfSqueezingVectorCalculation_Sphere_Sphere();

		colision.hit_vector = hit_vector_;
		colision.center_to_center = center_to_center_;
		colision.two_radius = two_radius_;

		return true;
	}

	return false;
}

void SphereColision::NecessaryLengthCalculation_Sphere_Sphere()
{
	center_to_center_ = pos01_ - pos02_;
	two_radius_ = radius01_ + radius02_;
}

bool SphereColision::Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection()
{
	return D3DXVec3Length(&center_to_center_) < (two_radius_);
}

void SphereColision::AmountOfSqueezingVectorCalculation_Sphere_Sphere()
{
	D3DXVECTOR3 centerlength;
	centerlength = center_to_center_;
	D3DXVec3Normalize(&center_to_center_, &center_to_center_);
	float length = D3DXVec3Length(&centerlength) - two_radius_;
	hit_vector_ = center_to_center_ * length;
}