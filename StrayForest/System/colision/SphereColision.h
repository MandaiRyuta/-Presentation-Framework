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
	//@Summary	Collision_detection_of_Sphere_and_Sphere	:	���Ƌ��̏Փ˔�����m�F����֐�
	//@ParamName	=	"colision"	:	1�ڂ̋�����2�ڂ̋���񂪓���
	bool Collision_detection_of_Sphere_and_Sphere(Entity::SphereColision& colision);
	//@Summary	NecessaryLengthCalculation_Sphere_Sphere	:	��̒��S�_�̋����ƁA�����𒲂ׂ�֐�
	void NecessaryLengthCalculation_Sphere_Sphere();
	//@Summary	Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection	:	�x�N�g���̒����𒲂ׂ�֐�
	bool Is_Sphere_and_Sphere_two_Square_Range_by_Collision_detection();
	//@Summary	AmountOfSqueezingVectorCalculation_Sphere_Sphere	:	�߂肱�ݗʂ𒲂ׂ�֐�
	void AmountOfSqueezingVectorCalculation_Sphere_Sphere();
private:
	D3DXVECTOR3 center_to_center_;	//��̒��S�_�̋���
	D3DXVECTOR3 hit_vector_;	//�߂荞�ݗ�
	D3DXVECTOR3 pos01_;	//1�Ԗڂ̋����
	D3DXVECTOR3 pos02_;	//2�Ԗڂ̋����
	float radius01_;	//1�Ԗڂ̋��̔��a
	float radius02_;	//2�Ԗڂ̋��̔��a
	float two_radius_;	//��̔��a�����킹����
};
