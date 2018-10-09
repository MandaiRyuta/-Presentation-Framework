//****************************************************
// @file : meshfiled.h
// @brief: ���b�V���t�B�[���h�̍쐬
// @Date : 2018/09/26
// @author:Mandai Ryuta
//****************************************************
//****************************************************
// include
//****************************************************
#include "meshfiled.h"
#include "../../Renderer/Renderer.h"
#include "../../LoadManager/CsvLoder.h"
#include "../../LoadManager/TextureLoder.h"
#include "../../ShaderManager/EffectShaderManager.h"
#include "Camera.h"
//****************************************************
// ������
//****************************************************
void MeshFiled::Init()
{
	/// <summary>
	/// �f�o�C�X���󂯎��
	/// </summary>
	LPDIRECT3DDEVICE9 device = GetDevice();

	VertexBufferCreate(device);
	IndexBufferCreate(device);

	/// <summary>
	/// �}�e���A���̏��������s������ɐݒ���s��
	/// </summary>
	ZeroMemory(&meshmaterial_, sizeof(meshmaterial_));

	//****************************************************
	// @ Diffuse : �g�U���̐ݒ�
	// @ Ambient : �����̐ݒ�
	// @ Specular: ���ˌ��̐ݒ�
	//****************************************************
	meshmaterial_.Diffuse = { 0.8f, 0.7f, 0.8f, 1.0f };
	meshmaterial_.Ambient = { 0.7f, 0.7f, 0.7f, 1.0f };

	/// <summary>
	/// ���[���h�s���P�ʍs��ɂ���
	/// </summary>
	D3DXMatrixIdentity(&matrix_.world);
	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.rotation);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixTranslation(&matrix_.position, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&matrix_.scale, 1.1f, 1.0f, 1.1f);
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, 0.0f, 0.0f, 0.0f);
}

//****************************************************
// �X�V
//****************************************************
void MeshFiled::Update()
{
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

//****************************************************
// �`�� ��Shader�ʂ��̂ňꎞ��ƒ�~
//****************************************************
void MeshFiled::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	device->SetFVF(FVF_FILED);
	device->SetStreamSource(0, buffer_.vertex_buffer, 0, sizeof(Entity::VECTOR3D));
	device->SetIndices(buffer_.index_buffer);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

	device->SetMaterial(&meshmaterial_);
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	device->SetTransform(D3DTS_WORLD, &matrix_.world);

	device->SetTexture(0, TextureLoder::GetTextureData(FLOOR01));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);

	device->SetTexture(0, TextureLoder::GetTextureData(FLOOR02));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);

	/*�Ȃ����G���[�f�����*/
	//LPDIRECT3DDEVICE9 device = GetDevice();
	//D3DXVECTOR4 v;
	//D3DXMATRIX mWVP = matrix_.world * CCamera::GetView() * CCamera::GetProj();
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTechnique("TShader");
	//EffectShaderManager::GetEffect(BUMPMAP)->Begin(NULL, 0);
	//EffectShaderManager::GetEffect(BUMPMAP)->BeginPass(0);
	//EffectShaderManager::GetEffect(BUMPMAP)->SetMatrix("mWVP", &mWVP);
	//D3DXVECTOR4 LightPos = D3DXVECTOR4(Light::GetLightPos().x, Light::GetLightPos().y, Light::GetLightPos().z, 0);
	//D3DXMatrixInverse(&mWVP, NULL, &matrix_.world);
	//D3DXVec4Transform(&v, &LightPos, &mWVP);
	//D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
	//v.w = -0.7f;
	//EffectShaderManager::GetEffect(BUMPMAP)->SetVector("vLightDir", &v);
	//D3DXMATRIX viewworld = matrix_.world * CCamera::GetView();
	//D3DXMatrixInverse(&viewworld, NULL, &viewworld);
	//v = D3DXVECTOR4(0, 0, 0, 1);
	//D3DXVec4Transform(&v, &v, &viewworld);
	//EffectShaderManager::GetEffect(BUMPMAP)->SetVector("vEyePos", &v);
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("NormalMap", TextureLoder::GetTextureData(FLOOR01NORMAL));
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("DecaleTex", TextureLoder::GetTextureData(FLOOR01));
	//device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);
	//
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("NormalMap", TextureLoder::GetTextureData(FLOOR02NORMAL));
	//EffectShaderManager::GetEffect(BUMPMAP)->SetTexture("DecaleTex", TextureLoder::GetTextureData(FLOOR02));
	//
	//device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->number_of_vertices_, 0, this->number_of_primities_);
	//EffectShaderManager::GetEffect(BUMPMAP)->EndPass();
	//EffectShaderManager::GetEffect(BUMPMAP)->End();
}

