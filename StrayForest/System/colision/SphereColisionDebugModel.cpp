#include "SphereColisionDebugModel.h"
#include <xnamath.h>

constexpr int COLLISION_LINE_SMOOTH = 30;

SphereColisionDebug::SphereColisionDebug()
{	
}

SphereColisionDebug::~SphereColisionDebug()
{
	pMesh->Release();
}

void SphereColisionDebug::Draw(const D3DXVECTOR3 & pos, float radius, int type)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mat, rot, trans, scale;
	D3DXMatrixIdentity(&mat);

	D3DXCreateSphere(
		device,        // �`���̃f�o�C�X
		radius,         // ���a�B0.0f�ł�����OK�B�}�C�i�X��NG
		16,             // �X���C�X�̐��B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
		8,              // �X�^�b�N���B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
		&pMesh,         // �o�͂��郁�b�V��
		NULL            // ���܂�g��Ȃ��炵�����NULL�ɂ��Ƃ���
	);

	D3DXMatrixRotationYawPitchRoll(&rot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);

	mat = scale * rot * trans;
	if (type == 0)
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	pMesh->CloneMeshFVF(NULL, D3DFVF_XYZ, device, &pMesh);
	device->SetTransform(D3DTS_WORLD, &mat);
	device->SetTexture(0, NULL);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	pMesh->DrawSubset(0);

	if (type == 0)
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if (pMesh != nullptr)
	{
		pMesh->Release();
	}
}
