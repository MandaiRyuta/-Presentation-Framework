#include "fade.h"
#include "../../../Renderer/GameManager.h"
#include "../Camera.h"

void Fade::Init()
{
	FadeSet_ = 0;
	FadeIn = 255;
	FadeOut = 0;
	BlackFadeInFlag_ = false;
	BlackFadeOutFlag_ = false;
	WhiteFadeInFlag_ = false;
	WhiteFadeOutFlag_ = false;
}

void Fade::Uninit()
{
	FadeSet_ = 0;
	FadeIn = 255;
	FadeOut = 0;
	BlackFadeInFlag_ = false;
	BlackFadeOutFlag_ = false;
	WhiteFadeInFlag_ = false;
	WhiteFadeOutFlag_ = false;
}

void Fade::Draw()
{
	switch (FadeSet_)
	{
	case 0:
		BlackFadeIn();
		break;
	case 1:
		BlackFadeOut();
		break;
	case 2:
		WhiteFadeIn();
		break;
	case 3:
		WhiteFadeOut();
		break;
	}
}

void Fade::Update()
{

}

void Fade::BlackFadeIn()
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();
	//�N���b�s���O��Ԃ��傤�ǂ̃T�C�Y�ŃN�A�b�h�����΂����i�X�N���[���N�A�b�h�j
	//�����x�����ԂƋ��ɑ�������
	if (FadeIn > 0)
	{
		FadeIn-=3;
	}
	else if (FadeIn <= 0)
	{
		BlackFadeInFlag_ = true;
	}
	FADE_VERTEX vPoint[] =
	{
		{-1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeIn,0,0,0)},//���_0	  
		{1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeIn,0,0,0)},//���_1	  
		{-1.0,-1.0,0.0,D3DCOLOR_ARGB(FadeIn,0,0,0)},//���_2	
		{1.0,-1.0,0.0 , D3DCOLOR_ARGB(FadeIn,0,0,0)}, //���_3
	};

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	pDevice->SetTransform(D3DTS_WORLD, &mat);
	pDevice->SetTransform(D3DTS_VIEW, &mat);
	pDevice->SetTransform(D3DTS_PROJECTION, &mat);

	pDevice->SetTexture(0,NULL);

	//�X�N���[���N�A�b�h�`��
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(FADE_VERTEX));
}

void Fade::BlackFadeOut()
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();
	//�N���b�s���O��Ԃ��傤�ǂ̃T�C�Y�ŃN�A�b�h�����΂����i�X�N���[���N�A�b�h�j
	//�����x�����ԂƋ��ɑ�������
	if (FadeOut < 255)
	{
		FadeOut+=3;
	}
	else if (FadeOut >= 255)
	{
		BlackFadeOutFlag_ = true;
	}
	FADE_VERTEX vPoint[] =
	{
		-1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeOut,0,0,0),//���_0	  
		1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeOut,0,0,0),//���_1	  
		-1.0,-1.0,0.0,D3DCOLOR_ARGB(FadeOut,0,0,0),//���_2	
		1.0,-1.0,0.0 , D3DCOLOR_ARGB(FadeOut,0,0,0), //���_3
	};

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	pDevice->SetTransform(D3DTS_WORLD, &mat);
	pDevice->SetTransform(D3DTS_VIEW, &mat);
	pDevice->SetTransform(D3DTS_PROJECTION, &mat);
	pDevice->SetTexture(0, NULL);
	//�X�N���[���N�A�b�h�`��
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(FADE_VERTEX));
}

void Fade::WhiteFadeIn()
{
	//LPDIRECT3DDEVICE9  pDevice = GetDevice();
	////�N���b�s���O��Ԃ��傤�ǂ̃T�C�Y�ŃN�A�b�h�����΂����i�X�N���[���N�A�b�h�j
	////�����x�����ԂƋ��ɑ�������

	//if (FadeIn > 0)
	//{
	//	FadeIn-=3;
	//}
	//else if (FadeIn <= 0)
	//{
	//	WhiteFadeInFlag_ = true;
	//}
	//FADE_VERTEX vPoint[] =
	//{
	//	-1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeIn,255,255,255),//���_0	  
	//	1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeIn,255,255,255),//���_1	  
	//	-1.0,-1.0,0.0,D3DCOLOR_ARGB(FadeIn,255,255,255),//���_2	
	//	1.0,-1.0,0.0 , D3DCOLOR_ARGB(FadeIn,255,255,255), //���_3
	//};

	//D3DXMATRIX mat;
	//D3DXMatrixIdentity(&mat);
	//pDevice->SetTransform(D3DTS_WORLD, &mat);
	//pDevice->SetTransform(D3DTS_VIEW, &mat);
	//pDevice->SetTransform(D3DTS_PROJECTION, &mat);
	//pDevice->SetTexture(0, NULL);
	////�X�N���[���N�A�b�h�`��
	//pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(FADE_VERTEX));
}

void Fade::WhiteFadeOut()
{
	//LPDIRECT3DDEVICE9  pDevice = GetDevice();
	////�N���b�s���O��Ԃ��傤�ǂ̃T�C�Y�ŃN�A�b�h�����΂����i�X�N���[���N�A�b�h�j
	////�����x�����ԂƋ��ɑ�������
	//if (FadeOut < 255)
	//{
	//	FadeOut+=3;
	//}
	//else if (FadeOut >= 255)
	//{
	//	FadeIn = 255;
	//	FadeOut = 0;
	//	WhiteFadeOutFlag_ = true;
	//}
	//FADE_VERTEX vPoint[] =
	//{
	//	-1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeOut,255,255,255),//���_0	  
	//	1.0,1.0,0.0 , D3DCOLOR_ARGB(FadeOut,255,255,255),//���_1	  
	//	-1.0,-1.0,0.0,D3DCOLOR_ARGB(FadeOut,255,255,255),//���_2	
	//	1.0,-1.0,0.0 , D3DCOLOR_ARGB(FadeOut,255,255,255), //���_3
	//};

	//D3DXMATRIX mat;
	//D3DXMatrixIdentity(&mat);
	//pDevice->SetTransform(D3DTS_WORLD, &mat);
	//pDevice->SetTransform(D3DTS_VIEW, &mat);
	//pDevice->SetTransform(D3DTS_PROJECTION, &mat);
	//pDevice->SetTexture(0, NULL);
	////�X�N���[���N�A�b�h�`��
	//pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(FADE_VERTEX));
}

bool Fade::GetFadeFlag()
{
	return BlackFadeOutFlag_;
	//switch (FadeSet_)
	//{
	//case 0:
	//	return BlackFadeInFlag_;
	//	break;
	//case 1:
	//	return BlackFadeOutFlag_;
	//	break;
	//case 2:
	//	return WhiteFadeInFlag_;
	//	break;
	//case 3:
	//	return WhiteFadeOutFlag_;
	//	break;
	//}
}

void Fade::FadeSetNumber(int fade)
{
	FadeSet_ = fade;
}

Fade * Fade::Create()
{
	Fade* CreateFade = new Fade();
	CreateFade->Init();
	return CreateFade;
}