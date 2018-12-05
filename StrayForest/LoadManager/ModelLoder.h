#pragma once
#include "../Entity/Entity.h"

class Models
{
public:
	Models() {}
	virtual ~Models() {}
	virtual Entity::Model* GetModelData() = 0;
	virtual void Relese() = 0;
};
//****************************************************
// class ModelLoder
//****************************************************
class ModelLoder : public Models
{
public:
	ModelLoder(std::string _filename);
	~ModelLoder();
public:
	//****************************************************
	// �Q�b�^�[
	//****************************************************
	/// <summary>
	/// ���f���f�[�^�[�̃Q�b�^�[
	/// </summary>
	//****************************************************
	// @ number : ���f���i���o�[
	//****************************************************
	Entity::Model* GetModelData();

	void Relese();
private:
	//****************************************************
	// �����o�[�ϐ�
	//****************************************************
	/// <summary>
	/// ���f���i�[�ϐ�
	/// </summary>
	Entity::Model* OneModel_;
	/// <summary>
	/// ���f���̃J�E���^�[
	/// </summary>
};