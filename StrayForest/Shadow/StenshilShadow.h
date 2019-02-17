#pragma once
#include "../GameObjectManager/GameObjectManager.h"
#include "../Entity/Entity.h"

class StenshilShadow : public GameObjectManager
{
public:
	StenshilShadow(int _type) 
		: GameObjectManager(0)
		, type_(_type)
	{}
	~StenshilShadow() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	//@Summary	Create	:	�X�e���V���V���h�E�����ׂ̊֐�
	//@ParamName	=	"_type"	:	1�Ԗڂ̕`�悩2�Ԗڂ̕`�悩�i���d�˂����������F�Ɏw�肵�Ċۉe�ɂ�����ׁj
	static StenshilShadow* Create(int _type);
private:
	int type_;	//1�Ԗڂ�2�Ԗڂ����w�肷��ϐ�
	Entity::MATRIX3D matrix_;	//�S�Ă̍s����������Ă���ϐ�
	Entity::Dx9Buffer buffer_;	//�o�b�t�@�\
};