//****************************************************
// �J��
//****************************************************
void MeshFiled::Uninit()
{
	/// <summary>
	/// �o�[�e�b�N�X�o�b�t�@�̉������
	/// </summary>
	if (buffer_.vertex_buffer != nullptr)
	{
		buffer_.vertex_buffer->Release();
		buffer_.vertex_buffer = nullptr;
	}
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̉������
	/// </summary>
	if (buffer_.index_buffer != nullptr)
	{
		buffer_.index_buffer->Release();
		buffer_.index_buffer = nullptr;
	}
}

//****************************************************
// �����֐�
//****************************************************
MeshFiled * MeshFiled::Create(Entity::MeshFiledSize _meshinfo)
{
	MeshFiled* pMeshfiled = new MeshFiled(_meshinfo);
	pMeshfiled->Init();
	return pMeshfiled;
}

//****************************************************
// �o�[�e�b�N�X�o�b�t�@�̐���
//****************************************************
void MeshFiled::VertexBufferCreate(LPDIRECT3DDEVICE9 _device)
{
	/// <summary>
	/// Vector�̓񎟌��z��
	/// </summary>
	std::vector<std::vector<std::string>> filedtable;

	/// <summary>
	/// Csv�ǂݍ���
	/// </summary>
	CsvLoder::CsvRead("Resource/CSVFile/meshfiled.csv", filedtable);
	
	/// <summary>
	/// ���_�̊J�n�n�_
	/// </summary>
	float fStartX = -meshinfo_.size_x * (meshinfo_.filed_x / 2);
	float fStartZ = meshinfo_.size_x * (meshinfo_.filed_z / 2);

	/// <summary>
	/// X�̌���Z�̌�
	/// </summary>
	int nCx = meshinfo_.filed_x + 1;
	int nCz = meshinfo_.filed_z + 1;

	/// <summary>
	/// �o�[�e�b�N�X���C���f�b�N�X���v���~�e�B�u���̌v�Z
	/// </summary>
	number_of_vertices_ = nCx * nCz;
	number_of_indices_ = (nCx * 2 + 1) * (nCz - 2) + (nCx - 2);
	number_of_primities_ = this->number_of_indices_ - 2;

	/// <summary>
	/// �o�b�t�@�\�̐���
	/// </summary>
	if (FAILED(_device->CreateVertexBuffer(
		sizeof(Entity::VECTOR3D) * number_of_vertices_,
		D3DUSAGE_WRITEONLY,
		FVF_FILED,
		D3DPOOL_MANAGED,
		&buffer_.vertex_buffer,
		NULL)))
	{
		MessageBox(NULL, "VertexBuffer�̐����Ɏ��s���܂����B", "MeshFiled", MB_OK);
		PostQuitMessage(0);
	}

	/// <summary>
	/// vertexbuffer�����b�N���ď������݁A�����ăA�����b�N����
	/// </summary>
	buffer_.vertex_buffer->Lock(0, 0, (void**)&mpv_, D3DLOCK_DISCARD);

	/// <summary>
	/// �O�όv�Z���邽�߂ɕK�v�ȕϐ�
	/// </summary>
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 normal;

	/// <summary>
	/// csv�t�@�C���̍Ō�̏��Ŏ~�܂�悤�ɂ���B
	/// </summary>
	char *end[1] = { "\n" };

	/// <summary>
	/// �t�B�[���h�̍�����csv����擾���AX���W��Z���W�����߂��Ă��郁�b�V���t�B�[���h�̏��i�[�ϐ��֑������
	/// </summary>
	for (int nZ = 0; nZ < nCz - 1; nZ++)
	{
		for (int nX = 0; nX < nCx - 1; nX++)
		{
			FiledHeight[nZ][nX] = strtof(filedtable[nZ][nX].c_str(), &end[0]);
		}
	}
	
	/*
		@nCount : ���b�V���t�B�[���h�̒��_�̐��𐔂���ϐ�
	*/
	for (int z = 0, nCount = 0; z < nCz; z++)
	{
		for (int x = 0; x < nCx; x++)
		{
			/// <summary>
			/// 3���̍��W���擾
			/// </summary>
			mpv_[nCount].position = D3DXVECTOR3(fStartX + (meshinfo_.size_x * x), FiledHeight[z][x], fStartZ - (meshinfo_.size_z * z));

			nCount++;
		}
	}

	for (int nZ = 0, nCount = 0; nZ < nCz; nZ++)
	{
		for (int nX = 0; nX < nCx; nX++)
		{
			/// <summary>
			/// �O�ςɕK�v�ȃx�N�g���̌v�Z
			/// </summary>
			vx = mpv_[(nZ * nCz) + (nX + 2)].position - mpv_[nZ * nCz + nX].position;
			vz = mpv_[(nZ * nCz) + (nX + 1)].position - mpv_[nZ * nCx + nX].position;
			/// <summary>
			/// �O�ς̌v�Z
			/// </summary>
			//****************************************************
			// normal.x = vx.y * vz.z - vx.z * vz.y
			// normal.y = vx.z * vz.x - vx.x * vz.z
			// normal.z = vx.x * vz.y - vx.y * vz.x
			//****************************************************
			D3DXVec3Cross(&normal, &vx, &vz);
			/// <summary>
			/// �x�N�g���̐��K��
			/// </summary>
			D3DXVec3Normalize(&normal, &normal);
			/// <summary>
			/// ���b�V���z�u���̖@���֊O�ς��ċ��߂��@������
			/// </summary>
			mpv_[(nZ * nCx) + nX].normal = normal;

			/// <summary>
			/// �J���[���
			/// </summary>
			mpv_[nCount].color = D3DCOLOR_RGBA(255, 255, 255, 255);

			/// <summary>
			/// �e�N�X�`��uv�l
			/// </summary>
			mpv_[nCount].texcoord = D3DXVECTOR2((meshinfo_.size_x * nX) / (meshinfo_.size_x * nCx), (meshinfo_.size_z * nZ) / (meshinfo_.size_z * nCz));

			/// <summary>
			/// ���b�V���z�u�J�E���^�[�ɂP�ǉ�
			/// </summary>
			nCount++;
		}
	}

	buffer_.vertex_buffer->Unlock();
}

