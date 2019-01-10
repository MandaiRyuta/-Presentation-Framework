#pragma once
#include "../../Entity/Entity.h"

class SphereColision
{
public:
	SphereColision() {}
	~SphereColision() {}
public:
	bool Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision& colision);
	void NecessaryLengthCalculation_Sphere_Sphere(Entity::SphereColision& colision);
	bool Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection(Entity::SphereColision& colision);
	void AmountOfSqueezingVectorCalculation_Sphere_Sphere(Entity::SphereColision& colision);
};
