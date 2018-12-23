#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <unordered_map>
#if _DEBUG
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Debug/EffekseerRendererDX9.lib" )
#else
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "Effekseer/src/lib/VS2015/Release/EffekseerRendererDX9.lib" )
#endif

#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class MyEffekseer : public GameObjectManager
{
public:
	MyEffekseer(int _priority, wchar_t _filepath[]);
	~MyEffekseer();
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

public:
	static MyEffekseer* CreateMyEffect(int _priority, wchar_t _filepath[]);
public:
	void SetMovePosition(D3DXVECTOR3 _addmove);
	void SetPosition(D3DXVECTOR3 _targetposition);
	void SetScale(D3DXVECTOR3 _scale);
	void SetRotation(D3DXVECTOR3 _rotation);
	void SetWorldMatrix(Entity::EffectInfomation _location);
	void SetIsDrawing(bool _drawing);
private:
	void SetEfkWorldMatrix(D3DXMATRIX _world);
public:
	void PlayEffect();
	void StopEffect();
public:
	const D3DXVECTOR3 GetPosition();
	const D3DXVECTOR3 GetRotation();
	const D3DXMATRIX GetWorld();
	const float GetFrameCount();
public:
	void SetFrameCount(float _deltatime);
private:
	float deltaframe_;
	float FrameCount_;
	float FrameStack_;
	bool FrameSet_;
	bool IsDrawing_;
	bool PlayFlag_;
	D3DXMATRIX world_;
	Effekseer::Manager* MyEfkManager_;
	EffekseerRendererDX9::Renderer* MyEfkRenderer_;
	Effekseer::Effect*	MyEfkEffect_;
	Effekseer::Handle	MyEfkHandle_;
	Entity::EffectInfomation location_;
};