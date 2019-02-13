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
		device,        // 描画先のデバイス
		radius,         // 半径。0.0fでも実はOK。マイナスはNG
		16,             // スライスの数。増やすときれいな球になるはず
		8,              // スタック数。増やすときれいな球になるはず
		&pMesh,         // 出力するメッシュ
		NULL            // あまり使わないらしいんでNULLにしといた
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