//****************************************************
// �C���f�b�N�X�o�b�t�@�̐���
//****************************************************
void MeshFiled::IndexBufferCreate(LPDIRECT3DDEVICE9 _device)
{
	/// <summary>
	/// X�̌���Z�̌�
	/// </summary>
	int nCx = meshinfo_.filed_x + 1;

	/// <summary>
	/// �C���f�b�N�X�ԍ��i�[�ϐ��i�|�C���^�[�j
	/// </summary>
	LPWORD ppIndex;

	/// <summary>
	/// �C���f�b�N�X�̐�����Ƌ����ŕ����ď��������邽�߂ɕK�v�ȕϐ�
	/// </summary>
	int nS = 0, nF = 0;
	int nC = 2 * nCx, nD = 2 * nCx + 1;

	if (FAILED(_device->CreateIndexBuffer(
		sizeof(WORD) * number_of_indices_,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&buffer_.index_buffer,
		NULL)))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s���܂���", "MeshFiled", MB_OK);
		PostQuitMessage(0);
	}

	buffer_.index_buffer->Lock(0, 0, (void**)&ppIndex, D3DLOCK_DISCARD);

	for (int nCount = 0; nCount < this->number_of_indices_; nCount++)
	{
		//�C���f�b�N�X�����Ԃ̏k��
		if (nCount == nC)
		{
			ppIndex[nCount] = ppIndex[nCount - 1];
			nC += (2 * (nCx + 1));
			continue;
		}
		//�C���f�b�N�X������
		if (nCount % 2 == 0)
		{
			ppIndex[nCount] = (WORD)(nCx + nS);
			nS++;
		}
		//�C���f�b�N�X��Ԃ̏k��
		if (nCount == nD)
		{
			ppIndex[nCount] = (WORD)(nCx + nS);
			nD += (2 * (nCx + 1));
			continue;
		}
		//�C���f�b�N�X���
		if (nCount % 2 == 1)
		{
			ppIndex[nCount] = (WORD)(nF);
			if (nCount == ((nC * nCx) - 1))
			{
				ppIndex[nCount] = (WORD)(nF);
				continue;
			}
			else
			{
				nF++;
			}
		}
	}

	buffer_.index_buffer->Unlock();

}

