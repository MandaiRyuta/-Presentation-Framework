#include "MyEffekseer.h"
#include "../Camera.h"

MyEffekseer::MyEffekseer(int _priority, wchar_t _filepath[])
	: GameObjectManager(_priority)
	, IsDrawing_(false)
	, FrameCount_(0)
{
	MyEfkRenderer_ = EffekseerRendererDX9::Renderer::Create(GetDevice(), 100);
	MyEfkManager_ = Effekseer::Manager::Create(100,false);

	MyEfkRenderer_->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(D3DX_PI / 3, (float)windows_rect::SCREEN_WIDTH / (float)windows_rect::SCREEN_HEIGHT, 1.0f, 10000.0f)
	);

	MyEfkManager_->SetSpriteRenderer(MyEfkRenderer_->CreateSpriteRenderer());
	MyEfkManager_->SetRibbonRenderer(MyEfkRenderer_->CreateRibbonRenderer());
	MyEfkManager_->SetRingRenderer(MyEfkRenderer_->CreateRingRenderer());
	MyEfkManager_->SetTrackRenderer(MyEfkRenderer_->CreateTrackRenderer());
	MyEfkManager_->SetModelRenderer(MyEfkRenderer_->CreateModelRenderer());

	MyEfkManager_->SetTextureLoader(MyEfkRenderer_->CreateTextureLoader());
	MyEfkManager_->SetModelLoader(MyEfkRenderer_->CreateModelLoader());

	MyEfkManager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	MyEfkEffect_ = Effekseer::Effect::Create(MyEfkManager_, (const EFK_CHAR*)_filepath);
	/**/
	MyEfkManager_->SetSpeed(MyEfkHandle_, 1.0f);
	
	location_.position = D3DXVECTOR3(0.0f, 70.0f, 0.0f);
	/**/
	MyEfkManager_->SetLocation(MyEfkHandle_, Effekseer::Vector3D(location_.position.x, location_.position.y, location_.position.z));
	location_.scale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	location_.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	deltaframe_ = 1.0f;
	FrameSet_ = false;
}

MyEffekseer::~MyEffekseer()
{
}

void MyEffekseer::Init()
{
}

void MyEffekseer::Update()
{
	MyEfkRenderer_->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(
			Effekseer::Vector3D(CCamera::GetEye().x, CCamera::GetEye().y, CCamera::GetEye().z),
			Effekseer::Vector3D(CCamera::GetAt().x, CCamera::GetAt().y, CCamera::GetAt().z),
			Effekseer::Vector3D(0.0f, 1.0f, 0.0f)
		)
	);

	PlayFlag_ = MyEfkManager_->Exists(MyEfkHandle_);

	if(!PlayFlag_)
	{
		if (IsDrawing_)
		{
			PlayEffect();
		}
		else if(!IsDrawing_)
		{
			StopEffect();
		}
	}

	SetWorldMatrix(location_);
	SetEfkWorldMatrix(world_);
	MyEfkManager_->Flip();
	MyEfkManager_->Update(deltaframe_);
}

void MyEffekseer::Draw()
{
	if (IsDrawing_)
	{
		MyEfkRenderer_->BeginRendering();
		MyEfkManager_->Draw();
		MyEfkRenderer_->EndRendering();
	}
}

void MyEffekseer::Uninit()
{
	if (MyEfkManager_ != nullptr)
	{
		MyEfkManager_->StopEffect(MyEfkHandle_);
		MyEfkManager_->Destroy();
		MyEfkManager_ = nullptr;
	}
	if (MyEfkEffect_ != nullptr)
	{
		ES_SAFE_RELEASE(MyEfkEffect_);
	}
	if (MyEfkRenderer_ != nullptr)
	{
		MyEfkRenderer_->Destroy();
		MyEfkRenderer_ = nullptr;
	}
}

MyEffekseer * MyEffekseer::CreateMyEffect(int _priority, wchar_t _filepath[])
{
	MyEffekseer* CreateMyEffect = new MyEffekseer(_priority, _filepath);
	CreateMyEffect->Init();
	return CreateMyEffect;
}

void MyEffekseer::SetMovePosition(D3DXVECTOR3 _addmove)
{
	location_.position += _addmove;
}

void MyEffekseer::SetPosition(D3DXVECTOR3 _targetposition)
{
	location_.position = _targetposition;
}

void MyEffekseer::SetScale(D3DXVECTOR3 _scale)
{
	location_.scale = _scale;
}

void MyEffekseer::SetRotation(D3DXVECTOR3 _rotation)
{
	location_.rotation = _rotation;
}

void MyEffekseer::SetWorldMatrix(Entity::EffectInfomation _location)
{
	D3DXMATRIX Translation;
	D3DXMATRIX Rotation;
	D3DXMATRIX Scale;
	
	D3DXMatrixIdentity(&world_);
	D3DXMatrixIdentity(&Translation);
	D3DXMatrixIdentity(&Rotation);
	D3DXMatrixIdentity(&Scale);

	D3DXMatrixTranslation(&Translation, _location.position.x, _location.position.y, _location.position.z);
	D3DXMatrixRotationYawPitchRoll(&Rotation, _location.rotation.y, _location.rotation.x, _location.rotation.z);
	D3DXMatrixScaling(&Scale, _location.scale.x, _location.scale.y, _location.scale.z);

	world_ = Scale * Rotation * Translation;
}

void MyEffekseer::SetIsDrawing(bool _drawing)
{
	IsDrawing_ = _drawing;
}

void MyEffekseer::SetEfkWorldMatrix(D3DXMATRIX _world)
{
	Effekseer::Matrix43 EfkWorldMatrix;
	//Rotation&Scale
	EfkWorldMatrix.Value[0][0] = _world._11; EfkWorldMatrix.Value[0][1] = _world._12; EfkWorldMatrix.Value[0][2] = _world._13;
	EfkWorldMatrix.Value[1][0] = _world._21; EfkWorldMatrix.Value[1][1] = _world._22; EfkWorldMatrix.Value[1][2] = _world._23;
	EfkWorldMatrix.Value[2][0] = _world._31; EfkWorldMatrix.Value[2][1] = _world._32; EfkWorldMatrix.Value[2][2] = _world._33;
	//Position
	EfkWorldMatrix.Value[3][0] = _world._41; EfkWorldMatrix.Value[3][1] = _world._42; EfkWorldMatrix.Value[3][2] = _world._43;

	MyEfkManager_->SetMatrix(MyEfkHandle_, EfkWorldMatrix);
}

void MyEffekseer::PlayEffect()
{
	MyEfkHandle_ = MyEfkManager_->Play(MyEfkEffect_, location_.position.x, location_.position.y, location_.position.z);
	MyEfkManager_->Flip();

	PlayFlag_ = true;
}

void MyEffekseer::StopEffect()
{
	MyEfkManager_->StopEffect(MyEfkHandle_);
}

const D3DXVECTOR3 MyEffekseer::GetPosition()
{
	return location_.position;
}

const D3DXVECTOR3 MyEffekseer::GetRotation()
{
	return location_.rotation;
}

const D3DXMATRIX MyEffekseer::GetWorld()
{
	return world_;
}

const float MyEffekseer::GetFrameCount()
{
	return FrameCount_;
}

void MyEffekseer::SetFrameCount(float _deltatime)
{
	deltaframe_ = _deltatime;
}
