#include "SphereColision.h"

bool SphereColision::Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision & colision)
{
	//’†SŠÔ‹——£‚Æ”¼Œa‚Ì‡Œv‚É‚æ‚éÕ“Ë”»’è(2æ)
	NecessaryLengthCalculation_Sphere_Sphere(colision);

	if (Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection(colision))
	{
		AmountOfSqueezingVectorCalculation_Sphere_Sphere(colision);
		return false;
	}
	return true;
}

void SphereColision::NecessaryLengthCalculation_Sphere_Sphere(Entity::SphereColision & colision)
{
	colision.center_to_center = colision.colision01.modelpos - colision.colision02.modelpos;
	colision.two_radius = colision.colision01.r + colision.colision02.r;
}

bool SphereColision::Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection(Entity::SphereColision & colision)
{
	return D3DXVec3Length(&colision.center_to_center) > (colision.two_radius);
}

void SphereColision::AmountOfSqueezingVectorCalculation_Sphere_Sphere(Entity::SphereColision & colision)
{
	if (colision.hit_vector)
	{
		D3DXVECTOR3 centerlength;
		centerlength = colision.center_to_center;
		D3DXVec3Normalize(&colision.center_to_center, &colision.center_to_center);
		float length = D3DXVec3Length(&centerlength);
		colision.hit_vector = colision.center_to_center * length;
	}
}