//****************************************************
// �ΏۂƂȂ�ʒu�̍��������߂�
//****************************************************
float MeshFiled::GetHeight(D3DXVECTOR3 _position)
{
	/// <summary>
	/// ���_�����񂾃x�N�g���̎Z�o�p�ϐ�
	/// </summary>
	D3DXVECTOR3 V01, V12, V20;

	/// <summary>
	/// �v���C���[�Ɗe�x�N�g�����r����ϐ�
	/// </summary>
	D3DXVECTOR3 V0p, V1p, V2p;

	/// <summary>
	/// 2�����̊O�ϒl
	/// </summary>
	float C0, C1, C2;
	float C3, C4, C5;

	/// <summary>
	/// �@���x�N�g���p�@�ϐ�
	/// </summary>
	D3DXVECTOR3 normal;

	/// <summary>
	/// �t�B�[���h�̍ő��
	/// </summary>
	//int MaxFiledX = (MeshFiledX)+1;
	int MaxFiledZ = (MeshFiledZ)+1;

	for (int nZ = 0; nZ < MeshFiledZ; nZ++)
	{
		for (int nX = 0; nX < MeshFiledX; nX++)
		{
			/// <summary>
			/// �����x�N�g�������߂�
			/// </summary>
			V01 = mpv_[(nZ + 1)* MaxFiledZ + nX].position - mpv_[nZ * MaxFiledZ + nX].position;
			V12 = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position - mpv_[(nZ + 1) * MaxFiledZ + nX].position;
			V20 = mpv_[nZ * MaxFiledZ + nX].position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// �ʒu�x�N�g�������߂�
			/// </summary>
			V0p = _position - mpv_[nZ * MaxFiledZ + nX].position;
			V1p = _position - mpv_[(nZ + 1) * MaxFiledZ + nX].position;
			V2p = _position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// ���������߂�
			/// </summary>
			C0 = V01.x * V0p.z - V01.z * V0p.x;
			C1 = V12.x * V1p.z - V12.z * V1p.x;
			C2 = V20.x * V2p.z - V20.z * V2p.x;

			/// <summary>
			/// D3DXVec3Cross() : �Փ˔���p�̖@��������, �@�����܂񂾌v�Z����,_position.y�ɕԂ�
			/// </summary>
			if (C0 >= 0.0f && C1 >= 0.0f && C2 >= 0.0f)
			{
				D3DXVec3Cross(&normal, &V01, &V12);
				_position.y = mpv_[nZ * MaxFiledZ + nX].position.y - (normal.x * (_position.x - mpv_[nZ * MaxFiledZ + nX].position.x) + normal.z * (_position.z - mpv_[nZ * MaxFiledZ + nX].position.z)) / normal.y;
				break;
			}
			/// <summary>
			/// �����x�N�g�������߂�
			/// </summary>
			V01 = mpv_[nZ * MaxFiledZ + nX].position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;
			V12 = mpv_[nZ * MaxFiledZ + (nX + 1)].position - mpv_[nZ * MaxFiledZ + nX].position;
			V20 = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position - mpv_[nZ * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// �ʒu�x�N�g�������߂�
			/// </summary>
			V0p = _position - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position;
			V1p = _position - mpv_[nZ * MaxFiledZ + nX].position;
			V2p = _position - mpv_[nZ * MaxFiledZ + (nX + 1)].position;

			/// <summary>
			/// ���������߂�
			/// </summary>
			C3 = V01.x * V0p.z - V01.z * V0p.x;
			C4 = V12.x * V1p.z - V12.z * V1p.x;
			C5 = V20.x * V2p.z - V20.z * V2p.x;

			/// <summary>
			/// D3DXVec3Cross() : �Փ˔���p�̖@��������, �@�����܂񂾌v�Z����,_position.y�ɕԂ�
			/// </summary>
			if (C3 <= 0.0f && C4 <= 0.0f && C5 <= 0.0f)
			{
				D3DXVec3Cross(&normal, &V01, &V12);
				_position.y = mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.y - (normal.x * (_position.x - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.x) + normal.z * (_position.z - mpv_[(nZ + 1) * MaxFiledZ + (nX + 1)].position.z)) / normal.y;
				break;
			}
		}
	}
	return _position.y;
}

//----------------------------------------------------
// EOF
//----------------------------------------------------