#pragma once
#include "../../Entity/Entity.h"

class SphereColision
{
public:
	SphereColision() {}
	~SphereColision() {}
public:
	bool Collision_detection_of_Sphere_and_Sphere();
	void NecessaryLengthCalculation_Sphere_Sphere();
	bool Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection();
	void AmountOfSqueezingVectorCalculation_Sphere_Sphere();
};