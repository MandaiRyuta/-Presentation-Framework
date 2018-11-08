#pragma once
#include "../Entity/Entity.h"

//****************************************************
// �񋓌^
//****************************************************
enum LOADMODEL
{
	SKYDOME,
	TREE,
	TESTMODEL,
	SHADOW,
	MODEL_MAX,	//���f���̍ő��
};

//****************************************************
// class ModelLoder
//****************************************************
class ModelLoder
{
private:
	ModelLoder() {}
	~ModelLoder() {}
public:
	/// <summary>
	/// ���[�h�f�[�^
	/// </summary>
	//****************************************************
	// @ _filename : �t�@�C���p�X
	// @ _LoadType : ��荞�ތ`���@0�ԁF�e�N�X�`���@1��: ���f��
	//****************************************************
	static void LoadData(std::string _filename);
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
	static Entity::Model* GetModelData(LOADMODEL _targetmodel);

	static void ReleseAll();
private:
	//****************************************************
	// �����o�[�ϐ�
	//****************************************************
	/// <summary>
	/// ���f���i�[�ϐ�
	/// </summary>
	static std::vector<Entity::Model*> model_;
	static Entity::Model InitModel[100];
	Entity::Model* OneModel_;
	/// <summary>
	/// ���f���̃J�E���^�[
	/// </summary>
	static int ModelCounter_;
};