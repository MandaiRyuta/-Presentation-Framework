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

void ModelLoder::LoadData(std::string _filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	Entity::Model* model;
	/// <summary>
	/// x�t�@�C�����烁�b�V�������[�h����
	/// </summary>
	if (FAILED(D3DXLoadMeshFromX(_filename.c_str(), D3DXMESH_SYSTEMMEM, GetDevice(), NULL, &pD3DXMtrlBuffer, NULL, &model->dw_material, &model->p_mesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", _filename.c_str(), MB_OK);
		PostQuitMessage(0);
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	model->p_meshmaterial = new D3DMATERIAL9[model->dw_material];
	model->p_meshtexture = new LPDIRECT3DTEXTURE9[model->dw_material];

	/// <summary>
	/// �}�e���A���������[�v����
	/// </summary>
	for (DWORD i = 0; i < model->dw_material; i++)
	{
		model->p_meshmaterial[i] = d3dxMaterials[i].MatD3D;
		model->p_meshmaterial[i].Ambient = model->p_meshmaterial->Diffuse;
		model->p_meshtexture[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(GetDevice(), d3dxMaterials[i].pTextureFilename, &model->p_meshtexture[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				PostQuitMessage(0);
			}
		}
	}
	model_.push_back(model);
	pD3DXMtrlBuffer->Release();
	ModelCounter_++;
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
	for (auto itr = model_.begin(); itr != model_.end(); itr++)
	{
		if ((*itr)->p_mesh != nullptr)
		{
			(*itr)->p_mesh->Release();
			(*itr)->p_mesh = nullptr;
			delete[] (*itr)->p_mesh;
		}
		if ((*itr)->p_meshtexture = nullptr)
		{
			delete[](*itr)->p_meshtexture;
		}
		if ((*itr)->p_meshmaterial)
		{
			delete[](*itr)->p_meshmaterial;
		}
	}
}
