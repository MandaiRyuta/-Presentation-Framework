#include "ModelLoder.h"

//****************************************************
// �ÓI�����o�\�ϐ��̐錾
//****************************************************
/// <summary>
/// ���f���i�[�ϐ��̐錾
/// </summary>

ModelLoder::ModelLoder(std::string _filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	OneModel_ = new Entity::Model;
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

	pD3DXMtrlBuffer->Release();
}

ModelLoder::~ModelLoder()
{
}

Entity::Model* ModelLoder::GetModelData()
{
	return OneModel_;
}

void ModelLoder::Relese()
{
	if (OneModel_->p_meshtexture != nullptr)
	{
		delete[] OneModel_->p_meshtexture;
	}
	
	if (OneModel_->p_meshmaterial != nullptr)
	{
		delete[] OneModel_->p_meshmaterial;
	}
	if (OneModel_->p_mesh != nullptr)
	{
		OneModel_->p_mesh->Release();
	}

	if (OneModel_ != nullptr)
	{
		delete OneModel_;
	}
	//for (unsigned int i = 0; i < model_.size(); i++)
	//{
	//	
	//}
}