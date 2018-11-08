#include "ModelLoder.h"

//****************************************************
// �ÓI�����o�\�ϐ��̐錾
//****************************************************
/// <summary>
/// ���f���i�[�ϐ��̐錾
/// </summary>
std::vector<Entity::Model*> ModelLoder::model_;

/// <summary>
/// ���f���J�E���^�[�̐錾
/// </summary>
int ModelLoder::ModelCounter_ = 0;
Entity::Model ModelLoder::InitModel[100];

void ModelLoder::LoadData(std::string _filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	Entity::Model* OneModel_ = &InitModel[ModelCounter_];
	/// <summary>
	/// x�t�@�C�����烁�b�V�������[�h����
	/// </summary>
	if (FAILED(D3DXLoadMeshFromX(_filename.c_str(), D3DXMESH_SYSTEMMEM, GetDevice(), NULL, &pD3DXMtrlBuffer, NULL, &OneModel_->dw_material, &OneModel_->p_mesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", _filename.c_str(), MB_OK);
		PostQuitMessage(0);
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	OneModel_->p_meshmaterial = new D3DMATERIAL9[OneModel_->dw_material];
	OneModel_->p_meshtexture = new LPDIRECT3DTEXTURE9[OneModel_->dw_material];

	/// <summary>
	/// �}�e���A���������[�v����
	/// </summary>
	for (DWORD i = 0; i < OneModel_->dw_material; i++)
	{
		OneModel_->p_meshmaterial[i] = d3dxMaterials[i].MatD3D;
		OneModel_->p_meshmaterial[i].Ambient = OneModel_->p_meshmaterial->Diffuse;
		OneModel_->p_meshtexture[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(GetDevice(), d3dxMaterials[i].pTextureFilename, &OneModel_->p_meshtexture[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				PostQuitMessage(0);
			}
		}
	}
	ModelCounter_++;
	model_.push_back(OneModel_);
	pD3DXMtrlBuffer->Release();
}

Entity::Model* ModelLoder::GetModelData(LOADMODEL _targetmodel)
{
	/// <summary>
	/// ���ݕێ����Ă��郂�f���̐������A�w�肳�ꂽ���l���z���Ă�����G���[�����ɓ���B
	/// </summary>
	if (_targetmodel > ModelCounter_)
	{
		MessageBox(NULL, "���f���̏����Ăяo���܂���ł���", "ModelLoderError", MB_OK);
		PostQuitMessage(0);
	}

	return model_[_targetmodel];
}

void ModelLoder::ReleseAll()
{
	model_.erase(model_.begin(), model_.end());
	//for (unsigned int i = 0; i < model_.size(); i++)
	//{
	//	if (model_[i]->p_mesh != nullptr)
	//	{
	//		model_[i]->p_mesh->Release();
	//		model_[i]->p_mesh = nullptr;
	//	}
	//	if (model_[i]->p_meshtexture != nullptr)
	//	{
	//		delete[] model_[i]->p_meshtexture;
	//	}
	//	if (model_[i]->p_meshmaterial != nullptr)
	//	{			
	//		delete[] model_[i]->p_meshmaterial;
	//	}
	//}
}
